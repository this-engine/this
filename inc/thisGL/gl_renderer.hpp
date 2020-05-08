// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_renderer_
#define _this_gl_renderer_

#include "renderer.hpp"


class TGLFWWindow;

/**
 *  TGLRenderer
 *  @brief      Class responsible for the main rendering loop
 *  @note       Will use the GL context from its window.
 *  @todo       Implements complex interface
 */
class TGLRenderer : public TRenderer
{
public: 

    /** 
     *  init 
     *  @brief  set this renderer. very important function. 
     *  @note   runs on main thread 
     */ 
    virtual void init(TWindow * window) override final;

protected:

    /**
     *  renderThread
     *  @brief      MOST important function, run on a separate thread (thanks to OMP)
     */
    virtual void renderThread() override;


private:

    /**
     *  GLFWWindow
     *  @brief      glfw window container 
     */
    TGLFWWindow * GLFWWindow;


};

#endif //_this_gl_renderer_