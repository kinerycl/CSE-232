#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
// add any other includes you need. Up to you

/*
  for this we will use:
  1 - rock
  2 - paper
  3 - scissors
*/

// PUT YOUR FUNCTIONS BELOW THIS LINE
int strategy1(int player, int previous_result, int previous_play, int opponent_play){
  if(previous_play != 3){
    return previous_play + 1;
  }else{
    return 1;
  }
}

int strategy2(int player, int previous_result, int previous_play, int opponent_play){
  if(previous_result == player or 0){ 
    return previous_play;
  }else{
    return opponent_play;
  }
}

int strategy3(int player, int previous_result, int previous_play, int opponent_play){
  if(previous_result == player or 0){ // not sure about "or"
    return previous_play;
  }else{
    int new_play = strategy1(player, previous_result, opponent_play, previous_play);
    return new_play;
    }
}

int score_round(int p1_play, int p2_play){
  if(p1_play == 1 and p2_play == 3){
    return 1;
  }
  if(p1_play == 3 and p2_play == 1){
    return 2;
  }
  if(p1_play == p2_play){
    return 0;
  }else{
    if(p1_play < p2_play){
      return 2;
    }else{
      return 1;
    }
  }
}
// MAIN IS BELOW, DON'T CHANGE

int main() {
 
  cout << boolalpha;   // print true or false for bools
  int test;
  cin >> test;
  
  switch (test) {
  case 1 : {   // strategy 1
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy1(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 1

  case 2:{    // strategy 2
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy2(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 2

  case 3: {    // strategy 3
    long player, previous_result, previous_play, opponent_play;
    cin >> player >> previous_result >> previous_play >> opponent_play;
    cout << strategy3(player, previous_result, previous_play, opponent_play) << endl;
    break;
  } // of case 3

  case 4: {       // score result
    long p1, p2;
    cin >> p1 >> p2;
    cout << score_round(p1, p2) << endl;
    break;
  } // of case 4
    
  } // of switch 
} // of main


	
