#include "Shader.h"

namespace AUMGraphics {

    unsigned int Shader::CompileShader(unsigned int type, const string& source)
    {
        unsigned int id = glCreateShader(type);
        // c_str makes a const char* out of strings. Same as &source[0], which is a pointer to the start of the array.
        const char* src = &source[0];
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE)
        {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            // Circumvent non dynamic stack array limitations.
            char* message = (char*)malloc(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            // Make an enum
            const char* shaderType = (type == GL_VERTEX_SHADER ? "vertex" : "fragment");
            AUMPluginError("{0}: Failed to compile {1} shader.", message, shaderType);
            glDeleteShader(id);
        }

        return id;
    }

    unsigned int Shader::CreateShader() {
        unsigned int program = glCreateProgram();
        unsigned int vs = this->CompileShader(GL_VERTEX_SHADER, this->vertexShader);
        unsigned int fs = this->CompileShader(GL_FRAGMENT_SHADER, this->fragmentShader);

        // Assert or catch this.
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs); glDeleteShader(fs); return program;
    }

    void Shader::SetVertexShader(string value) {
        this->vertexShader = value;
    }

    void Shader::SetFragmentShader(string value) {
        this->fragmentShader = value;
    }

}