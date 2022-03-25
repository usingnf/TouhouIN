#pragma once
#include <math.h>

class Vec2
{
public:
	double x;
	double y;

	Vec2()
	{
		x = 0;
		y = 0;
	}

	Vec2(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	Vec2(const Vec2& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
	}
	
	Vec2& normalized();
	static void normalize(Vec2& vec);
	static double distance(Vec2 left, Vec2 right);
	static double getAngle(Vec2 vec);
	static double getAngle(Vec2 left, Vec2 right);

	double length();

	bool operator==(const Vec2& vec) const
	{
		if (this->x == vec.x && this->y == vec.y)
			return true;
		return false;
	}

	bool operator!=(const Vec2& vec) const
	{
		return !(*this == vec);
	}

	Vec2& operator=(const Vec2& vec)
	{
		this->x = vec.x;
		this->y = vec.y;
		return *this;
	}
	Vec2& operator+=(const Vec2& vec)
	{
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}
	Vec2 operator+(const Vec2& vec)
	{
		return Vec2(this->x + vec.x, this->y + vec.y);
	}
	Vec2 operator-(const Vec2& vec)
	{
		return Vec2(this->x - vec.x, this->y - vec.y);
	}

	template<typename T>
	Vec2 operator*(const T value)
	{
		return Vec2(x * value, y * value);
	}
	template<typename T>
	Vec2 operator/(const T value)
	{

		return Vec2(x / value, y / value);
	}

};