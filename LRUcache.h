#ifndef LRUCACHE_H_INCLUDED
#define LRUCACHE_H_INCLUDED

#include<iostream>
#include<unordered_map>
namespace LRUcache
{
    //The linked list
    template<typename key_t, typename value_t>
    struct Node
    {
        key_t key;
        value_t value;
	Node *next;
	Node *prev;
	Node(key_t k, value_t v, Node *n=NULL, Node *p=NULL)
	{
		key = k;
		value = v;
		next = n;
		prev = p;
	}
	Node()
	{
		next = NULL;
		prev = NULL;
	}
    };


    template<typename key_t, typename value_t>
    class LRUcache
    {
    public:
	LRUcache(size_t size=10);
	~LRUcache();
	bool put(key_t key, value_t value); //put success or failed
	value_t get(key_t key); //get success or failed?
	int getMissCount();
    private:
	int size;
	int maxSize;
	Node<key_t,value_t> *head, *tail; //head node and tail node
	int count; // count the times of misses
	std::unordered_map<key_t, Node<key_t, value_t> *> m; // map a key to the node;
	typename std::unordered_map<key_t, Node<key_t, value_t> *>::iterator iter;
	//need 'typename' here to make sure that this is a declaration of variable rather than a type
	//vector<Node<key_t, value_t> *> emptyEntries; // store the address of current empty addresses;
	void print(); 
	bool setHead(Node<key_t, value_t> *node);
	bool remove(Node<key_t, value_t> *node);
    };
}

#endif // LRUCACHE_H_INCLUDED
