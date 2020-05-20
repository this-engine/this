// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// this includes
#include "gl_window.hpp"
#include "camera.hpp"
#include "visual.hpp"

// Qt includes
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

// std includes
#include <iostream>

TGLWindow::TGLWindow(QWindow* parent) : QOpenGLWindow(NoPartialUpdate, parent)
{
    //
    //  init GL 
    //
    QSurfaceFormat fmt;
    fmt.setDepthBufferSize(24);
    // Request OpenGL 3.3 core or OpenGL ES 3.0.
    if (QOpenGLContext::openGLModuleType() == QOpenGLContext::LibGL) {
        qDebug("Requesting 3.3 core context");
        fmt.setVersion(3, 3);
        fmt.setProfile(QSurfaceFormat::CoreProfile);
    } else {
        qDebug("Requesting 3.0 context");
        fmt.setVersion(3, 0);
    }
    QSurfaceFormat::setDefaultFormat(fmt);

    //
    // Init window specific
    // might need to move to GameWindow
    Camera = new TCamera(this);
    QObject::connect(Camera, &TCamera::cameraChanged, this, &TGLWindow::updateGL);
}

TGLWindow::~TGLWindow()
{
    makeCurrent();
    delete Camera;
}

   

void TGLWindow::initializeGL()
{
    QOpenGLFunctions *glfunc = QOpenGLContext::currentContext()->functions();

    TVisual* visual;
    foreach(visual, RenderObjects)
    {
        if(visual)
        {
            std::cout << visual->objectName().constData() << std::endl;
            visual->Init();
        }
    }
    
    glfunc->glEnable(GL_DEPTH_TEST);
    glfunc->glEnable(GL_CULL_FACE);

}

void TGLWindow::resizeGL(int w, int h)
{

}


void TGLWindow::updateGL()
{
    #if 0
    m_program->setUniformValue(m_projMatrixLoc, m_proj);
    m_program->setUniformValue(m_camMatrixLoc, camera);
    QMatrix4x4 wm = m_world;
    wm.rotate(m_r, 1, 1, 0);
    m_program->setUniformValue(m_worldMatrixLoc, wm);
    QMatrix4x4 mm;
    mm.setToIdentity();
    mm.rotate(-m_r2, 1, 0, 0);
    m_program->setUniformValue(m_myMatrixLoc, mm);
    m_program->setUniformValue(m_lightPosLoc, QVector3D(0, 0, 70));
    #endif

    
}

void TGLWindow::SetVisual(QList<TVisual*> render_objects)
{
    RenderObjects = render_objects;
    // maybe invalidate the scene...
}

void TGLWindow::paintGL()
{
    
    // Now use QOpenGLExtraFunctions instead of QOpenGLFunctions as we want to
    // do more than what GL(ES) 2.0 offers.
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    f->glClearColor(0, 0, 0, 1);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw all visual object straight in one pass
    TVisual * draw_object;
    foreach(draw_object, RenderObjects)
    {
        if(draw_object)
            draw_object->draw();
    }

    // Now call a function introduced in OpenGL 3.1 / OpenGL ES 3.0. We
    // requested a 3.3 or ES 3.0 context, so we know this will work.
    //f->glDrawArraysInstanced(GL_TRIANGLES, 0, m_logo.vertexCount(), 32 * 36);
}

