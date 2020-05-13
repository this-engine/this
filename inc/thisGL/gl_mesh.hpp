 // Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_mesh_
#define _this_gl_mesh_
 
#include "core.hpp"
  
// avoid including glad just for this type
typedef unsigned int	GLuint;

// forward declaration
class TMesh;

/**
 *  TGLMesh
 *  @brief      class converting a mesh into a buffer
 */
struct TGLMesh 
{
public:


    TGLMesh();


    TGLMesh(const TMesh& mesh);

    /**
     *  storeToBuffers()
     *  @brief     generate a valid buffer with 
     */
    void storeToBuffers(const TMesh& mesh);


    /**
     *  vertexBuffer()
     *  @brief     get the GL "pointer" to the buffer containing vertices
     */
    GLuint vertexBuffer() const {return ElementBuffers[0];}
    
    
    /**
     *  indexBuffer()
     *  @brief     get the GL "pointer" to the buffer containing indices
     */
    GLuint indexBuffer()  const {return ElementBuffers[1];}

private:

    /**
     *  ElementBuffers
     *  @brief     vertex and indice buffers
     */
    GLuint ElementBuffers[2];

    /**
     *  IsValid
     *  @brief     whether we pushed to buffer or not
     */
    bool IsValid = false;

};
	
#endif //_this_gl_mesh_