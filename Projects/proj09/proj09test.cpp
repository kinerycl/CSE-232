#include"proj09_bimap.h"
#include<algorithm>
using std::lower_bound;
#include <utility>
using std::make_pair; using std::pair;
#include<iostream>
using std::cout; using std::cin; using std::endl;
#include <vector>
using std::vector; 
#include <string>
using std::string; 


int main(){
    BiMap bm({{"a","z"},{"c","g"},{"b","n"},{"e","c"}});

    auto pr_result = bm.remove("c");
    //cout << bm << endl;
    //cout << pr_result.first << " " << pr_result.second << endl;
    //string pr_key_ans = "bill"; 
    //string pr_val_ans = "1";
    //string val = bm.value_from_key("bill");
    //string val_ans = "";
    //ASSERT_EQ(pr_result.first, pr_key_ans);
    //ASSERT_EQ(pr_result.second, pr_val_ans);
    //ASSERT_EQ(val, val_ans);

    //pr_result = bm.remove("irving");
    //pr_key_ans = ""; 
    //pr_val_ans = "";
   // ASSERT_EQ(pr_result.first, pr_key_ans);
   // ASSERT_EQ(pr_result.second, pr_val_ans);

    //ostringstream oss;
    //oss << bm;
    //string ans = "abby : 3, alan : 2";
    //string str_result = oss.str();
   // ASSERT_EQ(ans, str_result);
}


