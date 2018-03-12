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
  project1.text_index=0;
  project1.key_index=0;
	for(int i = 0; i < strlen(project1.affine_decrypted_text); i++){           //remove space or blocks of two
        if(project1.affine_decrypted_text[i] != ' '){
            tmp[j] = project1.affine_decrypted_text[i];
            j++;
        }     
    }                                                 //tmp array now holds the text except no longer in blocks of two
	for(int i = 0; i < strlen(tmp); i++){
      if(project1.mod == 26){                   //for uppercase characters
        for(int j = 0; j < (project1.upper).length(); j++){
          if(tmp[i] == project1.upper[j])
              project1.text_index = j;            //grab text index
          }
        for(int k = 0; k < (project1.upper).length(); k++){
          if(project1.padded_key[i] == project1.upper[k]) 
              project1.key_index = k;           //grab key index
          }
	        ii = ((project1.text_index - project1.key_index + project1.mod) % project1.mod);     //using indexes calculate the decrypted letter's index
          project1.vigenere_decrypted_text[i] = project1.upper[ii];         //grab the decrypted letter using the index calculated
      }
      else if(project1.mod == 52){              //same as above except for uppercase and lowercase
        for(int j = 0; j < (project1.upper_lower).length(); j++){
          if(tmp[i] == project1.upper_lower[j])
              project1.text_index = j;
          }
        for(int k = 0; k < (project1.upper_lower).length(); k++){
          if(project1.padded_key[i] == project1.upper_lower[k])
              project1.key_index = k;
          }
          ii = ((project1.text_index - project1.key_index + project1.mod) % project1.mod);
          project1.vigenere_decrypted_text[i] = project1.upper_lower[ii];
      }
  }
	ofstream decrypted_text("secondplaintext.txt");                        //create ouptut file
  cout << "Writing final decrypted text to secondplaintext.txt" << endl;
	decrypted_text.write(project1.vigenere_decrypted_text,strlen(project1.vigenere_decrypted_text));           //write
	decrypted_text.close();        //close

}
