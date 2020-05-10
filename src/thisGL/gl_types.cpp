// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "mesh.hpp"
#include "glad/glad.h"
#include "glm/gtc/type_ptr.hpp"
#include "gl_types.hpp"


TGLMesh::TGLMesh()
{
    glGenBuffers(2, ElementBuffers);
}

void TGLMesh::storeToBuffers(const TMesh &mesh)
{
    // TODO implement more sanity check
    if(mesh.Vertices.size()<= 3)
    {
        IsValid = false;
        return;
    }

    // buffer containing vertices
    glBindBuffer(GL_ARRAY_BUFFER, ElementBuffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.Vertices), mesh.Vertices.data(), GL_STATIC_DRAW);

    // buffer containing indices
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBuffers[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.Indices), mesh.Indices.data(), GL_STATIC_DRAW);

    IsValid = true;
}