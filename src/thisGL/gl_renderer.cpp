// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.




// External libs
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// this includes
#include "gl_renderer.hpp"
#include "gl_window.hpp"
#include "gl_shader.hpp"


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
 
static TGLShader vertex_shader_text = TGLShader(
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec2 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 0.0, 1.0);\n"
"    color = vCol;\n"
"}\n" , TGLShaderType::Vertex);
 
static TGLShader fragment_shader_text = TGLShader(
"#version 110\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_FragColor = vec4(color, 1.0);\n"
"}\n", TGLShaderType::Fragment);
 

static GLuint vertex_buffer, program;
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
 
    program = TGLShader::loadShaders(vertex_shader_text, fragment_shader_text);

    // TODO : implement error stop
    if(program == 0)
        return;

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
        int width, height;
        glm::mat4x4 m, p, mvp;
 
        glfwGetFramebufferSize(TargetWindow, &width, &height);
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        //glClearColor( 0.5f,0.2f, 0.3f,1.f);
 
        m = glm::mat4x4(1.f);
        glm::rotate(m, (float)glfwGetTime(), glm::vec3(0,1,0));

        //p = glm::perspective(60.0f, (float)width / (float)height, 0.1f, 100.0f);
        p = glm::ortho(0.0f, (float)width,(float)height,0.0f, 0.1f, 100.0f);
        mvp = p*m;
 
        glUseProgram(program);
        glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        glDrawArrays(GL_TRIANGLES, 0, 3);
 
        glfwSwapBuffers(TargetWindow);
}