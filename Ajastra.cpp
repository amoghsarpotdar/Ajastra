// Ajastra.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "defs.h"
#include "Init.h"

int main(){
	init _initializer;
	_initializer.AllInit();
	int index = 0;
	
	for(index=0; index<BRD_SQ_NUM;++index)
	{
		if (index % 10 == 0)
			std::cout << "\n";
		
		printf("%5d", Sq120ToSq64[index]);
	}
	
	printf("\n");
	printf("\n");

	for (index = 0; index < 64; ++index)
	{
		if (index % 8 == 0)
			printf("\n");

		printf("%5d", Sq64ToSq120[index]);
	}
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
