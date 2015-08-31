#include "Vector.hpp"

using namespace DevaFramework;

Vector::Vector()
{
	x = 0;
	y = 0;
}
Vector::Vector(float x, float  y)
{
	this->x = x;
	this->y = y;
}

Vector& Vector::operator*=(const Vector &p)
{
	*this = *this * p;
	return *this;
}
Vector& Vector::operator*=(const float &p)
{
	*this = *this * p;
	return *this;
}

Vector& Vector::operator/=(const Vector &p)
{
	*this = *this / p;
	return *this;
}
Vector& Vector::operator/=(const float p)
{
	*this = *this / p;
	return *this;
}
Vector& Vector::operator+=(const Vector &p)
{
	*this = *this + p;
	return *this;
}
Vector& Vector::operator+=(const float p)
{
	*this = *this + p;
	return *this;
}
Vector& Vector::operator-=(const Vector &p)
{
	*this = *this - p;
	return *this;
}
Vector& Vector::operator-=(const float p)
{
	*this = *this - p;
	return *this;
}

const Vector Vector::operator*(const Vector &p) const
{
	return Vector(x*p.x, y*p.y);
}
const Vector Vector::operator*(const float p) const
{
	return Vector(x*p, y*p);
}
const Vector Vector::operator/(const Vector &p) const
{
	return Vector(x / p.x, y / p.y);
}
const Vector Vector::operator/(const float p) const
{
	return Vector(x / p, y / p);
}
const Vector Vector::operator+(const Vector &p) const
{
	return Vector(x + p.x, y + p.y);
}
const Vector Vector::operator+(const float p) const
{
	return Vector(x + p, y + p);
}
const Vector Vector::operator-(const Vector &p) const
{
	return Vector(x - p.x, y - p.y);
}
const Vector Vector::operator-(const float p) const
{
	return Vector(x - p, y - p);
}


const Vector Vector::operator-() const
{
	return Vector(-this->x, -this->y);
}


bool Vector::operator==(const Vector &p) const
{
	return fabs(x - p.x) <= EPS && fabs(y - p.y) <= EPS;
}

bool Vector::operator!=(const Vector &p) const
{
	return !operator==(p);
}

std::string Vector::str() const
{
	return "Vector: " + strm(x) + strm(y);
}