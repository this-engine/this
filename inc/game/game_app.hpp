// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_GAME_APP_
#define _THIS_GAME_APP_

#include "app.hpp"

/*!
 * \class TGameApp
 * \brief Base app for games, it has less features than a base app
 * \see TApp
 * \since 0.1-Qt
 */
class TGameApp : public TApp
{
public:

    TGameApp(int &argc, char **argv) : TApp(argc, argv){}

    
};

#endif // _THIS_GAME_APP_
