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
#include "Node.h"

//
// BiMap
// 
template<typename K, typename V>
class BiMap{
 private:
  Node<K,V>* ordered_by_keys_head_ = nullptr;
  Node<K,V>* ordered_by_vals_head_ = nullptr;
 
  size_t sz_ = 0;
  
  pair<Node<K, V>*, Node<K, V>*> find_key(K);
  pair<Node<K, V>*, Node<K, V>*> find_value(V);
  
 public:
  BiMap()=default; 
  BiMap(initializer_list< Node<K,V> >);
  BiMap (const BiMap&);
  BiMap operator=(BiMap);
  ~BiMap();
  size_t size();
  K remove_val(V value); 
  V remove_key(K key); 
  bool add(K,V);
  V value_from_key(K);
  K key_from_value(V);
  bool update(K,V); 
  bool merge_update(K,V);   
  int compare(BiMap&);
  BiMap merge (BiMap&);

  friend ostream& operator<<(ostream &out, const BiMap &bm){
    Node<K, V>* tp = bm.ordered_by_keys_head_; //traverses linked list
    while(tp != nullptr){
      out << *tp; 
      tp= tp->next;
      if(tp != nullptr){ // adds comma unless last node
        out << ", ";
      }
    }
    return out;
  }  
};

//BiMap FUNCTIONS HERE
template<typename K, typename V> 
BiMap<K,V>::BiMap(initializer_list< Node<K,V> > bm){
    for(Node<K, V> node: bm){ //traverses bm
        add(node.first, node.second);
    }
}

template<typename K, typename V> 
BiMap<K,V>::BiMap (const BiMap& bm){ 
  auto tp = bm.ordered_by_keys_head_; 
  while(tp != nullptr){ //traverses bm
    add(tp->first, tp->second); //adds nodes to other bimap
    tp = tp->next;
  }
}

template<typename K, typename V> 
BiMap<K,V> BiMap<K,V>::operator=(BiMap<K,V> bm){
  swap(ordered_by_keys_head_, bm.ordered_by_keys_head_); 
  swap(ordered_by_vals_head_, bm.ordered_by_vals_head_);
  return *this;
}

template<typename K, typename V> 
BiMap<K,V>::~BiMap(){
  //node for both keys and vals
  Node<K,V>* del_key = ordered_by_keys_head_;
  Node<K,V>* del_val = ordered_by_vals_head_;
  
  while (del_key != nullptr){
	  ordered_by_keys_head_ = ordered_by_keys_head_->next; //deleting from key linked list
	  delete del_key;
	  del_key = ordered_by_keys_head_;

    ordered_by_vals_head_ = ordered_by_vals_head_->next; //deleting from val linked list 
	  delete del_val;
	  del_val = ordered_by_vals_head_;
  }

  ordered_by_keys_head_ = nullptr;
  ordered_by_vals_head_= nullptr;
}


template<typename K, typename V>
pair<Node<K, V>*, Node<K, V>*> BiMap<K,V>::find_key(K key){
  if(ordered_by_keys_head_ == nullptr){ //nothing in linked list
    pair<Node<K, V>*, Node<K, V>*> p_ptr (nullptr, nullptr); //return null pair
    return p_ptr;
  }
  if(ordered_by_keys_head_->first >= key){//if before the head of linked list
    pair<Node<K, V>*, Node<K, V>*> p_ptr (nullptr, ordered_by_keys_head_); //return pair
    return p_ptr;
  }

  Node<K, V>* tp = ordered_by_keys_head_-> next; //pointer after insertion
  Node<K, V>* pre_tp = ordered_by_keys_head_; //pointer before insertion

  while(tp != nullptr){ //loops through linked list
    if(tp->first >= key){ //if key is equal or greater
      pair<Node<K, V>*, Node<K, V>*> p_ptr (pre_tp, tp); //return pair
      return p_ptr;
    }
    pre_tp = pre_tp->next;
    tp = tp->next;
  }

  //if position is end of linked list
  pair<Node<K, V>*, Node<K, V>*> p_ptr (pre_tp, tp); //return pair
  return p_ptr;
}
template<typename K, typename V>
pair<Node<K, V>*, Node<K, V>*> BiMap<K,V>::find_value(V val){
  if(ordered_by_vals_head_ == nullptr){ //nothing in linked list
    pair<Node<K, V>*, Node<K, V>*> p_ptr (nullptr, nullptr); //return pair
    return p_ptr;
  }
  if(ordered_by_vals_head_->second >= val){ //if before the head of linked list
    pair<Node<K, V>*, Node<K, V>*> p_ptr (nullptr, ordered_by_vals_head_); //return pair
    return p_ptr;
  }
  Node<K, V>* tp = ordered_by_vals_head_->next; //pointer after insertion
  Node<K, V>* pre_tp = ordered_by_vals_head_; //pointer before insertion

  while(tp != nullptr){ //loops through linked list
    if(tp->second >= val){ //if val is equal or greater
      pair<Node<K, V>*, Node<K, V>*> p_ptr (pre_tp, tp); //return pair
      return p_ptr;
      
    }
    pre_tp = tp;
    tp = tp->next;
  }

  //if position is end of linked list
  pair<Node<K, V>*, Node<K, V>*> p_ptr (pre_tp, tp); //return pair
  return p_ptr;
}

template<typename K, typename V>
bool BiMap<K,V>::add(K key,V val){ 

  Node<K,V>* key_node = new Node<K,V>(key, val); //insertion node key
  Node<K,V>* val_node = new Node<K,V>(key, val); //insertion node val

  auto kp = find_key(key); //two pointers to position in key linked list
  auto vp = find_value(val); // two pointers to position in val linked list

  // if either key nor value
  if((vp.second != nullptr && vp.second->second == val)){
        return false;
      }
    else if((kp.second != nullptr && kp.second->first == key)){
        return false;
      }

  sz_++; //add to size

  //adds to value linked list
  if(vp.first == nullptr){
    if(vp.second == nullptr){ //empty linked list, pushes to front
      ordered_by_vals_head_ = val_node;
      ordered_by_vals_head_->next = nullptr;
    }else if(vp.second == ordered_by_vals_head_){ //full linked list, pushes to front
      val_node->next = ordered_by_vals_head_;
      ordered_by_vals_head_ = val_node;
    }
  }else{ //inserts in middle
    vp.first->next = val_node;
    val_node->next = vp.second;
  }

  //adds to key linked list
  if(kp.first == nullptr){
    if(kp.second == nullptr){ //empty ll, pushes to front
      ordered_by_keys_head_ = key_node;
      ordered_by_keys_head_->next = nullptr;
    }else if(kp.second == ordered_by_keys_head_){ //full linked list, pushes to front
      key_node->next = ordered_by_keys_head_;
      ordered_by_keys_head_ = key_node;
    }
  }else{ //inserts in middle
    kp.first->next = key_node;
    key_node->next = kp.second;
  }
  return true;
}

template<typename K, typename V>
size_t BiMap<K,V>::size(){
  auto tp = ordered_by_keys_head_;
  size_t size = 0;
  while(tp != nullptr){ //traverses linked list
    size++; //counts nodes
    tp = tp->next;
  }
  return size; //number of nodes
}

template<typename K, typename V>  
K BiMap<K,V>::key_from_value(V val){
  auto vp = find_value(val); 
  
  if(vp.second != nullptr){ // if in linked list
    if(vp.second->second == val){
      return vp.second->first; //return key
    }
  }
  return K();
}


template<typename K, typename V>
V BiMap<K,V>::value_from_key(K key){
  auto kp = find_key(key);
  if(kp.second != nullptr){ //if in linked list
    if(kp.second->first == key){ 
      return kp.second->second; // return value
    }
  }
  return V();
}

template<typename K, typename V> 
bool BiMap<K,V>::merge_update(K key, V val){
  //updates elements in the merge function
  auto kp = find_key(key);
  auto vp = find_value(val);

  // if key already exists
  if(kp.second != nullptr && kp.second->first == key){ //key in map
    remove_key(key);
    add(key, val);
    return true;
  }
  if(vp.second != nullptr && vp.second->second == val){ //val in map
    remove_val(val);
    add(key, val);
    return true;
  }

  return false;
}

template<typename K, typename V>
V BiMap<K, V>::remove_key(K element){ 
    V res_val = V(); 
    K res_key = K();
    
    // if element found as key 
    auto key = find_key(element);
    if(key.second == nullptr){
      return res_val;
    }
    if (key.second->first == element) {
      // remember the corresponding value
      res_val = key.second->second;

      //erase from key
      if(key.first == nullptr){
        ordered_by_keys_head_ = key.second->next; //updates head
      }else{
        key.first->next = key.second->next; //erase node from key linked list
      }
  
      //erase from val
      auto val = find_value(res_val);
      if(val.first == nullptr){ //if first in val linked list
        ordered_by_vals_head_ = val.second->next; //update head
      }else{
        val.first->next = val.second->next; //erase node from val linked list
      }
    }
    return res_val;
}

template<typename K, typename V> 
K BiMap<K,V>::remove_val(V element){
  V res_val = V(); 
  K res_key = K();
  
  // if element found as value 
  auto val = find_value(element);
  if(val.second == nullptr){
    return res_key;
  }
  if (val.second->second == element) {
    // remember the corresponding value
    res_key = val.second->first;

    //erase from value
    if(val.first == nullptr){
      ordered_by_vals_head_ = val.second->next; //update head
    }else{
      val.first->next = val.second->next; //erase from val linked list
    }
    
    //erase from key
    auto key = find_key(res_key);
    if(key.first == nullptr){ //if first in key linked list
      ordered_by_keys_head_ = key.second->next; //update head
    }else{
      key.first->next = key.second->next; //erase from key linked list
    }
  }
  return res_key;
}

template<typename K, typename V> 
int BiMap<K,V>::compare(BiMap& bm){
  Node<K,V>* bm_head = bm.ordered_by_keys_head_; //bm head
  auto tp = ordered_by_keys_head_; //compare bimap
  auto tp_bm = bm_head; //compare bm

  //traverses linked list, compares keys
  while(tp_bm != nullptr && tp != nullptr){ 
    if(tp_bm->first < tp->first){ 
      return 1;
    }else if(tp_bm->first > tp->first){
      return -1;
    }
    tp = tp->next;
    tp_bm = tp_bm->next;
  }

  if(bm.size() < sz_){ //compares sizes
      return 1;
  }else if(bm.size() > sz_){
      return -1;
  }
  return 0;
}

template<typename K, typename V> 
BiMap<K,V> BiMap<K,V>::merge (BiMap<K,V>& bm){

  BiMap<K,V> res;
  Node<K,V>* bm_head = bm.ordered_by_keys_head_; 
  auto tp = ordered_by_keys_head_;
  auto tp_bm = bm_head;

  //traverses first bimap, adds to new bm
  while(tp_bm != nullptr){ 

    auto key = tp_bm->first;
    auto val = tp_bm->second;

    res.add(key, val);

    tp_bm = tp_bm->next;
  }

  //traverses second bimap, adds/updates new bm
  while(tp != nullptr){ 

    auto key = tp->first;
    auto val = tp->second;

    //if key in bimap
    if(res.find_key(key).second != nullptr && res.find_key(key).second->first == key){ 
      res.merge_update(key, val);
    //if val in bimap
    }else if(res.find_value(val).second != nullptr && res.find_value(val).second->second == val){
      res.merge_update(key,val);
    }else{
      res.add(key, val);
    }
    tp = tp->next;
  }
  return res;
}

template<typename K, typename V> 
bool BiMap<K,V>::update(K key, V val){
  auto kp = find_key(key);

  // if key already exists
  if(kp.second == nullptr){
    return false;
  }
  if (kp.second->first == key) {
    auto kp_val = kp.second->second; //pervious value
      //erase from keys
      kp.first->next = kp.second->next;

      // erase from values
      auto vp = find_value(kp_val);
      if(vp.first == nullptr){ 
        //erase head
        ordered_by_vals_head_ = vp.second->next;
      }else{ //erase from middle
        vp.first->next = vp.second->next;
      }
      // add new node 
      add(key, val);
      return true;
  }
  return false;
}
