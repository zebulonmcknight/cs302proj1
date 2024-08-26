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
	string minutes = "", seconds = ""; 

	for (size_t i = 0; i < formattedTime.size(); i++)
	{
		if (formattedTime[i] == ':')
		{
			seconds = formattedTime.substr(i+1, 2); 
			break; 
		} 

		minutes += formattedTime[i];  
	} 

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

string convertToSpace(string word){ // Semmy 8/25/2024 (12:45 PM)
	for(int i = 0; i < word.size(); i++){
		if(word[i] == '_'){
			word[i] = ' ';
		}
	}
	return word;
}


int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		cerr<<"usage: ./lib_info.cpp filename"<<endl; 
		return 1; 
	}

	string name, time, artist, album, genre, track;
	ifstream fin; 
	fin.open(argv[1]); 
 
	while (fin>>name>>time>>artist>>album>>genre>>track)
	{
		cout<<time<<"::"<<timeToInt(time)<<endl; 
	} 

	return 0; 
} 
