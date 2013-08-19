
/*=====FIFTH TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "wrong";
	char test_output[] = "test_output";
	Encrypt(account, password);
	ofstream outfile(test_output, std::ofstream::app);
	
	bool deposit = makeDeposit(account, password, 10);

	if(!deposit){
		outfile<<"Passed Test : checked passphrase in makeDeposit"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in makeDeposit"<<endl;
	}

	outfile.close();
	return 0;
}