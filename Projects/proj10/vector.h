// sect 14, 11/28/18, project 10
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
using std::sort; using std::lower_bound; using std::swap; using std::copy;
#include<sstream>
using std::ostringstream;

template<typename T>
class Vector {
  private:
    T * data_; //points to dynamically allocated memory
    size_t size_; //default 0, number of elements in vect
    size_t capacity_; //default 10, capacity of vector
    void alloc_data();
  public:
    Vector(); // constructor
    Vector(const Vector&); //copy constructor
    ~Vector(); // destructor
    void push_back(T);
    T operator[](int);
    T at(int i);
    size_t size();
    T * begin(); //returns pointer to first    
    T * end(); //returns pointer to end  
    void insert(T * , T); // inserts an element into position
    Vector<T>& operator=(Vector &);
    void erase(T *); // removes an element (opposite of insert)
};

//vector methods/constructors
template<typename T> 
Vector<T>::Vector(const Vector<T> &v){
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = new T[v.size_];

    copy(v.data_, v.data_+v.size_, data_);
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector<T> &v){
    swap(this->size_, v.size_);
    swap(this->capacity_, v.capacity_);
    swap(this->data_, v.data_);
    return *this;
}

template<typename T>
Vector<T>::Vector() {
    capacity_ = 10; //default is 10
    size_ = 0; //default is 0
    data_ = new T[capacity_]; 
    T vect[capacity_]; //creates empty array
}

template<typename T> //allocates data
void Vector<T>::alloc_data(){
    capacity_ = capacity_*2;
    T * new_data = new T[capacity_];
    
    for(int i = 0; i <= size_; i++){
        new_data[i] = data_[i];
    }
    delete data_;
    data_ = new_data;
}

template<typename T> //pushes one element back
void Vector<T>::push_back(T ele){
    if(size_ !=  capacity_){ 
        data_[size_] = ele;
        size_++;
    }else{
        alloc_data(); 
    }
}

template<typename T> 
T Vector<T>::operator[](int index){ 
    return data_[index];
}

template<typename T>
T Vector<T>::at(int index){ 
    return data_[index];
}

template<typename T> //deconstructs 
Vector<T>::~Vector() {
    delete[] data_;
}

template<typename T> //returns size of vector
size_t Vector<T>::size() {
    return size_;
}
template<typename T>
void Vector<T>::erase(T * ptr){ //erases at an position
    int index = ptr - data_;

    T * new_data = new T[capacity_];
    
    int i = 0; // index for old array
    //copy elements in old array up to index
    for(i; i < index; i++){ 
        new_data[i] = data_[i];
    }

    //copies elements besides at index
    for(int j = 0; i < size_ - 1; j++){
        new_data[i] = data_[i+1]; 
        i++;
    }
    //Doesn't delete old data_
    data_ = new_data;
    size_--;
}

template<typename T> //inserts 
void Vector<T>::insert(T * ptr, T n) { //moves everything back by one
    if(size_ == capacity_){ //if out of index
        alloc_data();
    }
    int index = ptr - data_; //gets index of pointer

    T * new_data = new T[capacity_]; //new array
    
    int i = 0; // index for old array
    //copy elements in old array up to index
    for(i; i < index; i++){ 
        new_data[i] = data_[i];
    }

    new_data[index] = n; //inserts node into index

    int new_i = index;
    //copy remaining elements
    for(int j = 0; i < size_; j++){
        new_i ++;
        new_data[new_i] = data_[i]; 
        i++;
    }
    //delete data_;
    data_ = new_data;
    size_++;

}

template<typename T> //return end pointer
T * Vector<T>::begin() { //returns an iterator to first ele in array
    T * ptr = &data_[0] ;
    return ptr;
}

template<typename T> //return end pointer
T * Vector<T>::end() { //returns an iterator to first ele in array
    T * ptr = &data_[size_] ;
    return ptr;
}