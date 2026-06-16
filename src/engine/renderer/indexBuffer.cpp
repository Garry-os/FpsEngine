#include "indexBuffer.h"
#include <glad/glad.h>

// Similar to vertex buffer lol

IndexBuffer::IndexBuffer(const void* data, uint32_t size) {
    glGenBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_id);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
