#pragma once

#include <random>

namespace rng
{
	inline thread_local std::random_device rng_d;
	inline thread_local std::mt19937 rng_g(rng_d());

	inline int RandInt(int min, int max)
	{
		std::uniform_int_distribution<> dist(min, max);

		return dist(rng_g);
	}

	inline float RandFloat(float min, float max)
	{
		std::uniform_real_distribution<> dist(min, max);

		return dist(rng_g);
	}

	inline bool RandBool(float chance = 0.5f)
	{
		std::bernoulli_distribution dist(chance);

		return dist(rng_g);
	}
}