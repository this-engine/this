// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_ASSET_
#define _THIS_ASSET_

// Qt includes
#include <QObject>
#include <QByteArray>

/*!
 * \class TApp
 * \brief Base app for all this applications
 * \since 0.1-Qt
 */
class TAsset : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QByteArray Data READ data WRITE setData NOTIFY dataUpdate)

public:

    TAsset(QObject *parent = nullptr);

    inline QByteArray data() const {return Data;}

    inline void setData(QByteArray value) {Data = value;}

private:

    // actual data stored as 
    QByteArray Data;


signals:

    void dataUpdate();


};

#endif // _THIS_ASSET_