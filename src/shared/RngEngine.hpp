#pragma once

#include <cstddef>
#include <random>
#include <type_traits>

class Rng
{
	std::mt19937 rng;
public:
	inline Rng() : rng(std::random_device{}()) {}

	inline Rng(size_t seed) : rng(std::random_device{}())
	{
		rng.seed(seed);
	}

	template<typename T>
	inline T RandInt(T min, T max)
	{
		static_assert(std::is_integral_v<T>, "not a integral");
		std::uniform_int_distribution<T> dist(min, max);

		return dist(rng);
	}

	template<typename T, typename U>
	inline auto RandFloat(T min, U max)
	{
		using Common = std::common_type_t<T, U>;
		using Real = std::conditional_t<std::is_floating_point_v<Common>, Common, double>;
		std::uniform_real_distribution<Real> dist(static_cast<Real>(min), static_cast<Real>(max));

		return dist(rng);
	}

	inline bool RandBool(float chance = 0.5f)
	{
		std::bernoulli_distribution dist(chance);

		return dist(rng);
	}
};

namespace rng
{
	inline thread_local Rng main;

	template<typename T>
	inline T RandInt(T min, T max)
	{
		return main.RandInt(min, max);
	}

	template<typename T>
	inline T RandFloat(T min, T max)
	{
		return main.RandFloat(min, max);
	}

	inline bool RandBool(float chance = 0.5f)
	{
		return main.RandBool(chance);
	}
}