/*

	Daniel Aldridge
	CPE 485
	2/15/17

*/





#include <stdio.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

void setof12binarycheck();				//function to call part b

int main(int argc, char* argv[]){

	
	FILE* file_one;					//first binary file
	FILE* file_two;					//second binary file
	char file_checker1;				//variable to hold first binary file character
	char file_checker2;				//variable to hold second binary file character
							// We will check each file character by character
	bool breaker = true;				//bool checker


	file_one = fopen(argv[1],"rb");			//open the first file based on the first command line argument IN BINARY MODE BECAUSE OF "rb"
	if(file_one==0){				//if cant open or you didnt pass in argument
		cout << "Binary file1 did not open correctly"<< endl;		//print file did not open correctly
		return 0;							//exit
	}
	file_two = fopen(argv[2],"rb");			//open the second file based on the second command line argument IN BINARY MODE BECAUSE OF "rb"
	if(file_two==0){				//if cant open or you didnt pass in second argument
		cout << "Binary file2 did not open correctly"<< endl;		//print file did not open correctly
		return 0;							//exit just like before
	}

	while(!feof(file_one) && !feof(file_two)){			//loop through both input files until we reach the end of both
		fread(&file_checker1, sizeof(char), 1, file_one);	//read in character from file one
		fread(&file_checker2, sizeof(char), 1, file_two);	//read in character from file two
		if(file_checker1 != file_checker2){			//check to see if they are equal
			cout << argv[1] << " and " << argv[2] << " binary files differ...." << endl;		//if different then no need to check rest of files they are different
			breaker = false;				//set flag
			break;						//break
		}
	   if(breaker == false)						//break from nested loop
		break;
	   
	}
	if(breaker !=false)						//if we reached this point and flag was not set the files are indeed the same
		cout << "Files are the same " << endl;			//print message

	
	fclose(file_one);						//close file one
	fclose(file_two);						//close file two
	
	
	char part;							//variable for user input to check and see if they want to execute part b of project
	cout << "Do you wish to perform part b of this project...y/n" << endl;		//ask user
	cin >> part;							//read in character
	while(part!='y' && part!='n'){					//Error handling make sure the user dosent input wrong character
		cout << "Enter a valid key y for yes or n for no" << endl;
		cin >> part;
	}	
	if(part == 'y'){						//if yes or y 
		cout << "Now starting part b of project " << endl;	
		setof12binarycheck();					//execute part b of project
	}
									//n or "no" will just get to here and program will quit
	return 0;

}

void setof12binarycheck(){
	
	const char *file_array[12] = {"file1","file2","file3","file4","file5","file6","file7","file8","file9","file10","file11","file12"};		//array of all file names 
																	//could have done command line arguments but this is more clean
	
	for(int i = 0; i < 12; i++){					//iterate through each file and compare it to itself and other 11 files
		ifstream file_1;					//declare input file
		file_1.open(file_array[i], ios::binary);		//open the file based on iteration "i.e first time will be index 0 which is file1" and OPEN IT IN BINARY MODE
		if(file_1 == 0){						//if file could not be open 
			cout << "Binary "<<file_array[i]<<" did not open correctly" << endl;	//print message
			return;
		}
		for(int j = 0; j < 12; j++){				//nested loop to compare each file with other 11 and itself
			ifstream file_2;				//declare input file
			if(j == i)					//if we are comparing the file to itself
				goto here;					// no need to check "jump" to end
			
			file_2.open(file_array[j], ios::binary);	//open file IN BINARY MODE
			if(file_2 == 0){					//if we cant open
				cout << "Second Binary... specifically "<<file_array[j]<<" did not open correctly" << endl;		//print message
				return;					//exit
			}

			char checker1;				//variable for character being read from first file
			char checker2;				//variable for character being read from second file
			while((!file_1.eof()) && (!file_2.eof())){	//loop while both files have not reached the end
				file_1 >> checker1;		//read in character from first file
				file_2 >> checker2;		//read in character from second file
				if(checker1 != checker2){		//if the characters are not the same
					cout << file_array[i] << " and " << file_array[j] << " Differ...." << endl;  //print they are not equal
					file_2.close();		//close that second file
					goto next;		//jump to next
				}
			        
			}
			here:					//here jump point
			cout << file_array[i] << " and " << file_array[j] << " are equal " << endl;		//if we looped through and files are equal message, if we jumped because they differ wont print
			next:					//next jump point																
			if(file_2.is_open()){		//error handling make sure second file closes
			   cout << "closing file2 "<<endl;
			   file_2.close();	//close
			}
			
			
		}
		if(file_1.is_open()){				//same for first file
			//cout <<"closing file1 " << endl;			
			file_1.close();
		}
	}

	
}



	
