// Spring'22
// Instructor: Diba Mirza
// Student name: 
#include "movies.h"
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
using namespace std;

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
    
    Movies movies;
    vector<pair<string, pair<string, double>>> highestRatedMovies;
    // Create an object of a STL data-structure to store all the movies

    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
        movies.addMovie(movieName, movieRating);

    }

    movieFile.close();

    if (argc == 2){
        movies.printAllMovies();
        return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }

    for (const auto& prefix : prefixes) {
        auto highestRatedMovie = movies.findAndPrintMoviesWithPrefix(prefix);
        highestRatedMovies.emplace_back(prefix, highestRatedMovie);
    }

    // Print out the summary of highest-rated movies for each prefix
    for (const auto& item : highestRatedMovies) {
        const auto& prefix = item.first;
        const auto& movie = item.second;
        if (!movie.first.empty()) {
            cout << "Best movie with prefix " << prefix << " is " << movie.first
                      << " with rating " << movie.second << endl;
        }
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}