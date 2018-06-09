#include <iostream>
#include "bitset.h"

using namespace std;


int main(){
	size_t size = 19;
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


	cout << "Creating a bitset of 250 MB: ";
	Bitset<2000000000> big;

	big.asString();

	
	for(uint i = 0; i < 2000000000; i++){
		big.set(i);
	}
	if(not big.all()) cout << "WRONG!!" << endl;
	cout << "Bitset created and tested correctly!!!" << endl;
	








	return 0;
}