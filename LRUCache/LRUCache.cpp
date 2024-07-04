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
    cout<<"Just For Fun";
    return 0;
}
/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */