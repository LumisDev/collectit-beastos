#pragma once
#include <string>
#include <glad/glad.h>
class Shader {
    public:
        Shader(const std::string &name);
    private:
        GLuint vertex, fragment, progid;
};