#ifndef GLMATRIX_H
#define GLMATRIX_H

#include "glvector.h"
#include "cmath"

namespace glmath{

template<size_type size>
class GLMatrix
{
public:
    GLMatrix()
    {
        m_data[0]= 1.0; m_data[4]= 0.0; m_data[8]=  0.0; m_data[12]= 0.0;
        m_data[1]= 0.0; m_data[5]= 1.0; m_data[9]=  0.0; m_data[13]= 0.0;
        m_data[2]= 0.0; m_data[6]= 0.0; m_data[10]= 1.0; m_data[14]= 0.0;
        m_data[3]= 0.0; m_data[7]= 0.0; m_data[11]= 0.0; m_data[15]= 1.0;
    }
    GLMatrix(const GLMatrix<size> &rightMat) { memcpy(m_data, rightMat.m_data, sizeof(double) * size * size); }
    GLMatrix(const double *arr) { memcpy(m_data, arr, sizeof(double) * size * size); }
    GLMatrix(const GLMatrix<size + 1> &rightMat)
    {
        size_type newSize = size + 1;
        for(size_type i = 0; i < size; ++i) {
            for(size_type j = 0; j < size; ++j)
                m_data[i * size + j] = rightMat[i * newSize + j];
        }
    }
    GLMatrix(const GLMatrix<size + 2> &rightMat)
    {
        size_type newSize = size + 2;
        for(size_type i = 0; i < size; ++i) {
            for(size_type j = 0; j < size; ++j)
                m_data[i * size + j] = rightMat[i * newSize + j];
        }
    }
    GLMatrix(const GLMatrix<size - 1> &rightMat)
    {
        size_type newSize = size - 1;
        for(size_type i = 0; i < size; ++i) {
            for(size_type j = 0; j < size; ++j) {
                if((i * size) <= (newSize * newSize) && j < newSize)
                    m_data[i * size + j] = rightMat[i * newSize + j];
                else
                    m_data[i * size + j] = 0;
            }
        }
    }
    GLMatrix(const GLMatrix<size - 2> &rightMat)
    {
        size_type newSize = size - 2;
        for(size_type i = 0; i < size; ++i) {
            for(size_type j = 0; j < size; ++j) {
                if((i * size) <= (newSize * newSize) && j < newSize)
                    m_data[i * size + j] = rightMat[i * newSize + j];
                else
                    m_data[i * size + j] = 0;
            }
        }
    }
    GLMatrix(const std::initializer_list<double> &list)
    {
        if(list.size() > size * size)
            qFatal("initializer list size not equal defined matrix size");
        memcpy(m_data, list.begin(), sizeof(double) * size * size);
    }

//!TODO реализовать эти методы
//    static GLMatrix<size> createRotMatrix(const GLVector<size> &vec, const double &angle) {}
//    static GLMatrix<size> createRotMatrix(const GLVector<size> &vec_1, const GLVector<size> &vec_2) {}
//    static GLMatrix<size> createTransMatrix(const GLVector<size> &vec) {}
//    static GLMatrix<size> createTransMatrix(const double &x, const double &y, const double &z) {}
//    static GLMatrix<size> createScaleMatrix(const double &scaleFactor) {}

    GLMatrix<size> operator+(const GLMatrix<size> &rightMat)
    {
        GLMatrix<size> result;
        for(int i = 0; i < (size * size); ++i)
            result[i] = *(this)[i] + rightMat[i];
        return result;
    }
    GLMatrix<size> operator-(const GLMatrix<size> &rightMat)
    {
        GLMatrix<size> result;
        for(int i = 0; i < (size * size); ++i)
            result[i] = *(this)[i] - rightMat[i];
        return result;
    }
    GLMatrix<size> &operator-=(const GLMatrix<size> &rightMat)
    {
        GLMatrix<size> result;
        for(int i = 0; i < (size * size); ++i)
            *(this)[i] -= rightMat[i];
        return result;
    }
    GLMatrix<size> &operator+=(const GLMatrix<size> &rightMat)
    {
        GLMatrix<size> result;
        for(int i = 0; i < (size * size); ++i)
            *(this)[i] += rightMat[i];
        return result;
    }
    GLVector<size> operator*(const GLVector<size> &rightVec)
    {
        GLVector<size> result;
        for(int i = 0; i < size; ++i) {
            result[i] = 0;
            for(int k = 0; k < size; ++k)
                result[i] += (*this)[i * size + k] * rightVec[k];
        }
        return result;
    }
    GLMatrix<size> operator*(const GLMatrix<size> &rightMat)
    {
        GLMatrix<size> result;
        for(int i = 0; i < size; ++i)
            for(int j = 0; j < size; ++j) {
                result[i * size + j] = 0;
                for(int k = 0; k < size; ++k)
                    result[i * size + j] += (*this)[i * size + k] * rightMat[k * size + j];
            }
        return result;
    }
    GLMatrix<size> operator*(const double &rightVal)
    {
        GLMatrix<size> result;
        for(int i = 0; i < size * size; ++i)
            result[i] *= rightVal;
        return result;
    }
    bool operator==(const GLMatrix<size> &rightMat)
    {
        bool isEquial = true;
        for(int i = 0; i < (size * size); ++i)
            isEquial = *(this)[i] == rightMat[i];
        return isEquial;
    }
    bool operator!=(const GLMatrix<size> &rightMat)
    {
        return !operator==(rightMat);
    }
    GLMatrix<size> &operator=(const GLMatrix<size> &rightMat)
    {
        for(int i = 0; i < size; ++i)
            *(this)[i] = rightMat[i];
        return *this;
    }
    const double &operator[](size_type index) const
    {
        return m_data[index];
    }
    double &operator[](size_type index)
    {
        return m_data[index];
    }


    double determinant()
    {
        double result = 1;
        GLMatrix<size> mat = *this;
        for(int i = 0; i < size; ++i) {
            int k = i;
            for(int j = i+1; j < size; ++j)
                if(std::abs(mat[i * size + j]) > std::abs(mat[i * size + k]))
                    k = j;
            if(mat[i * size + k] == 0.0)
                return 0;
            mat.swapCols(i, k);
            if(i != k) result *= (-1);
            result *= mat[i * size + i];
            for(int j = i + 1; j < size; ++j)
                mat[i * size + j] /= mat[i * size + i];
            for(int j = 0; j < size; ++j)
                if(j != i && mat[i * size + j] != 0.0)
                    for(int k = i+1; k < size; ++k)
                        mat[k * size + j] -= mat[k * size + i] * mat[i * size + j];
        }
        return result;
    }
    const double *toData() const { return m_data; }

    void swapRows(size_type row_1, size_type row_2)
    {
        double temp;
        for(int i = 0; i < size; ++i) {
            temp = (*this)[row_1 + i];
            (*this)[row_1 + i] = (*this)[row_2 + i];
            (*this)[row_2 + i] = temp;
        }
    }
    void swapCols(size_type col_1, size_type col_2)
    {
        double temp;
        for(int i = 0; i < size; ++i) {
            temp = (*this)[i * size + col_1];
            (*this)[i * size + col_1] = (*this)[i * size + col_2];
            (*this)[i * size + col_2] = temp;
        }
    }

private:

    double m_data[size * size];
};

} //namespace glmath

#endif // GLMATRIX_H
