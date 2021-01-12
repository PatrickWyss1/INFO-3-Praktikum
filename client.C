/*
 * client.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */

#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h> //contains various constants
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include "SIMPLESOCKET.H"



using namespace std;

string pwdGen(int strLen,int symbLen);

string variables();

string Bot(string input);



int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);



	int i=0;
	bool goOn=1;
	while(goOn){ // send and receive data
		string var = variables();
		msg = Bot(var);

		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);

	}
}

string pwdGen(int strLen, int symbLen){
	int symbolIdx;
	const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
		string pwdGuess = string("");
		char *SymbArray_ = new char [symbLen + 1];
			strncpy(SymbArray_, SYMBOLS.c_str(), symbLen+1);

		for(int i=0; i < strLen; i++){
			symbolIdx = rand() % symbLen;
			pwdGuess += SymbArray_[symbolIdx];
		}
		cout << pwdGuess << endl;
		return pwdGuess;

}

string variables(){
	char pwdLen, symb, runs;


			cout << "Use Command makepwd![pwdLength, symbols, runs] to create password" << endl;

			int check = scanf("makepwd![%c,%c, %c]", &pwdLen, &symb, &runs);
			cout << pwdLen << symb << runs << endl;


			string var = "";

			var.append(0,pwdLen);
			var.append(1, symb);
			var.append(2,runs);
			return var;



}

string Bot(string input){

		for(int i = 0; i <= input[2]; i++){

			return pwdGen(input[0],input[1]);


		}
}
