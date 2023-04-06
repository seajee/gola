#include "common.h"

template<typename T>
class Matrix2D
{
private:
    std::vector<T> m_Data;
    int32_t m_Heigth;
    int32_t m_Width;

public:
    Matrix2D(int32_t height, int32_t width) :
        m_Data(height * width), m_Heigth(height), m_Width(width) 
    {
    }

    T* operator[](int32_t index)
    {
        return &m_Data[index * m_Width];
    }

    const T* operator[](int32_t index) const
    {
        return &m_Data[index * m_Width];
    }
};
