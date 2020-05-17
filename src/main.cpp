// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "app.hpp"
#include "gl_window.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QtCore>


int main(int argc, char *argv[])
{

    TApp app(argc, argv);

    //QFileDialog::getOpenFileUrl(nullptr, QString("mesh"));

    TGLWindow glWindow;
    glWindow.showMaximized();



    return app.exec();


}

