#ifndef STABLEMARRIAGE_HPP
#define STABLEMARRIAGE_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include "./Person.hpp"
#include "./HealthCenter.hpp"
#include "./Helpers.hpp"

class StableMarriage
{
private:
    std::map<int, std::vector<int>> matches;
    Helpers *helper;
    static std::map<int, std::vector<int>> initializeMatchesMap(int healthCentersLength);
    static bool orderByAge(Person *personA, Person *personB);
public:
    StableMarriage(int healthCentersLength);
    void createPreferenceList(
        std::vector<Person *> &people,
        std::vector<HealthCenter *> &healthCenters);
    void generateStableMatches(
        std::vector<HealthCenter *> healthCenters,
        std::vector<Person *> people);
    std::map<int, std::vector<int>> getMatchesMap();
};

#endif