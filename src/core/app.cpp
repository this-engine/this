// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "app.hpp"
#include "asset_manager.hpp"
#include <QSurfaceFormat>
#include <QOpenGLContext>

TApp::TApp(int &argc, char **argv, int appflag) : QApplication(argc,argv , appflag)
{
    AssetManager = new TAssetManager(this);
}


TApp::~TApp()
{
    delete AssetManager;
}