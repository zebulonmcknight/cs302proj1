// CS302 Fall 2024 Project 1: Music Library
// Zebulon Mcknight and Semmy

#include <iostream>
#include <fstream>
#include <string> 
#include <map>
#include <set> 
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
	string temp = (to_string(time % 60));

	if (temp.size() < 2)
	{
		temp.insert(0, "0"); 
	} 
	
	formattedTime += temp; 

	return formattedTime; 
} 

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

	string name1, time1, artist1, album1, genre, track1;
	ifstream fin; 
	fin.open(argv[1]); 
	
	map <string, Artist> artists; 

	while (fin>>name1>>time1>>artist1>>album1>>genre>>track1)
	{
		string name = convertToSpace(name1); 
		string artist = convertToSpace(artist1); 
		string album = convertToSpace(album1); 
		int time = timeToInt(time1); 
		int track = stoi(track1); 

		//ARTISTS
		if (artists.find(artist) == artists.end())			
		{
			Artist artistStruct; 
			//cout<<"New Artist"<<" "<<artist<<endl;

			artistStruct.nSongs = 1;
			artistStruct.time = 0 + time; 
			artistStruct.name = artist; 

			artists.insert({artist, artistStruct});
		} 

		else 
		{
			//cout<<"Old Artist"<<" "<<artist<<endl;

			artists[artist].nSongs++; 
			artists[artist].time += time; 
		}
		
		//ALBUMS
		if (artists[artist].albums.find(album) == artists[artist].albums.end())
		{
			Album albumStruct;

			albumStruct.nSongs = 1; 
			albumStruct.time = 0 + time; 
			albumStruct.name = album; 

			artists[artist].albums.insert({album, albumStruct}); 

			//cout<<"     New Album"<<" "<<album<<endl; 
		} 

		else 
		{
			artists[artist].albums[album].nSongs++; 
			artists[artist].albums[album].time += time; 
			//cout<<"     Old Album"<<" "<<album<<endl; 
		} 

		//SONGS	
		Song songStruct; 

		songStruct.title = name; 
		songStruct.time = time; 

		artists[artist].albums[album].songs.insert({track, songStruct}); 

	}
	
	map <string, Artist>::iterator it1;
	map <string, Album>::iterator it2; 
	map <int, Song>::iterator it3; 

	//https://stackoverflow.com/questions/26281979/how-do-you-loop-through-a-stdmap
	for (it1 = artists.begin(); it1 != artists.end(); it1++)
	{
		cout<<it1 -> first<<": "<<it1 -> second.nSongs<<", "<<timeToString(it1 -> second.time)<<endl;
		
		for (it2 = it1->second.albums.begin(); it2 != it1->second.albums.end(); it2++)
		{
			cout<<"        "<<it2->first<<": "<<it2->second.nSongs<<", "<<timeToString(it2 -> second.time)<<endl;

			for (it3 = it2->second.songs.begin(); it3 != it2->second.songs.end(); it3++)
			{
				cout<<"                "<<it3->first<<". "<<it3->second.title<<": "<<timeToString(it3->second.time)<<endl; 
			} 
		} 
	} 

	fin.close(); 

	return 0; 
} 
