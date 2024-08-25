// CS302 Fall 2024 Project 1: Music Library
// Zebulon Mcknight and Semmy

#include <iostream>
#include <fstream>
#include <string> 
using namespace std; 

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr<<"usage: ./lib_info.cpp filename"<<endl; 
		return 1; 
	} 
	
	string line; 

	char *filename = argv[1];
	ifstream fin; 
	fin.open(filename); 

	while (fin>>line)
	{
		cout<<line<<endl; 
	}

	fin.close(); 

	return 0; 
} 
