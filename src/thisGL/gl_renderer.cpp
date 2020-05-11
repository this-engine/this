// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

// External libs
#include <glm/gtx/transform.hpp>
#include "glad/glad.h"
#include <GLFW/glfw3.h>

// this includes
#include "mesh.hpp"
#include "gl_renderer.hpp"
#include "gl_window.hpp"
#include "gl_shader.hpp"
#include "gl_program.hpp"

static const struct
{
    float x, y ,z;
    float r, g, b;
} vertices[3] =
{
    { -0.6f, -0.4f, 1.f, 1.f, 0.f, 0.f },
    {  0.6f, -0.4f, 1.f, 0.f, 1.f, 0.f },
    {   0.f,  0.6f, 1.f, 0.f, 0.f, 1.f }
};
 
static TGLShader vertex_shader_text = TGLShader(
"#version 110\n"
"uniform mat4 MVP;\n"
"attribute vec3 vCol;\n"
"attribute vec3 vPos;\n"
"varying vec3 color;\n"
"void main()\n"
"{\n"
"    gl_Position = MVP * vec4(vPos, 1.0);\n"
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

    auto prog = TGLProgram({vertex_shader_text, fragment_shader_text});
    program = prog.makeProgram();

    // TODO : implement error stop
    if(program == 0)
        return;

    mvp_location = glGetUniformLocation(program, "MVP");
    vpos_location = glGetAttribLocation(program, "vPos");
    vcol_location = glGetAttribLocation(program, "vCol");
 
    glEnableVertexAttribArray(vpos_location);
    glVertexAttribPointer(vpos_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) 0);
    glEnableVertexAttribArray(vcol_location);
    glVertexAttribPointer(vcol_location, 3, GL_FLOAT, GL_FALSE,
                          sizeof(vertices[0]), (void*) (sizeof(float) * 2));


    return;
}

void TGLRenderer::renderFrame()
{
        int width, height;
        TMat4 m, p, mvp;
 
        glfwGetFramebufferSize(TargetWindow, &width, &height);
 
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glClearColor( 0.5f,0.2f, 0.3f,1.f);
 
        m = TMat4::identity();
        m.rotate(TVec3(0,1,0), (float)glfwGetTime());

        p = TMat4::perspective(60.0f, (float)width ,(float)height, 0.1f, 1000.0f);

        mvp = p*m;

        //glUniformMatrix4fv(mvp_location, 1, GL_FALSE, glm::value_ptr(mvp));
        //glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements
        glfwSwapBuffers(TargetWindow);
}



void TGLRenderer::drawMesh(TGLRenderData &render_info, const TGLMesh &mesh, GLuint program_id)
{
    // computed at build time
    constexpr size_t vertex_size = sizeof(TVertex);
    constexpr size_t vec3_size = sizeof(TVec3);
    constexpr size_t vec2_size = sizeof(TVec2);

    glUseProgram(program_id);
    glBindBuffer(GL_ARRAY_BUFFER,           mesh.vertexBuffer());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,   mesh.indexBuffer());
    
    // activate the shader access
    glEnableVertexAttribArray(0); // coord
    glEnableVertexAttribArray(1); // norm
    glEnableVertexAttribArray(2); // uv
    glEnableVertexAttribArray(3); // color

    //glVertexAttribPointer(attribute (cf. shader), taille, type, mormalized, vertex size, offset)
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)0 );
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(vec3_size) );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, vertex_size, (void*)(vec3_size + vec3_size));
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, vertex_size, (void*)(vec3_size + vec3_size + vec2_size ));
    
    // uniforms for the shader
    // TODO : make this dynamic
    glUniformMatrix4fv(render_info.MVP_id,   1, GL_FALSE, render_info.MVP.value_ptr());
    glUniformMatrix4fv(render_info.View_id,  1, GL_FALSE,  render_info.View.value_ptr());
    glUniformMatrix4fv(render_info.Model_id, 1, GL_FALSE,  render_info.Model.value_ptr());
    
    // draw geometry
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    //close the access
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
    // not necessary to unbind.
}
