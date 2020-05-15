// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_ASSET_MANAGER_
#define _THIS_ASSET_MANAGER_

// Qt includes
#include <QObject>
#include <QSharedPointer>

//forward declaration
class TAsset;


QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE


/*!
 * \class TAssetManager
 * \brief Class responsible for loading and unloading assets
 * \since 0.1-Qt
 */
class TAssetManager : public QObject
{
    Q_OBJECT

public:
    TAssetManager(QObject * parent = nullptr);

    /*!
     *  \fn QSharedPointer<TAsset> TAssetManager::loadAsset(const QFile* const file )
     * 
     *  \brief tries to load an asset synchronously
     */
    QSharedPointer<TAsset> loadAsset(const QFile* const file );


private:

    QList<QSharedPointer<TAsset>> AssetList; 
    
};


#endif // _THIS_ASSET_MANAGER_