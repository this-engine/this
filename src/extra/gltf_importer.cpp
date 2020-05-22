// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "gltf_importer.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QVector3D>
#include <QQuaternion>

// parser made from https://github.com/KhronosGroup/glTF/blob/master/specification/2.0/figures/gltfOverview-2.0.0b.png


TGLTFAssetData parseAsset( const QJsonObject &json)
{
    if(!json.contains(QString("asset")))
        return TGLTFAssetData(QString(), QString());

    QJsonValue asset_value = json.value(QString("asset"));
    QJsonObject asset_item = asset_value.toObject();

    QString generator = asset_item.contains(QString("generator")) ?
                        asset_item["generator"].toString()  :
                        QString();

    QString version   = asset_item.contains(QString("version")) ?
                        asset_item["version"].toString() : 
                        QString();

    return TGLTFAssetData(generator,version);
}

QList<TGLTFSceneData> parseScene( const QJsonObject &json)
{
    // we parse all the scenes, no need to have the info of number
    if( !json.contains(QString("scenes")) )
    //  !json.contains(QString("scene"))  )
        return QList<TGLTFSceneData>();

    // this might need guarding
    //QJsonValue scene_value = json.value(QString("scene"));
    //int num = scene_value.toInt();

    // getting list of scenes
    QJsonValue scenes_value = json.value(QString("scenes"));
    QJsonArray scenes = scenes_value.toArray();

    QList<TGLTFSceneData> retval;

    QJsonValue scene;
    foreach(scene, scenes)
    {
        auto scene_obj = scene.toObject();

        QString name =  scene_obj.contains("name") ?
                        scene_obj["name"].toString() :
                        QString("default_scene");

        QJsonArray indices_array = item["nodes"].toArray();
        QList<int> indices;

        QJsonValue index;
        foreach(index, indices_array)
        {
            indices.push_back(index.toInt());
        }
        retval.push_back(TGLT(name,indices));
    }

    //if(num != retval.size())
    //{
    //    ; // TODO: implement error handling 
    //}

    return retval;
}


QList<TGLTFNodeData> parseNodes( const QJsonObject &json)
{
    QJsonValue nodes_value = json.value(QString("nodes"));
    QJsonArray nodes = nodes_value.toArray();
    QJsonValue node;
    foreach(node, nodes)
    {
        QMatrix4x4 transform;
        auto node_info = node.toObject();
        if(node_info.contains(QString("matrix")))
        {
            auto matrix_values = node_info["matrix"].toArray();
            if(matrix_values.count() == 16)
            {
                transform = QMatrix4x4( matrix_values[00].toDouble(), matrix_values[01].toDouble(), matrix_values[02].toDouble(), matrix_values[03].toDouble(),
                                        matrix_values[04].toDouble(), matrix_values[05].toDouble(), matrix_values[06].toDouble(), matrix_values[07].toDouble(),
                                        matrix_values[08].toDouble(), matrix_values[09].toDouble(), matrix_values[10].toDouble(), matrix_values[11].toDouble(),
                                        matrix_values[12].toDouble(), matrix_values[13].toDouble(), matrix_values[14].toDouble(), matrix_values[15].toDouble() );
            }
        }
        else
        {
            transform.setToIdentity();
            // T * R * S
            // order might be wrong
            if(node_info.contains(QString("scale")))
            {
                auto sc_values = node_info["scale"].toArray();
                if(sc_values.count >= 3)
                {
                    auto scale = QVector3D(sc_values[0].toDouble(), sc_values[1].toDouble(), sc_values[2].toDouble());
                    transform.scale(scale);
                }
            }
            if(node_info.contains(QString("rotation")))
            {
                auto rot_values = node_info["rotation"].toArray();
                if(rot_values.count >= 4)
                {
                    auto rotate = QQuaternion(rot_values[0].toDouble(), rot_values[1].toDouble(), rot_values[2].toDouble(), rot_values[3].toDouble());
                    transform.rotate(rotate);
                }
            }
            if(node_info.contains(QString("translation")))
            {
                auto trans_values = node_info["translation"].toArray();
                if(trans_values.count >= 3)
                {
                    auto translate = QVector3D(trans_values[0].toDouble(), trans_values[1].toDouble(), trans_values[2].toDouble());
                    transform.translate(translate);
                }
            }

        }
        if(node_info.contains(QString))
        QJsonArray mesh_ids_array = node_info["meshes"].toArray();
        QList<int> mesh_ids;
        QJsonValue idx;
        foreach(idx, mesh_ids_array)
        {
            mesh_ids.push_back(idx.toInt());
        }

        QJsonArray mesh_ids_array = node_info["meshes"].toArray();
        QList<int> mesh_ids;
        QJsonValue idx;
        foreach(idx, mesh_ids_array)
        {
            mesh_ids.push_back(idx.toInt());
        }

        
    }
    QList<TGLTFNodeData> retval;
    return retval;
}



TGLTFImportData TGLTFImporter::ImportFile(QFile* file)
{
    if(file == nullptr)
        return TGLTFImportData();

    if(!file->exists())
        return TGLTFImportData();


    QString val;
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    val = file->readAll();
    file->close();

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject main = d.object();

    auto asset = parseAsset(main);
    auto scenes = parseScene(main);

    return TGLTFImportData();
}

