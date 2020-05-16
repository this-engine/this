// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "game_app.hpp"
#include "asset_manager.hpp"

TGameApp::TGameApp(int &argc, char **argv) : QGuiApplication(argc,argv )
{
    AssetManager = new TAssetManager(this);
}


TGameApp::~TGameApp()
{
    delete AssetManager;
}