// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_OBJ_IMPORTER_
#define _THIS_OBJ_IMPORTER_


// Qt includes
#include <QVector>
#include <QVector3D>
#include <QVector2D>
#include <QStringList>


// Qt forward declaration
QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE


/*!
 * \class TOBJVertice
 * \brief container for OBJ extracted vertex
 * \since 0.1-Qt
 */
struct TOBJVertex
{
    QVector3D Position;
    QVector3D Normal;
    QVector2D UV;

    TOBJVertex() = default;
    TOBJVertex(QVector3D position, QVector3D normal, QVector2D uv) : Position(position), Normal(normal), UV(uv) {}
};

/*!
 * \class TOBJImportData
 * \brief container for OBJ extracted data
 * \note  we have already regrouped the three arrays into one
 * \since 0.1-Qt
 */
struct TOBJImportData
{
    QList<unsigned int>  Indices;
    QList<TOBJVertex>    Vertices;
    QStringList Comments;
    QString MtlFile;
};


/*!
 * \class TGLTFImporter
 * \brief helper class to import gltf files
 * \since 0.1-Qt
 */
class TOBJImporter
{
public:

    static TOBJImportData ImportFile(QFile* file);

};

#endif // _THIS_OBJ_IMPORTER_ 