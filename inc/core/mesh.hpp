// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_MESH_
#define _THIS_MESH_

#include "visual.hpp"


QT_BEGIN_NAMESPACE
class QFile;
QT_END_NAMESPACE

/*!
 * \namespace   TAttributes
 * \brief       different possible buffer attribute
 * \since       0.1-Qt
 */
namespace TAttributes
{   
    Q_NAMESPACE

    enum types 
    { 
        position,
        normal,
        uv,
        color
    };
    Q_ENUM_NS(types)
}



/*!
 * \class TMesh
 * \brief 3D mesh Data class
 * \since 0.1-Qt
 */
class TMesh : public TVisual
{
public: 

    TMesh(QObject * parent =nullptr);

    ~TMesh();

    virtual void draw() override;

    virtual void init() override;


    static void addVerticesBufferUInt(const QVector<unsigned int>& new_verts , QOpenGLBuffer* vertex_buffer);
    static void addVerticesBuffer3D(  const QVector<QVector3D>& new_verts ,    QOpenGLBuffer* vertex_buffer);
    static void addVerticesBuffer2D(  const QVector<QVector2D>& new_verts ,    QOpenGLBuffer* vertex_buffer);


    inline void addIndices( const QVector<unsigned int>& new_indices) { addVerticesBufferUInt(new_indices,      VBOidx); }
    inline void addPosAttr( const QVector<QVector3D>& new_vertpos   ) { addVerticesBuffer3D(new_vertpos,   VBOVPosAttr); }
    inline void addNormAttr(const QVector<QVector3D>& new_vertnorm  ) { addVerticesBuffer3D(new_vertnorm,  VBONormAttr); }
    inline void addUVAttr(  const QVector<QVector2D>& new_vertUV    ) { addVerticesBuffer2D(new_vertUV,    VBOTexCAttr); }


protected:

    QSharedPointer<TShader> Shader;

    // Vertex Array Object
    // data with different access patterns in different buffers
    // Buffers which will be used together are grouped using VAO to minimise the total number of calls required to set up for each draw call.
    QOpenGLVertexArrayObject* VAO;

    // Vertex indices
    QOpenGLBuffer* VBOidx;
    // Vertex positions
    QOpenGLBuffer* VBOVPosAttr;
    // Vertex normals
    QOpenGLBuffer* VBONormAttr;
    // texture coordinates (ie. UVs)
    QOpenGLBuffer* VBOTexCAttr;


    virtual QList<QOpenGLBuffer*> getBuffers() const;


private :

    int vertices_count;
    int indices_count;

    int glAttribVertexPosition;
    int glAttribVertexColor;
    int glAttribVertexNormal;


};

#endif // _THIS_MESH_