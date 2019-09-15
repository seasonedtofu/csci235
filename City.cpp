#include "City.hpp"

City::City()
{
	visited=false;
}

City::City(string name)
{
	city_name_=name;
	visited=false;
}

//returns name of city
string City::getName() const
{
	return city_name_;
}

//if this city was visited, return true, else return false
bool City::wasVisited()
{
	return visited;
}

//if visited, set visited true
void City::setVisited()
{
	visited=true;
}

//sets city_name=name
void City::setName(string name)
{
	city_name_=name;
}