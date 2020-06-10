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
        GLUniformPointer = program->uniformLocation(PropertyName);
    }
}


void TUniform::setValue(QVariant value)
{
    
}