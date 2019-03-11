
	#include <bits/stdc++.h>
	#include <map>
	#include <set>
	#include <sstream>
	#include <string>
	#include <vector>
	#include <fstream>
	#include <utility>
	
	using namespace std;
	
	int main(){
	int i;
	
	int linecount=0;
	string line;
	int id;
	int timestamp;
	float temp;
	char comma;
	map< int/*sensor id*/,/*to*/int/*timestamp*/ > sensorToTimestamp;
	map< int/*sensor id*/,/*to*/float/*temperature*/ > sensorToTemp;
	map< int/*sensor id*/,/*to*/int/*initial timestamp*/ > sensorToInitTimestamp;
	map < pair<int,float> , int> map4ts;
	
	int previd;
	int prevts;
	float prevtemp;
	
	float gap;
	float increment;
	
	ofstream myfile2("input2.txt"); //gap filled file
	
		ifstream myfile("input.txt");
			while(std::getline(myfile, line))
			{
				std::istringstream tokenizer(line);
				tokenizer>>id>>comma>>timestamp>>comma>>temp;;
				
				if(!tokenizer){//improper format
					continue;
				}
				else //if correct format
				{
				if(map4ts.count(make_pair(id, temp)) == 0){
					map4ts[make_pair(id, temp)] = timestamp;
				}
					linecount++;
					if(linecount==1) //if it is first line
					{
						myfile2<<line<<'\n';
						sensorToTimestamp[id] = timestamp;
						sensorToTemp[id] = temp;
					}
					else{ //if it isn't first line
						if(sensorToTimestamp.count(id)==0)//if this sensor is first time
						{
							//cout<<"debug1\n";
							myfile2<<line<<'\n';
							sensorToTimestamp[id] = timestamp;
							sensorToTemp[id] = temp;
						}
						else if(sensorToTimestamp.count(id))//if this sensor has previously recorded
						{
							if(timestamp == sensorToTimestamp[id] + 1)//if the timestamp is one 
							{//	       greater than previous reading of same sensor..then also its fine
								myfile2<<line<<'\n';
								sensorToTimestamp[id] = timestamp;//UPDATE TIMESTAMP
								sensorToTemp[id] = temp;//UPDATE TEMPERATURE
							}
							else{//THERE IS A GAP!!!!
								gap = temp - sensorToTemp[id]; //find temperature difference
								increment = gap/((float)(timestamp - sensorToTimestamp[id]));
								for(i = sensorToTimestamp[id] + 1; i<=timestamp; i++){//fill gap. YAY!!
								  myfile2<<id<<", "<<i<<", "<<(float)(sensorToTemp[id] + increment)<<'\n';
							          sensorToTemp[id] = sensorToTemp[id] + increment;
								}
								sensorToTimestamp[id] = i - 1; // UPDATE TIMESTAMP
								sensorToTemp[id] = temp; //UPDATE TEMPERATURE
							}
						}
					}
					
				}
			}
		myfile.close();
		myfile2.close();
		
		// AT THIS POINT WE HAVE OUR FILE WITH GAPS FILLED. YAYYY!!!!
		// NOW LETS COMPRESS
		
		
		map< pair<int, float> , int > map1;	//map for id and temperature pair to store counts
		map< pair<float, int> , set<int> > map2;//map for temp and count pair to store sensor ids
		pair<int, float> p;
		
		
		ifstream inputfile("input2.txt");
			while(std::getline(inputfile, line))
			{
				std::istringstream tokenizer(line);
				
				tokenizer>>id>>comma>>timestamp>>comma>>temp;
				if(!tokenizer){ //invalid format
					continue;
				}
				else{
					p = make_pair(id, (std::trunc(100*temp)/100));
					map1[p] = map1[p] + 1;	
				}
			}
			
			for(auto it = map1.begin(); it!=map1.end(); it++){
			map2[make_pair(it->first.second/*temp*/, it->second/*count*/)].insert(it->first.first);//create set of ids with similar temp and count
			}
			
			
		inputfile.close();
		
		
		ofstream file("output.txt");
			for(auto it = map2.begin(); it!=map2.end(); it++){
				for(auto it2 = it->second.begin(); it2!=it->second.end(); it2++){ //print all sensor ids
					file<<*it2<<' ';
				}
				file<<", ";
				//file<<sensorToInitTimestamp[*(it->second.begin())]<<", ";//initial timestamp for that sensor
				file<<map4ts[make_pair(*(it->second.begin()), it->first.first)]<<", ";
				file<<it->first.first<<", "; //temperature. (i dont understand why it isn't printing decimal points. i checked properly)
				file<<it->first.second<<'\n';
			}
		file.close();
	return 0;
	}
	
