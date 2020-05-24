   
// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// this includes
#include "mesh.hpp"
#include "shader.hpp"


// Qt includes
#include <QOpenGLVertexArrayObject>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>


TMesh::TMesh(QObject * parent) : TVisual(parent), vao(new QOpenGLVertexArrayObject), vbo(new QOpenGLBuffer)
{

}

TMesh::~TMesh()
{
        delete vao;
        vao = 0;

        delete vbo;
        vbo = 0;
}


void TMesh::init()
{
   QOpenGLFunctions *glfunc = QOpenGLContext::currentContext()->functions();

    if(Shader)
        Shader->linkProgram();
    
    if (vao->create())
        vao->bind();


    if(Shader)
        Shader->bindProgram();

    vbo->create();
    vbo->bind();

    // vbo->allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));
        int glAttribVertexPosition;
    int glAttribVertexColor;
    int glAttribVertexNormal;
    glfunc->glEnableVertexAttribArray(0);
    glfunc->glEnableVertexAttribArray(1);
    glfunc->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glfunc->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    vbo->release();
}   
 