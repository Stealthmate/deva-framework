#ifndef DEVA_FRAMEWORK_MATH_VECTOR_H
#define DEVA_FRAMEWORK_MATH_VECTOR_H

#include "Config.hpp"

namespace DevaFramework
{
	struct Vector
	{
		float x, y;

		DEVA_API Vector();
		DEVA_API Vector(float x, float  y);

		DEVA_API Vector(Vector const &vec) = default;
		DEVA_API Vector& operator=(Vector const &vec) = default;

		///Arithmetic operators. All of these perform calculations on all 4 values of the Vector.
		DEVA_API Vector& operator*=(Vector const &p);
		DEVA_API Vector& operator*=(const float &p);
		DEVA_API Vector& operator/=(Vector const &p);
		DEVA_API Vector& operator/=(const float p);
		DEVA_API Vector& operator+=(Vector const &p);
		DEVA_API Vector& operator+=(const float p);
		DEVA_API Vector& operator-=(Vector const &p);
		DEVA_API Vector& operator-=(const float p);

		DEVA_API Vector const operator*(Vector const &p) const;
		DEVA_API Vector const operator*(const float p) const;
		DEVA_API Vector const operator/(Vector const &p) const;
		DEVA_API Vector const operator/(const float p) const;
		DEVA_API Vector const operator+(Vector const &p) const;
		DEVA_API Vector const operator+(const float p) const;
		DEVA_API Vector const operator-(Vector const &p) const;
		DEVA_API Vector const operator-(const float p) const;

		///Returns a Vector with all 4 coordinates inverted.
		DEVA_API Vector const operator-() const;

		///Returns \c TRUE if all the coordinates of <B>@e p</B> are equal 
		///to the coordinates of <B>this</B>, and \c FALSE otherwise.
		DEVA_API bool operator==(Vector const &p) const;
		///Returns \c TRUE if either of the coordinates of <B>@e p</B> is <B>NOT</B> equal 
		///to the coordinates of <B>this</B>, and false otherwise.
		DEVA_API bool operator!=(Vector const &p) const;

		///Returns a string representation
		DEVA_API std::string str() const;

	};
}

#endif //DEVA_FRAMEWORK_MATH_VECTOR_H