/*

Daniel Aldridge
CS 485 Project 1

Vigenere Decrypter
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


void VigenereDecrypt(){
  int ii = 0;
  int j = 0;
  char tmp[300];
	for(int i = 0; i < strlen(project1.affine_decrypted_text); i++){
        if(project1.affine_decrypted_text[i] != ' '){
            tmp[j] = project1.affine_decrypted_text[i];
            j++;
        }
    }
	for(int i = 0; i < strlen(tmp); i++){
      if(project1.mod == 26){
		      project1.cipherindex[i] = ((tmp[i] - project1.padded_key[i] + project1.mod) % project1.mod);
          ii = project1.cipherindex[i];
          project1.vigenere_decrypted_text[i] = project1.upper[ii];
      }
      else if(project1.mod == 52){
        project1.cipherindex[i] = ((tmp[i] - project1.padded_key[i] + project1.mod) % project1.mod);
        ii = project1.cipherindex[i];
        project1.vigenere_decrypted_text[i] = project1.upper_lower[ii];
      }
  }
	ofstream decrypted_text("secondplaintext.txt");
  cout << "Writing final decrypted text to secondplaintext.txt" << endl;
	decrypted_text.write(project1.vigenere_decrypted_text,strlen(project1.vigenere_decrypted_text));
	decrypted_text.close();

}
