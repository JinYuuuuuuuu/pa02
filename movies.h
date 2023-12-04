#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <map>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

class Movies {
public:
    void addMovie(const string& name, double rating);
    void printAllMovies() const;
    pair<string, double> findAndPrintMoviesWithPrefix(const std::string& prefix) const;

private:
    map<string, double> movieMap;
};

#endif
