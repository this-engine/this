// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_VISUAL_
#define _THIS_VISUAL_

// Qt includes
#include <QObject> 
#include <QVector>
#include "uniform.hpp"

// Qt forward declaration
QT_BEGIN_NAMESPACE
class QOpenGLTexture;
class QOpenGLShaderProgram;
class QOpenGLBuffer;
class QOpenGLVertexArrayObject;
QT_END_NAMESPACE

// forward declarations
class TShader;

/*!
 * \class TVisual
 * \brief abstract class for objects that needs to be renderer
 * 
 * 
 * \since 0.1-Qt
 */
class TVisual : public QObject
{
    Q_OBJECT

public:

    TVisual(QObject * parent =nullptr);

    void Draw();

protected:

    TShader* Shaders;

    QList<TUniform> Uniforms;

    QOpenGLBuffer* vbo;

    QOpenGLVertexArrayObject* vao;


};

#endif // _THIS_VISUAL_
