// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "app.hpp"
#include "gl_window.hpp"
#include "visual.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QtCore>
#include <QVector3D>
#include <QColor>
#include <QVector2D>


struct TVertex 
{
    QVector3D   Coord; 
    QVector3D   Norml;
    QVector2D   UVcrd; 
    QColor      Color;

    TVertex(QVector3D coord, QVector3D   norml, QVector2D   uvcrd, QColor  color)
    : Coord(coord), Norml(norml), UVcrd(uvcrd), Color(color){}
};


typedef struct TTriIndices { size_t idx[3]; } TTriIndices;


class TCube : public TVisual
{
    TCube(float width = 1.0f, float height = 1.0f, float depth = 1.0f);

    QVector<TVertex> Vertices;

    QVector<TTriIndices> Indices;

};



int main(int argc, char *argv[])
{

    TApp app(argc, argv);

    //QFileDialog::getOpenFileUrl(nullptr, QString("mesh"));

    TGLWindow glWindow;
    glWindow.showMaximized();



    return app.exec();


}

