// Fall'23
// Instructor: Diba Mirza
// Student name: Hechenjin Yu
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

/* Part3:
there are n movies in the dataset.
there are m prefixes specified in a given run of your program.
at most k movies begin with each prefix.
l is the maximum number of characters in a moview name
all n movies are already stored in your data structure.
all m prefixes are already stored in an array.

(a) Analyze the worst-case Big-O time complexity:
    Using movieMap.lower_bound to find lower and upper bounds has a complexity of O(log n) for each call.
    Total for finding the range is O(log n).
    Iterating over the movies within the found range is O(k) in the worst case, as up to k movies can match a prefix.
    nserting each of the k movies into the priority queue takes O(log k) time for each insertion.
    Total insertion time is O(k log k).
    opping each of the k movies from the priority queue also takes O(log k) time for each pop.
    Total extraction time is O(k log k).
    Combining the components, the time complexity for a single prefix is dominated by the priority queue operations:
    O(log n) + O(k log k).
    In the worst case, this becomes O(k log k).

    ./runMovies input_20_random.csv prefix_large.txt: Time taken: 0.08573 seconds
    ./runMovies input_100_random.csv prefix_large.txt: Time taken: 0.083951 seconds
    ./runMovies input_1000_random.csv prefix_large.txt: Time taken: 0.089056 seconds
    ./runMovies input_76920_random.csv prefix_large.txt: Time taken: 0.523198 seconds


(b) Analyze space complexity:
    Space Complexity Analysis:
    Space complexity for storing all n movies: O(n).
    Space complexity for storing all m prefixes: O(m).
    Transient space complexity for the priority queue in each function call: O(k).
    Final space complexity: O(n + m), dominated by the space for storing movies and prefixes.


(c) Algorithm Design Analysis:
    Designed for low time complexity: Primary focus was on reducing the time to find and sort movies.
    I tried to traverse all keys in map at first but did not pass the runtime test.
    Then I think about map are ordered and titles with the same prefixes are continuous,
    so it will be possible to use binary search to find the target and its neighbors.
    The largest space requirement is from storing n movies and m prefixes: O(n + m).
    Priority queue used transiently, not significantly adding to overall space complexity.
    Conclusion: The algorithm achieves its primary goal of low time complexity while maintaining a reasonable space complexity.
*/

bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}