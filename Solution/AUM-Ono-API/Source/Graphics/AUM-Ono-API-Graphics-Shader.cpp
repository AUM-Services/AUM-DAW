//Written by Eric Dee.

#include "AUM-Ono-API-Graphics-Shader.h"

namespace AUM_Ono_API_Graphics {

/********************************************************************************************************/
    ////              ////
    //// Construction ////
    ////              ////
    //////////////////////

    AUMOnoAPIGraphicsShader::AUMOnoAPIGraphicsShader

        () {
        this->filePath = "No info.";
        this->vertexShader = "No info.";
        this->uniformLocation = 0;
    }

/********************************************************************************************************/
    ////               ////
    //// Build methods ////
    ////               ////
    ///////////////////////

    unsigned int AUMOnoAPIGraphicsShader::CompileVertexAndFragmentShaders
        
        (unsigned int type, const string& source) const {
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
            AUMWorkstationItemError("{0}: Failed to compile {1} shader.", message, shaderType);
            glDeleteShader(id);
        }

        return id;
    }

    unsigned int AUMOnoAPIGraphicsShader::BuildVertexAndFragmentShaders
        
        (const string& filePath) {
        this->ReadAndSetTheShaderFromShaderFile(filePath);

        unsigned int program = glCreateProgram();
        unsigned int vs = this->CompileVertexAndFragmentShaders(GL_VERTEX_SHADER, this->vertexShader);
        unsigned int fs = this->CompileVertexAndFragmentShaders(GL_FRAGMENT_SHADER, this->fragmentShader);

        // Assert or catch this.
        glAttachShader(program, vs);
        glAttachShader(program, fs);

        glLinkProgram(program);
        glValidateProgram(program);

        glDeleteShader(vs); glDeleteShader(fs);
        
        return program;
    }

    void AUMOnoAPIGraphicsShader::SetTheVertexShader
        
        (string value) {
        this->vertexShader = value;
    }

    void AUMOnoAPIGraphicsShader::SetTheFragmentShader
        
        (string value) {
        this->fragmentShader = value;
    }

    void AUMOnoAPIGraphicsShader::ReadAndSetTheShaderFromShaderFile
        
        (const string& filePath) {
        this->filePath = (string)filePath;
        ifstream stream(filePath);
        string line;
        stringstream shaders[2];
        // Sets none out of range in a visually pleasing way.
        const int none = -1;
        enum class SHADERTYPE
        {
            NONE=(none+0), VERTEX=(none+1), FRAGMENT=(none+2)
        };
        SHADERTYPE type = SHADERTYPE::NONE;
        while (getline(stream, line))
        {
            if (line.find("Read shader") != string::npos)
            {
                if (line.find("vertex") != string::npos)
                {
                    type = SHADERTYPE::VERTEX;
                }
                else if (line.find("fragment") != string::npos) {
                    type = SHADERTYPE::FRAGMENT;
                }
            }
            else {
                shaders[(int)type] << line << '\n';
            }
        }
        this->SetTheVertexShader(shaders[(int)SHADERTYPE::VERTEX].str());
        this->SetTheFragmentShader(shaders[(int)SHADERTYPE::FRAGMENT].str());
        AUMWorkstationItemWarn("*SHADER DETAILS**");
        AUMWorkstationItemInfo("Vertex shader:");
        AUMWorkstationItemInfo("\n\n"+this->vertexShader);
        AUMWorkstationItemInfo("Fragment shader:");
        AUMWorkstationItemInfo("\n\n"+this->fragmentShader);
    }

/********************************************************************************************************/
    ////                ////
    //// Update methods ////
    ////                ////
    ////////////////////////

    void AUMOnoAPIGraphicsShader::UseShader(unsigned int shader) {
        glUseProgram(shader);
    }

    void AUMOnoAPIGraphicsShader::SetUniformLocation
        
        (unsigned int shader, const char* name) {
        this->uniformLocation = glGetUniformLocation(shader, name);
    }

    int AUMOnoAPIGraphicsShader::GetUniformLocation

        () {
        return this->uniformLocation;
    }

    void AUMOnoAPIGraphicsShader::SetUniform4f
    
        (float v0, float v1, float v2, float v3) {
        glUniform4f(this->GetUniformLocation(), v0, v1, v2, v3);
    }

    void AUMOnoAPIGraphicsShader::UnbindThisUniformLocation
    
        () {
        glUseProgram(0);
    }

}