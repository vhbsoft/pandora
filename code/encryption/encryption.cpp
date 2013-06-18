//
//====================================
//== PROVIDED FUNCTIONS:
//====================================
//- int encrypt(const char [] file_name, const char [] passphrase)
//- int decrypt(const char [] file_name, const char [] passphrase)
//- int CreateNewAccountFile(const char [] file_name)  
//- int md5Hash(const char [] account_no, char [] md5_hash_account_no)
//
//We will ensure that no linking library is needed and only "include" and copy and paste code is what is needed, which in that case we probably will provide a skeleton.
//

int md5Hash(const char [] account_no, char [] md5_hash_account_no);
int CreateNewAccountFile(const char [] account_no);
int Encrypt(const char [] account_no, const char [] passphrase);
int Decrypt(const char [] account_no, const char [] passphrase);

//--------------------------------------------------
//Encryption/Decryption using AES via a passphrase 
//
//int Encrypt(const char [] account_no, const char [] passphrase)
//int Decrypt(const char [] account_no, const char [] passphrase)
//
//- opens [md5_hash(account_no)] for read
//- replaces the file with the encrypted or decrypted one with the same file name 
//(it might need to overwrite (deletes and creates new file))
//- use passphrase as key for encryption
//- line-by-line encryption or entire file encryption 
//(whatever is easier, so it's up to you)
//
//--------------------------------------------------
int Encrypt(const char [] account_no, const char [] passphrase){

}

//--------------------------------------------------
//int CreateNewAccountFile(const char [] account_no)  
//
//- creates [md5_hash(account_no)]
//- returns 0 if success
//- returns non-zero if failed
//
//--------------------------------------------------

//--------------------------------------------------
//int md5Hash(const char [] account_no, char [] md5_hash_account_no)
//
//- calculates md5 checksum of account_no and stores it in md5_hash_account_no (passed by reference)
//- returns 0 if success
//- returns non-zero if failed
//--------------------------------------------------


#include <string>
#include <iostream>
using namespace std;

int md5Hash(const char [] account_no, char [] md5_hash_account_no)
{
	//Globals
		typedef unsigned char uint1; //  8bit
		typedef unsigned int uint4;  // 32bit
		typedef unsigned int size_type; // must be 32bit
		bool finalized;
		const int blocksize = 64;
		uint1 buffer[blocksize]; // bytes that didn't fit in last 64 byte chunk
		uint4 count[2];   // 64bit counter for number of bits (lo, hi)
		uint4 state[4];   // digest so far
		uint1 digest[16]; // the result
	//init();
		finalized=false;
		count[0] = 0;
		count[1] = 0;
		// load magic initialization constants.
		state[0] = 0x67452301;
		state[1] = 0xefcdab89;
		state[2] = 0x98badcfe;
		state[3] = 0x10325476;
		string text(account_no);
		cout<<text<<endl;
	
	//update(text.c_str(), text.length());
	//finalize();
	
	
	
	
	
}

int main(){
	const char str = "123456789";
	char matin[10];
	md4Hash(str, matin);
}