#ifndef GLVECTOR_H
#define GLVECTOR_H

#include <QDebug>
#include <cmath>

namespace glmath{

using size_type = unsigned int;

template<size_type size>
class GLVector
{
public:
    GLVector()
    {
        for(int i = 0; i < size; ++i)
            this->data[i] = 0;
    }
    GLVector(const GLVector<size> &vec)
    {
        memcpy(data, vec.data, sizeof(double) * size);
    }
    GLVector(const std::initializer_list<double> &list)
    {
        if(list.size() > size)
            qFatal("initializer list size not equal defined matrix size");
        memcpy(data, list.begin(), sizeof(double) * size);
    }

    double &operator[](int index) { return this->data[index]; }
    const double &operator[](int index) const { return this->data[index]; }
    bool operator==(const GLVector<size> &rightVec)
    {
        for(int i = 0; i < size; ++i)
            if(rightVec[i] != this->data[i])
                return false;
        return true;
    }
    bool operator!=(const GLVector<size> &rightVec)
    {
        return !((*this)==rightVec);
    }
    GLVector<size> operator+(const GLVector<size> &rightVec)
    {
        GLVector<size> resultVec;
        for(int i = 0; i < size; ++i)
            resultVec[i] = this->data[i] + rightVec[i];
        return resultVec;
    }
    GLVector<size> operator-(const GLVector<size> &rightVec)
    {
        GLVector<size> resultVec;
        for(int i = 0; i < size; ++i)
            resultVec[i] = this->data[i] - rightVec[i];
        return resultVec;
    }
    double operator*(const GLVector<size> &rightVec)
    {
        double result = 0;
        size_type count = size > 3 ? 3 : size;
        for(int i = 0; i < count; ++i)
            result += (*this)[i] * rightVec[i];
        return result;
    }
    GLVector<size> operator*(const double &scal)
    {
        GLVector<size> thisVec = *this;
        for(int i = 0; i < size; ++i)
            thisVec[i] = thisVec[i] * scal;
        return thisVec;
    }
    GLVector<size> &operator*=(const double &scal)
    {
        for(int i = 0; i < size; ++i)
            (*this)[i] = (*this)[i] * scal;
        return (*this);
    }
    GLVector<size> &operator=(const GLVector<size> &rightVec)
    {
        for(int i = 0; i < size; ++i)
            (*this)[i] = rightVec[i];
        return (*this);

    }
    GLVector<size> &operator+=(const GLVector<size> &rightVec)
    {
        return (*this) = (*this) + rightVec;
    }
    GLVector<size> &operator-=(const GLVector<size> &rightVec)
    {
        return (*this) = (*this) - rightVec;
    }
    GLVector<size> operator^(const GLVector<size> &rightVec)
    {
        GLVector<size> result;
        if(size == 2)
            qFatal("GLVector<size>::operator^(): a vector composition is not possible in two-dimensional space");
        result[0] = (*this)[1] * rightVec[2] - (*this)[2] * rightVec[1];
        result[1] = (*this)[2] * rightVec[0] - (*this)[0] * rightVec[2];
        result[2] = (*this)[0] * rightVec[1] - (*this)[1] * rightVec[0];
        return result;
    }
    double length()
    {
        double l = 0;
        double len = size > 3 ? 3 : size;
        for(int i = 0; i < len; ++i)
            l += (*this)[i] * (*this)[i];
        return std::sqrt(l);
    }
    GLVector<size> normalize()
    {
        return (*this) * (1 / length());
    }
    //функция возвращает угол в радианах!
    double angle(GLVector<size> rightVec)
    {
        GLVector thisVec = normalize();
        GLVector right = rightVec.normalize();
        const GLVector axeRot(thisVec ^ right);
        if(!axeRot.isEmpty()) {
            return std::acos(thisVec * right);
        }
        return 0;
    }
    GLVector<size> &invert()
    {
        for(int i = 0; i < size; ++i)
            (*this)[i] *= (-1);
        return *this;
    }
    bool isEmpty() const
    {
        double len = size > 3 ? 3 : size;
        for(int i = 0; i < len; ++i)
            if(!(qFuzzyCompare((*this)[i], 0.0))) return false;
        return true;
    }
    double *toData() const { return data; }

private:
    double data[size];
};

} //namespace glmath

#endif // GLVECTOR_H
