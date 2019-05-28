//sect 14, 10/15/18, project 5
#include "proj05_functions.h"
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string;
#include <locale> 


string prepare_plaintext(const string &s){
    string lower_string;
    string no_j_str;
    string no_double_str;

    //makes chars lower
    for(char ele: s){
        ele = tolower(ele);
        lower_string += ele;
    }

    //gets rid of 'j'
    for(char ele: lower_string){
        if(ele != 'j' && isalpha(ele)){
            no_j_str += ele;
        }
    }

    //checks for doubles, repeats becomes 'x'
    for(int i = 0; i < no_j_str.length(); i++){
        if(no_j_str[i] == no_j_str[i+1]){
            no_double_str += string{no_j_str[i], 'x'};
            i += 1; //skips new 'x' char
        }
        else{
            no_double_str += no_j_str[i];
        }
    }

    //checks for even adds 'x' if not
    if(no_double_str.length()%2 != 0){
        no_double_str += string{'x'};
    }

    return no_double_str;
}

string create_encoding(const string &key){
    string new_key;
    string alpha_str = "abcdefghijklmnopqrstuvwxyz";

    //beings making new key and checks for doubles
    for(int i = 0; i < key.length(); i++){
        if(key[i]=='j'){
            continue;
        }
        if(new_key.find(key[i]) == string::npos){ // checking if not in orginal key
            new_key += key[i];
        }
    }

    //adds on to new key with remaining alphabet
    for(int i = 0; new_key.length() < 25; i++){
        if(alpha_str[i]=='j'){
            continue;
        }
        if(new_key.find(alpha_str[i]) == string::npos){ // checking if not in orginal key
            new_key += alpha_str[i];
        }
    }
    return new_key; 
}

string encode_pair(const string &pr, const string &key){ 
    string encode_str;
    int key_index_1 = key.find(pr[0]); 
    int key_index_2 = key.find(pr[1]);
    int i;
    int b;

    //finds smaller index
    if(key_index_1 < key_index_2){
        i = key_index_1; //when iterating through indexes, smaller index
        b = key_index_2; //does not change, bigger index
    }else{
        i = key_index_2;//changes, smaller index
        b = key_index_1;//does not change, bigger index
    }
    
    //checks if pair in same column and encodes
    for(i; i <= key.length(); i+=5){ 
        if(i == b){
            if(key_index_1 +5 > key.length()-1){ //checks if in final row
                key_index_1 = key_index_1 - 20;
            }else{
                key_index_1 = key_index_1 + 5;
            }
            if(key_index_2 +5 > key.length()-1){ //checks if in final row
                key_index_2 = key_index_2 - 20;
            }else{
                key_index_2 = key_index_2 + 5;
            }
            encode_str = string{key[key_index_1], key[key_index_2]};
            break;
        }
    }

    //pairs in different columns and rows
    if(key_index_1 - 6 == key_index_2 || key_index_1 + 4 == key_index_2){ //top right and bottom right
        key_index_1 = key_index_1 - 1;
        key_index_2 = key_index_2 + 1;
    }
    else if(key_index_1 - 4 == key_index_2 || key_index_1 + 6 == key_index_2){ //top left and bottom left
        key_index_1 = key_index_1 +1;
        key_index_2 = key_index_2 - 1;
    }
    encode_str = string{key[key_index_1], key[key_index_2]};


    //resets i, finds smaller index
    if(key_index_1 < key_index_2){
        i = key_index_1; //when iterating through indexes, smaller index
        b = key_index_2; //does not change, bigger index
    }else{
        i = key_index_2;//changes, smaller index
        b = key_index_1;//does not change, bigger index
    }

    //checks if pair in same row and encodes
    for(i = i+1; i%5 != 0 ; i++){ 
        if(i == b){
            if((key_index_1 + 1 )% 5 == 0){ //checks if in final column
                key_index_1 = key_index_1 - 4;
            }else{
                key_index_1 = key_index_1 + 1;
            }
            if((key_index_2 + 1 )% 5 == 0){ //checks if in final column
                key_index_2 = key_index_2 - 4;
            }else{
                key_index_2 = key_index_2 + 1;
            }
            encode_str = string{key[key_index_1], key[key_index_2]};
            break;
        }
    }
    return encode_str;
}

string decode_pair(const string &pr, const string &key){
    string decode_str;
    int key_index_1 = key.find(pr[0]); 
    int key_index_2 = key.find(pr[1]);
    int i;
    int b; 

    //finds smaller index
    if(key_index_1 < key_index_2){
        i = key_index_1; //when iterating through indexes, smaller index
        b = key_index_2; //does not change, bigger index
    }else{
        i = key_index_2;//changes, smaller index
        b = key_index_1;//does not change, bigger index
    }
    
    //checks if pair in same column and encodes
    for(i; i <= key.length(); i+=5){ 
        if(i == b){
            if(key_index_1 == 0){ //checks if in final row
                key_index_1 = key_index_1 + 20;
            }else{
                key_index_1 = key_index_1 - 5;
            }
            if(key_index_2 == 0){ //checks if in final row
                key_index_2 = key_index_2 + 20;
            }else{
                key_index_2 = key_index_2 - 5;
            }
            decode_str = string{key[key_index_1], key[key_index_2]};
            break;
        }
    }

    //pairs in different columns and rows 
    if(key_index_1 - 6 == key_index_2 || key_index_1 + 4 == key_index_2){ //top right and bottom right
        key_index_1 = key_index_1 - 1;
        key_index_2 = key_index_2 + 1;
        decode_str = string{key[key_index_1], key[key_index_2]};
    }
    else if(key_index_1 - 4 == key_index_2 || key_index_1 + 6 == key_index_2){ //top left and bottom left
        key_index_1 = key_index_1 +1;
        key_index_2 = key_index_2 - 1;
        decode_str = string{key[key_index_1], key[key_index_2]};
    }
    
    
    //resets i, finds smaller index
    if(key_index_1 < key_index_2){
        i = key_index_1; //when iterating through indexes, smaller index
        b = key_index_2; //does not change, bigger index
    }else{
        i = key_index_2;//changes, smaller index
        b = key_index_1;//does not change, bigger index
    }

    //checks if pair in same row and encodes
    for(i = i+1; i%5 != 0; i++){ 
        if(i == b){
            if((key_index_1)% 5 == 0){ //checks if in final column
                key_index_1 = key_index_1 + 4;
            }else{
                key_index_1 = key_index_1 - 1;
            }
            if((key_index_2)% 5 == 0){ //checks if in final column
                key_index_2 = key_index_2 + 4;
            }else{
                key_index_2 = key_index_2 - 1;
            }
            decode_str = string{key[key_index_1], key[key_index_2]};
            break;
        }
    }

    return decode_str;
}

string encode(const string &plaintxt, const string &key){
    string plain = prepare_plaintext(plaintxt);
    string encode_str;
    string pair;

    //finds pairs and encodes
    for(int i = 0; i < plain.length(); i+=2){
        pair = string{plain[i], plain[i+1]};
        encode_str += encode_pair(pair, key);
    }
    return encode_str;
}

string decode(const string &encodedtxt, const string &key){
    string decode_str;
    string pair;

    //finds pairs and encodes
    for(int i = 0; i < encodedtxt.length(); i+=2){
        pair = string{encodedtxt[i], encodedtxt[i+1]};
        decode_str += decode_pair(pair, key);
    } 
    return decode_str;
}
