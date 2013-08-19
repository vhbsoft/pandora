
/*=====FOURTH TEST=====*/
int main(){
	char accounts[10][ACCOUNT_NUMBER_SIZE]=
		{"00000-00000", "11111-11111", "22222-22222", 
		 "33333-33333", "44444-44444", "55555-55555", 
		 "66666-66666", "77777-77777", "88888-88888", 
		 "99999-99999"};
	char password[] = "password";
	char test_output[] = "test_output";
	for(int i=0; i<10; i++){
		Encrypt(accounts[i], password);
	}
	ofstream outfile(test_output, std::ofstream::app);

	if(getBalance(accounts[2], password) != 0){
		outfile<<"Failed Test : getBalance(account, password)"<<endl;
	}
	else{
		outfile<<"Passed Test : getBalance(account, password)"<<endl;
	}

	outfile.close();
	return 0;
}