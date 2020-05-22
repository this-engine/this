// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_GLTF_IMPORTER_
#define _THIS_GLTF_IMPORTER_


#include <QVector> 
#include <QMatrix4x4>
#include <QList>

// Qt forward declaration
QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE


/*!
 * \class TGLTFAssetData
 * \brief container for GLTF asset data
 * \since 0.1-Qt
 */
class TGLTFAssetData
{
public:
    TGLTFAssetData(QString& generator, QString &version) : Generator(generator),Version(version){}
    QString Generator;
    QString Version;
};


/*!
 * \class TGLTFSceneData
 * \brief container for GLTF scene 
 * \since 0.1-Qt
 */
class TGLTFSceneData
{
public:
    TGLTFSceneData(QString& name,QList<int>& nodes) : Name(name),NodeIndices(nodes){}
    QString Name;
    QList<int> NodeIndices;
};

/*!
 * \class TGLTFNodeData
 * \brief container for GLTF scene 
 * \since 0.1-Qt
 * \todo  Add support to create _this_ nodes from it
 */
class TGLTFNodeData
{
public:

    TGLTFNodeData(QString& name,QList<int>& meshes) : Name(name),MeshIndices(meshes){}
    QString Name;
    QList<int> MeshIndices;
    QMatrix4x4 Transform; // contains scale, rotation and translation
};


/*!
 * \class TGLTFImportData
 * \brief container for GLTF extracted data
 * \since 0.1-Qt
 */
class TGLTFImportData
{


};


/*!
 * \class TGLTFImporter
 * \brief helper class to import gltf files
 * \since 0.1-Qt
 */
class TGLTFImporter
{
public:

    static TGLTFImportData ImportFile(QFile* File);

    static void parseMesh();
    
};

#endif // _THIS_GLTF_IMPORTER_