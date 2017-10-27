test: test.o lru.o
	g++ test.o lru.o -o test
test.o: test.cpp LRUcache.h
	g++ -c test.cpp -o test.o
lru.o: LRUcache.h LRUcache.cpp
	g++ -c LRUcache.cpp -o lru.o
clean:
	rm -rf *.o test
