
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(){
  int countOfLines=0;
  int id;
  int timestamp;
  float temp;
  char comma;

  ifstream myfile("input.txt");

  string line;
  while (std::getline(myfile, line))
  {
      istringstream tokenizer(line);
      if (!(tokenizer >> id >> comma >> timestamp >> comma >> temp)) { continue; } // error

      if(timestamp<=59 && temp<=(float)100.00)
      countOfLines++;
  }

  myfile.close();


  ofstream outFile("output.txt");
  outFile<<countOfLines;
  outFile.close();
  return 0;
}
