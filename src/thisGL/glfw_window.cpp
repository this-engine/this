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
    //TODO: retrieve ther current valid TGLFWindow and deinit it
    glfwDestroyWindow(window);
    // explicitly remove pointer reference window
    window = nullptr;
    glfwTerminate();
}



void TGLFWWindow::init()
{
    // first callback to be informed early when an issue occurs
    glfwSetErrorCallback(TGLFWWindow::handleError);

    // try to init glfw and GL
    if (!glfwInit())
    {
        return;
    }

    // create a window based on base class infos
    glfw_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);

    
    // 
    if (glfw_window == NULL)
    {
        deinit();
    }
    // making GL context
    glfwMakeContextCurrent(glfw_window);
 
    // enable window callbacks :
    glfwSetWindowCloseCallback(glfw_window, TGLFWWindow::handleQuit);

    // start renderer
    

}

void  TGLFWWindow::deinit()
{
    // glfwTerminate must be run from main thread no matter what
    glfwDestroyWindow(glfw_window);
    glfwTerminate();
    return;
}

bool TGLFWWindow::shouldClose()
{
    return   glfw_window == NULL; // glfwWindowShouldClose(glfw_window); 
}

void TGLFWWindow::refreshEvent()
{
    if(glfw_window)
        glfwPollEvents();
}

TGLFWWindow::TGLFWWindow(TString name, size_t x, size_t y) : TWindow(name, x,y){}

TGLFWWindow::~TGLFWWindow(){}
