//sect 14, 10/21/18, project 6
#include "proj06_functions.h"
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string; using std::atoi; using std::to_string;
#include <locale> 
#include <fstream>
using std::ifstream; using std::ofstream;
#include <sstream>
using std::istringstream; using std::ostringstream;

vector<vector<int>> read_file(const string &fname){ 
    vector<vector<int>> matrix; //2d vector
    ifstream infile (fname);
    if(infile.is_open()){
        while(!infile.eof()){
            vector<int> row;
            string s; //empty string for rows
            getline(infile, s);

            //converts char to int and appends to row vector
            for(char ele: s){
                int int_ele = ele - '0';
                row.push_back(int_ele); //creates rows
                
            }
            if(row.size() != 0){
                matrix.push_back(row);
            }    
        }
    }
    else{
        throw "runtime_error";
    }
    return matrix;
}

vector<int> get_row(const vector<vector<int>> &v, int row){
    return v[row];
}

vector<int> get_column(const vector<vector<int>> &v, int col){
    vector<int> ret_vect;
    for(vector<int> row: v){
        int col_num = row[col];
        ret_vect.push_back(col_num);
    
    }
    return ret_vect;
}

int col_to_int(const vector<vector<int>> &v, size_t col){ 
    int ret_int = 0;
    vector<int> mult_nums{64,32,16,8,4,2,1}; // values of rows

    for(int i = 1; i < 8; i++){ 
        int num = v[i][col]; //gets number from row and column
        num = num * mult_nums[i-1]; 
        ret_int += num;
    }
    return ret_int;
}

string get_time(const vector<vector<int>> & v){
    int min = col_to_int(v, 1);
    int hour = col_to_int(v, 4);
    
    string min_str = to_string(min);
    string hr_str = to_string(hour);
    if(min_str.length()<=1){ //accounts mins < 10
        min_str = {'0' + min_str};
    }
    if(hr_str.length()<=1){//accounts for hours < 10
        hr_str = {'0' + hr_str};
    }
    string time_str = {hr_str + ':' + min_str};
    return time_str;

}

string get_date(const vector<vector<int>> & v){
    int month = col_to_int(v, 6);
    int day = col_to_int(v, 5);
    int year = col_to_int(v, 7);

    //changing ints to strs
    string month_str = to_string(month);
    string day_str = to_string(day);
    string year_str = to_string(year);

    if(month_str.length()<=1){ //accounts months < 10
        month_str = {'0' + month_str};
    }
    if(day_str.length()<=1){//accounts for days < 10
        day_str = {'0' + day_str};
    }
    if(year_str.length()<=1){ //accounts years < 10
        year_str = {'0' + year_str};
    }

    year_str = {"20"+ year_str}; //adds 2000 to year

    string date_str = {month_str + '/' + day_str + '/' + year_str};


    return date_str;
}

string get_serial(const vector<vector<int>> & v){
    string serial_str;
    int one_num = col_to_int(v, 13);
    int two_num = col_to_int(v, 12);
    int three_num = col_to_int(v, 11);
    int four_num = col_to_int(v, 10);

    //change ints to strs
    string one_str = to_string(one_num);
    string two_str = to_string(two_num);
    string three_str = to_string(three_num);
    string four_str = to_string(four_num);

    vector<string> nums = {one_str, two_str, three_str, four_str};
    //adds zero in front of single nums, creates return str
    for(string ele: nums){
        if(ele.length() == 1){
            ele = string {'0'+ ele};
        }
        serial_str = string {serial_str + ele};
    }
    
    return serial_str;
}

int parity(int i){ 
    if(i%2 == 0){
        return 1;
    }
    else{
        return 0;
    }
}
string check_column_parity(vector<vector<int>> &v, int col){ 
    vector<int> col_ones = get_column(v, col);
    col_ones.erase(col_ones.begin() + 0); //removes parity row

    int one_sum = 0;
    string par_bool;

    for(int i: col_ones){ //ones count
        one_sum += i;
    }

    int col_parity = parity(one_sum); //parity 1/0

    if(col_parity == 1 && one_sum % 2 == 0){ //parity true/false
        par_bool = "true";
    }
    else if(col_parity != 1 && one_sum % 2 != 0){
        par_bool = "true";
    } 
    else{
        par_bool = "false";
    }

    string col_par_str = to_string(col_parity);

    string one_sum_str = to_string(one_sum);
    string ret_par = string {col_par_str + ':' + one_sum_str + ':' + par_bool};

    return ret_par;
}

string check_row_parity(vector<vector<int>> &v, int row){
    vector<int> par_vect = v[row];
    par_vect.erase(par_vect.begin() + 0); //removes parity column
    
    int one_sum = 0;
    string par_bool;

    for(int i: par_vect){ //ones count
        one_sum += i;
    }

    int row_parity = parity(one_sum); //parity 1/0

    if(row_parity == 1 && one_sum % 2 == 0){ //parity true/false
        par_bool = "true";
    }
    else if(row_parity != 1 && one_sum % 2 != 0){
        par_bool = "true";
    } 
    else{
        par_bool = "false";
    }

    string row_par_str = to_string(row_parity);
    string one_sum_str = to_string(one_sum);
    
    string ret_par = string {row_par_str + ':' + one_sum_str + ':' + par_bool};

    return ret_par;
}