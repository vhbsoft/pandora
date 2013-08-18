
/*=====FIRST TEST=====*/
int main(){
	char account[] = "00000-00000";
	char password[] = "password";
	Encrypt(account, password);
	char test_output[] = "test_output";

	ofstream outfile(test_output, std::ofstream::app);
	bool result = makeDeposit(account, password, 10);
	double balance = correctBalance(account, password);

	if(balance != 0){
		outfile<<"Passed Test : makeDeposit(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeDeposit(account, password, 10); -> nothing added to file"<<endl;
	}

	if(balance == 10){
		outfile<<"Passed Test : makeDeposit(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeDeposit(account, password, 10); -> returned wrong balance"<<endl;
	}

	if(result && balance == 10){
		outfile<<"Passed Test : makeDeposit(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeDeposit(account, password, 10); -> returned false"<<endl;
	}
	outfile.close();
	return 0;	
}