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

void Movies::findHighestRatedMovie(const string& prefix) const {
    using PairType = pair<double, string>;
    priority_queue<PairType, vector<PairType>, less<PairType>> pq;

    for (const auto& movie : movieMap) {
        if (movie.first.find(prefix) == 0) { // Movie name starts with the prefix
            pq.push(make_pair(movie.second, movie.first));
        }
    }

    if (!pq.empty()) {
        auto highestRated = pq.top();
        cout << "Best movie with prefix " << prefix << " is: " << highestRated.second
            << " with rating " << highestRated.first << endl;
    } 
    else {
        cout << "No movies found with prefix " << prefix << endl;
    }
}
