#pragma once

#include <string>

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);

    [[nodiscard]] unsigned int getId() const;

    void use() const;
    void setFloat(std::string name, float value) const;

private:
    unsigned int ID;

    static std::string readFile(const std::string& path);

    static void checkCompileErrors(unsigned int shader, std::string type);
};
