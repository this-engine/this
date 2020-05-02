// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "glfw_window.hpp"
#include <stdio.h>
//#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <omp.h>


void TGLFWWindow::initWindow()
{
    if (!glfwInit())
    {
        return;
    }

    glfwSetErrorCallback(handleError);
    
    glfw_window = glfwCreateWindow(windowWidth, windowHeight, windowTitle, NULL, NULL);
    
    if (glfw_window == NULL)
    {
        quitWindow();
    }
    // making GL context
    glfwMakeContextCurrent(glfw_window);
}

void TGLFWWindow::loopWindow()
{
    if (glfw_window == NULL)
    {
        quitWindow();
    }

    while (!glfwWindowShouldClose(glfw_window))
    {

    }  
      
}

int  TGLFWWindow::quitWindow()
{
    // glfwTerminate must be run from main thread no matter what
    //

    glfwTerminate();
    return 0;
}


void TGLFWWindow::handleError(int error,const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}