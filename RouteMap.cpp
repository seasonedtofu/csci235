#include "RouteMap.hpp"


/**
@param input_file_name of a csv file representing a route map where the first
 line is a comma-separated list of city names, and the remainder is a
 comma-separated list of city-pairs of the form A-B, indicating that B
 is adjacent to A (i.e. there is an arrow in the map going from A to B)
@post this depends on your design, the input data representing the map must
 have been stored. Adjacent cities must be stored and explored in the
 same order in which they are read from the input file
**/
bool RouteMap::readMap(std::string input_file_name)
{
	ifstream fin(input_file_name);
	string input;

	while(getline(fin,input))
	{
		stringstream info(input);
		string city, this_city, next_city;

		//read first line
		while(getline(info,city,','))
		{
			City* store_city = new City(city);
			cities.push_back(store_city);
		}

		//read second line
		while(getline(fin, this_city,'-')&&getline(fin,next_city,','))
		{
			City* city_from;
			City* city_connected;

			/*connect the city travelling from (this_city/city_from) to city in
			 first list of cities by giving address to it*/
			for(int i = 0; i<cities.size();i++){ 
				if(getCity(i)->getName() == this_city){
					city_from = getCity(i);
					break;
				}
			}
			connected.push_back(city_from); /*add to 2nd list for connected cities*/

			/*connect the city travelling to (next_city/city_connected) to city in
			 first list of cities by giving address to it*/
			for(int i = 0; i<cities.size();i++){
				if(getCity(i)->getName() == next_city){
					city_connected = getCity(i);
					break;
				}
			}
			connected.push_back(city_connected); /*add to 2nd list for connected cities*/
		}
	}
}

/**
@return a pointer to the city found at position, where
 0 <= position <= n-1, and n is the number of cities,
 and cities are stored in the same order in which they appear
 in the input file
**/
City* RouteMap::getCity(size_t position)
{
	if(int(position)<cities.size())
	{
		auto answer=cities.begin(); 
		advance(answer,position); //advances through each element in cities list until position is earched
		return(*answer); //return the city in specified position
	}
	else
	{
		cout << "getCity() called with empty list or invalid position" << endl;
		return nullptr;
	}
}

/**
@return true if there is a route from origin to destination, false otherwise
@post if a route is found from origin to destination, it will print it to
 standard output in the form “ORIGIN -> ... -> DESTINATION\n”
**/
bool RouteMap::isRoute(City* origin, City* destination)
{
	route.push(origin);
	route.top()->setVisited();

	/* if you can visit destination from the origin without having to find a route, print */
	if(canVisit(origin,destination)) 
	{
		route.push(destination); //add destination to stack
		stack<City*> reverse; //2nd stack to reverse so you can print in order
		while(!route.empty()) //pop from route stack after adding to reverse stack 
		{
			reverse.push(route.top());
			route.pop();
		}

		while(!reverse.empty()) //print out the reverse stack so cities are printed in order
		{
			cout << reverse.top()->getName();
			reverse.pop();
				if(!reverse.empty())
				cout << " -> ";
		}

		cout << endl;
		return true;
	}
	
	/* if top of stack is destination, meaning route is found successfully */
	string end = destination->getName();
	if( route.top()->getName() == destination->getName() )
	{
		stack<City*> reverse; //2nd stack to reverse so you can print in order
		while(!route.empty()) //pop from route stack after adding to reverse stack
		{
			reverse.push(route.top());
			route.pop();
		}

		while(!reverse.empty()) //print out the reverse stack so cities are printed in order
		{
			cout << reverse.top()->getName();
			reverse.pop();
			if(!reverse.empty())
				cout << " -> ";
		}

		cout << endl;
		return true;
	}	

	/* if route is not completed yet, destination is not on top of stack, continue
	   finding a route
	*/
	for(int i=0;i<connected.size();i=i+2) //looking at 2nd list for cities you can travel from->to
	{
		//route.top()->setVisited(); //set origin visited
		auto answer=connected.begin();
		auto answer2=connected.begin();
		advance(answer,i);
		advance(answer2,i+1);

		/* looking at list 2, if city from is same as top and the city you can visit was not visited */
		if((*answer)->getName()==route.top()->getName() && (*answer2)->wasVisited()!=true)
		{
			if(isRoute(*answer2,destination)) /* recursive with param city to and destination */
				return true; 
		}
	}

	route.pop(); //if no way to get to next city, pop stack and return false
	return false;
}

/**
@return true if you can visit the city from->to, false otherwise
@post if true, prints out the city from and city to in the format of:
"FROM -> TO"
**/
bool RouteMap::canVisit(City* from, City* to)
{
	for(int i=0;i<connected.size();i=i+2)
	{
		auto answer=connected.begin();
		auto answer2=connected.begin();
		advance(answer,i);
		advance(answer2,i+1);
		if((*answer)->getName()==from->getName() && ((*answer2)->getName())==to->getName())
			return true;
	}
	return false;
	
}