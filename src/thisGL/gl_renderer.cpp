// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.




// External libs
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
// this includes
#include "gl_renderer.hpp"
#include "gl_window.hpp"



static const struct
{
    float x, y;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 0.f, 0.f, 1.f }
};
 
static const char* vertex_shader_text =
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n";
 
static const char* fragment_shader_text =
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n";
 

static GLuint vertex_buffer, vertex_shader, fragment_shader, program;
static GLint mvp_location, vpos_location, vcol_location;


TGLRenderer::TGLRenderer(TWindow *window) : TRenderer(window)
{
    auto tglwindow = dynamic_cast<TGLWindow *>(window);
    if(!tglwindow)
        return;
    
    TargetWindow = tglwindow->GlfwWindow.get();
}

void TGLRenderer::init()
{
    if(!TargetWindow)
        return;

    // init glad;

    gladLoadGL();

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
 
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_shader_text, NULL);
    glCompileShader(vertex_shader);
 
    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_shader_text, NULL);
    glCompileShader(fragment_shader);
 
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
 
    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 2, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));


    return;
}

void TGLRenderer::renderFrame()
{

    //if(!TargetWindow)
    //    return;

    TRenderer::renderFrame();
    float ratio;
    int width, height;
    glm::mat4 m(1.0f), p, mvp;
 
    glfwGetFramebufferSize(TargetWindow, &width, &height);
    ratio = width / (float) height;
 
    glViewport(0, 0, width, height);
    glClearColor(0.f,1.f,1.f,1.f);
    //glClear(GL_COLOR_BUFFER_BIT);
 
    mvp = p* m;
 
    glUseProgram(program);
    glUniformMatrix4fv(mvp_location, 1, GL_FALSE, (const GLfloat*) glm::value_ptr(mvp));
    glDrawArrays(GL_TRIANGLES, 0, 3);
 
    glfwSwapBuffers(TargetWindow);
}