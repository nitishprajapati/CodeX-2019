
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>

using namespace std;

int main(){
  map< pair<int,float> , int > data;      map< pair<int,float> , int >::iterator it;
  map< pair<int,float> , int > map2;
  pair<int,float> idTempPair;
  //int countOfLines=0;
  int id;
  int timestamp;
  float temp;
  char comma;

  ifstream myfile("input.txt");

  string line;
  while (std::getline(myfile, line))
  {
      istringstream tokenizer(line);
      if (!(tokenizer >> id >> comma >> timestamp >> comma >> temp)) { continue; }

      if(timestamp>=0 && timestamp<=59 && temp<=(float)100.00 && temp>=(float)0.00){
        //countOfLines++;
        idTempPair = make_pair(id, temp);
        data[idTempPair] = data[idTempPair] + 1;
        map2[idTempPair] = timestamp;
      }

  }

  myfile.close();


  ofstream outFile("output.txt");
    for(it = data.begin(); it!=data.end(); it++){
      if(it == data.begin())
        if(it->second == 1)
          outFile<<it->first.first<<", "<<map2[it->first]<<", "<<it->first.second;
        else
          outFile<<it->first.first<<", "<<"0, "<<it->first.second<<", "<<it->second;

      else
        if(it->second == 1)
          outFile<<'\n'<<it->first.first<<", "<<map2[it->first]<<", "<<it->first.second;
        else
          outFile<<'\n'<<it->first.first<<", "<<"0, "<<it->first.second<<", "<<it->second;
    }
  outFile.close();
  return 0;
}
