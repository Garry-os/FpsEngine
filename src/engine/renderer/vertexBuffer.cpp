#include "vertexBuffer.h"
#include <glad/glad.h>

VertexBuffer::VertexBuffer(const void* data, uint32_t size) {
    // Generate a vertex buffer object
    glGenBuffers(1, &m_id);

    // Select the vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    // Copies data
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    // Unselect
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(GL_ARRAY_BUFFER, &m_id);
}

void VertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
