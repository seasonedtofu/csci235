#ifndef CITY_HPP
#define CITY_HPP

#include <iostream>
#include <list>
#include <iterator>
#include <string>
#include <vector>
using namespace std;

class City
{
public:
	City();
	City(string name);
	//returns name of city
	string getName() const;
	//if this city was visited, return true
	bool wasVisited();
	//if visited, set visited true
	void setVisited();
	//set name
	void setName(string name);
private:
	string city_name_;
	bool visited;
};

#endif