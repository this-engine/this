// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#include "gl_window.hpp"
#include "camera.hpp"
#include <QOpenGLContext>
#include <QOpenGLFunctions>
#include <QOpenGLExtraFunctions>

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
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

#if 0
    if (m_program) {
        delete m_program;
        m_program = 0;
    }
    m_program = new QOpenGLShaderProgram;
    // Prepend the correct version directive to the sources. The rest is the
    // same, thanks to the common GLSL syntax.
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, versionedShaderCode(vertexShaderSource));
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, versionedShaderCode(fragmentShaderSource));
    m_program->link();

    m_projMatrixLoc = m_program->uniformLocation("projMatrix");
    m_camMatrixLoc = m_program->uniformLocation("camMatrix");
    m_worldMatrixLoc = m_program->uniformLocation("worldMatrix");
    m_myMatrixLoc = m_program->uniformLocation("myMatrix");
    m_lightPosLoc = m_program->uniformLocation("lightPos");

    // Create a VAO. Not strictly required for ES 3, but it is for plain OpenGL.
    if (m_vao) {
        delete m_vao;
        m_vao = 0;
    }
    m_vao = new QOpenGLVertexArrayObject;
    if (m_vao->create())
        m_vao->bind();

    if (m_vbo) {
        delete m_vbo;
        m_vbo = 0;
    }
    m_program->bind();
    m_vbo = new QOpenGLBuffer;
    m_vbo->create();
    m_vbo->bind();
    m_vbo->allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat),
                             reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vbo->release();

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);

#endif
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

void TGLWindow::paintGL()
{
    
    // Now use QOpenGLExtraFunctions instead of QOpenGLFunctions as we want to
    // do more than what GL(ES) 2.0 offers.
    QOpenGLExtraFunctions *f = QOpenGLContext::currentContext()->extraFunctions();

    f->glClearColor(0, 0, 0, 1);
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    // Now call a function introduced in OpenGL 3.1 / OpenGL ES 3.0. We
    // requested a 3.3 or ES 3.0 context, so we know this will work.
    //f->glDrawArraysInstanced(GL_TRIANGLES, 0, m_logo.vertexCount(), 32 * 36);
}

