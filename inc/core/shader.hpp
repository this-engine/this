// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_CAMERA_
#define _THIS_CAMERA_

// Qt includes
#include <QList>
#include "asset.hpp"
#include "uniform.hpp"

// Qt forward declaration
QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE


/*!
 * \class TShader
 * \brief class to handle shaders programs and uniforms
 * 
 * Contains pointers to the shader in memory
 * 
 * \since 0.1-Qt
 */
class TShader: public QObject
{
    Q_OBJECT

public:

    TShader(const QString& vertex, const QString& fragment);

    ~TShader();

    const QOpenGLShaderProgram* getProgram() const;

    void linkProgram() const;

    void bindProgram() const;

protected:

    void setProgramLocations(TUniform::TypesEnum type, QString custom_name);

    QOpenGLShaderProgram* program;

    QList<TUniform*> Uniforms;

};

#endif //_THIS_CAMERA_