// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_APP_
#define _THIS_APP_

// Qt includes
#include <QApplication>

// forward declaration
class TAssetManager;

/*!
 * \class TApp
 * \brief Base app for all this applications
 * \since 0.1-Qt
 */
class TApp : public QApplication
{
    Q_OBJECT

public:
    TApp(int &argc, char **argv, int = ApplicationFlags);

    ~TApp();

private:

    TAssetManager * AssetManager;

};

#endif // _THIS_APP_

