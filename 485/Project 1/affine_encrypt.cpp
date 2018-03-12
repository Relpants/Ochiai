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
#include <math.h>
#include "lab1.h"

using namespace std;

void AffineEncrypt(){
  int ii = 0;
  int j = 0;
  int k = 0;
  project1.text_index=0;
  cout << "Dividing up the vigenere cipher text into blocks of two" << endl;          //divide the vigenere text into blocks of two
  for(int i = 0; i < strlen(project1.vigenere_encrypted_text);i++){         //iterate through encrypted array
      if(k==2){                                         
          project1.two_block_ciphertext[j] = ' ';           //add space between every 2 characters
          k = 0;
          i--;
      }
      else{                                                 //otherwise read in encrypted text to the two_block array
          project1.two_block_ciphertext[j] = project1.vigenere_encrypted_text[i];
          k++;
      }
      j++;

  }
cout << "Padded Cipher text " << project1.two_block_ciphertext << endl;       //print out the padded array now in the form of blocks of two
cout << "Enter the desired multiplier" << endl;           //read in multiplier
cin >> project1.multiplier;

int tmp_mult = project1.multiplier;
int tmp_mod = project1.mod;
int tmp = 0;
if(project1.multiplier > project1.mod){               //check if values are co-prime
	while(tmp_mod!=0){                         //while not zero
		tmp = tmp_mult % tmp_mod;           //do modulo 
		tmp_mult = tmp_mod;
		tmp_mod = tmp;
	}
	if(tmp_mult!=1){                               //keep performing operation and verify that the values are co-prime ... i.e they share no other factor other than one
		cout << "The Values are not coprime exiting program..." << endl;        //if value is not one they are not coprime
    project1.coprime_check = false;         //set flag 
    return; 
  }
}
else if(project1.multiplier <= project1.mod){         //doing the same thing as above but in this case the multiplier is greater than the modulo
	while(tmp_mult!=0){
		tmp = tmp_mod % tmp_mult;
		tmp_mod = tmp_mult;
		tmp_mult = tmp;
	}
	if(tmp_mod!=1){                          //again if this value is not zero after looping through the two numbers share a factor other than 1
		cout << "The Values are not coprime...exiting program..." << endl;          //print message
    project1.coprime_check = false;         //set flag
    return;
  }
}




cout << "Enter the offset" << endl;       //read in offset
cin >> project1.offset;

int pad_index = 0;
ofstream affine_cipher_text("blockaffinecipheroutput.txt");           //create output file for affine cipher text
for(int i = 0; i<strlen(project1.two_block_ciphertext); i++){       //iterate while content in the array
      if((project1.two_block_ciphertext[i]) == ' '){              
          project1.affine_encrypted_text[i] = project1.two_block_ciphertext[i];     //if a space read it in
      }
      else{
          if(project1.mod == 26){         //if uppercase
            for(int j = 0; j < (project1.upper).length(); j++){
              if(project1.two_block_ciphertext[i] == project1.upper[j])         //grab index of the text from alphabetic string
                  project1.text_index = j;
              }
              ii = (((project1.multiplier * project1.text_index) + project1.offset) % project1.mod);    //grabing the index or number corresponding the the letter
	            if(ii <= 9){         //if the number is less than 9
		              affine_cipher_text << '0';        //pad with extra zero to make the blocks even
		              affine_cipher_text << ii;         //write out number
              		pad_index++;
                  if(pad_index ==2){              //if wrote out two numbers
			               affine_cipher_text << ' ';    //write out a space
			               pad_index = 0;
	      	        }
	            }
	            else{
		              affine_cipher_text << ii;         //write out number
	                pad_index++;
		              if(pad_index ==2){              //again if written out two numbers 
			               affine_cipher_text << ' ';      //write out a space
			               pad_index = 0;
	      	        }
	            }
		
              project1.affine_encrypted_text[i] = project1.upper[ii];         //grab the corresponding encrypted letter from the index
          }
          else if(project1.mod == 52){            // do the same operation as above except for uppercase followed by lowercase
            for(int j = 0; j < (project1.upper_lower).length(); j++){
              if(project1.two_block_ciphertext[i] == project1.upper_lower[j])         //using upper_lower string
                  project1.text_index = j;
              }
              ii = (((project1.multiplier * project1.text_index) + project1.offset) % project1.mod);
              if(ii <= 9){
                  affine_cipher_text << '0';
                  affine_cipher_text << ii;
                  pad_index++;
                  if(pad_index == 2){
                    affine_cipher_text << ' ';        //same as above
                    pad_index = 0;
                  }
              }
              else{
                  affine_cipher_text << ii;
                  pad_index++;
                  if(pad_index == 2){
                    affine_cipher_text << ' ';
                    pad_index = 0;
                  }
              }
              project1.affine_encrypted_text[i] = project1.upper_lower[ii];
          }
      }
  //cout << "Value: " << what << endl;
}
cout << "Writing Block affine encrypted text to blockaffinecipheroutput.txt" << endl;       //print useful message
affine_cipher_text.close();       //close file
}
