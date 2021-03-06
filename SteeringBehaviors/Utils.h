#pragma once
#include <cmath>
#include <ctime>
#include <cstdlib>
#include "SFML\Graphics.hpp"

#define PI 3.14159265359
#define DEGREES_PER_RADIAN	57.29577951f
#define MIN(a,b)    (((a) < (b)) ? (a) : (b))
#define MAX(a,b)	(((a) > (b)) ? (a) : (b))

namespace utils
{
	static void RandSeed()
	{
		std::srand(std::time(0));
	}

	static inline const float randflt(float max = 1)
	{
		return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / max));
	}

	static float Dot(const sf::Vector2f &a, const sf::Vector2f &b)
	{
		return a.x*b.x + a.y*b.y;
	}

	const static float VectorLenght(const sf::Vector2f& p)
	{
		return std::sqrtf(std::powf(p.x, 2) + std::powf(p.y, 2));
	}

	const static float Distance(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return std::sqrtf(std::powf(p2.x - p1.x, 2) + std::powf(p2.y - p1.y, 2));
	}

	static sf::Vector2f VectorNormalize(const sf::Vector2f& p)
	{
		float lenght = VectorLenght(p);
		float x = p.x / lenght;
		float y = p.y / lenght;

		return sf::Vector2f(x, y);
	}

	static void CLAMPVECTORLENGTH(sf::Vector2f& value, float floor, float ceiling)
	{
		float vecLength = VectorLenght(value);
		float adjust = -1.0f;
		if (vecLength < floor)
			adjust = floor;
		else if (vecLength > ceiling)
			adjust = ceiling;

		if (adjust != -1.0f)
		{
			value = VectorNormalize(value);
			value *= adjust;
		}
	}
}