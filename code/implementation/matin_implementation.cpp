#include <iostream>     // std::cout, std::fixed
#include <iomanip>      // std::setprecision
#include <cmath>	//floor, ceil
#include <cstring> //memset
#include <fstream> //ofstream, 
using namespace std;

//Provided Functions
	int md5Hash(const char account_no[], char md5_hash_account_no[], int size_of_hash);
	int CreateNewAccountFile(const char account_no[]);
	int Encrypt(const char account_no[], const char passphrase[]);
	int Decrypt(const char account_no[], const char passphrase[]);
//End of Provided Functions

bool makeDeposit(const char account_no[], const char passphrase[], double amount);  
bool makeWithdraw(const char account_no[], const char passphrase[], double amount);  
double getBalance(const char account_no[], const char passphrase[]);
bool addNewAccount(const char account_no[], const char passphrase[]);
void printTopNTransactions(const char account_no[], const char passphrase[], int n);
bool createLogFile();

// Matin's Helper Functions
	// check if amount is proper format
	bool checkTransactionFormat(double amount);
//End Matin's Helper Functions

/*
*	It first checks if amount is in the proper amount format (e.g., 57.20, 90, 120.41), 
*	if it is not it returns false. It makes a deposit of amount to the account 
*	(i.e., appends amount to the account file).
*/
bool makeDeposit(const char account_no[], const char passphrase[], double amount)
{
	if(!checkTransactionFormat(amount) || amount < 0)
	{
		cout<<"Error: Incorrect Double Format"<<endl;
		return false;
	}
	Decrypt(account_no, passphrase);

	//Get Account Name from md5Hash
	char account_name[64];
	memset(account_name,0,64);
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//output amount to file
	ofstream outfile;   // outfile is a name of our choosing.
	outfile.open(account_name, std::ofstream::out | std::ofstream::app);
	if ( !outfile )		   // Did the creation fail?
	{
	    cout << "Error: Cannot create results.txt!" << endl;
	    return false; 
	}
	outfile <<setprecision(2)<<fixed<< amount << endl;
	outfile.close();

	memset(account_name,0,64);//remove account hash from memory
	Encrypt(account_no, passphrase);
	return true;
}

/*
*	It first checks if amount is in the proper amount format (e.g., 57.20, 90, 120.41), 
*	if it is not it returns false. It checks if amount is less than or equal to balance 
*	before making the withdrawal. If there is insufficient amount in the account to
*	make the withdrawal, it will log a proper message and charges $10 overdraft penalty 
*	fee to the account, without making the requested withdrawal.
*/
bool makeWithdraw(const char account_no[], const char passphrase[], double amount)
{
	if(!checkTransactionFormat(amount) || amount < 0)
	{
		cout<<"Error: Incorrect Double Format"<<endl;
		return false;
	}
	Decrypt(account_no, passphrase);

	//Get Account Name from md5Hash
	char account_name[64];
	memset(account_name,0,64);
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//output amount to file
	ofstream outfile;   // outfile is a name of our choosing.
	outfile.open(account_name, std::ofstream::out | std::ofstream::app);
	if ( !outfile )		   // Did the creation fail?
	{
	    cout << "Error: Cannot create results.txt!" << endl;
	    return false; 
	}

	//Check the amount in account currently
	double account_amount = getBalance(account_no, passphrase);
	if(account_amount < amount)
	{
		//TODO: log a message in log file
		outfile <<setprecision(2)<<fixed<< -10.0 << endl;
		return false;
	}

	//if there is enough in account, withdraw amount
	amount = -1*amount;
	outfile <<setprecision(2)<<fixed<< amount << endl;
	outfile.close();

	return true;
}

/*
*	For the particular bank account (account_no), this function calculates the account 
*	balance by summing all the deposits and withdrawals in the transaction history for 
*	that particular bank account. For instance, for the example provided the function 
*	will return 10 because 0+20+100-10+100-200=10.
*/
double getBalance(const char account_no[], const char passphrase[])
{
	//cout<<endl<<endl;
	Decrypt(account_no, passphrase);

	//Get Account Name from md5Hash
	char account_name[64];
	memset(account_name,0,64);
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//read amounts from file
	ifstream infile;   // infile is a name of our choosing.
	infile.open(account_name, std::ofstream::out | std::ofstream::app);
	double current_amount = 0.0;
	double total_amount = 0.0;
	while(!infile.eof())
	{
		infile >> current_amount;
		//cout<<current_amount<<endl;
		total_amount += current_amount;
		current_amount = 0.0;
	}

	infile.close();
	memset(account_name,0,64);//remove account hash from memory
	Encrypt(account_no, passphrase);


	return total_amount;
}

/*
*	This function returns the n transactions with highest amount (whether they are deposits 
*	or withdraws). If n is greater than the number of transactions it will return all 
*	transactions recorded in the account transaction history. 
*
*	For example, executing printTopNTransactions("12345-67890", 3) would output: 
*	-200
*	100
*	100
*/
void printTopNTransactions(const char account_no[], const char passphrase[], int n)
{
	return;
}

/*
*	Description for addNewAccount
*/
bool addNewAccount(const char account_no[], const char passphrase[])
{
	if(CreateNewAccountFile(account_no) > 0)
		return false;
	makeDeposit(account_no, passphrase, 0);
	return true;
}

/*
*	Description for createLogFile
*/
bool createLogFile()
{
	return false;
}

/****************************************************************************************************
*****************************************************************************************************
*****************************************************************************************************/
//Matin's Implentation of Helper Functions

bool checkTransactionFormat(double amount)
{
	if(amount < 0)
		return false;
	int count = 0;
	double decimal_to_int = amount*100.0;
	double decimal_floor= floor(decimal_to_int);
	double decimal_ceil = ceil(decimal_to_int);
	/*cout<<"Amount is "<<decimal_to_int<<": "<<endl;
	cout<<"         Floor is = "<<decimal_floor<<endl;
	cout<<"         Ceil  is = "<<decimal_ceil<<endl;
	cout<<"(decimal_ceil - decimal_floor) = "<<(decimal_ceil - decimal_floor)<<endl;*/
	if((decimal_ceil - decimal_floor) > 0.0)
	{
		//cout<<"false"<<endl;
		return false;
	}
	//cout<<"true"<<endl;
	return true;
}

int main()
{
	char account_no[] = "12345";
	char passphrase[] = "hello world";
	if(!addNewAccount(account_no, passphrase))
	{
		cout<<"add account failure"<<endl;
		return 1;
	}
	if(!makeDeposit(account_no, passphrase, 20.00))
	{
		cout<<"deposite failure"<<endl;
	}
	//if(!makeDeposit(account_no, passphrase, 10.123))
	//{
	//	cout<<"deposite failure"<<endl;
	//}
	if(!makeWithdraw(account_no, passphrase, 200.00))
	{
		cout<<"withdraw failure"<<endl;
	}
	if(!makeDeposit(account_no, passphrase, 100.30))
	{
		cout<<"deposite failure"<<endl;
	}
	if(!makeWithdraw(account_no, passphrase, 80.00))
	{
		cout<<"withdraw failure"<<endl;
	}
	if(!makeDeposit(account_no, passphrase, 59.0000))
	{
		cout<<"deposite failure"<<endl;
	}

	cout<<"balance is "<<getBalance(account_no,passphrase)<<endl;// 20-10+100.3+-80+59

	return 0;

}

/************************************************************************************************************
DO NOT TOUCH ===== PROVIED FUNCTIONS IMPLEMENTATION ===== DO NOT TOUCH ==== PROVIDED FUNCTIONS IMPLEMENTATION
*************************************************************************************************************/


/*Provied Functions Impementation*/

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

#include <cstdio>

int Encrypt(const char account_no[], const char passphrase[]){
	const int size_of_hash = 64;
	char account_hash[size_of_hash];
	if(md5Hash(account_no, account_hash, size_of_hash) != 0 )
		return 1;
	FILE* new_account_file;
	if(fopen_s(&new_account_file, account_hash, "r+") != 0)
	{
		return 1;
	}
	//Encrypt
	fclose(new_account_file);
	//cout<<"Successfully Encrypted"<<endl;
	return 0;
}

int Decrypt(const char account_no[], const char passphrase[]){
	const int size_of_hash = 64;
	char account_hash[size_of_hash];
	if(md5Hash(account_no, account_hash, size_of_hash) != 0 )
		return 1;
	FILE* new_account_file;
	if(fopen_s(&new_account_file, account_hash, "r+") != 0)
	{
		return 1;
	}
	//Decrypt

	//Close File
	fclose(new_account_file);
	//cout<<"Successfully Decrypted"<<endl;
	return 0;
}

//--------------------------------------------------
//int CreateNewAccountFile(const char [] account_no)  
//
//- creates [md5_hash(account_no)]
//- returns 0 if success
//- returns non-zero if failed
//
//--------------------------------------------------

int CreateNewAccountFile(const char account_no[])
{
	const int size_of_hash = 64;
	char account_hash[size_of_hash];
	if(md5Hash(account_no, account_hash, size_of_hash) != 0 )
		return 2;
	FILE* new_account_file;
	if(fopen_s(&new_account_file, account_hash, "a") == 0)
	{
		fclose(new_account_file);
		return 0;
	}
	return 1;
}

//--------------------------------------------------
//int md5Hash(const char [] account_no, char [] md5_hash_account_no)
//
//- calculates md5 checksum of account_no and stores it in md5_hash_account_no (passed by reference)
//- returns 0 if success
//- returns non-zero if failed
//--------------------------------------------------


#include <string.h> //strcpy(), 
#include <stdio.h>
#include <string>
#include <iostream>
using namespace std;

int md5Hash(const char account_no[], char md5_hash_account_no[], const int size_of_hash)
{
	strcpy_s(md5_hash_account_no, size_of_hash, account_no);
	return 0;
}