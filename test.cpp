#include "LRUcache.hpp"
//#include "LRUcache.cpp"
using namespace lei;
int main()
{
	LRUcache<int,int> cache(3);
	cache.print();
	cache.put(1,2);
	//cache.print();
	cache.put(3,4);
	cache.put(4,5);
	cache.put(6,7);
	cache.put(7,8);
	cache.put(9,1000);
	cache.put(10,12);
	std::cout<<cache.get(6)<<std::endl;
	cache.print();
	std::cout<<cache.get(10)<<std::endl;	
	cache.print();
	std::cout<<cache.get(9)<<std::endl;
	cache.print();
	return 0;
}
