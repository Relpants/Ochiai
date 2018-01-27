/*

Daniel Aldridge
CS 485 Project 1

Vigenere Encrypter
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
 #include <ctype.h>
 #include "lab1.h"

 using namespace std;



void ReadPlainText(){

  ifstream plain_text("plaintext.txt");
  int index = 0;
  if(!plain_text){
    cout << "Error could not open plain text file...perhaps it does not exist" << endl;
    exit;
  }
  while(!plain_text.eof()){
    plain_text >> project1.text[index];
    char c = project1.text[index];
    if(project1.mod == 26){
      if(islower(c))
        project1.text[index] = toupper(c);
    }

    index++;
  }
  plain_text.close();
}

void ReadVKey(){

  ifstream vkey("vcipherkey.txt");
  int index = 0;
  if(!vkey){
    cout << "Error could not open the file vcipherkey.txt perhaps it does not exist" << endl;
    exit;
  }
  while(!vkey.eof()){
    vkey >> project1.key[index];
    char c = project1.key[index];
    if(project1.mod == 26){
      if(islower(c))
        project1.key[index] = toupper(c);
    }

    index++;
  }

  vkey.close();
}

void PadKey(){
	int j = 0;
	for(int i = 0; i < strlen(project1.text); i++){
		if(j == strlen(project1.key)){
			//cout <<" HERE " << endl;
			j = 0;
		}

			//cout <<"key_array: " << key_array[j] << endl;
			project1.padded_key[i] = project1.key[j];
			//cout <<"padded_key_array["<<i<<"]: " << padded_key_array[i] << endl;
			j++;
	}

}

void VigenereEncrypt(){
  int ii=0;
	for(int i = 0; i < strlen(project1.text); i++){
    if(project1.mod == 26){
        //cout << "lowercase before " << project1.vigenere_encrypted_text[i] << endl;
        project1.cipherindex[i] = ((project1.text[i] + project1.padded_key[i]) % project1.mod);
        ii = project1.cipherindex[i];
        project1.vigenere_encrypted_text[i] = project1.upper[ii];
        //cout << "uppercase after" << project1.vigenere_encrypted_text[i] << endl;
    }
    else if(project1.mod == 52){
        //cout << "uppercase before" << project1.vigenere_encrypted_text[i] << endl;
        project1.cipherindex[i] = ((project1.text[i] + project1.padded_key[i]) % project1.mod);
        ii = project1.cipherindex[i];
        project1.vigenere_encrypted_text[i] = project1.upper_lower[ii];
        //cout << "uppercase after" << project1.vigenere_encrypted_text[i] << endl;
    }

	}
	ofstream vigenere_cipher_text("vigenerecipheroutput.txt");
  cout << "Writing Vigenere Encrypted text to vigenerecipheroutput.txt" << endl;
	vigenere_cipher_text.write(project1.vigenere_encrypted_text,strlen(project1.vigenere_encrypted_text));
	vigenere_cipher_text.close();

}
