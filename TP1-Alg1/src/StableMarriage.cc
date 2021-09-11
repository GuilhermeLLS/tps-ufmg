#include "../include/StableMarriage.hpp"

StableMarriage::StableMarriage(int healthCentersLength)
{
    this->matches = this->initializeMatchesMap(healthCentersLength);
    helper = new Helpers();
}

std::map<int, std::vector<int>> StableMarriage::getMatchesMap() {
    return this->matches;
}

std::map<int, std::vector<int>> StableMarriage::initializeMatchesMap(int healthCentersLength)
{
    std::map<int, std::vector<int>> matches;
    for (int i = 0; i < healthCentersLength; i++)
    {
        matches.insert(std::pair<int, std::vector<int>>(i, std::vector<int>()));
    }
    return matches;
}

bool StableMarriage::orderByAge(Person *personA, Person *personB)
{
    return personA->age == personB->age
               ? personA->id < personB->id
               : personA->age > personB->age;
}

void StableMarriage::createPreferenceList(std::vector<Person *> &people, std::vector<HealthCenter *> &healthCenters)
{
    std::sort(people.begin(), people.end(), orderByAge);
    for (Person *person : people)
    {
        person->preferenceList = this->helper->calcDistances(healthCenters, person->local);
    }
}

void StableMarriage::generateStableMatches(
    std::vector<HealthCenter *> healthCenters,
    std::vector<Person *> people)
{

  for (auto *personItem : people)
  {
    for (auto *orderedHealthCenter : personItem->preferenceList)
    {
      if (int(this->matches.at(orderedHealthCenter->id).size()) < healthCenters[orderedHealthCenter->id]->capacity)
      {
        this->matches.at(orderedHealthCenter->id).push_back(personItem->id);
        break;
      }
    }
  }
}