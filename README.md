# LRUcache
A implementation of LRU cache
# Remarks
I want to implement a LRU cache template, supporting k-v style data, at first I put the declaration in LRUcache.h and the implementation in LRUcache.cpp, but it doesn't work, and the compilier complains that the methods are not defined. After googling, I found out that the methods of templete class can not separated from its declaratoin. So I put all code in ```LRUcache.hpp```, and it works.

# How to use it
Just include ```hpp``` file in your project. Please check ```test.cpp```.
