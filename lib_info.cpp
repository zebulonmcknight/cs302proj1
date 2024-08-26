// CS302 Fall 2024 Project 1: Music Library
// Zebulon Mcknight and Semmy

#include <iostream>
#include <fstream>
#include <string> 
#include <map> 
using namespace std; 

struct Song
{
	string title; 
	int time; 
}; 

struct Album
{
	map <int, Song> songs;
	string name; 
	int time; 
	int nSongs; 
}; 

struct Artist
{
	map <string, Album> albums; 
	string name; 
	int time; 
	int nSongs; 
};  

// Converts a string representing time of format "MM:SS" to an integer number of seconds
int timeToInt(string formattedTime)
{
	int time = 0; 

	string minutes = formattedTime.substr(0,2); 
	string seconds = formattedTime.substr(3,4); 

	time += stoi(minutes) * 60; 
	time += stoi(seconds); 

	return time; 	
} 

// Converts an integer representing seconds to a string in format "MM:SS"
string timeToString(int time)
{
	string formattedTime; 

	formattedTime.append(to_string(time / 60)); 
	formattedTime += ':'; 
	formattedTime.append(to_string(time % 60)); 

	return formattedTime; 
} 

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr<<"usage: ./lib_info.cpp filename"<<endl; 
		return 1; 
	}  

	return 0; 
} 
