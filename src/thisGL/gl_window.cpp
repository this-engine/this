// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.


#include <stdio.h>
#include <omp.h>
#include <GLFW/glfw3.h>
#include "gl_window.hpp"
#include "gl_renderer.hpp"


void TGLWindow::handleError(int error,const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

void TGLWindow::handleQuit(GLFWwindow * window)
{
    void* user_ptr = glfwGetWindowUserPointer(window);
    TGLWindow* t_window = reinterpret_cast<TGLWindow*>(user_ptr);
    if(t_window)
    {
        t_window->deleteWindow();
    }
}

void TGLWindow::deleteWindow()
{
    TWindow::deleteWindow();
    if(GlfwWindow)
        GlfwWindow.reset(nullptr);
}


bool TGLWindow::shouldClose()
{
    return  !(GlfwWindow);// || glfwWindowShouldClose(GlfwWindow.get());
}

void TGLWindow::windowEvents()
{
    glfwPollEvents();
}

void TGLWindow::render() const
{
    // check window is current context
    if(glfwGetCurrentContext() != GlfwWindow.get())
        glfwMakeContextCurrent(GlfwWindow.get());

    // start rendering
    if(Renderer)
        Renderer->renderFrame();
}

TGLWindow::TGLWindow(TString name, size_t x, size_t y) : TWindow(name, x,y), GlfwWindow(nullptr, &glfwDestroyWindow)
{
    // first callback to be informed early when an issue occurs
    glfwSetErrorCallback(TGLWindow::handleError);

    // try to init glfw and GL
    if (!glfwInit())
    {
        return;
    }

    // create a window based on base class infos
    GlfwWindow.reset(glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL));
    
    glfwSetWindowUserPointer(GlfwWindow.get(), this);
    // 
    if (GlfwWindow == NULL)
    {
        return;
    }
    // making GL context
    glfwMakeContextCurrent(GlfwWindow.get());
    Renderer.reset( new TGLRenderer(this));
    glfwSwapInterval(1);
 
    // enable window callbacks :
    glfwSetWindowCloseCallback(GlfwWindow.get(), TGLWindow::handleQuit);
}

TGLWindow::~TGLWindow()
{
    deleteWindow();
    // lets get rid of glfw
    glfwTerminate();
}
