#include <vector>
using std::vector;
#include <string>
using std::string; 
#include <utility>
using std::initializer_list; 
#include <ostream>
using std::ostream; 
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<stdexcept>

//I seriously tried my best. I got really confused with the template types
//this is not working

namespace student {
    template<typename T>
    class vector{
        private:
            vector <T> * data_; //don't think this initalizes a templated pointer
            size_t capacity_; 
            size_t size_;
    public:
        void set_vector(size_t capacity){
            if(capacity){
                capacity_ = capacity;
            }else{
                capacity_ = 10;
            }

            size_ = 0;

            long array[capacity_]; //unsure of type
            data_ = array;
        }

        void init_lst(initializer_list <T> ilst){
            capacity_ = ilst.size();
            size_ = ilst.size();
            long array[ilst.size()]; //unsure of type
            data_ = array;

            copy(ilst.begin(), ilst.end(), data_.begin()); //not sure how to change data from pointer
        }
        
        size_t capacity(){
            return capacity_;
        }
        size_t size(){
            return size_;
        }

        void push_back(templatetype val){ 
            if(size_ >= capacity_){
                capacity_ = vector2*capacity_; 
                vector * new_data;
                copy(data_.begin(), data_.end(), new_data.begin());
                swap(data_, new_data);
                data_.push_back(val);
                size_ = size_ +1;

            }else{
                data_.pushback(val);
            }
        
        }

        templatetype& operator[](size_t val){
            if(val <= size_){
                return & data_[val];
            }else{
                throw range_error("range error");
            }
            
        }
    };
}
