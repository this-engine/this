// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "app.hpp"
#include "gl_window.hpp"
#include "obj_importer.hpp"
#include "mesh.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QtCore>
#include <QVector3D>
#include <QColor>
#include <QVector2D>



int main(int argc, char *argv[])
{

    TApp app(argc, argv);
    
    QFile* mesh_file = nullptr;

    while(mesh_file == nullptr)
    {
        auto file_url = QFileDialog::getOpenFileUrl(nullptr, QString("mesh to render"));
        auto path = file_url.toLocalFile();
        mesh_file = new QFile(path);

        if (!mesh_file->exists())
        {
            delete mesh_file;
            mesh_file = nullptr;
        }
    }

    auto mesh_data = TOBJImporter::ImportFile(mesh_file);

    qDebug(" found %d vertex positions", mesh_data.Position.count());
    qDebug(" found %d indices", mesh_data.Indices.count());

    TGLWindow glWindow;

    TMesh* mesh = new TMesh((QObject *)&glWindow);


    mesh->addIndices(mesh_data.Indices);
    mesh->addPosAttr(mesh_data.Position);
    mesh->addNormAttr(mesh_data.Normal);
    mesh->addUVAttr(mesh_data.UV);

    QList<TVisual*> render_list;
    render_list.push_back(mesh);
    glWindow.SetVisual(render_list);

    glWindow.showMaximized();

    return app.exec();
}

