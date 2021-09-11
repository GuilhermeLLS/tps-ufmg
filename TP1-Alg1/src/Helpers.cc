#include "../include/Helpers.hpp"

Helpers::Helpers() {}

std::tuple<int, int, int> Helpers::parseLine(std::string line)
{
    std::regex regexz(" ");
    std::vector<std::string> list(std::sregex_token_iterator(line.begin(), line.end(), regexz, -1),
                                  std::sregex_token_iterator());

    return std::make_tuple(stoi(list[0]), stoi(list[1]), stoi(list[2]));
}

bool isHealthCenter(int iterator, int breakpoint) { return iterator < breakpoint + 1; }

std::tuple<
    std::vector<Person *>,
    std::vector<HealthCenter *>>
Helpers::readFile()
{
    std::string line;
    std::getline(std::cin, line);

    int healthCenterBreakpoint = stoi(line);
    int iterator = 0;

    std::vector<Person *> people;
    std::vector<HealthCenter *> healthCenters;
    int healthCenterIndexCounter = 0, personIndexCounter = 0;

    while (std::getline(std::cin, line))
    {
        iterator++;
        if (line.find(" ") == std::string::npos) continue;
        if (line.empty()) break;
        else
        {
            int data, xCoordinate, yCoordinate;
            std::tie(data, xCoordinate, yCoordinate) = this->parseLine(line);
            if (isHealthCenter(iterator, healthCenterBreakpoint + 1))
            {
                HealthCenter *auxHc = new HealthCenter();
                auxHc->capacity = data;
                auxHc->id = healthCenterIndexCounter;
                auxHc->relativeDistance = float(0);
                auxHc->local = Coordinates({x : xCoordinate, y : yCoordinate});
                healthCenters.push_back(auxHc);
                healthCenterIndexCounter++;
            }
            else
            {
                Person *auxP = new Person();
                auxP->age = data;
                auxP->id = personIndexCounter;
                auxP->local = Coordinates({x : xCoordinate, y : yCoordinate});
                people.push_back(auxP);
                personIndexCounter++;
            }
        }
    }
    return std::make_tuple(people, healthCenters);
}

bool Helpers::orderByDistance(HealthCenter *healthCenterA, HealthCenter *healthCenterB)
{
    return healthCenterA->relativeDistance == healthCenterB->relativeDistance
               ? healthCenterA->id < healthCenterB->id
               : healthCenterA->relativeDistance < healthCenterB->relativeDistance;
}

std::vector<HealthCenter *> Helpers::calcDistances(
    std::vector<HealthCenter *> &healthCenters,
    Coordinates personCoordinates)
{
    std::vector<HealthCenter *> preferenceList;
    float distance;
    for (HealthCenter *healthCenter : healthCenters)
    {
        distance = sqrt(pow((personCoordinates.x - healthCenter->local.x), 2) + pow((personCoordinates.y - healthCenter->local.y), 2));
        HealthCenter *aux = new HealthCenter();
        aux->capacity = healthCenter->capacity;
        aux->id = healthCenter->id;
        aux->local = healthCenter->local;
        aux->relativeDistance = distance;
        preferenceList.push_back(aux);
    }

    std::sort(preferenceList.begin(), preferenceList.end(), orderByDistance);
    return preferenceList;
}

void Helpers::printMap(std::map<int, std::vector<int>> map)
{
    for (auto &item : map)
    {
        if (item.second.size() == 0)
            continue;
        std::cout << item.first << std::endl;
        for (auto &itemValue : item.second)
        {
            std::cout << itemValue << " ";
        }
        std::cout << std::endl;
    }
}

void Helpers::clean(std::vector<Person *> &people, std::vector<HealthCenter *> &healthCenters)
{
    for (unsigned int i = 0; i < people.size(); ++i)
    {
        delete people[i];
    }
    for (unsigned int i = 0; i < healthCenters.size(); ++i)
    {
        delete healthCenters[i];
    }
}