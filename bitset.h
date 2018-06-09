#ifndef _BITSET_H_
#define _BITSET_H_

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;
//#define WHOLE_PART_SUP(size) 

template <size_t size>
class Bitset{

	public:
		
		Bitset(){
			size_t realSize = (size%8==0)? size/8 : (size/8)+1;
			for(u_int i = 0; i < realSize; i++){
				numbers[i] = 0;
			}
		}

		bool test(size_t x){
			size_t quotient = x / 8;
			size_t remainder = x % 8;

			uint8_t k = ( numbers[x/8] >> (7 - x % 8) ) & 1;

			return k == 1;

		}

		bool all(){
			size_t n = this->realSize();

			for(uint i = 0; i < n; i++ ){

				uint nshifts = (i < n-1)? 0 : 7 - (this->maxValue() % 8);
				if( numbers[i] != (uint8_t)(0b11111111 << nshifts) )
					return false;
			}

			return true;	
		}

		bool any(){
			size_t n = this->realSize();

			for(uint i = 0; i < n-1; i++ ){
				if(numbers[i]) return true;
			}

			size_t remainder = this->maxValue() % 8;
			if( (numbers[n-1] >> (7-remainder) ) > 0 ) return true;

			return false;

		}

		void set(size_t x){
			if(this->outOfIndex(x)) throw;
			size_t quotient = x / 8;
			size_t remainder = x % 8;
			numbers[quotient] = (numbers[quotient] | 0b10000000 >> remainder);

		}



		void flip(size_t x){
			if(this->outOfIndex(x)) throw;

			size_t quotient = x/8;
			size_t remainder = x % 8;

			if(this->test(x)){
				numbers[quotient] = numbers[quotient] ^ (0b10000000 >> remainder);
			} else {
				this->set(x);
			}
		}

		string asString(){

			vector<char> init(size, '0');
			string digits(begin(init), end(init));
			size_t n = this->realSize();

			for(uint i = 0; i < n; i++ ){
				uint ndigits = (i < n-1)? 8 : (this->maxValue() % 8)+1;
				byteAsString(digits, numbers[i], i*8, ndigits);
			}

			return digits;

		}

		void byteAsString(string &s, uint8_t k, size_t start, size_t ndigits){

			for(uint i = 0; i < ndigits; i++){
				if((k >> 7-i) & 1){
					s[start+i] = '1';
				}
			}

		}	

		bool outOfIndex(size_t x){

			return (x < 0 or x > this->maxValue())? true:false;
		}
		size_t realSize() { return (size%8==0)? size/8 : (size/8)+1; }
		size_t byteIndex(size_t x) { return x/8; }	
		size_t remainder(size_t x) { return x % 8; }
		size_t maxValue() { return max; }
		


		
	private: 
		size_t max = size - 1;
		uint8_t* numbers = new uint8_t[(size%8==0)? size/8 : (size/8)+1];

};

#endif