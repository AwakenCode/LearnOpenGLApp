#include <sstream>
#include <fstream>
#include <iostream>
#include "Shader.h"
#include "glad/glad.h"

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath)
{
    std::string vertexCode = readFile(vertexPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexShaderCode = vertexCode.c_str();
    const char* fragmentShaderCode = fragmentCode.c_str();
    unsigned int vertex, fragment;

    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

unsigned int Shader::getId() const
{
    return ID;
}

void Shader::use() const
{
    glUseProgram(ID);
}

std::string Shader::readFile(const std::string& path)
{
    std::fstream file(path);
    std::stringstream buffer;

    if (!file.is_open())
    {
        std::cerr << "Failed to read file: " << path << std::endl;
        return "";
    }

    buffer << file.rdbuf();
    return buffer.str();
}

void Shader::checkCompileErrors(unsigned int shader, std::string type)
{
    int success;
    const unsigned int infoLogSize = 1024;
    char infoLog[infoLogSize];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, infoLogSize, nullptr, infoLog);
            std::cerr << "Compile error " << type << " shader:\n" << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, infoLogSize, nullptr, infoLog);
            std::cerr << "Program linking error:\n" << infoLog << std::endl;
        }
    }
}

void Shader::setFloat(std::string name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}
