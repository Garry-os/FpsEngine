#include "resourceManager.h"
#include <engine/renderer/mesh.h>
#include <cassert>

// ID: (generation << 24) | index

MeshHandle ResourceManager::createMesh(const MeshInfo& info) {
    uint8_t generation = 0;
    uint32_t index = meshes.size();

    // Create a mesh slot
    MeshSlot slot;
    slot.generation = 0;
    slot.mesh = std::make_unique<Mesh>(info.vertices, info.vertexSizeInBytes, info.indices, info.indexCount, info.layout);
    meshes.push_back(std::move(slot));

    // Construct a handle
    MeshHandle handle = (generation << 24) | (index & 0x00FFFFFF);
    return handle;
}

Mesh& ResourceManager::getMesh(MeshHandle handle) {
    // Decode
    uint8_t generation = ((handle >> 24) & 0xFF);
    uint32_t index = (handle & 0x00FFFFFF);

    // Check if it's valid
    if (meshes[index].mesh == nullptr) {
        assert(false && "Invalid mesh index");
    }

    if (meshes[index].generation != generation) {
        assert(false && "Outdated current mesh generation");
    }

    return *meshes[index].mesh;
}

ShaderHandle ResourceManager::loadShader(const std::string& vertexPath, const std::string& fragmentPath) {
    uint8_t generation = 0;
    uint32_t index = shaders.size();

    // Create a shader slot
    ShaderSlot slot;
    slot.generation = generation;
    slot.shader = std::make_unique<Shader>(vertexPath, fragmentPath);
    shaders.push_back(std::move(slot));

    // Construct a handle
    ShaderHandle handle = (generation << 24) | (index & 0x00FFFFFF);
    return handle;
}

Shader& ResourceManager::getShader(MeshHandle handle) {
    // Decode
    uint8_t generation = (handle >> 24) & 0xFF;
    uint32_t index = (handle & 0x00FFFFFF);

    // Check if it's valid
    if (shaders[index].shader == nullptr) {
        assert(false && "Invalid shader index");
    }

    if (shaders[index].generation != generation) {
        assert(false && "Outdated shader generation");
    }

    return *shaders[index].shader;
}
