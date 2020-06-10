   
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
#include <QVector2D>
#include <QVector3D>

TMesh::TMesh(QObject * parent) : TVisual(parent),
                                 VAO(new QOpenGLVertexArrayObject),
                                 VBOidx      (new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer)),
                                 VBOVPosAttr (new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                 VBONormAttr (new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer)),
                                 VBOTexCAttr (new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer))
{
    vertices_count = 0;
    indices_count  = 0;
}

TMesh::~TMesh()
{
 delete VAO;
 VAO = 0;

 delete VBOidx;
 VBOidx      = 0;

 delete VBOVPosAttr;
 VBOVPosAttr = 0;

 delete VBONormAttr;
 VBONormAttr = 0;

 delete VBOTexCAttr;
 VBOTexCAttr = 0;
}


void TMesh::init()
{
   QOpenGLFunctions *glfunc = QOpenGLContext::currentContext()->functions();

    if(Shader)
        Shader->linkProgram();
    
    if (VAO->create())
        VAO->bind();


    if(Shader)
        Shader->bindProgram();

    
    for (auto itr : getBuffers())
        if(itr)
        {
            itr->create();
            itr->bind();
        }
   

    // vbo->allocate(m_logo.constData(), m_logo.count() * sizeof(GLfloat));
    int glAttribVertexPosition;
    int glAttribVertexColor;
    int glAttribVertexNormal;
    glfunc->glEnableVertexAttribArray(0);
    glfunc->glEnableVertexAttribArray(1);
    glfunc->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), 0);
    glfunc->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));

    for (auto itr : getBuffers())
        if(itr)
            itr->release();
} 

void TMesh::draw()
{
    
}
 


void TMesh::addVerticesBufferUInt(const QVector<unsigned int>& new_indices , QOpenGLBuffer* vertex_buffer)
{
    if(!vertex_buffer)
        return;

    vertex_buffer->bind();
    vertex_buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertex_buffer->write(0,new_indices.data(),new_indices.size() * sizeof(unsigned int));
    vertex_buffer->release();
}


void TMesh::addVerticesBuffer3D(const QVector<QVector3D>& new_verts , QOpenGLBuffer* vertex_buffer)
{
    if(!vertex_buffer)
        return;

    vertex_buffer->bind();
    vertex_buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    // not sure about this, at all
    vertex_buffer->write(0,new_verts.data(), new_verts.size() * sizeof(QVector3D));
    vertex_buffer->release();
}


void TMesh::addVerticesBuffer2D(const QVector<QVector2D>& new_verts , QOpenGLBuffer* vertex_buffer)
{
    if(!vertex_buffer)
        return;

    vertex_buffer->bind();
    vertex_buffer->setUsagePattern(QOpenGLBuffer::StaticDraw);
    vertex_buffer->write(0,new_verts.data(), new_verts.size() * sizeof(QVector2D));
    vertex_buffer->release();
}


QList<QOpenGLBuffer*> TMesh::getBuffers() const
{
    return { VBOidx, VBOVPosAttr, VBONormAttr, VBOTexCAttr };
}