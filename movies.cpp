#include "movies.h"
#include <iostream>
#include <iomanip>

void Movies::addMovie(const std::string& name, double rating) {
    movieMap[name] = rating;
}

void Movies::printAllMovies() const {
    for (const auto& movie : movieMap) {
        std::cout << movie.first << ", " << std::fixed << std::setprecision(1) << movie.second << std::endl;
    }
}

void Movies::findHighestRatedMovie(const std::string& prefix) const {
    using PairType = std::pair<double, std::string>; // Rating, Movie Name
    std::priority_queue<PairType, std::vector<PairType>, std::less<PairType>> pq;

    for (const auto& movie : movieMap) {
        if (movie.first.find(prefix) == 0) { // Movie name starts with the prefix
            pq.push(std::make_pair(movie.second, movie.first));
        }
    }

    if (!pq.empty()) {
        auto highestRated = pq.top();
        std::cout << "Best movie with prefix " << prefix << " is: " << highestRated.second
                  << " with rating " << std::fixed << std::setprecision(1) << highestRated.first << std::endl;
    } else {
        std::cout << "No movies found with prefix " << prefix << std::endl;
    }
}
