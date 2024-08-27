// CS302 Fall 2024 Project 1: Music Library
// Zebulon Mcknight and Semilo Abiodun-Adeniyi
// August 27th, 2024
// This program reads in an unordered list of musicians, songs, and albums, 
// and neatly prints them organized alphabetically by artist name, with each 
// of that artists albums and songs printed below. 

#include <iostream>
#include <fstream>
#include <string> 
#include <map>
using namespace std; 

// Structures for organizing necessary data
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
	string temp = (to_string(time % 60));

	if (temp.size() < 2)
	{
		temp.insert(0, "0"); 
	} 
	
	formattedTime += temp; 

	return formattedTime; 
} 

// Converts underscores in spaces to strings
string convertToSpace(string &word){ // Semmy 8/25/2024 (12:45 PM)
	for(size_t i = 0; i < word.size(); i++){
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
	
	// Temporary variables to store unprocessed data
	// Genre is never used 
	string name1, time1, artist1, album1, genre, track1;
	
	ifstream fin; 
	fin.open(argv[1]); 
	
	// artists map will store an artists name as a string, and an Artist struct
	map <string, Artist> artists; 

	// READ IN LOOP
	while (fin>>name1>>time1>>artist1>>album1>>genre>>track1)
	{
		// Processing temporary variables and storing in permanent variables
		string name = convertToSpace(name1); 
		string artist = convertToSpace(artist1); 
		string album = convertToSpace(album1); 
		int time = timeToInt(time1); 
		int track = stoi(track1); 

		//ARTISTS
		// If an artist is not in the artists map, create an entry for that artist
		if (artists.find(artist) == artists.end())			
		{
			// Initializing artist struct 
			Artist artistStruct; 
			
			// Increment struct values
			artistStruct.nSongs = 1;
			artistStruct.time = 0 + time; 
			artistStruct.name = artist; 

			// Inserting artist
			artists.insert({artist, artistStruct});
		} 

		else 
		{
			// Given the artist struct already exists, increment its values 
			artists[artist].nSongs++; 
			artists[artist].time += time; 
		}
		
		//ALBUMS
		// If an album is not in an artists albums map, create an entry for that album
		if (artists[artist].albums.find(album) == artists[artist].albums.end())
		{
			// Initializing album struct
			Album albumStruct;
			
			// Incrementing struct values
			albumStruct.nSongs = 1; 
			albumStruct.time = 0 + time; 
			albumStruct.name = album; 
			
			// Inserting album struct
			artists[artist].albums.insert({album, albumStruct});  
		} 

		else 
		{
			// Incrementing struct values
			artists[artist].albums[album].nSongs++; 
			artists[artist].albums[album].time += time;  
		} 

		//SONGS	
		// Initialize a Song struct for ever song read in 
		Song songStruct; 

		// Assigning member values
		songStruct.title = name; 
		songStruct.time = time; 

		// Inserting song into the correct artist and album map
		artists[artist].albums[album].songs.insert({track, songStruct}); 

	}
	
	// Iterators 
	map <string, Artist>::iterator it1; // This iterator will loop through the artists map
	map <string, Album>::iterator it2; // This iterator will loop through each artists albums map
	map <int, Song>::iterator it3; // This iterator will loop through each albums songs map
	
	// PRINT OUT LOOP
	// CITATION::https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
	// For every artist
	for (it1 = artists.begin(); it1 != artists.end(); it1++)
	{
		//Printing artist, total number of songs, and total time by the artist
		cout<<it1 -> first<<": "<<it1 -> second.nSongs<<", "<<timeToString(it1 -> second.time)<<endl;
		
		// For every album by the current artist
		for (it2 = it1->second.albums.begin(); it2 != it1->second.albums.end(); it2++)
		{
			// Printing album name, number of songs and total time in album 
			cout<<"        "<<it2->first<<": "<<it2->second.nSongs<<", "<<timeToString(it2 -> second.time)<<endl;
			
			// For every song in the current album 
			for (it3 = it2->second.songs.begin(); it3 != it2->second.songs.end(); it3++)
			{
				//Printing track number, title, and time 
				cout<<"                "<<it3->first<<". "<<it3->second.title<<": "<<timeToString(it3->second.time)<<endl; 
			} 
		} 
	} 

	fin.close(); 

	return 0; 
} 
