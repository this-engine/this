// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _THIS_SHADER_
#define _THIS_SHADER_

// Qt includes
#include <QList>
#include "asset.hpp"
#include "uniform.hpp"

// Qt forward declaration
QT_BEGIN_NAMESPACE
class QOpenGLShaderProgram;
QT_END_NAMESPACE


/*!
 * \enum TCommonUniformNames
 * \brief list of uniform the this engine is supposed to recognize and assign automagically
 *
 * \since 0.1-Qt
 */
namespace TUniformNames
{
    Q_NAMESPACE

    enum types 
    { 
        LightVec3,
        CameraMat4x4,
        WorldMat4x4,
        ProjectionMat4x4,
        CustomFloat,
        CustomVec2,
        CustomVec3,
        CustomVec4,
        CustomMat4x4
    };
    Q_ENUM_NS(types)

    static const QHash<QString, TUniformNames::types> UniformGLSLNames =
    {
    {"LightPos"   , LightVec3        },
    {"CamMatrix"  , CameraMat4x4     },
    {"WorldMatrix", WorldMat4x4      },
    {"ProjMatrix" , ProjectionMat4x4 },
    {""           , CustomFloat      },
    {""           , CustomVec2       },
    {""           , CustomVec3       },
    {""           , CustomVec4       },
    {""           , CustomMat4x4     }
    };
}

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

    TShader(const QString& vertex, const QString& fragment, QObject *parent=nullptr);

    ~TShader();

    const QOpenGLShaderProgram* getProgram() const;

    void linkProgram() const;

    void bindProgram() const;

    void releaseProgram() const;

    TUniform* findUniform(QString name) const;


protected:

    QHash<QString, TUniform*> Uniforms;

    QOpenGLShaderProgram* Program;

};

#endif //_THIS_SHADER_