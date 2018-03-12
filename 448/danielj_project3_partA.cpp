#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using namespace std;

#define NUM_STATIONS 5

float running_time=0;
float timer = 0;
int array[100];
int array_index=0;
int array_size;

int run(int num_of_stations, int rnum, int slot, int time);
class station{
	public:
	void reset(){
		Next_attempt = 0;
		Collision_counter = 0;
	}
	
	void collision(int random, int station_number,int slot){
		int tmp;
		int tslot = slot + 1;
		Collision_counter++;
		tmp = backoff_calc(Collision_counter);
		Next_attempt = ( random % tmp ) + tslot;
		cout << "Station :" << station_number << " backing off to slot " << Next_attempt << " collisions: " << Collision_counter << endl;
	}
	bool transmit_checker(int T){
		return Next_attempt == T;
	}
	int stations_next_attempt(){
		return Next_attempt;
	}	
	private:
		int Next_attempt;
		int Collision_counter;
		int backoff_calc(int n){
			int mask = pow(2,n);
			return mask;
		}
		


};

station S[5];



int run(int num_of_stations,int slot){
	int slot_collision_counter=0;
	int transmitter_station;
	for(int i=0; i < num_of_stations; i++){
		if(S[i].transmit_checker(slot))
			slot_collision_counter++;
	}
	//cout << "slot_collision_counter: " << slot_collision_counter << endl;

	if(slot_collision_counter == 1){
		for(int i = 4; i >= 0; i--){
			if(S[i].stations_next_attempt() == slot)
				transmitter_station = i;
		}
		cout << "Station :" << transmitter_station << " has successfully transmitted " << endl;
		running_time = timer;
		//cout << "running time: " << running_time << endl;
	}
	else if(slot_collision_counter > 1){
		for(int i=0; i < num_of_stations; i++){
			if(S[i].transmit_checker(slot)){
				S[i].collision(array[array_index],i,slot);
				array_index++;
				if(array_index == array_size)
					array_index = 0;
			}
			
		}
	}
	else 
		cout << "No stations transmitted at this slot " << endl;
	
	timer = timer + 51.2;
}


int main(int argc, char *argv[] ){

	
	ifstream random_nums;
	int slot=0;
	int stupid=0;
	random_nums.open(argv[1], ios::in);/*
	if(random_nums == 0){
		cout << "Random number file did not open correctly exiting now.."<<endl;
		return 0;
	}*/

	for(int i=0; i < NUM_STATIONS; i++)
		S[i].reset();
	for(array_size = 0; !random_nums.eof(); array_size++)
		random_nums >> array[array_size];
	while(stupid < array_size){
		int num;
		stupid++;
		//random_nums >> num;
		cout << "-------------------------------------------"<< endl;
		cout << "Checking time slot: "<< slot << endl;
		run(NUM_STATIONS,slot);
		if(running_time > 0){
			cout << "In slot number "<< slot << " which is " << running_time << "ms " << endl;
			cout << "-------------------------------------------"<< endl << endl;
			return 0;
		}
		cout << "-------------------------------------------"<< endl << endl;
		slot++;


	}

	random_nums.close();


	

	return 0;


}