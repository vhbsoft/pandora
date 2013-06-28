#include <iostream>     // std::cout, std::fixed(no longer used)
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

/*
*	It first checks if amount is in the proper amount format
*	(e.g., 57.20, 90, 120.41),if it is not it returns false. 
*	It makes a deposit of amount to the account (i.e., 
*	appends amount to the account file).
*/
bool makeDeposit(const char account_no[], const char passphrase[], double amount)
{
	return false;
}

/*
*	It first checks if amount is in the proper amount format
*	(e.g., 57.20, 90, 120.41), if it is not it returns false. 
*	It checks if amount is less than or equal to balance 
*	before making the withdrawal. If there is insufficient 
*	amount in the account to make the withdrawal, it will log 
*	a proper message and charges $10 overdraft penalty fee to 
*	the account, without making the requested withdrawal.
*/
bool makeWithdraw(const char account_no[], const char passphrase[], double amount)
{
	return false;
}

/*
*	For the particular bank account (account_no), this 
*	function calculates the account balance by summing all 
*	the deposits and withdrawals in the transaction history 
*	for that particular bank account. For instance, for the 
*	example provided the function will return 10 because 
*	0+20+100-10+100-200=10.
*/
double getBalance(const char account_no[], const char passphrase[])
{
	return 0.0;
}

/*
*	This function returns the n transactions with highest 
*	amount from the last 1000 transactions (whether they 
*	are deposits or withdraws). If n is greater than the 
*	number of transactions it will return all transactions 
*	recorded in the account transaction history.
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
bool addNewAccount(const char account_no[], const char passphrase[])
{
	return false;
}

/*
*	Description for createLogFile
*/
bool createLogFile()
{
	return false;
}