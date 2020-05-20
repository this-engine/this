// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "gltf_importer.hpp"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

// parser made from https://github.com/KhronosGroup/glTF/blob/master/specification/2.0/figures/gltfOverview-2.0.0b.png


TGLTFAssetData parseAsset( const QJsonObject &json)
{
    QJsonValue asset_value = json.value(QString("asset"));
    QJsonObject asset_item = asset_value.toObject();
    QString generator = asset_item["generator"].toString();
    QString version   = asset_item["version"].toString();
    return TGLTFAssetData(generator,version);
}

QList<TGLTFSceneData> parseScene( const QJsonObject &json)
{
    QJsonValue scene_value = json.value(QString("scene"));
    int num = scene_value.toInt();

    QJsonValue scenes_value = json.value(QString("scenes"));
    QJsonArray scenes = scenes_value.toArray();

    QList<TGLTFSceneData> retval;

    QJsonValue scene;
    foreach(scene, scenes)
    {
        auto item = scene.toObject();
        QString name = item["name"].toString();
        QJsonArray indices_array = item["nodes"].toArray();
        QList<int> indices;
        QJsonValue index;
        foreach(index, indices_array)
        {
            indices.push_back(index.toInt());
        }
        retval.push_back(TGLTFSceneData(name,indices));
    }
    if(num != retval.size())
    {
        ;
    }

    return retval;
}


QList<TGLTFNodeData> parseNode( const QJsonObject &json)
{
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

    //QJsonObject item = value.toObject();

    /* in case of string value get value and convert into string*/
    //qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    //QJsonValue subobj = item["description"];
    //qWarning() << subobj.toString();

    /* in case of array get array and convert into string*/
    //qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    //QJsonArray test = item["imp"].toArray();
    //qWarning() << test[1].toString();

    return TGLTFImportData();
}

