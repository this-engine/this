// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_GAME_APP_
#define _THIS_GAME_APP_

// Qt includes
#include <QGuiApplication>

// forward declarations
class TAssetManager;


/*!
 * \class TGameApp
 * \brief Base app for games, it has less features than a base app
 * \see TApp
 * \since 0.1-Qt
 */
class TGameApp : public QGuiApplication
{
    Q_OBJECT

public:

    TGameApp(int &argc, char **argv);

    ~TGameApp();

private:

    TAssetManager * AssetManager;
    
};

#endif // _THIS_GAME_APP_
