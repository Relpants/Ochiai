/*

Daniel Aldridge
CS 485 Project 1

Block Affine Encrypter
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

void AffineEncrypt(){
  int ii = 0;
  int j = 0;
  int k = 0;
  cout << "Dividing up the vigenere cipher text into blocks of two" << endl;
  for(int i = 0; i < strlen(project1.vigenere_encrypted_text);i++){
      if(k==2){
          project1.two_block_ciphertext[j] = ' ';
          k = 0;
          i--;
      }
      else{
          project1.two_block_ciphertext[j] = project1.vigenere_encrypted_text[i];
          k++;
      }
      j++;

  }
cout << "Padded Cipher text " << project1.two_block_ciphertext << endl;
cout << "Enter the desired multiplier" << endl;
cin >> project1.multiplier;
cout << "Enter the offset" << endl;
cin >> project1.offset;
//int what=0;
for(int i = 0; i<strlen(project1.two_block_ciphertext); i++){
  //what = (((multiplier * reading[i]) + offset) % project1.mod);
      if((project1.two_block_ciphertext[i]) == ' '){
          //cout << "Doing nothing on this "<< endl;
          project1.affine_encrypted_text[i] = project1.two_block_ciphertext[i];
      }
      else{
          if(project1.mod == 26){
              project1.cipherindex[i] = (((project1.multiplier * project1.two_block_ciphertext[i]) + project1.offset) % project1.mod);
              ii = project1.cipherindex[i];
              project1.affine_encrypted_text[i] = project1.upper[ii];
          }
          else if(project1.mod == 52){
              project1.cipherindex[i] = (((project1.multiplier * project1.two_block_ciphertext[i]) + project1.offset) % project1.mod);
              ii = project1.cipherindex[i];
              project1.affine_encrypted_text[i] = project1.upper_lower[ii];
          }
      }
  //cout << "Value: " << what << endl;
}
ofstream affine_cipher_text("blockaffinecipheroutput.txt");
cout << "Writing Block affine encrypted text to blockaffinecipheroutput.txt" << endl;
affine_cipher_text.write(project1.affine_encrypted_text,strlen(project1.affine_encrypted_text));
affine_cipher_text.close();
}
