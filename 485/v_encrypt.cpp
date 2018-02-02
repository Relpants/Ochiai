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

  ifstream plain_text("plaintext.txt");       //set as input file
  int index = 0;
  if(!plain_text){              //verify you can read file
    cout << "Error could not open plain text file...perhaps it does not exist" << endl;
    project1.file_flag = false;     // cant read file set flag to false
    return;                     
  }
  while(!plain_text.eof()){       //read contents of file until end of file
    plain_text >> project1.text[index];     //read in 
    char c = project1.text[index];        
    if(project1.mod == 26){               //make sure that if uppercase was selected we convert to alluppercase characters
      if(islower(c))                    //is it a lowercase ?
        project1.text[index] = toupper(c);    //convert to uppercase
    }

    index++;
  }
  plain_text.close();         //close file
}

void ReadVKey(){

  ifstream vkey("vcipherkey.txt");      //set as input file
  int index = 0;
  if(!vkey){          //can we open ?
    cout << "Error could not open the file vcipherkey.txt perhaps it does not exist" << endl;
    project1.file_flag = false;     //cant read file set flag to false
    return;
  }
  while(!vkey.eof()){           //same as above read the key in until end of file
    vkey >> project1.key[index];
    char c = project1.key[index];
    if(project1.mod == 26){       //same as above if just uppercase alphabet 
      if(islower(c))          //check if lowercase
        project1.key[index] = toupper(c); //convert to uppercase
    }

    index++;
  }

  vkey.close();         //close file
}

void PadKey(){
	int j = 0;
	for(int i = 0; i < strlen(project1.text); i++){            //while text in array
		if(j == strlen(project1.key)){        //if reach end of key set other index to zero
			//cout <<" HERE " << endl;
			j = 0;                       //set back to zero, to go back through key again
		}

			//cout <<"key_array: " << key_array[j] << endl;
			project1.padded_key[i] = project1.key[j];            //read in key characters to padded_key characters
			//cout <<"padded_key_array["<<i<<"]: " << padded_key_array[i] << endl;
			j++;           //increment other index 
	}

}

void VigenereEncrypt(){
  int ii=0;
  project1.text_index=0;
  project1.key_index=0;
	for(int i = 0; i < strlen(project1.text); i++){                //while text exists iterate
    if(project1.mod == 26){                   //if uppercase alphabet
        //cout << "lowercase before " << project1.vigenere_encrypted_text[i] << endl;
        for(int j = 0; j < (project1.upper).length(); j++){             //iterate through uppercase string
          if(project1.text[i] == project1.upper[j])
              project1.text_index = j;                            //grab the corresponding index of the letter in text from the "alphabetic" string
        }
        for(int k = 0; k < (project1.upper).length(); k++){       
          if(project1.padded_key[i] == project1.upper[k])
              project1.key_index = k;                             //grab the corresponding index of the key from the "alphabetic" string
        }
        ii = ((project1.text_index + project1.key_index) % project1.mod);                     //perform vigenere encryption formula and grab the index of the encrypted letter
        project1.vigenere_encrypted_text[i] = project1.upper[ii];                       //compare to the "alphabetic" string using the index to grab the resulting letter
        //cout << "uppercase after" << project1.vigenere_encrypted_text[i] << endl;
    }
    else if(project1.mod == 52){                                                          //if uppercase followed by lowercase
        //cout << "uppercase before" << project1.vigenere_encrypted_text[i] << endl;
        for(int j = 0; j < (project1.upper_lower).length(); j++){                   //use upper and lowercase alphabetic string
          if(project1.text[i] == project1.upper_lower[j])
              project1.text_index = j;                            //grab the corresponding index of the letter in text from the "alphabetic" string
        }
        for(int k = 0; k < (project1.upper_lower).length(); k++){
          if(project1.padded_key[i] == project1.upper_lower[k])
              project1.key_index = k;                             //grab the corresponding index of the key from the "alphabetic" string
        }
        ii = ((project1.text_index + project1.key_index) % project1.mod);           //perform vigenere encryption formula using the indexes to grab the index of the encrypted letter
        project1.vigenere_encrypted_text[i] = project1.upper_lower[ii];         //using the encrypted letter index grab the resulting encrypted letter
        //cout << "uppercase after" << project1.vigenere_encrypted_text[i] << endl;
    }

	}
	ofstream vigenere_cipher_text("vigenerecipheroutput.txt");             //write out to file
  cout << "Writing Vigenere Encrypted text to vigenerecipheroutput.txt" << endl;      //print useful message
	vigenere_cipher_text.write(project1.vigenere_encrypted_text,strlen(project1.vigenere_encrypted_text));       //write out whole encrypted text
	vigenere_cipher_text.close();        //close file

}
