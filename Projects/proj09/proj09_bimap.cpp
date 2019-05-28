 
#include "proj09_bimap.h"
#include<algorithm>
using std::lower_bound;
#include <utility>
using std::make_pair;

vector< pair <string, string> >::iterator BiMap::find_key(string key){ 
    auto vlambda = [](auto pair, string my_key)-> bool{return pair.first < my_key;}; 
    return lower_bound(ordered_by_keys_.begin(), ordered_by_keys_.end(), key, vlambda); //finds iterator pointing to key
}

vector< pair <string, string> >::iterator BiMap::find_value(string value){
    auto vlambda = [](auto pair, string my_val)-> bool{return pair.second < my_val;}; 
    return lower_bound(ordered_by_vals_.begin(), ordered_by_vals_.end(), value, vlambda); //finds iterator pointing to key
} 

bool BiMap::add(string key, string val){
    pair<string, string> add_pair_key = make_pair(key, val);//key vector pair
    
    
    if(!(find_key(key) != ordered_by_keys_.end()  && find_key(key)->first == key) &&
     !(find_value(val) != ordered_by_vals_.end()  && find_value(val)->second == val)){ 
        ordered_by_keys_.insert(find_key(key), add_pair_key); //key insert
        ordered_by_vals_.insert(find_value(val), add_pair_key);// add_pair_key from add pair val
        return true;
    }else{
        return false;
    }
}

BiMap::BiMap(initializer_list< pair<string, string> > bm){ 
    for(pair<string, string> pair: bm){ //iterates through bm
        add(pair.first, pair.second);
    }
}

ostream& operator<<(ostream& stream, BiMap& bm){ 
    for(auto i = bm.ordered_by_keys_.begin(); i != bm.ordered_by_keys_.end(); i++){
        if(i == ordered_by_keys_.end()-1){
            stream << i->first + " : " + i->second; //removes comma if end
        }else{
            stream << i->first + " : " + i->second + ", "; 
        }
    }
    return stream;
}

size_t BiMap::size(){
    int size = 0;
    for(auto i = ordered_by_keys_.begin(); i!= ordered_by_keys_.end(); i++){
        size++;
    }
   return size;
}

string BiMap::value_from_key(string s){
    auto i = find_key(s); //iterator to key
    if(i != ordered_by_keys_.end() && find_key(s)->first == s){
        return i->second;
    }else{
        return "";
    }
}

string BiMap::key_from_value(string s){
    auto i = find_value(s); //iterator to value
    if(i != ordered_by_vals_.end() && find_value(s)->second == s){ //changed first to second
        return i->first; //changed second to first
    }else{
        return "";
    }
}

bool BiMap::update(string key, string val){
    if(value_from_key(key) == ""){
        return false;
    }else{
        auto i = find_key(key);
        i->second = val;
        return true;
    }
}

pair<string, string> BiMap::remove(string s){ 
    //pair if s is removed from ordered keys vector
    string key1;
    string val1;

    //pair if s is removed from ordered vals vector
    string key2;
    string val2;
    
    pair<string, string> p; //empty pair
    string kv = key_from_value(s);
    string vk = value_from_key(s);
    int no_map = 0; //checks to see if s is in both maps

    if(find_key(s) != ordered_by_keys_.end() && find_key(s)->first == s){ //search key vect 
        if(kv != ""){
            auto ikv = find_key(kv); //second iterator for key
            ordered_by_keys_.erase(ikv);
        }
        
        auto ik = find_key(s); //iterator for key
        key1 = ik->first;
        val1 = ik->second;
        p.first = key1;
        p.second = val1;
        ordered_by_keys_.erase(ik);
        no_map++;
    }else{ 
        if(kv != ""){
            auto ikv = find_key(kv); //second iterator for key
            ordered_by_keys_.erase(ikv);
        }
    }

    if(find_value(s) != ordered_by_vals_.end() && find_value(s)->second == s){ //search val vect
        if(vk != ""){
            auto ivk = find_value(vk); //second iterator for key
            ordered_by_vals_.erase(ivk);
        }
        

        auto iv = find_value(s);
        key2 = iv->first;
        val2 = iv->second;
        p.first = key2;
        p.second = val2;
        ordered_by_vals_.erase(iv);
        no_map++;

    }else{
        if(vk != ""){
            auto ivk = find_value(vk); //second iterator for key
            ordered_by_vals_.erase(ivk);
        }

    }

    if(no_map != 0){
        if(no_map == 2){ //sets pair if s is in both vectors
            p.first = key2;
            p.second = val1; 
        }
        return p;
    }else{ //if s is in no vectors
        p.first = "";
        p.second = "";
        pair<string, string> p;
        return p;
    }
    
}

int BiMap::compare(BiMap & bm){
    vector<pair<string, string>> bmv = bm.ordered_by_keys_; //bm vector
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

    if(bm.size() < ordered_by_keys_.size()){ //compares sizes
        return 1;
    }else if(bm.size() > ordered_by_keys_.size()){
        return -1;
    }

    return 0;
}

BiMap BiMap::merge(BiMap & bm){
    BiMap new_bm;
    for(auto ele: ordered_by_keys_){ //iterates through first biMap
        string key = ele.first;
        string val = ele.second;
        if(new_bm.find_key(key)!= new_bm.ordered_by_keys_.end() && new_bm.find_key(key)->first == key){
            new_bm.update(key, val);
        }else{
            new_bm.add(key, val);
        }
    }

    for(auto ele: bm.ordered_by_keys_){
        string key = ele.first;
        string val = ele.second;
        if(new_bm.find_key(key)!= new_bm.ordered_by_keys_.end() && new_bm.find_key(key)->first == key){
            //ignores if in bimap
        }else{
            new_bm.add(key, val);
        }
    }
    return new_bm;
}

