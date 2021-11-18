#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{
   
   protected: 
   map<int,Node*> mp; //map the key to the node in the linked list
   int cp;  //capacity
   Node* tail; // double linked list tail pointer
   Node* head; // double linked list head pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function

};
class LRUCache:public Cache{
    public:
    LRUCache(int);
    void set(int, int);
    int get(int);
};
LRUCache::LRUCache(int a){
    cp = a;
    head = new Node(0,0);
    tail = new Node(0,0);
    head->prev=NULL;
    head->next=tail;
    tail->prev=head;
    tail->next=NULL;
}//Initialised a doubly linked list by using parameterized constructor
void LRUCache::set(int k, int val){
       Node *x;
       if(head->next==tail){
           //If linked list is empty
           x = new Node(head,tail,k,val);
           head->next = x;
           tail->prev = x;
           mp.insert({k,x});--cp;
       }
       else if(head->next!=tail&&cp!=0&&mp.count(k)==0){
           //if ll is not empty but key is not there
           x = new Node(head,head->next,k,val);
           head->next->prev = x;
           head->next = x;
           mp.insert({k,x});--cp; 
       }
       else if(head->next!=tail&&cp!=0&&mp.count(k)>0){
           //if ll is not empty but key-value pair exists
           x = new Node(mp[k]->prev,mp[k]->next,k,val);
           delete mp[k];
           mp[k] = x;
       }
       else if(head->next!=tail&&cp==0&&mp.count(k)==0)
       {
           // if ll is full and key-val pair doesnt exit
           //deleting last node
           Node *temp = new Node(NULL,tail->prev,0,0);
           tail->prev->prev->next = tail;
           tail->prev = tail->prev->prev;
           mp.erase(temp->next->key);
           delete temp->next;
           delete temp;
           //deletion done
           //Now insertion of new node begins
           x = new Node(head,head->next,k,val);
           head->next->prev = x;
           head->next = x;
           mp.insert({k,x});    
           //insertion done       
       }
       else if(head->next!=tail&&cp==0&&mp.count(k)!=0){
           //if ll is full but key-val pair exists
           //This case amounts to replacement
           x = new Node(mp[k]->prev,mp[k]->next,k,val);
           delete mp[k];
           mp[k] = x;
       }
}
int LRUCache::get(int k)
{
    if(mp.count(k)==0){
        return -1;
    }    
    else 
    return mp[k]->value;
}
int main() {
       int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
