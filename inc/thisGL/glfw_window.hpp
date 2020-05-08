// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_glfw_window_
#define _this_glfw_window_


#include "window.hpp"
#include <memory>

// forward declarations
class GLFWwindow;
class TRenderer;
void glfwDestroyWindow(GLFWwindow* window);


/**
 *  TSDLWindow
 *  @brief      Simple wrapper around sdl
 *  @todo       Implements resolution checking
 */
class TGLFWWindow  : public TWindow
{

protected:

    void deleteWindow();

public:

    /** 
     *  glfw_window 
     *  @brief  The actual glfw window of this class
     *  @todo   use smart pointer
     */ 
    std::unique_ptr<GLFWwindow, decltype(&glfwDestroyWindow)> glfw_window;


public :

    /** 
     *  handleError 
     *  @brief  callback called by glfw when an error occurs
     *  @param  error   
     *  @note   glfw uses C-style 
     */ 
    static void handleError(int error, const char* description);

    /** 
     *  handleQuit 
     *  @brief  callback called by glfw when a request to quit has been made
     *  @param  window  the window receiving the callback
     *  @note   GLFWwindow is a GLFW type
     *  @note   glfw uses C-style callback, so we use static function
     */ 
    static void handleQuit(GLFWwindow * window);
    


    // window overrides
    virtual bool shouldClose()  override final;
    virtual void refreshEvent() override final;


    /** Constructor */
    TGLFWWindow(TString name, size_t x, size_t y);
    
    /** post window cleanup */
    ~TGLFWWindow();

};


#endif // _this_glfw_window_