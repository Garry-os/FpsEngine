#pragma once
#include <cstdint>
#include <string>
#include <optional>

class Shader {
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void bind() const;
    void unbind() const;

private:
    std::optional<uint32_t> createProgram(const std::string& vertexSrc, const std::string& fragmentSrc);
    std::optional<uint32_t> compileShader(uint32_t type, const std::string& shaderSrc);

    uint32_t m_id;
};

