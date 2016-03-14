#pragma once
#include <cmath>
#include "SFML\Graphics.hpp"

#define PI 3.14159265359
#define DEGREES_PER_RADIAN	57.29577951f

namespace utils
{
	const static float VectorLenght(const sf::Vector2f& p)
	{
		return std::sqrtf(std::powf(p.x, 2) + std::powf(p.y, 2));
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