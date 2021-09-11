#ifndef HEALTHCENTER_HPP
#define HEALTHCENTER_HPP

#include <iostream>
#include "./Coordinates.hpp"

struct HealthCenter
{
  int capacity;
  int id;
  float relativeDistance;
  Coordinates local;
};

#endif