#include <iostream>
#include <fstream>

#include "Vector.hpp"

int main(void)
{
	BaseVector<double> v1(10);
	
	for(int i = 0; i < v1.size(); ++i)
	{
		v1[i] = i;
	}
	
	for(int i = 0; i < v1.size(); ++i)
	{
		std::cout << v1[i] << std::endl;
	}
	
	SubVector<double> v2(v1,2,8);
	std::cout << std::endl;
	for (int i = 0; i < v2.size(); ++i)
	{
		std::cout << v2[i] << std::endl;
	}
	
	SubVector<double> v3(v2,2,4);
	std::cout << std::endl;
	for (int i = 0; i < v3.size(); ++i)
	{
		std::cout << v3[i] << std::endl;
	}
	
	return 0;

}



