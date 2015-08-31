#ifndef MATRICES_H
#define MATRICES_H

#include <string>

namespace DevaFramework
{

struct Point;

struct Matrix
{
    ///Basic operation to matrix conversions
    static Matrix getScaleMatrix(const Point &p);
    static Matrix getRotationMatrix(float angle, char matrix);
    static Matrix getTranslationMatrix(const Point &p);

    ///The matrix
    float m[4][4];

    ///Constructor
    Matrix();
    Matrix(float a[4][4]);
    Matrix(float i0j0, float i0j1, float i0j2, float i0j3,
           float i1j0, float i1j1, float i1j2, float i1j3,
           float i2j0, float i2j1, float i2j2, float i2j3,
           float i3j0, float i3j1, float i3j2, float i3j3);

    Matrix(const Matrix &mat);
    Matrix(Matrix&& m);

    Matrix& operator=(const Matrix &mat);
    Matrix& operator=(Matrix &&mat);

    Matrix operator*(const Matrix &mat) const;
    Point operator*(const Point &p) const;

    ///Easy access
    float& operator()(int i, int j);

    const float* operator()();

    std::string str() const;
};

}

#endif // MATRIX_H
