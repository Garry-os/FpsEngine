#include "indexBuffer.h"
#include <glad/glad.h>

// Similar to vertex buffer lol

IndexBuffer::IndexBuffer(const uint32_t* data, uint32_t count) {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), data, GL_STATIC_DRAW);
    m_count = count;
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
