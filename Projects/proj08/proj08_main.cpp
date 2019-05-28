#include "proj08.h"
#include <iostream>
#include<string>
using std::string; using std::to_string;

int main(int, char**args) {

  Painter painter(args[1]); //want to change to file name
  painter.CreateCanvas();

  auto result = painter.GetErrorLog().empty() ? 
                painter.GetCanvas() :
                painter.GetErrorLog();

  for (auto &line : result) 
    std::cout << line << "\n";
}
