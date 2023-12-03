#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <map>
#include <queue>
#include <vector>
#include <functional>

class Movies {
public:
    void addMovie(const std::string& name, double rating);
    void printAllMovies() const;
    void findHighestRatedMovie(const std::string& prefix) const;

private:
    std::map<std::string, double> movieMap; // Map for storing movies
};

#endif // MOVIES_H
