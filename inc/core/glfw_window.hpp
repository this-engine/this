// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "window.hpp"

class GLFWwindow;


/**
 *  TSDLWindow
 *  @brief      Simple wrapper around sdl
 *  @todo       Implements resolution checking
 */
class TGLFWWindow  : public TWindow
{
private :

    GLFWwindow* glfw_window;

public:
    TGLFWWindow(TString name, size_t x, size_t y) : TWindow(name, x,y){}

    // TWindow Overrides 
    virtual void initWindow() override final;
    virtual void loopWindow() override final;
    virtual int  quitWindow() override final;

    /** 
     *  handleError 
     *  @brief callback called by glfw when an error occurs
     */ 
    static void handleError(int error, const char* description);


};
