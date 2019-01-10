#pragma once

//ceil() - 소수점 이하 올림
//floor() - 소수점 이하 버림
//round() - 소수점 이하 반올림

enum Intersection
{
	Outside,
	Inside,
	Intersect
};

class Math
{
public:
	static const float PI;
	static const float PI_2;
	static const float PI_DIV_2;
	static const float PI_DIV_4;
	static const float TO_RAD;
	static const float TO_DEG;

public:
	static const float ToRadian(const float& degree) { return degree * TO_RAD; }
	static const float ToDegree(const float& radian) { return radian * TO_DEG; }
	static const float Random(const float& min, const float& max);
	static const int Random(const int& min, const int& max);

	template <typename T>
	static const T Clamp(const T& x, const T& min, const T& max)
	{
		return x < min ? min : (x > max ? max : x);
	}

	template <typename T>
	static const T Abs(const T& value) { return value >= 0 ? value : -value; }

	template <typename T>
	static const T Max(const T& value1, const T& value2)
	{
		return value1 > value2 ? value1 : value2;
	}

	template <typename T>
	static const T Min(const T& value1, const T& value2)
	{
		return value1 < value2 ? value1 : value2;
	}
};