#ifndef POINT_H
#define POINT_H
#include<math.h>
#include<iostream>

#include "Config.hpp"

namespace DevaFramework
{

struct Matrix;

/// \brief Represents a Point in a 2-dimensional Cartesian plane.
struct Point
{
    ///Returns the distance between Point p1 and Point p2.
    static float distance(const Point &p1, const Point &p2);
    ///Returns the dot product of the vectors given by the Points p1 and p2.
    static float dot_prod(const Point &p1, const Point &p2);

    ///Returns the origin of the cartesian plane, i.e. Point O(0, 0, 0).
    static const Point& O();

    ///The X coordinate of the Point.
    float x;
    ///The Y coordinate of the Point.
    float y;
    ///The Z coordinate of the Point.
    float z;
    ///The W of the Point.
    float w;

    ///Initializes to the origin, O(0, 0, 0).
    Point();
    ///Initializes to a Point P(x, y, z, w)
    Point(float x, float y, float z = 0.0, float w = 0.0);

	Point(const Point &p) = default;
	Point& operator=(const Point &p) = default;

    ///Arithmetic operators. All of these perform calculations on all 4 values of the point.
    Point& operator*=(const Point &p);
    Point& operator*=(float p);
    Point& operator/=(const Point &p);
    Point& operator/=(float p);
    Point& operator+=(const Point &p);
    Point& operator+=(float p);
    Point& operator-=(const Point &p);
    Point& operator-=(float p);

    const Point operator*(const Point &p) const;
    const Point operator*(float p) const;
    const Point operator/(const Point &p) const;
    const Point operator/(float p) const;
    const Point operator+(const Point &p) const;
    const Point operator+(float p) const;
    const Point operator-(const Point &p) const;
    const Point operator-(float p) const;

    ///Returns a point with all 4 coordinates inverted.
    const Point operator-() const;

    ///Returns \c TRUE if both of the coordinates of <B>@e p</B> are equal to the coordinates of <B>this</B>, and \c FALSE otherwise.
    bool operator==(const Point &p) const;
    ///Returns \c TRUE if either of the coordinates of <B>@e p</B> is <B>NOT</B> equal to the coordinates of <B>this</B>, and false otherwise.
    bool operator!=(const Point &p) const;

    ///Returns a string representation
    std::string str() const;

    ///Returns the length of the segment OP, where O is the origin (0, 0) and P is <B>this</B>
    float length() const;
};

typedef Point Vector;

}

#endif // POINT_H
