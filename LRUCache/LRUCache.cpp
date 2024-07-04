#include<iostream>
#include<limits.h>
#include<math.h>
#include<vector>
#include <algorithm> 
#include<unordered_set>
#include <unordered_map>
using namespace std;
class LRUCache {
public:
    class Node{
        public:
            int key;
            int val;
            Node* next;
            Node* pre;
            Node(int key,int val){
                this->key=key;
                this->val=val;
            }
    };
    Node* head = new Node(-1, -1);
    Node* tail = new Node(-1, -1);
    int capacity;
    unordered_map<int,Node*> m;

    LRUCache(int capacity) {
        this->capacity=capacity;
        head->next=tail;
        tail->pre=head;
    }

    void addNode(Node* newNode){
        newNode->pre=head;
        newNode->next=head->next;
        head->next->pre=newNode;
        head->next=newNode;
    }

    void deleteNode(Node* node){
        node->pre->next=node->next;
        node->next->pre=node->pre;
    }
    
    int get(int key) {
        if(m.find(key)!=m.end()){
            Node* temp=m[key];
            m.erase(key);
            deleteNode(temp);
            addNode(temp);
            m[key]=head->next;
            return temp->val;
        }
        return -1;
    }
    
    void put(int key, int value) {
        if(m.find(key)!=m.end()){
            Node* temp=m[key];
            deleteNode(temp);
            m.erase(key);
        }
        if(m.size()==capacity){
            m.erase(tail->pre->key);
            deleteNode(tail -> pre);
        }
        addNode(new Node(key,value));
        m[key]=head->next;
    }
};
int main(){
    LRUCache* obj = new LRUCache(4);
    for(int i=1;i<4;i++) obj->put(i,i);
    cout<<obj->get(1);
    obj->put(5,5);
    obj->put(6,6);
    return 0;
}