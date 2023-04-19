#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
// include other libraries
#include <string>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        HASH_INDEX_T w[5] = {0};
				int cindex = k.size() - 1; // represent the current index we are at
				// calculate values for w
				for(int i = 4; i >= 0; i--) { // going from tail to head
					if(cindex - 5 <= 0) { // already reached the last string
					  HASH_INDEX_T temp_value = 0;
						for(int j = 0; j <= cindex; j++) {
							temp_value += pow_helper(36, cindex - j)*letterDigitToNumber( k[j] );
						}
						w[i] = temp_value;
					}
					else { // not the last string yet
					  HASH_INDEX_T temp_value = 0;
						for(int j = cindex - 5; j <= cindex; j++) {
							temp_value += pow_helper(36, cindex - j)*letterDigitToNumber( k[j] );
						}
						w[i] = temp_value;
					}
					cindex -= 6;
					if(cindex < 0) {break;}
				}
				// calculate h
				HASH_INDEX_T output = 0;
				for(int i = 0; i <= 4; i++) {
					output += w[i]*rValues[i];
				}
				return output;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
				if(letter >= '0' && letter <= '9') {
					return atoi(&letter) + 26; 
				}
				else if(letter >= 'a' && letter <= 'z') {
					return static_cast<int>(letter) - 97;
				}
				else { // letter is from 'A' to 'Z'
				  char temp = letter + 32;
					return static_cast<int>(temp) - 97;
				}
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }

		// helper function to calculate pow()
		HASH_INDEX_T pow_helper(HASH_INDEX_T base, HASH_INDEX_T exponent) const 
		{
			if(base == 0) {return 0;}
			if(exponent == 0) {return 1;}
			if(exponent == 1) {return base;}
			// --------------------
			int result = 1;
			while(exponent > 0) {
				if(exponent % 2 == 1) {
					result *= base;
				}
				base *= base;
				exponent = exponent / 2;
			}
			return result;
		}
};

#endif
