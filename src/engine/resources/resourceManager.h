#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <engine/renderer/vertexBufferLayout.h>
#include <engine/renderer/mesh.h>
#include <engine/renderer/shader.h>

// Slot types
struct MeshSlot {
    std::unique_ptr<Mesh> mesh;
    uint8_t generation;
};

struct ShaderSlot {
    std::unique_ptr<Shader> shader;
    uint8_t generation;
};

// Info structs
struct MeshInfo {
    const float* vertices;
    uint32_t vertexSizeInBytes;
    const uint32_t* indices;
    uint32_t indexCount;
    VertexBufferLayout layout;
};

// Handle types
typedef uint32_t MeshHandle;
typedef uint32_t ShaderHandle;

class ResourceManager {
public:
    ResourceManager() = default;
    ~ResourceManager() = default;

    MeshHandle createMesh(const MeshInfo& info);
    Mesh& getMesh(MeshHandle handle);

    ShaderHandle loadShader(const std::string& vertexPath, const std::string& fragmentPath);
    Shader& getShader(ShaderHandle handle);

private:
    std::vector<MeshSlot> meshes;
    std::vector<ShaderSlot> shaders;
};
