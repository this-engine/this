   
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
    ValidShader = false;
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

    for (auto itr : getBuffers())
        if(itr)
            itr->release();


    // auto set shader to check it's valid.
    setShader(Shader);
    
} 

void TMesh::draw()
{
    if(!ValidShader)
        return;
    QOpenGLFunctions *glfunc = QOpenGLContext::currentContext()->functions();
    QOpenGLVertexArrayObject::Binder vaoBinder(VAO);

    Shader->bindProgram();
    for (auto buffer : getBuffers())
    {
        buffer->bind();
    }

    //program->setUniformValue(m_projMatrixLoc, m_proj);
    //program->setUniformValue(m_mvMatrixLoc, m_camera * m_world);

    //QMatrix3x3 normalMatrix = m_world.normalMatrix();

    //program->setUniformValue(m_normalMatrixLoc, normalMatrix);

    // Draw the triangles !
	glfunc->glDrawElements(GL_TRIANGLES, indices_count, GL_UNSIGNED_SHORT, (void*)0 );

    for (auto buffer : getBuffers())
    {
        buffer->release();
    }
    Shader->releaseProgram();


}
 
 void TMesh::setShader(TShader * new_shader)
 {
    Shader = new_shader;
    if(Shader != nullptr)
    {
        if(Shader->getProgram())
        {
            ValidShader = true;
        }
    }
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