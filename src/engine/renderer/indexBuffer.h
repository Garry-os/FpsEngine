#pragma once
#include <cstdint>

class IndexBuffer {
public:
    IndexBuffer(const void* data, uint32_t size);
    ~IndexBuffer();

    void bind() const;
    void unbind() const;
private:
    uint32_t m_id;
};
