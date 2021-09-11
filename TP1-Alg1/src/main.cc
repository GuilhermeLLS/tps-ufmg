#include <iostream>
#include "../include/Person.hpp"
#include "../include/HealthCenter.hpp"
#include "../include/Coordinates.hpp"
#include "../include/Helpers.hpp"
#include "../include/StableMarriage.hpp"

int main(int argc, char *argv[])
{
  std::vector<Person *> people;
  std::vector<HealthCenter *> healthCenters;
  Helpers *helper = new Helpers();
  std::tie(people, healthCenters) = helper->readFile();

  StableMarriage *minister = new StableMarriage(healthCenters.size());
  minister->createPreferenceList(people, healthCenters);
  minister->generateStableMatches(healthCenters, people);
  
  helper->printMap(minister->getMatchesMap());
  helper->clean(people, healthCenters);
  return 0;
}