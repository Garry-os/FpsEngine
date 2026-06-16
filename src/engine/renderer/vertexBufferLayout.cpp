#include "vertexBufferLayout.h"

uint32_t getDataSize(DataType type) {
    switch (type) {
        case DataType::Float: return 4;
        case DataType::Int: return 4;
    };
}

VertexBufferLayout::VertexBufferLayout()
    :m_stride(0) {}

void VertexBufferLayout::addElement(DataType type, uint32_t count, bool normalized) {
    m_elements.push_back({ type, count, normalized });
    m_stride += getDataSize(type) * count;
}
