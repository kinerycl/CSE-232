// sect 14, 11/28/18, project 10
#pragma once

#include"vector.h"
//#include"proj10_bimap.h"
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
using std::sort; using std::lower_bound; using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;

template<typename K, typename V>
struct Node {
public:
  K first;
  V second;
  // constructors
  Node() = default;
  Node(K, V);
  // the rest
  bool operator<(const Node&) const;
  bool operator==(const Node&) const;
  friend ostream& operator<<(ostream &out, const Node &n) { // print Node
    out << n.first << ':' << n.second;
    return out;
  }
};

template<typename K, typename V> //constructs Node
Node<K, V>::Node(K key, V val) {
  first = key;
  second = val;
}

template <typename K, typename V> // checks if less than
bool Node<K,V>::operator<(const Node & comp_node) const{ 
    if(comp_node.first > this->first){
      return true;
    }else{
      return false;
    }
}

template <typename K, typename V> // checks if equal
bool Node<K,V>::operator==(const Node & comp_node) const{ 
    if(comp_node.first == this->first){
      return true;
    }else{
      return false;
    }
}