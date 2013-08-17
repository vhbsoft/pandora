
/*=====FIFTH TEST=====*/
int main(){
	char account[] = "00000-00000";
	char password[] = "password";
	char test_output[] = "test_output";
	ofstream outfile(test_output, std::ofstream::app);
	if(makeWithdrawal(account, password, 10)){
		outfile<<"Failed Test 3 : Attempt to Overdraw from Account -> returned true "<<endl;
		outfile.close();
		return 1;
	}
	else{
		if(matin_getBalance(account, password) != -10){
			outfile<<"Failed Test 3 : Attempt to Overdraw from Account -> incorrect balance"<<endl;
			outfile.close();
			return 2;
		}
		else{
			outfile<<"Passed Test 3 : Attempt to Overdraw from Account"<<endl;
		}
	}
	outfile.close();
	return 0;
}