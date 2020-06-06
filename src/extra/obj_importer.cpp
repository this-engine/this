// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "obj_importer.hpp"
#include <QFile>
#include <QVector3D>
#include <QQuaternion>

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
    QVector<unsigned int> vertex_indices;
    QVector<unsigned int> uv_indices;
    QVector<unsigned int> normal_indices;
    QVector<unsigned int> vertex_count;

    QVector<QVector3D> temp_vertices;
    QVector<QVector2D> temp_uvs;
    QVector<QVector3D> temp_normals;

    
    QStringRef line;

    const QRegExp whitespace = QRegExp("\s+"); 

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
            temp_vertices.push_back(v);
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
            temp_normals.push_back(vn);
        } else
        if (line.startsWith("f"))
        {
            int pos         = line.lastIndexOf("f");
            auto f_str      = line.right(pos).toString();
            auto f_str_val  = f_str.splitRef(whitespace);
            int count = 0;
            QStringRef f_elem;
            foreach(f_elem, f_str_val)
            {
                auto idxs = f_elem.toString().splitRef(QRegExp("/"));
                vertex_indices.push_back(idxs[0].toUInt());
                uv_indices.push_back(idxs[1].toUInt());
                normal_indices.push_back(idxs[2].toUInt());
                count ++;
            }
            vertex_count.push_back(count);
        }
    }

    // end of text parsing. 
    // let's fix vertices indexing
 
    // first let's make all faces

    struct TOBJVertex_idx
    {
        unsigned int p_idx;
        unsigned int n_idx;
        unsigned int u_idx;

        TOBJVertex_idx() = default;
        TOBJVertex_idx(unsigned int p, unsigned int n, unsigned int u) : p_idx(p), n_idx(n), u_idx(u) {}

        bool operator== (const TOBJVertex_idx& rhv) const {return rhv.p_idx == p_idx && rhv.n_idx == n_idx && rhv.u_idx == u_idx;}
    };

    QVector<TOBJVertex_idx> obj_faces_vertex;
    QVector<unsigned int> indices;
    // let's build the correct vertices indices
    for(int f_idx = 0; f_idx < vertex_indices.length(); f_idx ++ )
    {
        // obj starts at 1 instead of 0
        auto new_vertex =  TOBJVertex_idx (vertex_indices[f_idx] - 1, normal_indices[f_idx] - 1, uv_indices[f_idx] - 1 );
        if (!obj_faces_vertex.contains(new_vertex))
        {
            obj_faces_vertex.push_back(new_vertex);
            indices.push_back(obj_faces_vertex.length()-1); // add the index of the last added vertex
        }
        else
        {
            indices.push_back(obj_faces_vertex.indexOf(new_vertex)); // add the index of the vertex we encountered
        }
    }

    // let's now regroup vertices according to indices
    TOBJVertex_idx vert_idx;
    QVector<TOBJVertex> vertices;
    foreach(vert_idx, obj_faces_vertex)
    {
        auto new_vert =  TOBJVertex(
                                    temp_vertices[vert_idx.p_idx],
                                    temp_normals[vert_idx.n_idx],
                                    temp_uvs[vert_idx.u_idx]
                                    );
        // add this vertices
        vertices.push_back( new_vert );
    }

    found_data.Vertices = vertices;  
    found_data.Indices  = indices;

    return found_data;
}