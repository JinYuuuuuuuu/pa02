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
    pair<string, double> highestRatedMovie = {"", 0.0};

    using PairType = pair<double, string>;
    priority_queue<PairType, vector<PairType>, less<PairType>> pq;

    for (const auto& movie : movieMap) {
        if (movie.first.find(prefix) == 0) {
            pq.push(make_pair(movie.second, movie.first));
            if (movie.second > highestRatedMovie.second) {
                highestRatedMovie = movie;
            }
        }
    }

    if (pq.empty()) {
        cout << "No movies found with prefix " << prefix << endl << endl;
        return highestRatedMovie;
    }

    while (!pq.empty()) {
        auto movie = pq.top();
        pq.pop();
        cout << movie.second << ", " << fixed << setprecision(1) << movie.first << endl;
    }

    cout << endl;

    return highestRatedMovie;
}