// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// this includes
#include "asset_manager.hpp"
#include "asset.hpp"

// Qt includes
#include <QFile>



TAssetManager::TAssetManager(QObject * parent) : QObject(parent)
{

}

QSharedPointer<TAsset> TAssetManager::loadAsset(const QFile* const file )
{   
    if(!file->exists())
    {
        return QSharedPointer<TAsset> (nullptr);
    }
    // 
    auto new_asset = new TAsset((QObject *)this);

    // add this asset to the list 
    AssetList.push_front(QSharedPointer<TAsset> (new_asset));
    return QSharedPointer<TAsset> (new_asset);
}