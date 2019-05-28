// sect 14, 11/12/18, project 8
#include "proj08.h"
#include <string>
using std::string; using std::stoi; using std::to_string;
#include <set>
using std::set;
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include <fstream>
using std::ifstream; using std::ofstream;
#include<algorithm>
using std::transform;
#include <map>
using std::pair;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream;

Painter::Painter(const string& fname) { 
    filename = fname;
}

void Painter::CreateCanvas(){ 
    ifstream infile (filename);
    int i = 1; //line number
    while(!infile.eof()){
        string s; //empty string for lines
        getline(infile, s);
        if(s == ""){
            continue;
        }
        lines_.insert(pair<int, string>(i, s)); //adds line number and line to map
        i+=1;
    }

    for(auto i = lines_.begin(); i != lines_.end(); i++){ //iterates through map
        auto num = i->first; //num in pair
        auto val = i->second; //str part of pair
        Parse(num, val);
    }
}

void Painter::Parse(int line_num, const std::string& line){
    vector<string> line_vect;
    string token;

    if(line.length() == 0){ //ignores empty lines
        return;
    }
    //creates a vector of strings splitting on empty spaces
    istringstream ss(line);
    while(getline(ss, token, ' ')){
        line_vect.push_back(token);
    }

    //calls functions based on first word in line
        if(!line_vect.empty()){
            if(line_vect[0] == "SetDim"){
                SetDim(line_num, stoi(line_vect[1]), stoi(line_vect[2]));
            }
            else if(line_vect[0] == "SetPenPosition"){
                SetPenPosition(line_num, stoi(line_vect[1]), stoi(line_vect[2]));
            }
            else if(line_vect[0] == "SetPenSymbol"){  
                SetPenSymbol(line_num, stoi(line_vect[1]));
            }
            else if(line_vect[0] == ("Draw")){
                Draw();
            }
            else if(line_vect[0] == "Move"){
                Move(stoi(line_vect[1]));
            }
            else if(line_vect[0] == "Turn"){
                Turn(stoi(line_vect[1]));
            }
            else if(line_vect[0] == "Repeat"){
                char num1 = line_vect[2][0];
                char num2 = line_vect[2][2];
                int first_num = num1 - 48; //changes chars to ints
                int sec_num = num2 - 48;
                Repeat(line_num, stoi(line_vect[1]), first_num, sec_num);
            }
            else if(line_vect[0] == "#"){ //ignores comments 
            }
            else{
                string error = "error on line " + to_string(line_num) + 
                ": unable to parse " + "\"" + line_vect[0] + "\"";
                error_log_.push_back(error);
            }
        }

}
void Painter::SetDim(int line_num, int x_dim, int y_dim){ 
    if(x_dim < 10 || y_dim < 10){ //throws errors if row or column less than 10 
        if(x_dim < 10){
            string error = "error on line " + to_string(line_num) + 
            ": Row Dimension out of bounds";
            error_log_.push_back(error);
        }else{
            string error = "error on line " + to_string(line_num) + 
            ": Column Dimension out of bounds";
            error_log_.push_back(error);
        }
    }

    if(x_dim > 80 || y_dim > 80){ //throws errors if row/column greater than 80
       if(x_dim > 80){
           string error = "error on line " + to_string(line_num) + 
           ": Row Dimension out of bounds";
            error_log_.push_back(error);
        }else{
            string error = "error on line " + to_string(line_num) + 
            ": Column Dimension out of bounds";
            error_log_.push_back(error);
        } 
    }

    rows_ = x_dim;
    columns_ = y_dim;
    canvas_ = std::vector<std::string>(rows_,std::string(columns_,' '));

}

void Painter::SetPenPosition(int line_num, int x_pos, int y_pos){
    // throws error if x is out of range
    if(x_pos < 0 || x_pos > rows_){
        string error = "error on line " + to_string(line_num) + 
        ": Pen cannot be placed on canvas at position " 
        + to_string(x_pos) + " " + to_string(y_pos);
        error_log_.push_back(error);
    }
    // throws error if y is out of range
    else if(y_pos < 0 || y_pos > columns_){
        string error = "error on line " + to_string(line_num) + 
        ": Pen cannot be placed on canvas at position " + 
        to_string(x_pos) + " " + to_string(y_pos);
        error_log_.push_back(error);
    }

    pen_position_ = {x_pos,y_pos};
}

void Painter::SetPenSymbol(int line_num, int pen_symbol){
    //checks if char is vaild
   if(32 < pen_symbol && pen_symbol < 126){
        char ascii = static_cast<char>(pen_symbol);
        pen_symbol_ = ascii; 
    }
    else{
        string error = "error on line " + to_string(line_num) + ": Invalid Pen Symbol " 
        + to_string(pen_symbol);
        error_log_.push_back(error);
    }
    
}

void Painter::Draw(){
    canvas_[pen_position_.first][pen_position_.second] = pen_symbol_;
}

void Painter::Move(int n){ 
    //if direction up/down move by items in vector (row)
    if(dir_ == direction::up){
        int new_pos = ( pen_position_.first - n) % rows_;
        pen_position_.first = new_pos;
    }
    else if(dir_ == direction::down){
        int new_pos = ( pen_position_.first + n) % rows_;
        pen_position_.first = new_pos;
    }
    //if direction right/left move in string (column)
    else if(dir_ == direction::left){
        int new_pos = ( pen_position_.second - n) % columns_;
        pen_position_.second = new_pos;
    }
    else if(dir_ == direction::right){
        int new_pos = ( pen_position_.second + n) % columns_;
        pen_position_.second = new_pos;
    }
}

void Painter::Turn(int n){
    for(int i = 1; i <= n; i++){ //number of switches
        switch(dir_){ //switches directions
            case direction::right:
                dir_ = direction::down;
                continue;
            case direction::left:
                dir_ = direction::up;
                continue;
            case direction::up:
                dir_ = direction::right;
                continue;
            case direction::down:
                dir_ = direction::left;
                continue;
        }
    }

}

void Painter::Repeat(int line_num, int n, int start, int end){ //use the map lines and put line back into parse
    if(lines_.find(start) == lines_.end()){ //if start not in lines_
        string error = "error on line " + to_string(line_num) + ": Line " 
        + to_string(start) + " is not in the file"; 
        error_log_.push_back(error);
    }
    else if(lines_.find(end) == lines_.end()){ //if end not in lines_
        string error = "error on line " + to_string(line_num) + ": Line " 
        + to_string(end) + " is not in the file"; 
        error_log_.push_back(error);
    }
    else if(end < start){ //if end greater than start
        string error = "error on line " + to_string(line_num) + 
        ": Repeat range must be ascending"; 
        error_log_.push_back(error);
    }
    else if(line_num > start){ //if line_num greater than start
        string error = "error on line " + to_string(line_num) + 
        ": Repeat command contains itself or refers to previous commands; infinite loop!"; 
        error_log_.push_back(error);
    }else{

        for(auto i = 0; i < n; i++){ //number of repeats
            for(auto start_it = start; start_it <= end; start_it++){ //lines to repeat
                //find params for parse
                Parse(start_it, lines_[start_it]);
            }
        }
    }

}



