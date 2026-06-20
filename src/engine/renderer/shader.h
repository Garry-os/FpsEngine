#pragma once
#include <cstdint>
#include <string>
#include <optional>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

    // Uniform functions
    // Floats
    bool setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    bool setUniform3f(const std::string& name, float v0, float v1, float v2);
    bool setUniform2f(const std::string& name, float v0, float v1);
    bool setUniform1f(const std::string& name, float v0);

    // Matrices
    bool setUniformMat4f(const std::string& name, const glm::mat4& matrix);

private:
    std::optional<uint32_t> createProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
    std::optional<uint32_t> compileShader(uint32_t type, const std::string& shaderSrc);

    std::optional<int> findUniformLocation(const std::string& name);

    uint32_t m_id;
    std::unordered_map<std::string, int> m_locationCache; // Uniform location cache
};

