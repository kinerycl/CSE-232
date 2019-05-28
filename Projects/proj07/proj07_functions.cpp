//sect 14, 10/29/18, project 7
#include "proj07_functions.h"
#include <set>
using std::set;
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include<string>
using std::string;
#include <fstream>
using std::ifstream; using std::ofstream;
#include<algorithm>
using std::transform;

void deletes (const string &word, set<string> & result){

    for(int i = 0; i < word.length(); i++){
        string dum_str = word; //copy of word
        string delete_str = dum_str.erase(i,1);
        result.insert(dum_str);
    }
}

void replaces(const string &word, set<string> & result){
    for(int i = 0; i < word.length(); i++){
        string dum_str = word; //copy of word
        string base_str = dum_str.erase(i,1); // word minus a letter
        for(char a:letters){
            string rep_str = base_str; //replace string
            rep_str.insert(i, 1, a);
            result.insert(rep_str); //insert replace word to set
        }
    }

}

void transposes (const string &word, set<string> &result){
    for(int i = 0; i < word.length(); i++){
        string dum_str = word; //copy of word
        if(dum_str[i+1]){ //range check
            char let_1 = dum_str[i];
            char let_2 = dum_str[i+1];
            string rep_str = dum_str.erase(i,2);

            //switches letters
            rep_str.insert(i, 1, let_2);
            rep_str.insert(i+1, 1, let_1);
            result.insert(rep_str);
        }
    }
}

void inserts (const string &word, set<string> &result){
     for(int i = 0; i <= word.length(); i++){
        string rep_str = word; //copy of word
        for(char a:letters){
            rep_str = word; //resets
            rep_str.insert(i, 1, a);
            result.insert(rep_str); //insert replace word to set
        }
    }
}

void read_words (string fname, set<string> &result){
    ifstream infile (fname);

    while(!infile.eof()){
        string s; //empty string for lines
        getline(infile, s);

        string ret_str;//empty string for words

        for(char c: s){
            if(!isalpha(c)){//ignores digits from string //try isalpha not equal zero
                continue;
            }
            if(c == ' '){
                transform(ret_str.begin(), ret_str.end(), ret_str.begin(), ::tolower);
                result.insert(ret_str);
                ret_str.clear();// empty string for new word
            }
            ret_str += c; //adds char to string
        } 

        if(ret_str.empty()){ //skips empty lines
            continue;
        }
        transform(ret_str.begin(), ret_str.end(), ret_str.begin(), ::tolower);
        result.insert(ret_str);
        ret_str.clear();// empty string for new word

    }

}

void find_completions(const string &w, const set<string> &word_list, set<string> &result){
    int w_len = w.length();//for substring
    for(string pos_word: word_list){
    string sub_word = pos_word.substr(0, w_len); 
        if(w == sub_word){
            result.insert(pos_word);
        }
    }
}

void find_corrections(const string &word, set<string> &result){
    deletes(word, result);
    replaces(word, result);
    transposes(word, result);
    inserts(word, result);
}

void find_2step_corrections(const string &word, set<string> &result){
    find_corrections(word, result);
    set<string> step1 = result; //copy of result for loop
    for(string correct_word: step1){
        find_corrections(correct_word, result);
    }
}

void find_reasonable_corrections(const set<string> & possibles, 
const set<string>&word_list, set<string> & result){
    for(string pos_word: possibles){
        if(word_list.find(pos_word)!= word_list.end()){ //if possible word in wordlist
            result.insert(pos_word);
        }
    }
}
