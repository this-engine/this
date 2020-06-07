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


    void addIndices(const QVector<unsigned int>& new_indices);

    void addVerticesBuffer3D(const QVector<QVector3D>& new_verts );

    void addVerticesBuffer2D(const QVector<QVector2D>& new_verts );

protected:

    QSharedPointer<TShader> Shader;

    QOpenGLVertexArrayObject* vao;

    QOpenGLBuffer* vbo;

private :

    int vertices_count;
    int indices_count;

    int glAttribVertexPosition;
    int glAttribVertexColor;
    int glAttribVertexNormal;


};

#endif // _THIS_MESH_