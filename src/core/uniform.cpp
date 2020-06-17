// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "uniform.hpp"
#include <QOpenGLShaderProgram>

const QMap<const char *,QMetaType::Type> TUniform::TypeConversionMap = 
{
    {"float", QMetaType::Float      },
    {"vec2" , QMetaType::QVector2D  },
    {"vec3" , QMetaType::QVector3D  },
    {"vec4" , QMetaType::QVector4D  },
    {"mat4" , QMetaType::QMatrix4x4 }
};


void TUniform::setUniformLocation(QOpenGLShaderProgram * program)
{
    if(program)
    {
        Program = program;
        GLUniformPointer = program->uniformLocation(PropertyName);
    }
}

void TUniform::setValue(QVariant value)
{
    if(Program)
    {
        switch (value.type())
        {
        case QMetaType::QVector2D   :
            Program->setUniformValue(GLUniformPointer, value.value<QVector2D>() );
            break;
        case QMetaType::QVector3D   :
            Program->setUniformValue(GLUniformPointer, value.value<QVector3D>() );
            break;
        case QMetaType::QMatrix4x4  :
            Program->setUniformValue(GLUniformPointer, value.value<QMatrix4x4>() );
            break;
        case QMetaType::QVector4D   :
            Program->setUniformValue(GLUniformPointer, value.value<QVector4D>() );
            break;
        default:
            break;
        }

        
    }
}