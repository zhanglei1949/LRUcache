#include "LRUcache.h"
#include<assert.h>
#include<iostream>
namespace LRUcache
{
	template<typename key_t, typename value_t>
	LRUcache<key_t, value_t>::LRUcache(size_t size_)
	{
		assert(size_ > 0);
		std::cout<<"Initialize"<<endl;
		head = NULL;
		tail = NULL;
		maxSize = size_;
		size = 0;
	}
	template<typename key_t, typename value_t>
        void LRUcache<key_t, value_t>::print()
	{
		std::cout<<"LRUcache print"<<endl;
		if (size == 0) return ;
		//else print the items
		return ;
	}
	template<typename key_t, typename value_t>
	bool LRUcache<key_t, value_t>::setHead(Node<key_t, value_t> *node)
	{
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
		//check whether this the last node
		if (tail == node)[
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
		if (tail->prev == NULL) head = NULL;
		tail = tail->prev;
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
		
		Node<key_t, value_t> *tmp = new Node(key, value);
		//insert this node to the head
		//in failure return false;
		if (setHead(tmp)==false) return false;
		if (size == 1) tail = tmp;
		//update map
		m.insert(std::make_pair<key_t, Node<key_t, value_t> *>(key, tmp));
		print();
		return true;
        }
	template<typename key_t, typename value_t>
        bool LRUcache<key_t, value_t>::get(key_t key)
        {
		iter = m.find(key);
		if (iter == m.end()){
			return false;
		}
		else {
			Node<key_t, value_t> *tmp = iter->second;
			Node<key_t, value_t> *n = new Node<key_t,value_t>(tmp->key, tmp-value);
			if (removeNode(tmp)==false) return false;
			//in function remove, all data should be erased
			if (setHead(n)==false) return false;
			//update map
			m[key] = n;
			return true;
		}
        }
	template<typename key_t, typename value_t>
        void LRUcache<key_t, value_t>::print()
	{
		Node<key_t, value_t> tmp = head;
		while (tmp!=NULL){
			std::cout<<"< "<<tmp->key<<" , "<<tmp->value<<" > ;";
		}
		cout<<endl;
	}

}
