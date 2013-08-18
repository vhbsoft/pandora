
/*=====SECOND TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "password";
	Encrypt(account, password);
	char test_output[] = "test_output";

	ofstream outfile(test_output, std::ofstream::app);
	bool result = makeWithdrawal(account, password, 10);
	double balance = correctBalance(account, password);

	if(balance != 1000){
		outfile<<"Passed Test : makeWithdrawal(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeWithdrawal(account, password, 10); -> nothing added to file"<<endl;
	}

	if(balance == 990){
		outfile<<"Passed Test : makeWithdrawal(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeWithdrawal(account, password, 10); -> returned wrong balance"<<endl;
	}

	if(result && balance == 990){
		outfile<<"Passed Test : makeWithdrawal(account, password, 10);"<<endl;
	}
	else{
		outfile<<"Failed Test : makeWithdrawal(account, password, 10); -> returned false"<<endl;
	}
	outfile.close();
	return 0;
}