#include "movies.h"
#include <iostream>
#include <iomanip>

using namespace std;

void Movies::addMovie(const string& name, double rating) {
    movieMap[name] = rating;
}

void Movies::printAllMovies() const {
    for (const auto& movie : movieMap) {
        cout << movie.first << ", " << movie.second << endl;
    }
}

pair<string, double> Movies::findAndPrintMoviesWithPrefix(const string& prefix) const {
    pair<string, double> highestRatedMovie = {"", 0.0}; // Pair to hold the highest-rated movie

    for (const auto& movie : movieMap) {
        if (movie.first.find(prefix) == 0) { // Movie name starts with the prefix
            cout << movie.first << ", " << movie.second << endl;
            if (movie.second > highestRatedMovie.second) {
                highestRatedMovie = movie;
            }
        }
    }

    if (highestRatedMovie.first.empty()) {
        std::cout << "No movies found with prefix " << prefix << endl << endl;
    }

    cout << endl;

    return highestRatedMovie;
}
