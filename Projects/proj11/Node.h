// sect 14, 12/5/18, project 11
#pragma once

#include<iostream>
using std::ostream; using std::cout; using std::endl;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;


//
// Node
//
template<typename K, typename V>
struct Node {
  K first;
  V second;
  Node *next = nullptr;
  
  Node() = default;
  Node(K,V);
  Node(const Node&);
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n){
    //WRITE OPERATOR<< CODE HERE
    out << n.first << ':' << n.second; 
    return out;
  }
};

//WRITE NODE FUNCTIONS HERE
template<typename K, typename V> 
Node<K,V>::Node(const Node<K, V> &Node){ //copy Node
    first = Node.first;
    second = Node.second;
    next = Node.next;
}

template<typename K, typename V> //constructs Node
Node<K, V>::Node(K key, V val) {
  first = key;
  second = val;
  next = nullptr; 
}

template <typename K, typename V> 
bool Node<K,V>::operator==(const Node & comp_node) const{ 
    if(comp_node.first == this->first){
      return true;
    }else{
      return false;
    }
}
