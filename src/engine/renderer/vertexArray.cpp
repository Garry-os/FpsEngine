#include "vertexArray.h"
#include <glad/glad.h>

uint32_t getDataSize(DataType type);

VertexArray::VertexArray() {
    glGenVertexArrays(1, &m_id);
    glBindVertexArray(m_id);
}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &m_id);
}

static GLenum type_to_opengl(DataType type) {
    switch (type) {
        case DataType::Float: return GL_FLOAT;
        case DataType::Int: return GL_INT;
    };
}

void VertexArray::addVertexBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout) {
    buffer.bind();

    const auto& elements = layout.getElementArray();
    uint64_t offset = 0;

    for (uint32_t i = 0; i < elements.size(); i++) {
        const auto& element = elements[i];

        // Setup vertex buffer layout
        glEnableVertexAttribArray(i);
        glVertexAttribPointer(i, element.count, type_to_opengl(element.type),
            element.normalized, layout.getStride(), (void*)offset);

        // Increase offset
        offset += getDataSize(element.type) * element.count;
    }

    buffer.unbind();
}

void VertexArray::setIndexBuffer(const IndexBuffer& buffer) {
    this->bind();
    buffer.bind();

    this->m_indexBuff = std::make_shared<IndexBuffer>(buffer);
}

void VertexArray::bind() const {
    glBindVertexArray(m_id);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
