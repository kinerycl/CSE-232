#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<iomanip>
using std::setprecision;
#include<string>
using std::string;
// any other includes you think you might need here

// global variable for count -> char code
const string code = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//
string encode_sequence(string str, char en_char){
  int str_len = str.length();
  if(str_len < 4){ // accounts for if str too short to be encoded
    return str;
  }
  char val_letter = code.at(str_len - 4); // if str is long enough to be encoded
  char let_str = str[0]; 
  string ret;
  ret += en_char; 
  ret += val_letter;
  ret += let_str;
  return ret;
}

string encode(string str, char en_char){ // encodes a portion of string
  string ret_str = "";
  char char_init = str[0];
  int char_num = 0;
  string same_let = ""; // string to encompass all the same letters

  // loops through all chars in string to create an encoded string
  for(int i = 0; i < str.length(); i++){
    if(str[i] == char_init){
      char_num += 1; // length of substring
    }else{ // for cases where string can not be encoded 
      same_let = str.substr(str.find(char_init), char_num);
      ret_str += encode_sequence(same_let, en_char);
      char_num = 1;
      char_init = str[i];
    }
  }

  // adds final portion of string
  same_let = str.substr(str.find(char_init), char_num);
  ret_str += encode_sequence(same_let, en_char);
  return ret_str;
}

string decode_sequence(string str, char en_char){ // decodes given sequence
  char let_num = str[1]; // letter number
  int num = code.find(let_num) + 4; // number of times letter needs to appear
  string ret_code = "";
   for(int i = 0; i < num; i++){ // loop to get string with correct number repeted letter
     ret_code += str[2];
  } 
  return ret_code; 
}

string decode(string str, char en_char){ // decodes entire sequence
  string seq = ""; // decode_sequence string
  string ret_str = "";
  int l_count = 0; // counts iterations through for loop
  int beg_pos = 0; // position of first en_char

  for(int i = 0; i <= str.length(); i++){ //decodes string in segments 
    if(l_count == 0 && str[0] != en_char){ // checks for beginning strs not encoded
      beg_pos = str.find(en_char);
      ret_str += str.substr(0, beg_pos);
      str = str.substr(beg_pos); // change length of string
    }

    if(str[0] == en_char){ // for portions that are encoded
      seq = str.substr(0, 3); 
      ret_str += decode_sequence(seq, str[0]); 
      str = str.substr(3); // changes length of string
    }
    l_count += 1;
  }
  ret_str += str; // adds undecoded portion of string
  return ret_str; 
}

double reduction(string org_str, string encode_str){ // finds the reduction
  double en_len = encode_str.length();
  double org_len = org_str.length();
  return en_len / org_len;
}
//

int main (){
  long test_num;
  cin >> test_num;

  switch(test_num) {

  case 1: {
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode_sequence(input, sep);
    break;
  }

  case 2:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << encode(input, sep);
    break;
  }

  case 3:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode_sequence(input, sep);
    break;
  }

  case 4:{
    string input;
    char sep;
    cin >> input;
    cin >> sep;
    cout << decode(input, sep);
    break;
  }

  case 5:{
    string s1,s2;
    cin >> s1;
    cin >> s2;
    cout << setprecision(2);
    cout << reduction(s1,s2);
    break;
  }
    
  }  // of switch 

}  // of main
  
