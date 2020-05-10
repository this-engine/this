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

    /**
     *  storeToBuffers()
     *  @brief     generate a valid buffer with 
     */
    void storeToBuffers(const TMesh &mesh);


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
	

/**
 *  TGLRenderData
 *  @brief      struct holding strictly necessary render info
 */
struct TGLRenderData : public TRenderMatrices
{

    /**
     *  MVP_id
     *  @brief      id of the Model-View-Projection matrix (stored in @see TRenderMatrices)
     */
    GLuint MVP_id;

    /**
     *  View_id
     *  @brief      id of the View matrix (stored in @see TRenderMatrices)
     */
    GLuint View_id;

    /**
     *  Model_id
     *  @brief      id of the Model matrix (stored in @see TRenderMatrices)
     */
    GLuint Model_id;

};

#endif //_this_gl_mesh_