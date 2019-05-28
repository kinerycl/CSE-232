#include <iostream>
using std::cout; using std::cin; using std::endl; using std::fixed;
#include<cmath>
using std::sqrt;

int main(){
   
    long long perf_num;
    long long k_max;

    cin >> perf_num >> k_max; // vaild input check
    if(perf_num < 6 or k_max < 1){
        cout << 0 << endl;
        return(0);
    }


    long long add_vals = 0;
    long long divisor = 2; // potential divisiors
    long long divisor2 = 0; // second divisor
    while(divisor <= sqrt(perf_num)){
        if(perf_num % divisor == 0){
            add_vals += divisor;
            if(perf_num / divisor != divisor){
                divisor2 = perf_num / divisor;
                add_vals += divisor2;
            }
        }
        divisor++;
    }
   
    long flag=0;
    long k;
    for (k=1; k<k_max; k++){
        if(((add_vals * k) + 1) == perf_num){
               flag=1;
               break;
        } 
    }

    if (flag==1){
        cout << k << endl;
        } 
    else{
            cout << 0 << endl;
        }

    return(0);
}