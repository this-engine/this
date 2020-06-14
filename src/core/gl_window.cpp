// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// this includes
#include "gl_window.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "visual.hpp"


// Qt includes
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

// std includes
#include <iostream>

TGLWindow::TGLWindow() 
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

    makeCurrent();

    emit onGLcontextReady();

    //
    // Init window specific
    // might need to move to GameWindow
    Camera = new TCamera(this);

    QObject::connect(Camera, &TCamera::cameraChanged, this, &TGLWindow::updateGL);

    // resolution callback
    QObject::connect(this, &TGLWindow::widthChanged,  Camera, &TCamera::onResolutionXChanged);
    QObject::connect(this, &TGLWindow::heightChanged, Camera, &TCamera::onResolutionYChanged);
}

TGLWindow::~TGLWindow()
{
    makeCurrent();
    delete Camera;
}
  

void TGLWindow::initializeGL()
{
    QOpenGLWindow::initializeGL();
    QOpenGLFunctions *glfunc = QOpenGLContext::currentContext()->functions();

    for (auto draw_object : RenderObjects.values())
    {
        if(draw_object)
        {
            draw_object->init();
            auto shader = draw_object->getShader();
            if (shader)
            {
                auto w = shader->findUniform("worldMatrix");
                auto c = shader->findUniform("camMatrix");
                auto p = shader->findUniform("projMatrix");
                auto m = shader->findUniform("myMatrix");
            }
        }
            
    }

    glfunc->glEnable(GL_DEPTH_TEST);
    glfunc->glEnable(GL_CULL_FACE);

    emit onGLinitialized();
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

void TGLWindow::setVisual(QList<TVisual*> render_objects)
{
    QList<TVisual*> new_items;

    // find differences 
    for (auto new_visual : render_objects)
    {
        auto itr = RenderObjects.find(new_visual->objectName());
        if(itr == RenderObjects.end())
        {
            RenderObjects.insert(new_visual->objectName(), new_visual);
            new_items.push_back(new_visual);
        }
            
    }

    // init those new objects
    for(TVisual* visual : new_items)
    {
        if(visual)
        {
            qDebug() << "init render object" << visual->objectName();
            visual->init();
        }
    }
    
}

void TGLWindow::paintGL()
{
    
    // Now use QOpenGLExtraFunctions instead of QOpenGLFunctions as we want to
    // do more than what GL(ES) 2.0 offers.
    QOpenGLExtraFunctions *glfunc = QOpenGLContext::currentContext()->extraFunctions();

    glfunc->glClearColor(0, 1, 0, 1);

    glfunc->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glfunc->glEnable(GL_DEPTH_TEST);
    glfunc->glEnable(GL_CULL_FACE);

    // draw all visual object straight in one pass
    
    for (auto draw_object : RenderObjects.values())
    {
        if(draw_object)
            draw_object->draw();
    }

    // Now call a function introduced in OpenGL 3.1 / OpenGL ES 3.0. We
    // requested a 3.3 or ES 3.0 context, so we know this will work.
    //f->glDrawArraysInstanced(GL_TRIANGLES, 0, m_logo.vertexCount(), 32 * 36);
}

