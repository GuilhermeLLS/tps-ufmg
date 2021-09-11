#ifndef PERSON_HPP
#define PERSON_HPP

#include <iostream>
#include <vector>
#include "./Coordinates.hpp"
#include "./HealthCenter.hpp"

struct Person
{
  int age;
  int id;
  Coordinates local;
  std::vector<HealthCenter *> preferenceList;
};

#endif