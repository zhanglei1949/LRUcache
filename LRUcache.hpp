
#include<assert.h>
#include<iostream>
#include<unordered_map>
namespace lei
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
        LRUcache(size_t size_=10);
        ~LRUcache()
	{
	};
        bool put(key_t key, value_t value); //put success or failed
value_t get(key_t key); //get success or failed?
        int getMissCount();
        void print();
    private:
        int size;
        int maxSize;
        Node<key_t,value_t> *head, *tail; //head node and tail node
        int count; // count the times of misses
        std::unordered_map<key_t, Node<key_t, value_t> *> m; // map a key to the node;
        typename std::unordered_map<key_t, Node<key_t, value_t> *>::iterator iter;
        //need 'typename' here to make sure that this is a declaration of variable rather than a type
        //vector<Node<key_t, value_t> *> emptyEntries; // store the address of current empty addresses;
        //void print(); 
        bool setHead(Node<key_t, value_t> *node);
        bool removeNode(Node<key_t, value_t> *node);
        bool removeLastNode();
        };
}


//now the implementation

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
		m[node->key] = NULL;
		node->next->prev = node->prev;
                //if node === head, then prev is null
		if (node != head)node->prev->next = node->next;
                else head = node->next;
		//release the space;
                delete node;
                size -= 1;
                return true;
        }
        template<typename key_t, typename value_t>
        bool LRUcache<key_t, value_t>::removeLastNode()
        {
		std::cout<<"remove tail node"<<std::endl;
                Node<key_t, value_t> *tmp = tail;
                m[tmp->key] = NULL;
		if (tail->prev == NULL){
                        head = NULL;
                        tail = NULL;
                }
                else {
			tail = tail->prev;
                	tail->next = NULL;
		}
		size -= 1;
                delete tmp;
		return true;
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
                //std::pair<key_t, Node<key_t, value_t> *> pair = std::make_pair<key_t, Node<key_t, value_t> *>(key, tmp);
                //m.insert(pair);
                m[key] = tmp;
		print();
                return true;
        }
	template<typename key_t, typename value_t>
        value_t LRUcache<key_t, value_t>::get(key_t key)
        {
                iter = m.find(key);
                if (iter == m.end() || iter->second == NULL){
                        std::cout<<"key "<<key<<" doesn't exist"<<std::endl;
			return -1;
                }
                else {
                        Node<key_t, value_t> *tmp = iter->second;
                        Node<key_t, value_t> *n = new Node<key_t,value_t>(tmp->key, tmp->value);
                        assert(removeNode(tmp)==true);
                        //in function remove, all data should be erased
                        assert(setHead(n)==true);
                        //update map
                        m[key] = n;
                        return n->value;
                }
        }
        template<typename key_t, typename value_t>
        void LRUcache<key_t, value_t>::print()
        {
                Node<key_t, value_t>* tmp = head;
               	std::cout<<size<<"\t elements:";
		while (tmp!=NULL){
                        std::cout<<"< "<<tmp->key<<" , "<<tmp->value<<" > \t";
			tmp = tmp->next;
                }
                std::cout<<std::endl;
		//again from tail
		tmp = tail;
		std::cout<<size<<"\t elements:";
                while (tmp!=NULL){
                        std::cout<<"< "<<tmp->key<<" , "<<tmp->value<<" > \t";
                        tmp = tmp->prev;
                }
                std::cout<<std::endl;

        }

}
