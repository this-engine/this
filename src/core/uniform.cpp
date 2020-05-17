// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "uniform.hpp"


const QMap<const char *,QMetaType::Type> TUniform::TypeConversionMap = 
{
    {"float", QMetaType::Float      },
    {"vec2" , QMetaType::QVector2D  },
    {"vec3" , QMetaType::QVector3D  },
    {"vec4" , QMetaType::QVector4D  },
    {"mat4" , QMetaType::QMatrix4x4 }
};

const QMap<const char *, TUniform::TypesEnum> TUniform::PropertiesGLSLNames =
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