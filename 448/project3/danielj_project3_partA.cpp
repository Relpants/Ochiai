

/*

	Daniel Aldridge
	CPE 448
	Project3 Part A
	3/7/18
*/








#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <math.h>

using namespace std;

#define NUM_STATIONS 5				//number of stations is 5

float running_time=0;
float timer = 0;						//flag for printing the running time when a station transmits succes.
int array[100];							//current time gets updated after each pass slot*51.2
int array_index=0;							//dummy array to hold random values 
int array_nums;							//index of the array

int run(int num_of_stations, int rnum, int slot);		// caller function
class station{
	public:
	void reset(){
		Next_attempt = 0;		//reset function called at to initalize values
		Collision_counter = 0;
	}
	
	void collision(int random, int station_number,int slot){		//function for collision
		int tmp;
		int tslot = slot + 1;
		Collision_counter++;			//update collision counter
		tmp = backoff_calc(Collision_counter);		//grab the backoff value using the collision counter
		Next_attempt = ( random % tmp ) + tslot;	//next attempted slot = random number from array % tmp + tslot which is the next slot
		cout << "Station :" << station_number << " backing off to slot " << Next_attempt << " collisions: " << Collision_counter << endl;
	}
	bool transmit_checker(int T){
		return Next_attempt == T;		//if the station's next attempt is the current slot
	}
	int stations_next_attempt(){
		return Next_attempt;			//return the station's next attempt
	}	
	private:
		int Next_attempt;
		int Collision_counter;
		int backoff_calc(int n){
			int mask = pow(2,n);		//backoff calculator
			return mask;
		}
		


};

station S[5];



int run(int num_of_stations,int slot){
	int slot_collision_counter=0;			//reset the slot's collision counter
	int transmitter_station;				//who is the transmitter station
	timer = slot* 51.2;
	for(int i=0; i < num_of_stations; i++){		//update the counter
		if(S[i].transmit_checker(slot))
			slot_collision_counter++;		//how many collisions at slot ???
	}

	if(slot_collision_counter == 1){
		for(int i = 4; i >= 0; i--){
			if(S[i].stations_next_attempt() == slot)
				transmitter_station = i;		//grab the lowest station number this will be the one transmitting because there is no collision at this slot
		}
		cout << "Station :" << transmitter_station << " has successfully transmitted " << endl;
		running_time = timer;
	}
	else if(slot_collision_counter > 1){
		for(int i=0; i < num_of_stations; i++){
			if(S[i].transmit_checker(slot)){
				S[i].collision(array[array_index],i,slot);			//call collision function on each station whose next attempt is at this slot
				array_index++;
				if(array_index == array_nums)
					array_index = 0;			//loop back to beginning of random number array
			}
			
		}
	}
	else 
		cout << "No stations transmitted at this slot " << endl;    //no stations transmitted
	
}


int main(int argc, char *argv[] ){

	
	ifstream random_nums;
	int slot=0;
	int numer=0;
	random_nums.open(argv[1], ios::in);		//open Part1_rn.txt
	if(random_nums == 0){
		cout << "Random number file did not open correctly exiting now.."<<endl;
		return 0;
	}

	for(int i=0; i < NUM_STATIONS; i++)
		S[i].reset();			//initalize all stations
	for(array_nums = 0; !random_nums.eof(); array_nums++)
		random_nums >> array[array_nums];		//read into array
	while(numer < array_nums){
		numer++;				//iterate through random number array and use a different number each time		
		cout << "-------------------------------------------"<< endl;
		cout << "Checking time slot: "<< slot << endl;
		run(NUM_STATIONS,slot);		//call run function
		if(running_time > 0){		//if one station has transmitted once
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
