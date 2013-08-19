
/*=====FIFTH TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "wrong";
	char test_output[] = "test_output";
	Encrypt(account, password);
	ofstream outfile(test_output, std::ofstream::app);
	
	bool withdraw = makeWithdrawal(account, password, 1);

	if(!withdraw){
		outfile<<"Passed Test : checked passphrase in makeWithdrawal"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in makeWithdrawal"<<endl;
	}

	outfile.close();
	return 0;
}