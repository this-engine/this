// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_renderer_
#define _this_gl_renderer_

#include "renderer.hpp"


class GLFWwindow;

/**
 *  TGLRenderer
 *  @brief      Class responsible for the main rendering loop
 *  @note       Will use the GL context from its window.
 *  @todo       Implements complex interface
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


private:

    GLFWwindow * TargetWindow;


};

#endif //_this_gl_renderer_