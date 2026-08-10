#include "RngEngine.hpp"
#include <cstdint>
#include <cstring>

#include "iostream"

namespace aii 
{
	float MutateFloat(float chance, uint64_t bid) 
	{
    	uint32_t float_bits;
    	std::memcpy(&float_bits, &chance, sizeof(float_bits));

    	uint64_t hash = (static_cast<uint64_t>(float_bits) << 32) ^ bid;

    	hash ^= hash >> 30;
    	hash *= 0xbf58476d1ce4e5b9ULL;
    	hash ^= hash >> 27;
    	hash *= 0x94d049bb133111ebULL;
    	hash ^= hash >> 31;

    	uint32_t random_bits = static_cast<uint32_t>(hash & 0x00FFFFFFu);
    
    	return static_cast<float>(random_bits) / 16777215.0f;
	}

	bool RandBoolMut(float chance, uint64_t bid) 
	{
    	float ch = MutateFloat(chance, bid);

		//std::cout << ch << "\n";
		
		return rng::RandBool(ch);
	}
}