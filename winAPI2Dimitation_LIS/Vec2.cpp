#include "pch.h"
#include "Vec2.h"
//
//void normalize(Vec2& vec)
//{
//	double temp = sqrt((vec.x* vec.x)+ (vec.y* vec.y));
//	if (temp == 0)
//		return;
//	double x = vec.x / temp;
//	double y = vec.y / temp;
//	vec.x = x;
//	vec.y = y;
//}
//
//double distance(Vec2 left, Vec2 right)
//{
//	return sqrt(abs((left.x - right.x) * (left.x - right.x)) + abs((left.y - right.y) * (left.y - right.y)));
//}
//
//double getAngle(Vec2 vec)
//{
//	double temp = atan((vec.y / vec.x)) / RADIAN;
//	return temp;
//}
//
//double getAngle(Vec2 left, Vec2 right)
//{
//	return atan(-(right.y-left.y) / (right.x-left.x)) / RADIAN;
//}

Vec2& Vec2::normalized() 
{
	double temp = sqrt((this->x * this->x) + (this->y * this->y));
	if (temp == 0)
		return *this;
	double x = this->x / temp;
	double y = this->y / temp;
	this->x = x;
	this->y = y;
	return *this;
}

void Vec2::normalize(Vec2& vec)
{
	double temp = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (temp == 0)
		return;
	double x = vec.x / temp;
	double y = vec.y / temp;
	vec.x = x;
	vec.y = y;
}

double Vec2::distance(Vec2 left, Vec2 right)
{
	return sqrt(abs((left.x - right.x) * (left.x - right.x)) + abs((left.y - right.y) * (left.y - right.y)));
}

double Vec2::getAngle(Vec2 vec)
{
	return atan((vec.y / vec.x)) / RADIAN;
}

double Vec2::getAngle(Vec2 left, Vec2 right)
{
	return atan(-(right.y - left.y) / (right.x - left.x)) / RADIAN;
}

double Vec2::length()
{
	return sqrt((x * x) + (y * y));
}
