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

    auto lower = movieMap.lower_bound(prefix);
    if (isLastPrefixInitialized && prefix.find(lastPrefix) == 0) {
        // If the current prefix is an extension of the last one,
        // start from the last prefix's first movie
        lower = lastPrefixStartIterator;
    }
    
    string upperPrefix = prefix;
    ++upperPrefix[upperPrefix.length() - 1];
    auto upper = movieMap.lower_bound(upperPrefix);

    // Update for the next call
    lastPrefix = prefix;
    lastPrefixStartIterator = lower;
    isLastPrefixInitialized = true;

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