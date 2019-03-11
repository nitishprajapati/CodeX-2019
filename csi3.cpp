
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <utility>
#include <vector>
#include <set>

using namespace std;

int main(){
  map< pair<int,float> , int > data;      map< pair<int,float> , int >::iterator it;
  map< pair<int,float> , int > map2;
  map< pair<float,int> , set<int> > map3;      map< pair<float,int> , set<int>  >::iterator i;

  pair<int,float> idTempPair;
  pair<float,int> tempCountPair;

  set<int>::iterator sit;
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
        if(data[idTempPair]==1)
        map2[idTempPair] = timestamp;
      }

  }

  myfile.close();

  for(it = data.begin(); it!=data.end(); it++){
    tempCountPair = make_pair(it->first.second, it->second);
    map3[tempCountPair].insert(it->first.first);
  }


  ofstream outFile("output.txt");
    for(i=map3.begin(); i!=map3.end(); i++){
        for(sit=i->second.begin(); sit!=i->second.end(); sit++){
          outFile<<*sit<<' ';
        }
        outFile<<", ";
        outFile<<i->first.first<<", "<<i->first.second<<'\n';
    }

  outFile.close();
  return 0;
}
