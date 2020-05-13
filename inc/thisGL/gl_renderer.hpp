// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_renderer_
#define _this_gl_renderer_

#include <vector>
#include "core.hpp"
#include "renderer.hpp"
#include "gl_mesh.hpp"

class TMesh;
class GLFWwindow;


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


/**
 *  TGLRenderer
 *  @brief      Class responsible for the main rendering loop
 *  @note       Will use the GL context from its window.
 */
class TGLRenderer : public TRenderer
{
public:

    /** TRenderer @brief constructor with window reference   */ 
    TGLRenderer(TWindow *window);


    /** 
     *  init 
     *  @brief  set this renderer. very important function. 
     *  @note   runs on main thread 
     */ 
    virtual void init() override final;

protected:

    // renderer override
    virtual void renderFrame() override;

    /** 
     *  drawMesh 
     *  @brief  draw a mesh with specified info
     *  @param  render_info     MVP related information
     *  @param  mesh            the mesh to render
     *  @param  program_id      the shading program to use
     */ 
    void drawMesh(TGLRenderData &render_info, const TGLMesh &mesh, GLuint program_id);

    /** 
     *  Meshes 
     *  @brief  Meshes to draw
     *  @todo   replace by custom struct/class to determine rendering/shading etc.. for each
     */ 
    std::vector<TGLMesh> Meshes;

private:

    /** 
     *  TargetWindow 
     *  @brief  raw pointer to the window we belong to.
     */ 
    GLFWwindow * TargetWindow;


};

#endif //_this_gl_renderer_