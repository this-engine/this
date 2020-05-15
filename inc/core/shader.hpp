// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_CAMERA_
#define _THIS_CAMERA_

// Qt includes
#include <QByteArray> //TODO: is the minimal include ?
#include "asset.hpp"

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
class TShader : public TAsset
{
public:

    TShader();

protected:

    QOpenGLShaderProgram* program;

public:

   /*!
    * \fn static QByteArray TShader::versionedShaderCode(const char *src)
    * 
    * Appends the version of the the OpenGL to use with the shader
    * 
    * \note  could be left alone in the cpp
    * \since 0.1-Qt
    */
    static QByteArray versionedShaderCode(const char *src);

};

#endif //_THIS_CAMERA_