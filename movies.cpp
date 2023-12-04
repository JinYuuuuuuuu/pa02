#include "movies.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

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
    auto lower = movieMap.lower_bound(prefix);
    string upperPrefix = prefix;
    ++upperPrefix[upperPrefix.length() - 1];
    auto upper = movieMap.lower_bound(upperPrefix);

    if (lower == movieMap.end()) {
        cout << "No movies found with prefix " << prefix << endl;
        return {"", -0.1};
    }

    pair<string, double> highestRatedMovie = {"", -0.1};

    // Use a vector to store movies for sorting
    vector<pair<double, string>> moviesWithPrefix;

    for (auto it = lower; it != upper; ++it) {
        if (it->second > highestRatedMovie.second) {
            highestRatedMovie = make_pair(it->first, it->second);
        }
        moviesWithPrefix.push_back(make_pair(it->second, it->first));
    }

    // Sorting the vector based on ratings (and then names if ratings are equal)
    sort(moviesWithPrefix.begin(), moviesWithPrefix.end(), [](const pair<double, string>& a, const pair<double, string>& b) {
        return a.first > b.first || (a.first == b.first && a.second < b.second);
    });

    // Print all movies with the prefix sorted by their ratings
    for (const auto& movie : moviesWithPrefix) {
        cout << movie.second << ", " << movie.first << endl;
    }

    cout << endl;

    return highestRatedMovie;
}
