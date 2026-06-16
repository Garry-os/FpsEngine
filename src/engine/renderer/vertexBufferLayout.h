#pragma once
#include <cstdint>
#include <vector>

enum class DataType {
    Float,
    Int,
};

struct VertexBufferElement {
    DataType type;
    uint32_t count;
    bool normalized;
};

class VertexBufferLayout {
public:
    VertexBufferLayout();
    ~VertexBufferLayout() = default;

    void addElement(DataType type, uint32_t count, bool normalized);

    inline const std::vector<VertexBufferElement>& getElementArray() const { return m_elements; }
    inline uint32_t getStride() const { return m_stride; }

private:
    std::vector<VertexBufferElement> m_elements;
    uint32_t m_stride;
};
