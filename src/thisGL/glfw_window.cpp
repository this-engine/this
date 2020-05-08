// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#include <stdio.h>
#include <omp.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include "glfw_window.hpp"


void TGLFWWindow::handleError(int error,const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void TGLFWWindow::handleQuit(GLFWwindow * window)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    TGLFWWindow* t_window = reinterpret_cast<TGLFWWindow*>(user_ptr);
    if(t_window)
    {
        t_window->deleteWindow();
    }
}

void TGLFWWindow::deleteWindow()
{
    glfw_window.reset(nullptr);
}


bool TGLFWWindow::shouldClose()
{
    return   (bool)!(glfw_window) ; // glfwWindowShouldClose(glfw_window); 
}

void TGLFWWindow::refreshEvent()
{
    glfwPollEvents();
}

TGLFWWindow::TGLFWWindow(TString name, size_t x, size_t y) : TWindow(name, x,y), glfw_window(nullptr, &glfwDestroyWindow)
{
    // first callback to be informed early when an issue occurs
    glfwSetErrorCallback(TGLFWWindow::handleError);

    // try to init glfw and GL
    if (!glfwInit())
    {
        return;
    }

    // create a window based on base class infos
    glfw_window.reset(glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL));
    
    glfwSetWindowUserPointer(glfw_window.get(), this);
    // 
    if (glfw_window == NULL)
    {
        return;
    }
    // making GL context
    glfwMakeContextCurrent(glfw_window.get());
 
    // enable window callbacks :
    glfwSetWindowCloseCallback(glfw_window.get(), TGLFWWindow::handleQuit);

}

TGLFWWindow::~TGLFWWindow()
{
        // lets get rid of glfw
        glfwTerminate();
}
