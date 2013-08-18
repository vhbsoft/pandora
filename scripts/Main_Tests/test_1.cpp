
/*=====FIRST TEST=====*/
int main(){
	char account[] = "00000-00000";
	char password[] = "password";
	Encrypt(account, password);
	char test_output[] = "test_output";
	ofstream outfile(test_output, std::ofstream::app);
	if(!makeDeposit(account, password, 10)){
		outfile<<"Failed Test 1 : makeDeposit(account, password, 10); -> returned false"<<endl;
		outfile.close();
		return 1;
	}
	else{
		if(correctBalance(account, password) != 10){
			outfile<<"Failed Test 1 : makeDeposit(account, password, 10); -> incorrect balance"<<endl;
			outfile.close();
			return 2;
		}
		else{
			outfile<<"Passed Test 1 : makeDeposit(account, password, 10);"<<endl;
		}
	}
	outfile.close();
	return 0;	
}