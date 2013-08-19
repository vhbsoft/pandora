
/*=====FIFTH TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "wrong";
	char test_output[] = "test_output";
	Encrypt(account, password);
	ofstream outfile(test_output, std::ofstream::app);
	
	double balance = getBalance(account, password);
	
	if(balance == -10000){
		outfile<<"Passed Test : checked passphrase in getBalance"<<endl;
	}
	else{
		outfile<<"Failed Test : returend true for invalid passphrase in getBalance"<<endl;
	}

	outfile.close();
	return 0;
}