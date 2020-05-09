// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#ifndef _this_gl_shader_
#define _this_gl_shader_


#include "glad/glad.h"
#include "core.hpp"


/**
 *  TGLShaderType
 *  @brief      type of shaders to compile
 */
enum class TGLShaderType : bool
{
    Vertex   /* Vertex shader   */,
    Fragment /* Fragment shader */
};


/**
 *  TGLShader
 *  @brief      simplifies the loading and unloading of gl shaders
 */
class TGLShader : public TString
{
protected:

    /** 
     *  Type 
     *  @brief  shader type
     */ 
    TGLShaderType Type;

public:

    /** 
     *  TGLShader 
     *  @brief  constructor from __this__ string
     *  @param  string_text a __this__ string
     *  @param  type        what shader this is.
     */ 
    TGLShader(const TString& string_text, TGLShaderType type) : TString(string_text), Type(type)
    {}

    /** 
     *  TGLShader 
     *  @brief  constructor from raw text
     *  @param  raw_text    a c-style string
     *  @param  type        what shader this is.
     */ 
    TGLShader(const char* raw_text, TGLShaderType type) : TString(raw_text), Type(type)
    {}

    /** 
     *  compile_shader 
     *  @brief  generate the executable shader
     *  @todo   improve description
     */ 
    GLuint compileShader();

    /** 
     *  type() 
     *  @return     Type
     */ 
    inline TGLShaderType type() const {return Type;}

    /** 
     *  type 
     *  @return     the correct GLenum for this
     */ 
    inline GLenum glType() const
    {
        switch (type())
        {
        case TGLShaderType::Vertex:
            return GL_VERTEX_SHADER;
        case TGLShaderType::Fragment:
            return GL_FRAGMENT_SHADER;
        default:
            return 0;
        }
    }

};

#endif //_this_gl_shader_