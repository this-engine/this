// Copyright (c) 2020 Noé Perard-Gayot. All rights reserved.
// This work is licensed under the terms of the MIT license. 
// For a copy, see <https://opensource.org/licenses/MIT>.

#include "gl_shader.hpp"
#include "log.hpp"
#include <vector>

static TString getShaderLog(GLuint shader_id,   GLenum shader_type)
{
        std::string error = "error while compiling "; 

		switch (shader_type) 
        {
		case GL_VERTEX_SHADER:
			error +="vertex ";
			break;
		case GL_FRAGMENT_SHADER:
            error +="fragment ";
			break;
		}
        error +="shader: ";

        GLint log_length;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        std::vector<char> v(log_length);
        glGetShaderInfoLog(shader_id, log_length, NULL,  v.data());
        error += std::string(begin(v), end(v));

        return TString(error);

}


GLuint TGLShader::compileShader()
{
    GLenum shader_type = glType();
	GLuint shader_id = glCreateShader(shader_type);
	GLint shader_lenght = length();
    const char * shader_source = c();

	glShaderSource(shader_id, 1, &shader_source, &shader_lenght);

	glCompileShader(shader_id);
	
    GLint result = GL_FALSE;
	
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);

    // TODO add debug macro
	if (!result) 
    {
        TLog::log(TLogTypes::Error,  getShaderLog(shader_id, shader_type));
	}

	if (!result) glDeleteShader(shader_id);

	return result ? shader_id : 0;
}
