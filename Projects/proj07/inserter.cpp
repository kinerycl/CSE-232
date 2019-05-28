#include<iostream>
using std::cout; using std::endl;
#include<algorithm>
using std::set_union; using std::copy;
#include<iterator>
using std::inserter; using std::ostream_iterator;
#include<string>
using std::string;
#include<set>
using std::set;

int main (){
  
  set<long> s1 ={1,2,3,4,5};
  set<long> s2 = {3,4,5,6,7};
  set<long> result;
  set_union(s1.begin(), s1.end(),
	    s2.begin(), s2.end(),
	    inserter(result, result.end())
	    );
  copy(result.begin(), result.end(), ostream_iterator<long>(cout, ",") );
  cout << endl;
}
	  
