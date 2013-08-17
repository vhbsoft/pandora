
/*=====SECOND TEST=====*/
int main(){
	char account[] = "11111-11111";
	char password[] = "password";
	char test_output[] = "test_output";
	ofstream outfile(test_output, std::ofstream::app);
	if(!makeWithdrawal(account, password, 10)){
		outfile<<"Failed Test 2 : makeWithdrawal(account, password, 10); -> returned false"<<endl;
		outfile.close();
		return 1;
	}
	else{
		if(matin_getBalance(account, password) != 990){
			outfile<<"Failed Test 2 : makeWithdrawal(account, password, 10); -> incorrect balance"<<endl;
			outfile.close();
			return 2;
		}
		else{
			outfile<<"Passed Test 2 : makeWithdrawal(account, password, 10);"<<endl;
		}
	}
	outfile.close();
	return 0;	
}