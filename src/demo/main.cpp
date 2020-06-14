// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "app.hpp"
#include "gl_window.hpp"
#include "obj_importer.hpp"
#include "mesh.hpp"
#include "shader.hpp"

#include <QFileDialog>
#include <QMainWindow>
#include <QtCore>
#include <QVector3D>
#include <QColor>
#include <QVector2D>

QFile* openFile(QString path)
{
    QFile * file = new QFile(path);
    if (!file->exists())
    {
        delete file;
        file = nullptr;
        return nullptr;
    }
    return file;
}

QString openFileString(QString path)
{
    QFile * file = openFile(path);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    QString val = file->readAll();
    file->close();
    delete file;
    return val;
}

int main(int argc, char *argv[])
{

    TApp app(argc, argv);

    TGLWindow gl_window;

    // QString sh_vert  = openFileString("vertex shader");
    // QString sh_frag  = openFileString("fragment shader");

    QString sh_vert  = openFileString("res/shd/default.vert");
    QString sh_frag  = openFileString("res/shd/default.frag");
    QFile* mesh_file = openFile("res/cube.obj");
    auto   mesh_data = TOBJImporter::ImportFile(mesh_file);
    
    qDebug(" found %d vertex positions", mesh_data.Position.count());
    qDebug(" found %d indices",          mesh_data.Indices.count());

    auto add_mesh =  [&gl_window, &mesh_data, &sh_vert, &sh_frag]()
    {
        TMesh*    mesh = new TMesh((QObject *)&gl_window);
        TShader * shad = new TShader(sh_vert,sh_frag , &gl_window);

        mesh->addIndices(mesh_data.Indices);
        mesh->addPosAttr(mesh_data.Position);
        mesh->addNormAttr(mesh_data.Normal);
        mesh->addUVAttr(mesh_data.UV);
        
        mesh->setShader(shad);

        QList<TVisual*> render_list;
        render_list.push_back(mesh);

        // update list to render
        gl_window.setVisual(render_list);
    };

    
    QObject::connect(&gl_window, &TGLWindow::onGLinitialized ,add_mesh);

    gl_window.showMaximized();
    return app.exec();
}

