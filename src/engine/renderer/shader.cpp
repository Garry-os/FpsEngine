#include "shader.h"
#include <string>
#include <fstream>
#include <iostream>
#include <glad/glad.h>
#include <util.h>
#include <glm/gtc/type_ptr.hpp>

static std::optional<std::string> readFile(const std::string& filePath) {
    std::ifstream file(filePath);

    // Check for errors
    if (!file.is_open()) {
        std::cerr << "Failed to open file " << filePath << std::endl;
        return std::nullopt;
    }
    
    // Read the file
    std::string line, content;
    while (std::getline(file, line)) {
        content.append(line + '\n');
    }

    // Close the file
    file.close();
    return content;
}

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
    // Open shader files
    TRY_ASSERT(vertexSrc, readFile(vertexPath), "Failed to open vertex shader");
    TRY_ASSERT(fragmentSrc, readFile(fragmentPath), "Failed to open fragment shader");

    // Create a shader program
    auto program = createProgram(vertexSrc, fragmentSrc);
    if (!program)
        return;
    m_id = program.value();
}

Shader::~Shader() {
    glDeleteProgram(m_id);
}

std::optional<uint32_t> Shader::compileShader(uint32_t type, const std::string& shaderSrc) {
    // Create a shader
    uint32_t shader = glCreateShader(type);
    
    // Attach & compile shader
    const char* src_cstr = shaderSrc.c_str();
    glShaderSource(shader, 1, &src_cstr, NULL);
    glCompileShader(shader);

    // Check for errors
    int result;
    char msgBuff[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    
    if (!result) {
        // Compilation error
        glGetShaderInfoLog(shader, 512, NULL, msgBuff);
        std::cerr << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cerr << "Error: " << msgBuff << std::endl;
        return std::nullopt;
    }

    return shader;
}

std::optional<uint32_t> Shader::createProgram(const std::string& vertexSrc, const std::string& fragmentSrc) {
    // Create a shader program
    uint32_t program = glCreateProgram();

    // Compile the shaders 
    TRY_OPT(vertexShader, compileShader(GL_VERTEX_SHADER, vertexSrc));
    TRY_OPT(fragmentShader, compileShader(GL_FRAGMENT_SHADER, fragmentSrc));

    // Attach the shaders & link them
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);

    // Check for errors
    int result;
    char msgBuff[512];
    glGetProgramiv(program, GL_LINK_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(program, 512, NULL, msgBuff);
        std::cerr << "Failed to link shader program" << std::endl;
        std::cerr << "Error: " << msgBuff << std::endl;
        return std::nullopt;
    }

    // Validate the program
#ifndef RELEASE
    glValidateProgram(program);
    glGetProgramiv(program, GL_VALIDATE_STATUS, &result);
    if (!result) {
        glGetProgramInfoLog(program, 512, NULL, msgBuff);
        std::cerr << "Failed to validate shader program" << std::endl;
        std::cerr << "Error: " << msgBuff << std::endl;
        return std::nullopt;
    }
#endif

    // Activate program
    glUseProgram(program);

    // Delete shaders
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}

void Shader::bind() const {
    glUseProgram(m_id);
}

void Shader::unbind() const {
    glUseProgram(m_id);
}

// Uniform functions
std::optional<int> Shader::findUniformLocation(const std::string& name) {
    // Check the cache
    if (m_locationCache.find(name) != m_locationCache.end()) {
        return m_locationCache[name];
    }

    int location = glGetUniformLocation(m_id, name.c_str());
    if (location < 0) {
        std::cerr << "Uniform " << name << "doesn't exist" << std::endl;
        return std::nullopt;
    }

    // Save it in the cache
    m_locationCache[name] = location;
    return location;
}

// Floats
bool Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    TRY_RETURN_FALSE(uniform, findUniformLocation(name));
    glUniform4f(uniform, v0, v1, v2, v3);
    return true;
}


bool Shader::setUniform3f(const std::string& name, float v0, float v1, float v2) {
    TRY_RETURN_FALSE(uniform, findUniformLocation(name));
    glUniform3f(uniform, v0, v1, v2);
    return true;
}

bool Shader::setUniform2f(const std::string& name, float v0, float v1) {
    TRY_RETURN_FALSE(uniform, findUniformLocation(name));
    glUniform2f(uniform, v0, v1);
    return true;
}

bool Shader::setUniform1f(const std::string& name, float v0) {
    TRY_RETURN_FALSE(uniform, findUniformLocation(name));
    glUniform1f(uniform, v0);
    return true;
}

// Matrices
bool Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    TRY_RETURN_FALSE(uniform, findUniformLocation(name));
    glUniformMatrix4fv(uniform, 1, GL_FALSE, glm::value_ptr(matrix));
    return true;
}


