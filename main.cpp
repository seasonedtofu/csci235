#include "RouteMap.hpp"

int main()
{
	/*
	City test;
	test.addNext("city1");
	test.addNext("city2");
	cout << test.canVisit("city1");
	cout << endl;
	*/

	/*
	RouteMap m;
	m.readMap("sample_map.txt");

	cout << m.getCity(0)->getName() << endl;

	for(auto h:m.cities)
		cout << h->getName();
	
	//for(auto h:m.adj_city)
	//	cout << h->getName() << " ";
	//cout << endl;
	
	cout << endl;
	*/

	RouteMap m;
	m.readMap("sample_map.txt");

	/*
	for(auto h:m.connected)
		cout << h->getName();
	cout << endl;
	*/

	//cout << m.getCity(0)->canVisit("Cairo") << endl;
	//m.getCity(0)->print_next_();
	m.isRoute(m.getCity(2),m.getCity(4));
	//cout << m.route.size() << endl;
	/*
	for(int i=0;i<m.route.size();i++)
	{
		cout << m.route.top()->getName();
		m.route.pop();
	}
	*/
}
