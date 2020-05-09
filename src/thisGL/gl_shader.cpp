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


GLuint TGLShader::compileShader()
{
    GLenum shader_type;

    switch (Type)
    {
    case TGLShaderType::Vertex:
        shader_type = GL_VERTEX_SHADER;
        break;
    case TGLShaderType::Fragment:
        shader_type = GL_FRAGMENT_SHADER;
    break;
    default:
        break;
    }
 
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


GLuint TGLShader::loadShaders(TGLShader vertex_shader_source, TGLShader fragment_shader_source)
{
	// Create the shaders
	GLuint vertex_shader_id = vertex_shader_source.compileShader();
	if (vertex_shader_id == 0) return 0;
	GLuint fragment_shader_id = fragment_shader_source.compileShader();
	if (fragment_shader_id == 0) {
		glDeleteShader(vertex_shader_id);
		return 0;
	}
	// Link the program
	GLuint program_id = glCreateProgram();
	glAttachShader(program_id, vertex_shader_id);
	glAttachShader(program_id, fragment_shader_id);
	glLinkProgram(program_id);

	// Check the program
	GLint result = GL_FALSE;
	glGetProgramiv(program_id, GL_LINK_STATUS, &result);

    // TODO add debug macro
    if (!result) 
    {
        TLog::log(TLogTypes::Error,  getProgramLog(program_id));
	}

	glDetachShader(program_id, vertex_shader_id);
	glDetachShader(program_id, fragment_shader_id);

	glDeleteShader(vertex_shader_id);
	glDeleteShader(fragment_shader_id);

	if (!result) glDeleteProgram(program_id);
	return result ? program_id : 0;
}


