// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "obj_importer.hpp"
#include <QFile>
#include <QVector3D>
#include <QQuaternion>

// std tuples
#include <tuple>

// enable hashing of tuples of ints
namespace std
{
    inline uint qHash(const std::tuple<int, int, int>& key, uint seed = 0)
    {
        return ::qHashBits(&key, sizeof(int) * 3, seed);
    }
}
// hashing include
#include <QHash>


TOBJImportData TOBJImporter::ImportFile(QFile* file)
{
    TOBJImportData found_data;

    if(file == nullptr)
        return found_data;

    if(!file->exists())
        return found_data;


    QString content;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    content = file->readAll();
    file->close();

    // lets make that an array of reference of strings (we're not editing, but memory usage can soon be huge if we store too much)
    QVector<QStringRef> lines = content.splitRef(QRegExp("\n+"), Qt::SkipEmptyParts);

    // vertices indexes

    QList<QVector3D> temp_pos;
    QList<QVector2D> temp_uvs;
    QList<QVector3D> temp_nor;

    // final data
    QList<TOBJVertex>   vertices;
    QList<unsigned int> indices;

    QHash<std::tuple<int, int, int>,unsigned int> faces_vertices_table;
    
    QStringRef line;

    const QRegExp whitespace = QRegExp("\\s+"); 

    foreach(line, lines)
    {
        if (line.startsWith("#"))
        {
            int pos = line.lastIndexOf("#");
            found_data.Comments.push_back(line.right(pos).toString());
        }else 
        if (line.startsWith("mtllib"))
        {
            int pos = line.lastIndexOf("mtllib");
            found_data.MtlFile = line.right(pos).toString();
        }else 
        if (line.startsWith("usemtl"))
        {
            ;// we do not implement this yet 
        } else
        if (line.startsWith("s"))
        {
            ;// we do not implement this yet 
        } else
        if (line.startsWith("v"))
        {
            int pos        = line.lastIndexOf("v");
            auto v_str     = line.right(pos).toString();
            auto v_str_val = v_str.splitRef(whitespace);
            QVector3D v    = {  v_str_val[0].toFloat(),
                                v_str_val[1].toFloat(),
                                v_str_val[2].toFloat()};
            temp_pos.push_back(v);
        } else
        if (line.startsWith("vt"))
        {
            int pos         = line.lastIndexOf("vt");
            auto vt_str     = line.right(pos).toString();
            auto vt_str_val = vt_str.splitRef(whitespace);
            QVector2D vt    = { vt_str_val[0].toFloat(),
                                vt_str_val[1].toFloat()};
            temp_uvs.push_back(vt );
        } else
        if (line.startsWith("vn"))
        {
            int pos         = line.lastIndexOf("vn");
            auto vn_str     = line.right(pos).toString();
            auto vn_str_val = vn_str.splitRef(whitespace);
            QVector3D vn    = { vn_str_val[0].toFloat(),
                                vn_str_val[1].toFloat(),
                                vn_str_val[2].toFloat()};
            temp_nor.push_back(vn);
        } else
        if (line.startsWith("f"))
        {
            int pos         = line.lastIndexOf("f");
            auto f_str      = line.right(pos).toString();
            auto f_str_val  = f_str.splitRef(whitespace);
            QStringRef f_elem;
            foreach(f_elem, f_str_val)
            {
                
                auto idxs = f_elem.toString().splitRef(QRegExp("/"));
            
                bool p_ok;
                auto p = idxs[0].toUInt(&p_ok);
                bool n_ok;
                auto n = idxs[1].toUInt(&n_ok);
                bool v_ok;
                auto v = idxs[2].toUInt(&v_ok);

                std::tuple<int, int , int> value = {p_ok ?  p : 0, n_ok ?  n : 0, v_ok ?  v : 0};

                auto it = faces_vertices_table.find(value);
                unsigned int vertex_index = 0;
                if (it == faces_vertices_table.end())
                {
                    QVector3D pos = p_ok ?  temp_pos[p] : QVector3D();
                    QVector3D nor = n_ok ?  temp_nor[n] : QVector3D();
                    QVector2D uv  = v_ok ?  temp_uvs[v] : QVector2D();

                    vertex_index = faces_vertices_table.size();
                    faces_vertices_table.insert(value, vertex_index);
                    vertices.push_back(TOBJVertex(pos, nor, uv));
                } 
                else 
                {
                    vertex_index = it.value();
                }

            }
        }
    }

    // assigning to our return value
    found_data.Vertices = vertices;  
    found_data.Indices  = indices;

    return found_data;
}