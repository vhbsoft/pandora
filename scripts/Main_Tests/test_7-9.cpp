
/*=====THIRD TEST=====*/
int main(){
	char account[] = "00000-00000";
	char password[] = "password";
	Encrypt(account, password);
	char test_output[] = "test_output";

	ofstream outfile(test_output, std::ofstream::app);
	bool result = makeWithdrawal(account, password, 10);
	double balance = correctBalance(account, password);

	if(balance == -10){
		outfile<<"Passed Test : Attempt to Overdraw from Account"<<endl;
	}
	else{
		outfile<<"Failed Test : Attempt to Overdraw from Account -> incorrect balance"<<endl;
	}

	if(!result && balance == -10){
		outfile<<"Passed Test : Attempt to Overdraw from Account"<<endl;
	}
	else{
		outfile<<"Failed Test : Attempt to Overdraw from Account -> returned true or incorrect balance"<<endl;
	}

	ifstream banking("banking.log");
	if(banking){
		outfile<<"Passed Test : Created Log File"<<endl;
	}
	else{
		outfile<<"Failed Test : Failed to Create Log File"<<endl;
	}
	banking.close();
	remove("banking.log");
	
	outfile.close();
	return 0;
}