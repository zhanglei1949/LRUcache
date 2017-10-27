test: test.o lru.o
	g++ -std=c++11 test.o lru.o -o test
test.o: test.cpp LRUcache.h
	g++ -std=c++11 -c test.cpp -o test.o
lru.o: LRUcache.h LRUcache.cpp
	g++ -std=c++11 -c LRUcache.cpp -o lru.o
clean:
	rm -rf *.o test
