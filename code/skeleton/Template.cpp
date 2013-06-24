
bool makeDeposit(const char account_no[], const char passphrase[], double amount);  
bool makeWithdraw(const char account_no[], const char passphrase[], double amount);  
double getBalance(const char account_no[], const char passphrase[]);
bool addNewAccount(const char account_no[], const char passphrase[]);
void printTopNTransactions(const char account_no[], const char passphrase[], int n);
bool createLogFile();

/*
*	It first checks if amount is in the proper amount format (e.g., 57.20, 90, 120.41), 
*	if it is not it returns false. It makes a deposit of amount to the account 
*	(i.e., appends amount to the account file).
*/
bool makeDeposit(const char account_no[], const char passphrase[], double amount)
{
	return false;
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
	return false;
}

/*
*	For the particular bank account (account_no), this function calculates the account 
*	balance by summing all the deposits and withdrawals in the transaction history for 
*	that particular bank account. For instance, for the example provided the function 
*	will return 10 because 0+20+100-10+100-200=10.
*/
double getBalance(const char account_no[], const char passphrase[])
{
	return 0.0;
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
	return false;
}

/*
*	Description for createLogFile
*/
bool createLogFile()
{
	return false;
}