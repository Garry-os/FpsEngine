#include "mesh.h"
#include "engine/renderer/vertexBufferLayout.h"
#include <glad/glad.h>

Mesh::Mesh(const float* vertices, 
         uint32_t vertexSize,
         const uint32_t* indices,
         uint32_t indexCount,
         VertexBufferLayout layout)
    :vbo(vertices, vertexSize),
    ibo(indices, indexCount),
    vao()
{
    // Setup vertex array object
    vao.setIndexBuffer(ibo);
    vao.addVertexBuffer(vbo, layout);
}

void Mesh::draw() {
    vao.bind();
    ibo.bind();

    glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_INT, nullptr);
}

