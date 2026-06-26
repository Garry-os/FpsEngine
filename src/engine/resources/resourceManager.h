#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <engine/renderer/vertexBufferLayout.h>
#include <engine/renderer/mesh.h>

// Slot types
struct MeshSlot {
    std::unique_ptr<Mesh> mesh;
    uint32_t generation;
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

class ResourceMananager {
public:
    ResourceMananager() = default;
    ~ResourceMananager() = default;

    MeshHandle createMesh(const MeshInfo& info);
    Mesh& getMesh(MeshHandle handle);

private:
    std::vector<MeshSlot> meshes;
};
