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

#include <vector>
#include <algorithm>

std::pair<std::string, double> Movies::findAndPrintMoviesWithPrefix(const std::string& prefix) const {
    std::vector<std::pair<double, std::string>> matchingMovies;
    std::pair<std::string, double> highestRatedMovie = {"", -1};

    // Collect movies that match the prefix
    for (const auto& movie : movieMap) {
        if (movie.first.find(prefix) == 0) {
            matchingMovies.emplace_back(movie.second, movie.first);
            if (movie.second > highestRatedMovie.second) {
                highestRatedMovie = movie;
            }
        }
    }

    // Check if no movies were found
    if (matchingMovies.empty()) {
        std::cout << "No movies found with prefix " << prefix << std::endl;
        return highestRatedMovie;
    }

    // Sort the vector in descending order of ratings, 
    // and in case of a tie, sort alphabetically by movie names
    std::sort(matchingMovies.begin(), matchingMovies.end(), 
        [](const std::pair<double, std::string>& a, const std::pair<double, std::string>& b) {
            if (a.first == b.first) {
                return a.second < b.second; // Sort alphabetically for ties
            }
            return a.first > b.first; // Sort by descending ratings
        });

    // Print the sorted movies
    for (const auto& movie : matchingMovies) {
        std::cout << movie.second << ", " << movie.first << std::endl;
    }

    std::cout << std::endl;

    return highestRatedMovie;
}
