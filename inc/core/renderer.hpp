// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_renderer_
#define _this_renderer_


class TWindow;

/**
 *  TRenderer
 *  @brief      Class responsible for the main rendering loop
 *  @note       Will use the GL context from its window.
 *  @todo       Implements complex interface
 */
class TRenderer
{
public: 

    /** TRenderer @brief constructor with window reference   */ 
    TRenderer(TWindow *window);

    /** TRenderer @brief destructor is default, but need to be virtual   */ 
    virtual ~TRenderer() = default;

    /** 
     *  init 
     *  @brief  tries to get ressources to start rendering
     */ 
    virtual void init() {}

    /**
     *  renderFrame
     *  @brief      MOST important function, run on a separate thread (thanks to OMP)
     */
    virtual void renderFrame();

private:

    /** 
     *  stopRenderThread 
     *  @brief  boolean flag to stop the render thread 
     *  @todo   implement thread safety
     */ 
    bool StopRenderThread = false;

    /** 
     *  RenderThreadIsRunning 
     *  @brief  boolean flag to inform us on running status 
     *  @todo   implement thread safety
     */ 
    bool RenderThreadIsRunning = false;

};

#endif //_this_renderer_