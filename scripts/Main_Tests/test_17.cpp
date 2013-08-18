
/*=====SIXTH TEST=====*/
int main(){
	char account[] = "00000-00000";
	char password[] = "password";
	char test_output[] = "test_output";
	Encrypt(account, password);


	ofstream outfile(test_output, std::ofstream::app);
	printTopTenTransactions(account,password);

	outfile.close();
	return 0;
}