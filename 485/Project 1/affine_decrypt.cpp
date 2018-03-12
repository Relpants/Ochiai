/*

Daniel Aldridge
CS 485 Project 1

Block Affine Decrypter
To compile project...

type command make...

To run project....
Type command

./project1

*/
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "lab1.h"

using namespace std;


void AffineDecrypt(){
	//Calculate Inverse Modulo
	int ii=0;
	int inverse = 0;
	int inverse_modulo = 0;
	project1.text_index=0;
	for(int d = 0; d < project1.mod; d++){						//loop through all values
		inverse = ((project1.multiplier * d) % project1.mod);		//grab the "possible" inverse
		if(inverse == 1){				//if this value is one  we have found the inverse modulo
			cout << "Inverse Modulo found" << endl;
			inverse_modulo = d;
			break;					//break out
		}

	}

	for(int i = 0; i < strlen(project1.affine_encrypted_text); i++){					//iterate through
        if(project1.affine_encrypted_text[i] == ' ' || project1.affine_encrypted_text[i] == '\0'){		//if a space or terminating char
          	project1.affine_decrypted_text[i] = project1.affine_encrypted_text[i];					//read in
        }
        else if(project1.affine_encrypted_text[i] != ' ' || project1.affine_encrypted_text[i] != '\0'){						//if it is not a space or null
					if(project1.mod == 26){								//for uppercase
						for(int j = 0; j < (project1.upper).length(); j++){
							if(project1.affine_encrypted_text[i] == project1.upper[j])
									project1.text_index = j;							//grab text index from "uppercase" string
							}
          					ii = (((project1.text_index - project1.offset)*inverse_modulo) % project1.mod);				//calculate the index of decrypted letter
							if(ii < 0)										//if somehow less than zero loop back through "uppercase" string
								ii = ii + 26;								//by adding 26 ... uppercase = 26 characters
							project1.affine_decrypted_text[i] = project1.upper[ii];				//grab the decrypted letter from the index
					}
					else if(project1.mod == 52){			// for uppercase and lowercase
						for(int j = 0; j < (project1.upper_lower).length(); j++){
							if(project1.affine_encrypted_text[i] == project1.upper_lower[j])
									project1.text_index = j;										//do same thing except using uppercase and lowercase string
							}
          					ii = (((project1.text_index - project1.offset)*inverse_modulo) % project1.mod);				//grab the index of decrypted letter
							if(ii < 0)
								ii = ii + 52;
							project1.affine_decrypted_text[i] = project1.upper_lower[ii];				//grab the decrypted letter from the index calculated
					}
		}
				//cout << "affine_decrypted_text["<<i<<"]:"<< project1.affine_decrypted_text[i] << endl;

	}

	ofstream affine_plain_text("blockaffinecipherplaintextoutput.txt");						//create output file
    cout << "Writing block affined decrypted text to blockaffinecipherplaintextouput.txt" << endl;
	affine_plain_text.write(project1.affine_decrypted_text,strlen(project1.affine_encrypted_text));			//write 
	affine_plain_text.close();				//close

}
