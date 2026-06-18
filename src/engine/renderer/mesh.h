#pragma once
#include "vertexBuffer.h"
#include "vertexArray.h"
#include "indexBuffer.h"

class Mesh {
public:
    Mesh(const float* vertices, 
         uint32_t vertexSize,
         const uint32_t* indices,
         uint32_t indexCount,
         VertexBufferLayout layout);
    ~Mesh() = default;

    void draw();

private:
    VertexBuffer vbo;
    IndexBuffer ibo;
    VertexArray vao;
};

