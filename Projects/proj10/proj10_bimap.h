// sect 14, 11/28/18, project 10
#pragma once

#include"vector.h"
#include"proj10_bimap_starter.h"
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
class BiMap {
private:
  Vector<Node<K, V>> ordered_by_keys_;
  Vector<Node<K, V>> ordered_by_vals_;

  Node<K, V> * find_key(K);
  Node<K, V> * find_value(V);
public:

  // constructors
  BiMap() = default; 
  BiMap(initializer_list< Node<K, V> >);
  size_t size();
  V value_from_key(K);
  K key_from_value(V);
  bool update(K, V);
  K remove_val(V value); 
  V remove_key(K key);
  bool add(K, V);
  int compare(BiMap &);
  friend ostream& operator<<(ostream & out, BiMap &bm){
      size_t size= bm.ordered_by_keys_.size();
      cout << "size" << size << endl;
      for(int i = 0; i < size; i++){
          if(i+1 == size){
              out << bm.ordered_by_keys_[i];
          }else{
              out << bm.ordered_by_keys_[i];
              out << ", ";
          }
      }
      
      return out;
  }
};

template<typename K, typename V>
Node<K, V> * BiMap<K,V>::find_key(K key){ 
    auto vlambda = [](auto node, K my_key)-> bool{return node.first < my_key;}; 
    return lower_bound(ordered_by_keys_.begin(), ordered_by_keys_.end(), key, vlambda); //finds iterator pointing to key
}

template<typename K, typename V>
Node<K, V> * BiMap<K,V>::find_value(V value){ 
    auto vlambda = [](auto node, V my_val)-> bool{return node.second < my_val;}; 
    return lower_bound(ordered_by_vals_.begin(), ordered_by_vals_.end(), value, vlambda); //finds iterator pointing to key
}

template<typename K, typename V>
BiMap<K, V>::BiMap(initializer_list< Node<K, V> > bm){ 
    for(Node<K, V> node: bm){ //iterates through bm
        add(node.first, node.second);
    }
}

template<typename K, typename V>
bool BiMap<K,V>::add(K key, V val){
    Node<K, V> add_node_key(key, val); 
    
    
    if(!(find_key(key)->first == key) && 
     !( find_value(val)->second == val)){ 
        ordered_by_keys_.insert(find_key(key), add_node_key); //key insert
        ordered_by_vals_.insert(find_value(val), add_node_key);// add_pair_key from add pair val
        return true;
    }else{
        return false;
    }
}

template<typename K, typename V>
size_t BiMap<K,V>::size(){
    return ordered_by_keys_.size();
}

template<typename K, typename V>
K BiMap<K,V>::key_from_value(V s){
    auto i = find_value(s); //iterator to value
    if( find_value(s)->second == s){ //changed first to second
        return i->first; //changed second to first
    }else{
        return K(); 
    }
}

template<typename K, typename V>
V BiMap<K,V>::value_from_key(K s){
    auto i = find_key(s); //iterator to key
    if(find_key(s)->first == s){
        return i->second;
    }else{
        return V();
    }
}

template<typename K, typename V> 
bool BiMap<K,V>::update(K key, V value){
    auto kp = find_key(key);

    // if key already exists
    if (kp->first == key) {
        ordered_by_keys_.erase(kp);
        // find value iterator and erase
        ordered_by_vals_.erase(find_value(kp->second));
        // add new node 
        add(kp->first, value);
        return true;
    }

    return false;
}

template<typename K, typename V>
int BiMap<K,V>::compare(BiMap &bm){
    Vector<Node<K, V>> bmv = bm.ordered_by_keys_; //bm vector
    int i = 0; //keeps track of postion

    for(auto ele:bmv){
        cout << i << endl;
        if(i  > ordered_by_keys_.size() - 1){ //checks for out of range
            break;
        }
        if(ele.first < ordered_by_keys_.at(i).first){
            return 1;
            
        }else if(ele.first > ordered_by_keys_.at(i).first){
            return -1;
        }
        i++;
    }

    if(bmv.size() < ordered_by_keys_.size()){ //compares sizes
        return 1;
    }else if(bmv.size() > ordered_by_keys_.size()){
        return -1;
    }

    return 0;
}

template<typename K, typename V>
K BiMap<K,V>::remove_val(V element){
    V res_val = V();
    K res_key = K(); 

    // if element found as value
    auto val = find_value(element);
    if ( val->second == element) {
    // remember the corresponding key
    res_key = val->first;
    // erase from both vectors
    ordered_by_vals_.erase(val);
    ordered_by_keys_.erase(find_key(res_key));
    }
    
    return res_key;
}

template<typename K, typename V>
V BiMap<K,V>::remove_key(K element){
    V res_val = V(); 
    K res_key = K();
    
    // if element found as key 
    auto key = find_key(element);
    if ( key->first == element) {
    // remember the corresponding value
    res_val = key->second;
    // erase from both vectors
    ordered_by_keys_.erase(key);
    ordered_by_vals_.erase(find_value(res_val));
    }

    return res_val;
}