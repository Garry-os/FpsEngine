#pragma once
#include "vertexBufferLayout.h"
#include "vertexBuffer.h"
#include "indexBuffer.h"
#include <memory>

class VertexArray {
public:
    VertexArray();
    ~VertexArray();

    void addVertexBuffer(const VertexBuffer& buffer, const VertexBufferLayout& layout);
    void setIndexBuffer(const IndexBuffer& buffer);

    void bind() const;
    void unbind() const;

    const std::shared_ptr<IndexBuffer> getIndexBuffer() { return m_indexBuff; }

private:
    std::shared_ptr<IndexBuffer> m_indexBuff;
    uint32_t m_id;
};
