// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_program_
#define _this_gl_program_

#include <vector>
#include <initializer_list>
#include "glad/glad.h"

class TGLShader;

/**
 *  TGLProgram
 *  @brief      make a program out of shaders
 */
class TGLProgram
{

protected:

    /**
     *  Shaders
     *  @brief   array of shaders 
     */
    std::vector<TGLShader> Shaders;

public: 

    /** 
     *  TGLProgram 
     *  @brief  construct a program from shaders
     *  @param  shader_list     array of shaders (vertex and fragment)
     */ 
    TGLProgram(std::initializer_list<TGLShader> shader_list) : Shaders(shader_list) 
    {}

    /** 
     *  makeProgram 
     *  @brief  compile and load shaders
     *  @return the program id of the loaded program or 0 if it failed 
     *  @todo might nee to find a better name
     */ 
    GLuint makeProgram();


};


#endif //_this_gl_program_


