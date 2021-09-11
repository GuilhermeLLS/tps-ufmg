#ifndef HELPERS_HPP
#define HELPERS_HPP

#include <iostream>
#include <tuple>
#include <fstream>
#include <regex>
#include <algorithm>
#include <string>
#include <map>
#include <math.h>
#include <vector>
#include "./Person.hpp"
#include "./HealthCenter.hpp"
#include "./Coordinates.hpp"

class Helpers
{
private:
    static bool orderByDistance(HealthCenter *healthCenterA, HealthCenter *healthCenterB);

public:
    Helpers();
    std::tuple<int, int, int> parseLine(std::string line);
    std::tuple<std::vector<Person *>, std::vector<HealthCenter *>> readFile();
    std::vector<HealthCenter *> calcDistances(std::vector<HealthCenter *> &healthCenters, Coordinates personCoordinates);
    void printMap(std::map<int, std::vector<int>> map);
    void clean(std::vector<Person *> &people, std::vector<HealthCenter *> &healthCenters);
};

#endif