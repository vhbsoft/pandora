
/*=====FIFTH TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "wrong";
	char test_output[] = "test_output";
	Encrypt(account, password);
	ofstream outfile(test_output, std::ofstream::app);
	
	bool deposit = makeDeposit(account, password, 10);
	bool withdraw = makeWithdrawal(account, password, 1);
	bool balance = getBalance(account, password);

	if(!deposit){
		outfile<<"Passed Test : checked passphrase in makeDeposit"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in makeDeposit"<<endl;
	}

	if(!withdraw){
		outfile<<"Passed Test : checked passphrase in makeWithdrawal"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in makeWithdrawal"<<endl;
	}

	if(!balance){
		outfile<<"Passed Test : checked passphrase in getBalance"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in getBalance"<<endl;
	}

	outfile.close();
	return 0;
}