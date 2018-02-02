/*

Daniel Aldridge
CS 485 PROJECT1

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

proj project1;


int main(){
  project1.upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";                                  //uppercase alphabet
  project1.upper_lower = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";  //uppercase and lowercase alphabet
  project1.coprime_check = true;                                                  //set flag to true *will be false if not co-prime*
  project1.file_flag =true;                                                       //file reading checker flag
  cout << "Are we using an all uppercase alphabet(modulo = 26, enter 'S' or both lowercase and uppercase(modulo = 52, 'L'))" << endl;
  cin >> project1.answer;           //read in user selection
  if(project1.answer == 'S'){       
     project1.mod = 26;             //set modulo based on answer
  }
  else if(project1.answer == 'L'){
     project1.mod = 52;             //same as above
  }
  else{                             //exit if not valid choice
     cout << "Did not pick a correct choice for alphabet... exiting now..." << endl;
     return 0;
  }

  cout << "Reading plain text from plaintext.txt" << endl;
  ReadPlainText();        //read plain text from plaintext.txt
  if(project1.file_flag == false){
    return 0;
  }
  cout << "Plain Text: " << project1.text << endl;
  cout << endl;

  cout << "Reading key for vigenere from vcipherkey.txt" << endl;
  ReadVKey();             //read vigenere key
  if(project1.file_flag == false){
    return 0;
  }
  cout << "Key: " << project1.key << endl;
  cout << endl;

  cout << "Padding key to match length of plain text so encryption can be performed properly" << endl;
  PadKey();               //pad the key
  cout << "Padded Key: " << project1.padded_key << endl;
  cout << endl;

  cout << "Performing Vigenere Encryption on plain text now..." << endl;
  VigenereEncrypt();      // encrypt with vigenere cipher
  cout << "Vigenere Encrypted Text: " << project1.vigenere_encrypted_text << endl;
  cout << endl;

  cout << "Perfoming Affine Encryption now.." << endl;
  AffineEncrypt();        // encrypt with block affine
  if(project1.coprime_check == false){      //are the multiplier and modulo co-prime? if not exit
    return 0;
  }
  //cout << "Affine Encrypted cipher text Expressed as letters (*written in correct format to blockaffinecipheroutput.txt as numbers*): " << project1.affine_encrypted_text << endl;
  cout << endl;

  cout << "Perfoming Block Affine Decryption now..." << endl;
  AffineDecrypt();      //decrypt with block affine
  cout << "Affine Decrypted cipher text: " << project1.affine_decrypted_text << endl;
  cout << endl;

  cout <<"Perfoming Vigenere Decryption Now..." << endl;
  VigenereDecrypt();    //decrypt with vigenere
  cout << "Final text: " << project1.vigenere_decrypted_text << endl;
  cout << endl;



 return 0;
}
