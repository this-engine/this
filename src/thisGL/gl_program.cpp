// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "gl_program.hpp"
#include "gl_shader.hpp"
#include "log.hpp"

static TString getProgramLog(GLuint program_id)
{
    std::string error = "error while loading program "; 
    GLint log_length;
	glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &log_length);
	std::vector<char> v(log_length);
    glGetProgramInfoLog(program_id, log_length, NULL,  v.data());
    error += std::string(begin(v), end(v));
    return TString(error);
}


GLuint TGLProgram::makeProgram()
{

    std::vector<GLuint> vertex_shader_ids;
    std::vector<GLuint> fragment_shader_ids;
    for(auto shader : Shaders)
    {
        switch (shader.type())
        {

        case TGLShaderType::Vertex:
        {
            GLuint vertex_shader = shader.compileShader();
            if (vertex_shader != 0)
                vertex_shader_ids.push_back(vertex_shader);
        }
        break;
        case TGLShaderType::Fragment:
        {
            GLuint fragment_shader = shader.compileShader();
            if (fragment_shader  == 0)
		        glDeleteShader(fragment_shader);
            else
                fragment_shader_ids.push_back(shader.compileShader());
        }
        break;
        default:
            break;
        }
    }
	
    if (vertex_shader_ids.size() <= 0)
    {
        // an error happened
        // TODO : error messages
        return 0;
    }


	// create a program reference
	GLuint program_id = glCreateProgram();
    
    std::vector<GLuint> shaders_ids = std::vector<GLuint>(vertex_shader_ids);
    shaders_ids.insert(shaders_ids.end(), fragment_shader_ids.begin(), fragment_shader_ids.end());

    // attach vertex shaders
    for (auto shader_id : shaders_ids)
	    glAttachShader(program_id, shader_id);

    // ling the program
	glLinkProgram(program_id);

	// Check the program
	GLint result = GL_FALSE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);

    // TODO add debug macro
    if (!result) 
    {
        TLog::log(TLogTypes::Error,  getProgramLog(program_id));
	}

    // detach shaders 
    for (auto shader_id : shaders_ids)
	    glDetachShader(program_id, shader_id);


    // get rid of shaders
    for (auto shader_id : shaders_ids)    
	    glDeleteShader(shader_id);


	if (!result) glDeleteProgram(program_id);
	return result ? program_id : 0;
}
