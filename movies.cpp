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
    using PairType = pair<double, string>;
    priority_queue<PairType, vector<PairType>, MovieComparator> pq;

    // Start from the last upper bound if initialized, else start from lower_bound
    auto lower = isLastUpperBoundInitialized ? lastUpperBound : movieMap.lower_bound(prefix);
    string upperPrefix = prefix;
    ++upperPrefix[upperPrefix.length() - 1];
    auto upper = movieMap.lower_bound(upperPrefix);

    // Update last upper bound for the next call
    lastUpperBound = upper;
    isLastUpperBoundInitialized = true;

    pair<string, double> highestRatedMovie = {"", -0.1};

    for (auto it = lower; it != upper; ++it) {
        pq.push(make_pair(it->second, it->first));
        if (it->second > highestRatedMovie.second) {
            highestRatedMovie = *it;
        }
    }

    if (pq.empty()) {
        cout << "No movies found with prefix " << prefix << endl;
        return highestRatedMovie;
    }

    while (!pq.empty()) {
        auto movie = pq.top();
        pq.pop();
        cout << movie.second << ", " << movie.first << endl;
    }

    cout << endl;

    return highestRatedMovie;
}