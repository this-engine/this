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
        return TGLTFAssetData();

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


        QList<int> indices;
        if(scene_obj.contains(QString("nodes")))
        {
            QJsonArray indices_array = scene_obj["nodes"].toArray();
            QJsonValue index;
            foreach(index, indices_array)
            {
            indices.push_back(index.toInt());
            }
        }
       
        retval.push_back(TGLTFSceneData(name,indices));
    }

    //if(num != retval.size())
    //{
    //    ; // TODO: implement error handling 
    //}
    return retval;
}


QList<TGLTFNodeData> parseNodes( const QJsonObject &json)
{
    if (!json.contains(QString("nodes")))
        return QList<TGLTFNodeData>();

    QList<TGLTFNodeData> retval;

    QJsonValue nodes_value = json.value(QString("nodes"));
    QJsonArray nodes = nodes_value.toArray();
    QJsonValue node;

    foreach(node, nodes)
    {
        // node data
        TGLTFNodeData node_data;
       


        auto node_info = node.toObject();
        if(node_info.contains(QString("matrix")))
        {
            auto matrix_values = node_info["matrix"].toArray();
            if(matrix_values.count() == 16)
            {
                node_data.Transform = QMatrix4x4( matrix_values[ 0].toDouble(), matrix_values[ 1].toDouble(), matrix_values[ 2].toDouble(), matrix_values[ 3].toDouble(),
                                                  matrix_values[ 4].toDouble(), matrix_values[ 5].toDouble(), matrix_values[ 6].toDouble(), matrix_values[ 7].toDouble(),
                                                  matrix_values[ 8].toDouble(), matrix_values[ 9].toDouble(), matrix_values[10].toDouble(), matrix_values[11].toDouble(),
                                                  matrix_values[12].toDouble(), matrix_values[13].toDouble(), matrix_values[14].toDouble(), matrix_values[15].toDouble() );
            }
        }
        else
        {
             node_data.Transform.setToIdentity();
            // T * R * S
            // order might be wrong
            if(node_info.contains(QString("scale")))
            {
                auto sc_values = node_info["scale"].toArray();
                if(sc_values.count() >= 3)
                {
                    auto scale = QVector3D(sc_values[0].toDouble(), sc_values[1].toDouble(), sc_values[2].toDouble());
                     node_data.Transform.scale(scale);
                }
            }
            if(node_info.contains(QString("rotation")))
            {
                auto rot_values = node_info["rotation"].toArray();
                if(rot_values.count() >= 4)
                {
                    auto rotate = QQuaternion(rot_values[0].toDouble(), rot_values[1].toDouble(), rot_values[2].toDouble(), rot_values[3].toDouble());
                     node_data.Transform.rotate(rotate);
                }
            }
            if(node_info.contains(QString("translation")))
            {
                auto trans_values = node_info["translation"].toArray();
                if(trans_values.count() >= 3)
                {
                    auto translate = QVector3D(trans_values[0].toDouble(), trans_values[1].toDouble(), trans_values[2].toDouble());
                     node_data.Transform.translate(translate);
                }
            }


        }

        // Meshes indices
        if(node_info.contains(QString("meshes")))
        {
            QJsonArray mesh_ids_array = node_info["meshes"].toArray();
            QJsonValue idx;
            foreach(idx, mesh_ids_array)
            {
                node_data.MeshIndices.push_back(idx.toInt());
            }
        }

        if(node_info.contains(QString("camera")))
        {
            QJsonArray mesh_ids_array = node_info["camera"].toArray();
            QJsonValue idx;
            foreach(idx, mesh_ids_array)
            {
                node_data.CameraIndices.push_back(idx.toInt());
            }
        } 

        retval.push_back(node_data);    
    }

    return retval;
}


QList<TGLTFMeshData> parseMeshes(const QJsonObject &json)
{
    QList<TGLTFMeshData> retval;

    if(!json.contains(QString("meshes"))) // || json.contains(QString("buffer")))
        return retval;
        
    QJsonValue meshes_value = json.value(QString("meshes"));
    QJsonArray meshes = meshes_value.toArray();

    //
    // first we try to get buffers bufferviews and accessors
    //
    // first buffers :
    if(!json.contains(QString("buffers")))
        return retval;
    // we have at least one buffer
    QVector<QByteArray> Buffers;
    {
        auto buffers_array = json.value(QString("accessors")).toArray();
        QJsonValue buffer_value;
        foreach(buffer_value, buffers_array)
        {
            auto buffer_obj = buffer_value.toObject();
            auto URI = buffer_obj.value(QString("uri")).toString();

            if(URI.startsWith("data:", Qt::CaseInsensitive))
            {
                // we have a buffer written there, something like :
                /*
                    "uri" : "data:application/gltf-buffer;base64,AAAIAAcAAAABAAgAAQAJAAgAAQACAAkAAgAKAAkAAgADAAoAAwALAAoAAwAEAAsABAAMAAsABAAFAAwABQANAAwABQAGAA0AAAAAAAAAAAAAAAAAAACAPwAAAAAAAAAAAAAAQAAAAAAAAAAAAABAQAAAAAAAAAAAAACAQAAAAAAAAAAAAACgQAAAAAAAAAAAAADAQAAAAAAAAAAAAAAAAAAAgD8AAAAAAACAPwAAgD8AAAAAAAAAQAAAgD8AAAAAAABAQAAAgD8AAAAAAACAQAAAgD8AAAAAAACgQAAAgD8AAAAAAADAQAAAgD8AAAAACAAKAAwAAAAAAIA/AAAAQAAAAAAAAEBAAABAQAAAAAAAAKBAAACAQAAAAAA=",
                */
            }
            else
            {
                // we need to read a separate file:   
                QFile data_file(URI);
                if (!data_file.open(QIODevice::ReadOnly)) continue;
                QByteArray blob = data_file.readAll();
                data_file.close();
                Buffers.push_back(blob);
            }
            
        }
    }


    // lastly accessors :  
    QVector<QVariantList> buffers_data;
    QVariant t;
    t.type();
    // accessors
    if(!json.contains(QString("accessors")))
        return retval;

    // we have at least one accessor
    {
        auto accessors_array = json.value(QString("accessors")).toArray();
                    QJsonValue accessor_value;
                    foreach(accessor_value,accessors_array )
                    {
                        auto accessor_object = accessor_value.toObject();
                        if( ! accessor_object.contains(QString("bufferView")) ||
                            ! accessor_object.contains(QString("type")) ||
                            ! accessor_object.contains(QString("componentType")))
                            continue;

                        if(accessor_object["type"].toString() == QString("SCALAR"))
                        {
                            
                        }
                        
                    }
    }



    QJsonValue mesh;
    foreach(mesh, meshes)
    {
        TGLTFMeshData mesh_data; 
        auto mesh_info = mesh.toObject(); 
        // mesh has no inner value else than "primitives" 
        
        mesh_data.MeshName = mesh_info.contains(QString("name")) ? mesh_info.value(QString("name")).toString() : QString("unnamed_mesh");

        if(mesh_info.contains(QString("primitives")))
        {
            auto primitives = mesh_info["primitives"].toObject();
            QJsonValue primitive;
            foreach(primitive,primitives)
            {
                // different attributes stored in different accessors
                int pos      ;
                int norm     ;
                int texcoord0;

                // let's get the attributes
                auto primitive_obj = primitive.toObject();
                if(primitive_obj.contains(QString("attributes")))
                {
                    pos       = primitive_obj.value(QString("POSITION")).toInt(-1);
                    norm      = primitive_obj.value(QString("NORMAL")).toInt(-1);
                    texcoord0 = primitive_obj.value(QString("TEXCOORD_0")).toInt(-1);
                }



            }
        }

        retval.push_back(mesh_data);
    }


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

