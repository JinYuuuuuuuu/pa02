#ifndef MOVIES_H
#define MOVIES_H

#include <string>
#include <map>
#include <queue>
#include <vector>
#include <functional>

using namespace std;

class Movies {
    struct MovieComparator {
        bool operator()(const pair<double, string>& a, const pair<double, string>& b) const {
            if (a.first == b.first) {
                return a.second > b.second;
            }
            return a.first < b.first;
        }
    };
    public:
        void addMovie(const string& name, double rating);
        void printAllMovies() const;
        pair<string, double> findAndPrintMoviesWithPrefix(const string& prefix) const;

    private:
        map<string, double> movieMap;
        mutable string lastPrefix;
        mutable map<string, double>::const_iterator lastPrefixStartIterator;
        mutable bool isLastPrefixInitialized = false;
};

#endif