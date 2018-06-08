#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

template <u_long size>
class Bitset{

	public:
		
		Bitset(){
			u_long realSize = (size%8==0)? size/8 : (size/8)+1;
			for(u_int i = 0; i < realSize; i++){
				numbers[i] = 0;
			}
		}

		bool test(u_long x){
			u_long quotient = x / 8;
			u_long remainder = x % 8;

			uint8_t k = ( numbers[x/8] >> (7 - x % 8) ) & 1;

			return k == 1;

		}

		bool all(){
			u_long n = this->realSize();

			for(uint i = 0; i < n; i++ ){

				uint nshifts = (i < n-1)? 0 : 7 - (this->maxValue() % 8);
				if( numbers[i] != (uint8_t)(0b11111111 << nshifts) )
					return false;
			}

			return true;	
		}

		bool any(){
			u_long n = this->realSize();

			for(uint i = 0; i < n-1; i++ ){
				if(numbers[i]) return true;
			}

			u_long remainder = this->maxValue() % 8;
			if( (numbers[n-1] >> (7-remainder) ) > 0 ) return true;

			return false;

		}

		void set(u_long x){
			if(this->outOfIndex(x)) throw;
			u_long quotient = x / 8;
			u_long remainder = x % 8;
			numbers[quotient] = (numbers[quotient] | 0b10000000 >> remainder);

		}



		void flip(u_long x){
			if(this->outOfIndex(x)) throw;

			u_long quotient = x/8;
			u_long remainder = x % 8;

			if(this->test(x)){
				numbers[quotient] = numbers[quotient] ^ (0b10000000 >> remainder);
			} else {
				this->set(x);
			}
		}

		string asString(){

			vector<char> init(size, '0');
			string digits(begin(init), end(init));
			u_long n = this->realSize();

			for(uint i = 0; i < n; i++ ){
				uint ndigits = (i < n-1)? 8 : (this->maxValue() % 8)+1;
				byteAsString(digits, numbers[i], i*8, ndigits);
			}

			return digits;

		}

		void byteAsString(string &s, uint8_t k, u_long start, u_long ndigits){

			for(uint i = 0; i < ndigits; i++){
				if((k >> 7-i) & 1){
					s[start+i] = '1';
				}
			}

		}	

		bool outOfIndex(u_long x){

			return (x < 0 or x > this->maxValue())? true:false;
		}
		u_long realSize() { return (size%8==0)? size/8 : (size/8)+1; }
		u_long byteIndex(u_long x) { return x/8; }	
		u_long remainder(u_long x) { return x % 8; }
		u_long maxValue() { return max; }
		


		
	private: 
		u_long max = size - 1;
		uint8_t* numbers = new uint8_t[(size%8==0)? size/8 : (size/8)+1];

};



int main(){
	u_long size = 19;
	Bitset<19> b; // Numbers from: 0 to: 18
	cout << "Size: " << size << ", max value: " << b.maxValue() << ", real size: " << b.realSize() << endl;
	cout << "............................................" << endl;

	cout << "Setting number 4: ";
	if(b.any()) cout<< "WRONG!!" << endl;
	b.set(4);
	if(not b.any()) cout<< "WRONG!!" << endl;
	cout << b.asString() << endl;

	cout << "Setting number 18: ";
	b.set(18);
	cout << b.asString() << endl;


	cout << "	- Testing elements set....";
	b.set(15);
	b.set(18);
	b.set(16);
	b.set(17);
	b.set(0);
	b.set(7);
	b.set(8);
	b.set(12);
	if(not b.test(15)) cout<< "WRONG!!" << endl;
	if(not b.test(16)) cout<< "WRONG!!" << endl;
	if(not b.test(18)) cout<< "WRONG!!" << endl;
	if(not b.test(17)) cout<< "WRONG!!" << endl;
	if(not b.test(4))  cout<< "WRONG!!" << endl;
	cout << "........Finished" << endl;


	cout << "	- Testing elements not set....";
	if(b.test(19)) cout<< "WRONG!!" << endl;
	if(b.test(3))  cout<< "WRONG!!" << endl;
	cout << "....Finished" << endl;



	cout << "	- Testing all elements set....";
	if(b.all()) cout << "WRONG!!" << endl;
	for(uint i = 0; i < 19; i++){
		b.set(i);
	}
	if(not b.all()) cout << "WRONG!!" << endl;

	for(uint i = 0; i < 19; i++){
		if(not b.test(i)) cout << "WRONG!!" << endl;
	}
	cout << "....Finished" << endl;

	cout << "All elementes setted: " << b.asString() << endl;


	cout << "Testing flip bit  7th: ";
	b.flip(7);
	cout << b.asString() << endl;
	cout << "Testing flip bit 18th: ";
	b.flip(18);
	cout << b.asString() << endl;
	cout << "Testing flip bit 15th: ";
	b.flip(15);
	cout << b.asString() << endl;

	cout << "--------Finished testing small bitset---------" << endl;


	/*
	cout << "Creating a bitset of 250 MB: ";
	Bitset<2000000000> big;

	big.asString();

	
	for(uint i = 0; i < 2000000000; i++){
		big.set(i);
	}
	if(not big.all()) cout << "WRONG!!" << endl;
	cout << "Bitset created and tested correctly!!!" << endl;
	*/








	return 0;
}