#include "Point.hpp"
#include "../System/Logger.hpp"

using namespace DevaFramework;


//Static Functions
float Point::distance(const Point &p1, const Point &p2)
{
    if(p1==p2) return 0;
    return sqrt(pow(sqrt(pow(fabs(p1.x - p2.x), 2) + pow(fabs(p1.y - p2.y), 2)), 2) + pow(fabs(p1.z - p2.z), 2));
}

float Point::dot_prod(const Point &p1, const Point &p2)
{
    return p1.x*p2.x + p1.y*p2.y + p1.z*p2.z;
}

const Point& Point::O()
{
    static const Point p(0, 0, 0, 1.0f);
    return p;
}

//Ctors
Point::Point()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1.0f;
}

Point::Point(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
};


//Compound assignment
Point& Point::operator*=(const Point &p)
{
    this->x *= p.x;
    this->y *= p.y;
    this->z *= p.z;
    return *this;
}

Point& Point::operator*=(float p)
{
    this->x *= p;
    this->y *= p;
    this->z *= p;
    return *this;
}

Point& Point::operator/=(const Point &p)
{
    this->x /= p.x;
    this->y /= p.y;
    this->z /= p.z;
    return *this;
}

Point& Point::operator/=(float p)
{
    this->x /= p;
    this->y /= p;
    this->z /= p;
    return *this;
}

Point& Point::operator+=(const Point &p)
{
    this->x += p.x;
    this->y += p.y;
    this->z += p.z;
    return *this;
}
Point& Point::operator+=(float p)
{
    this->x += p;
    this->y += p;
    this->z += p;
    return *this;
}
Point& Point::operator-=(const Point &p)
{
    this->x -= p.x;
    this->y -= p.y;
    this->z -= p.z;
    return *this;
}
Point& Point::operator-=(float p)
{
    this->x -= p;
    this->y -= p;
    this->z -= p;
    return *this;
}

//Arithmetic operations
const Point Point::operator*(const Point &p) const
{
    Point r = *this;
    r.x *= p.x;
    r.y *= p.y;
    r.z *= p.z;
    return r;
}

const Point Point::operator*(float p) const
{
    Point r = *this;
    r.x *= p;
    r.y *= p;
    r.z *= p;
    return r;
}

const Point Point::operator/(const Point &p) const
{
    Point r = *this;
    r.x /= p.x;
    r.y /= p.y;
    r.z /= p.z;
    return r;
}

const Point Point::operator/(float p) const
{
    Point r = *this;
    r.x /= p;
    r.y /= p;
    r.z /= p;
    return r;
}

const Point Point::operator+(const Point &p) const
{
    Point r = *this;
    r.x += p.x;
    r.y += p.y;
    r.z += p.z;
    return r;
}

const Point Point::operator+(float p) const
{
    Point r = *this;
    r.x += p;
    r.y += p;
    r.z += p;
    return r;
}

const Point Point::operator-(const Point &p) const
{
    Point r = *this;
    r.x -= p.x;
    r.y -= p.y;
    r.z -= p.z;
    return r;
}

const Point Point::operator-(float p) const
{
    Point r = *this;
    r.x -= p;
    r.y -= p;
    r.z -= p;
    return r;
}

Point const Point::operator-() const
{
    return Point(-x, -y, -z);
}

//Comparison
bool Point::operator==(const Point &p) const
{
    return fabs(this->x - p.x) < EPS && fabs(this->y - p.y) < EPS && fabs(this->z - p.z) < EPS;
}

bool Point::operator!=(const Point &p) const
{
    return !(*this==p);
}

//Misc
std::string Point::str() const
{
    std::string output;
    output += strm(x) + " ";
    output += strm(y) + " ";
    output += strm(z) + " ";
    output += strm(w);
    output += "\n";
    return output;
}

float Point::length() const
{
    return sqrt(pow(sqrt((x*x)+(y*y)), 2) + z*z);
}
