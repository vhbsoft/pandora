
/*=====SEVENTH TEST=====*/
int main(){
	char account[] = "33333-33333";
	char password[] = "password";
	char test_output[] = "test_output";
	Encrypt(account, password);


	ofstream outfile(test_output, std::ofstream::app);
	printTopTenTransactions(account,password);

	outfile.close();
	return 0;
}