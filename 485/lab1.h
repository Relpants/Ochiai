
#ifndef PROJECT1_H
#define PROJECT1_H

struct proj{
char text[300];								//array for reading in plain text from plaintext.txt
char key[300];								//array for reading in key from vcipherkey.txt
char padded_key[300];						//array to pad key to match length of text
char vigenere_encrypted_text[300];			//array to store vigenere cipher text 
char vigenere_decrypted_text[300];			//array to store vigenere decrypted text.. i.e 2nd plaintext.txt
char affine_encrypted_text[300];			//array to store affine encrypted text ... written to blockaffinecipheroutput.txt
char affine_decrypted_text[300];			//array to store affine decrypted text ... written to blockaffinecipherplaintextoutput.txt
char two_block_ciphertext[300];				//array to store cipher text into blocks of two
int mod;									//modulo selected based on alphabet
char answer;								//checker for which alphabet was chosen
int multiplier;								//multiplier for block affine cipher
int offset;									//offset for block affine cipher
int key_index;								//index of key
int text_index;								//index of text
std::string upper;							//string holding all uppercase letters
std::string upper_lower;					//string holding uppercase followed by lower case
bool coprime_check;							//flag for is co-prime
bool file_flag;								//can you read file?
};

											//function calls 
void ReadPlainText();
void ReadVKey();
void PadKey();
void VigenereEncrypt();
void VigenereDecrypt();
void AffineEncrypt();
void AffineDecrypt();

extern proj project1;						


#endif
