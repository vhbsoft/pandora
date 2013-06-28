#include <iostream>     // std::cout, std::fixed(no longer used)
#include <iomanip>      // std::setprecision(no longer used)
#include <cmath>	//floor, ceil (will try to not use)
#include <cstring> //memset(no longer used)
#include <fstream> //ofstream, ifstream (input/output from file)
using namespace std;

//Provided Functions
	int md5Hash(const char account_no[], char md5_hash_account_no[], int size_of_hash);
	int CreateNewAccountFile(const char account_no[]);
	int Encrypt(const char account_no[], const char passphrase[]);
	int Decrypt(const char account_no[], const char passphrase[]);
//End of Provided Functions

//Required Functions to Implement
	bool makeDeposit(const char account_no[], const char passphrase[], double amount);  
	bool makeWithdrawal(const char account_no[], const char passphrase[], double amount);  
	double getBalance(const char account_no[], const char passphrase[]);
	bool addNewAccount();
	void printTopNTransactions(const char account_no[], const char passphrase[], int n);
	bool createLogFile();
//End of Required Functions to Implement

// Matin's Helper Functions
	// check if amount is proper format
	bool checkTransactionFormat(double amount);
	bool isValidAccountNumber(char account_no[]);
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
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//output amount to file
	ofstream outfile(account_name, std::ofstream::app);   // outfile is a name of our choosing.
	if ( !outfile )		   // Did the creation fail?
	{
	    cout << "Error: Cannot create results.txt!" << endl;
	    return false; 
	}
	outfile << amount << endl;
	outfile.close();

	//TODo: remove account hash from memory
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
bool makeWithdrawal(const char account_no[], const char passphrase[], double amount)
{
	if(!checkTransactionFormat(amount) || amount < 0)
	{
		cout<<"Error: Incorrect Double Format"<<endl;
		return false;
	}
	Decrypt(account_no, passphrase);

	//Get Account Name from md5Hash
	char account_name[64];
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//output amount to file
	ofstream outfile(account_name, std::ofstream::app);
	if ( !outfile )
	{
	    cout << "Error: Cannot create results.txt!" << endl;
	    return false; 
	}

	//Check the amount in account currently
	double account_amount = getBalance(account_no, passphrase);
	if(account_amount < amount)
	{
		//TODO: log a message in log file
		outfile <<-10.0 << endl;
		return false;
	}

	//if there is enough in account, withdraw amount
	amount = -1*amount;
	outfile << amount << endl;
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
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//read amounts from file
	ifstream infile(account_name);
	//skip first line
	char trash[100];
	infile.getline(trash, 10000, '\n');

	double current_amount = 0.0;
	double total_amount = 0.0;
	while(infile >> current_amount)
	{
		cout<<current_amount<<endl;
		total_amount += current_amount;
		current_amount = 0.0;
	}

	infile.close();
	//TODO: remove account hash from memory
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
	double top_trans[1000];
	Decrypt(account_no, passphrase);
	//Get Account Name from md5Hash
	char account_name[64];
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return;
	}

	//read amounts from file
	ifstream infile(account_name);
	infile.seekg(0, infile.end);
	int length_of_file = infile.tellg();
	length_of_file = length_of_file -1;
	if(length_of_file <= 1000)
	{
		infile.seekg(1,infile.beg);
	}
	else
	{
		int start_pos = length_of_file - 1000;
		infile.seekg(start_pos, infile.beg);
	}

	//Read in Last 1000 Transactions
	int i=0;
	while(infile >> top_trans[i])
	{
		i++;
	}

	//Put the top transactions in order SORTING
	for(i=0; i<1000;i++)
	{
		double find_largest = top_trans[i];
		for(int j=i; j<(1000-i); j++)
		{
			if(find_largest < top_trans[j])
			{
				find_largest = top_trans[j];
			}
		}
		top_trans[i] = find_largest;
	}
	infile.close();

	//Print Out Top N Transactions from Array
	if(n>1000)
	{
		n=1000;
	}
	for(i=0; i<n;i++)
	{
		cout<<top_trans[i]<<endl;
	}

	//TODO: remove account hash from memory
	Encrypt(account_no, passphrase);
	return;
}


/*
*	Upon calling this function it will ask the user the necessary information to open up an account.
*	The newly created account will be encrypted before returning the function.
*	Your function will technically do the following in the order provided. 
*
*	- Ask user for the account number
*	- Checks if the entered bank account is valid otherwise it should return false
*	(i.e. it is in the following format: XXXXX-XXXXX) 
*	(we recommend creating a function called isValidAccountNumber(const char account_no[])) to check for that)
*	- Ask user for the passphrase that will be associated to the account number
*	- Ask user for the account holder's personal information
*	- Call CreateNewAccountFile(account_no)
*	- Add the account holder personal information in one line to the file
*	- Add 0 to the file in the second line to represent the initial transaction amount
*	- Encrypt file using passphrase
*/
bool addNewAccount()
{
	char account_no[12];
	char passphrase[60];
	cout<<"Please Enter an Account Number formatted as XXXXX-XXXXX :"<<endl;
	cin >> account_no;
	if(isValidAccountNumber(account_no))
	{
		cerr<<"Invalid Account Number in addNewAccount()"<<endl;
		return false;
	}
	if(CreateNewAccountFile(account_no) > 0)
	{
		cout<<"Error: Account Already Exists"<<endl;
		return false;
	}
	cout<<"Please Enter a Password to Associate with Your Account :"<<endl;
	cin >> passphrase;
	//TODO: Check if valid passphrase
	//TODO: Add Personal Information to First Line of Document
	//Get Account Name from md5Hash
	char account_name[64];
	if(md5Hash(account_no, account_name, 64) != 0)
	{
		cout<<"Error: MD5HASH Error"<<endl;
		return false;
	}

	//output amount to file
	ofstream outfile(account_name, std::ofstream::app);   // outfile is a name of our choosing.
	if ( !outfile )		   // Did the creation fail?
	{
	    cout << "Error: Cannot create " << account_name<<endl;
	    return false; 
	}
	outfile <<"Personal Info Goes Here"<< endl;
	outfile.close();

	Encrypt(account_no, passphrase);
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
bool isValidAccountNumber(char account_no[])
{
	if(account_no[11] = '\0')
		return true;
	return false;
}


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

//bool insertInArray(double* arr_ptr, int curr_len, int max_len, double value, int pos)
//{
//	if(pos >= max_len)
//		return false;
//	if(max_len != curr_len)
//	{
//		if(pos>
//	}
//	return true;
//}

int main()
{
	char account_no[] = "12345-12345";
	char passphrase[] = "hello world";
	if(!addNewAccount())
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
	if(!makeWithdrawal(account_no, passphrase, 200.00))
	{
		cout<<"withdraw failure"<<endl;
	}
	if(!makeDeposit(account_no, passphrase, 100.30))
	{
		cout<<"deposite failure"<<endl;
	}
	if(!makeWithdrawal(account_no, passphrase, 80.00))
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