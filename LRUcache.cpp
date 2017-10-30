#include "LRUcache.h"
#include<assert.h>
#include<iostream>
namespace lei
{
	template<typename key_t, typename value_t>
	LRUcache<key_t, value_t>::LRUcache(size_t size_)
	{
		assert(size_ > 0);
		std::cout<<"Initialize"<<std::endl;
		head = NULL;
		tail = NULL;
		maxSize = size_;
		size = 0;
	}
	template<typename key_t, typename value_t>
	bool LRUcache<key_t, value_t>::setHead(Node<key_t, value_t> *node)
	{
		if (head==NULL){
			head = node;
			tail = node;
			//head->pre and tail->next is already NULL
			size += 1;
			return true;
		}
		head->prev = node;
		node->next = head;
		head = node;
		head->prev = NULL;
		size += 1;
		return true;
	}
	template<typename key_t, typename value_t>
        bool LRUcache<key_t, value_t>::removeNode(Node<key_t, value_t> *node)
        {
		if (size == 0||tail==NULL|| node==NULL) return false;
		//check whether this the last node
		if (tail == node){
			return removeLastNode();
		}
		node->next->prev = node->prev;
		node->prev->next = node->next;
		//release the space;
		delete node;
		size -= 1;
		return true;
        }
	template<typename key_t, typename value_t>
        bool LRUcache<key_t, value_t>::removeLastNode()
        {
		Node<key_t, value_t> *tmp = tail;
		if (tail->prev == NULL){
			head = NULL;
			tail = NULL;
			size -= 1;
			delete tmp;
			return true;
		};
		tail = tail->prev;
		size -= 1;
		delete tmp;
		return removeNode(tmp);
        }
	template<typename key_t, typename value_t>
        bool LRUcache<key_t, value_t>::put(key_t key, value_t value)
        {
		iter = m.find(key);
		if (iter != m.end()) return false;
		//first check whether this key already exists
		if (size == maxSize){
			//remove the least recent used node;
			removeLastNode();
			//size -= 1 done in removeNode
		}
		
		Node<key_t, value_t> *tmp = new Node<key_t,value_t>(key, value);
		//insert this node to the head
		//in failure return false;
		if (setHead(tmp)==false) return false;
		//update map
		m.insert(std::make_pair<key_t, Node<key_t, value_t> *>(key, tmp));
		print();
		return true;
        }
	template<typename key_t, typename value_t>
        value_t LRUcache<key_t, value_t>::get(key_t key)
        {
		iter = m.find(key);
		if (iter == m.end()){
			return false;
		}
		else {
			Node<key_t, value_t> *tmp = iter->second;
			Node<key_t, value_t> *n = new Node<key_t,value_t>(tmp->key, tmp->value);
			if (removeNode(tmp)==false) return false;
			//in function remove, all data should be erased
			asset(setHead(n)==true);
			//update map
			m[key] = n;
			return n->value;
		}
        }
	template<typename key_t, typename value_t>
        void LRUcache<key_t, value_t>::print()
	{
		Node<key_t, value_t> tmp = head;
		while (tmp!=NULL){
			std::cout<<"< "<<tmp->key<<" , "<<tmp->value<<" > ;";
		}
		std::cout<<std::endl;
	}

}
