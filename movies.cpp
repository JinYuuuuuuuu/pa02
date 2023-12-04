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

std::pair<std::string, double> Movies::findAndPrintMoviesWithPrefix(const std::string& prefix) const {
    using PairType = std::pair<double, std::string>; // Define PairType here
    std::priority_queue<PairType, std::vector<PairType>, MovieComparator> pq;

    if (movieMap.empty()) {
        std::cout << "No movies found with prefix " << prefix << std::endl;
        return {"", -0.1};
    }

    auto lower = movieMap.lower_bound(prefix);
    std::string upperPrefix = prefix;
    ++upperPrefix[upperPrefix.length() - 1]; // Increment the last character of the prefix
    auto upper = movieMap.lower_bound(upperPrefix);

    if (lower == movieMap.end()) {
        std::cout << "No movies found with prefix " << prefix << std::endl;
        return {"", -0.1};
    }

    std::pair<std::string, double> highestRatedMovie = {"", -0.1};

    for (auto it = lower; it != upper; ++it) {
        pq.push(make_pair(it->second, it->first));
        if (it->second > highestRatedMovie.second) {
            highestRatedMovie = *it;
        }
    }

    if (pq.empty()) {
        std::cout << "No movies found with prefix " << prefix << std::endl;
        return highestRatedMovie;
    }

    while (!pq.empty()) {
        auto movie = pq.top();
        pq.pop();
        std::cout << movie.second << ", " << movie.first << std::endl;
    }

    std::cout << std::endl;

    return highestRatedMovie;
}
