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
	for(int i = 0; i < project1.mod; i++){
		inverse = ((project1.multiplier * i) % project1.mod);
		if(inverse == 1){
			cout << "Inverse Modulo found" << endl;
			inverse_modulo = i;
			break;
		}

	}

	for(int j = 0; j < strlen(project1.affine_encrypted_text); j++){
        if(project1.affine_encrypted_text[j] == ' ')
          project1.affine_decrypted_text[j] = project1.affine_encrypted_text[j];
        else{
					if(project1.mod == 26){
          		project1.cipherindex[j] = (((26 + project1.affine_encrypted_text[j] - project1.offset)*inverse_modulo) % project1.mod);
							ii = project1.cipherindex[j];
							project1.affine_decrypted_text[j] = project1.upper[ii];
					}
					else if(project1.mod == 52){
          		project1.cipherindex[j] = (((52 + project1.affine_encrypted_text[j] - project1.offset)*inverse_modulo) % project1.mod);
							ii = project1.cipherindex[j];
							project1.affine_decrypted_text[j] = project1.upper_lower[ii];
					}
				}

	}
	ofstream affine_plain_text("blockaffinecipherplaintextoutput.txt");
  cout << "Writing block affined decrypted text to blockaffinecipherplaintextouput.txt" << endl;
	affine_plain_text.write(project1.affine_decrypted_text,strlen(project1.affine_decrypted_text));
	affine_plain_text.close();

}
