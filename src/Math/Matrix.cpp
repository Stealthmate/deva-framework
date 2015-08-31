#include "Matrix.hpp"
#include "../System/Logger.hpp"

#include "Point.hpp"

using namespace DevaFramework;

const double M_PI = 3.1415;

Matrix Matrix::getScaleMatrix(const Point &p)
{
    float m[4][4]
    {
        { p.x, 0.0, 0.0, 0.0 },
        { 0.0, p.y, 0.0, 0.0 },
        { 0.0, 0.0, p.z, 0.0 },
        { 0.0, 0.0, 0.0, 1.0 }
    };
    return Matrix(m);
}

Matrix Matrix::getRotationMatrix(float angle, char axis)
{
    angle=angle*M_PI/180.0;
    switch(axis)
    {
    case 1 : ///X-axis
    {
        float m[4][4] =
        {
            { 1.0,                0.0,                 0.0, 0.0 },
            { 0.0, (float) cos(angle), -(float) sin(angle), 0.0 },
            { 0.0, (float) sin(angle),  (float) cos(angle), 0.0 },
            { 0.0,                0.0,                 0.0, 1.0 }
        };
        return Matrix(m);
    }
    break;
    case 2 : ///Y-axis
    {
        float m[4][4] =
        {
            { (float) cos(angle), 0.0,  - (float) sin(angle), 0.0 },
            {                0.0, 1.0,                   0.0, 0.0 },
            { (float) sin(angle), 0.0,    (float) cos(angle), 0.0 },
            {                0.0, 0.0,                  0.0,  1.0 }
        };
        return Matrix(m);
    }
    break;
    case 3 : ///Z-axis
    {
        float m[4][4] =
        {
            { (float) cos(angle), -(float) sin(angle), 0.0, 0.0 },
            { (float) sin(angle),  (float) cos(angle), 0.0, 0.0 },
            {                0.0,         0.0,         1.0, 0.0 },
            {                0.0,         0.0,         0.0, 1.0 }
        };
        return Matrix(m);
    }
    break;
    default :
    {
        float m[4][4] =
        {
            { 1.0, 0.0, 0.0, 0.0 },
            { 0.0, 1.0, 0.0, 0.0 },
            { 0.0, 0.0, 1.0, 0.0 },
            { 0.0, 0.0, 0.0, 1.0 }
        };
        return Matrix(m);
    }
    }

}

Matrix Matrix::getTranslationMatrix(const Point &p)
{
    float m[4][4] =
    {
        { 1.0, 0.0, 0.0, p.x },
        { 0.0, 1.0, 0.0, p.y },
        { 0.0, 0.0, 1.0, p.z },
        { 0.0, 0.0, 0.0, 1.0 }
    };
    return Matrix(m);
}

Matrix Matrix::operator*(const Matrix &mat) const
{
    Matrix t = Matrix(*this);
    Matrix res(t);
    for(int i=0;i <= 3; i++)
    {
        for(int j=0; j<=3; j++)
        {
            res.m[i][j] = 0;
            for(int k=0; k<=3 ;k++)
            {
                res.m[i][j] += (t.m[i][k] * mat.m[k][j]);
            }
        }
    }

    return res;
}

Point Matrix::operator*(const Point &p) const
{
    Point res;
    res.x = (m[0][0] * p.x) + (m[0][1] * p.y) + (m[0][2] * p.z) + (m[0][3] * p.w);
    res.y = (m[1][0] * p.x) + (m[1][1] * p.y) + (m[1][2] * p.z) + (m[1][3] * p.w);
    res.z = (m[2][0] * p.x) + (m[2][1] * p.y) + (m[2][2] * p.z) + (m[2][3] * p.w);
    res.w = (m[3][0] * p.x) + (m[3][1] * p.y) + (m[3][2] * p.z) + (m[3][3] * p.w);
    return res;
}

Matrix::Matrix()
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++) m[i][j] = 0.f;
    m[0][0] = 1.f;
    m[1][1] = 1.f;
    m[2][2] = 1.f;
    m[3][3] = 1.f;
}

Matrix::Matrix(float a[4][4])
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++) m[i][j] = a[i][j];
}

Matrix::Matrix(float i0j0, float i0j1, float i0j2, float i0j3,
       float i1j0, float i1j1, float i1j2, float i1j3,
       float i2j0, float i2j1, float i2j2, float i2j3,
       float i3j0, float i3j1, float i3j2, float i3j3)
{
    m[0][0] = i0j0;
    m[0][1] = i0j1;
    m[0][2] = i0j2;
    m[0][3] = i0j3;

    m[1][0] = i1j0;
    m[1][1] = i1j1;
    m[1][2] = i1j2;
    m[1][3] = i1j3;

    m[2][0] = i2j0;
    m[2][1] = i2j1;
    m[2][2] = i2j2;
    m[2][3] = i2j3;

    m[3][0] = i3j0;
    m[3][1] = i3j1;
    m[3][2] = i3j2;
    m[3][3] = i3j3;
}

Matrix::Matrix(const Matrix &mat)
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++) m[i][j] = mat.m[i][j];
}

Matrix::Matrix(Matrix &&mat)
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++) m[i][j] = mat.m[i][j];
}

Matrix& Matrix::operator=(const Matrix &mat)
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++)
            this->m[i][j] = mat.m[i][j];
    return *this;
}

Matrix& Matrix::operator=(Matrix &&mat)
{
    for(auto i=0; i<=3; i++) for(auto j=0; j<=3; j++)
            this->m[i][j] = mat.m[i][j];
    return *this;
}

float& Matrix::operator()(int i, int j)
{
    return m[i][j];
}

const float* Matrix::operator()()
{
    return &m[0][0];
}

std::string Matrix::str() const
{
    std::string output = "\n";
    for(auto i=0; i<=3; i++)
    {
        for(auto j=0; j<=3; j++)
        {
            output += strm(m[i][j]);
            output += " ";
        }
        output += "\n";
    }
    return output;
}
