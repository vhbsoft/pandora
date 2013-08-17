
/*=====FOURTH TEST=====*/
int main(){
	char accounts[10][ACCOUNT_NUMBER_SIZE]=
		{"00000-00000", "11111-11111", "22222-22222", 
		 "33333-33333", "44444-44444", "55555-55555", 
		 "66666-66666", "77777-77777", "88888-88888", 
		 "99999-99999"};
	char password[] = "password";
	char test_output[] = "test_output";
	ofstream outfile(test_output, std::ofstream::app);
	if(getBalance(accounts[0], password) != 0){
		outfile<<"Failed Test 4 : getBalance(account, password)"<<endl;
		outfile.close();
		return 1;
	}
	else{
		outfile<<"Passed Test 4 : getBalance(account, password)"<<endl;
	}
	if(getBalance(accounts[1], password) != 1000){
		outfile<<"Failed Test 5 : getBalance(account, password)"<<endl;
		outfile.close();
		return 1;
	}
	else{
		outfile<<"Passed Test 5 : getBalance(account, password)"<<endl;
	}
	if(getBalance(accounts[2], password) != 0){
		outfile<<"Failed Test 6 : getBalance(account, password)"<<endl;
		outfile.close();
		return 1;
	}
	else{
		outfile<<"Passed Test 6 : getBalance(account, password)"<<endl;
	}
	if(getBalance(accounts[5], password) != 3599.93){
		outfile<<"Failed Test 7 : getBalance(account, password)"<<endl;
		outfile.close();
		return 1;
	}
	else{
		outfile<<"Passed Test 7 : getBalance(account, password)"<<endl;
	}
	outfile.close();
	return 0;
}