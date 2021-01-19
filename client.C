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
#include <sstream>

using namespace std;



/**
 * \function pwdGen
 * \brief random password Generator to produce different password guesses based on input parameters
 */
string pwdGen(int strLen,int symbLen);
string pwdGen_02(int strLen, int symbLen);

/**
 * \class Vars
 *
 * \brief stores parameters which are used to generate passwords and run the password-guesser
 */

class Vars{
public:
	/**
	 *\brief stores the length of the password to be created server-side and guessed by client
	 */
	int a_;
	/**
	 * \brief stores the length/amount of symbols of the alphabet that the passwords can be generated with
	 */
	int b_;
	/**
	 * \brief stores the amount of of times the client should guess different passwords correctly
	 */
	int c_;
};

Vars variables();

string Bot(Vars a);
string Bot_02(Vars a);


int main(int argc, char *argv[]) {

	if(argc != 4){	//checks if an adequate amount of parameters was given when running client.C
			cout << "Wrong number of command line parameters" << endl;
			cout << "1. Argument: password length\n2. Argument: Alphabet length\n3. Argument: Number of runs\n" << endl;
			exit(0);
		}


	srand(time(NULL));
	TCPclient c; // initiates client object
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);

	int i=0;
	int counter = 1;

	Vars var;



	sscanf(argv[1], "%i", &var.a_);
	sscanf(argv[2], "%i", &var.b_);
	sscanf(argv[3], "%i", &var.c_);

	string initmsg = "makepwd![]";
	string convert;
	stringstream ss;
	ss << var.a_ << "," << var.b_;
	ss >> convert;
	initmsg.insert(9, convert);


	for(int r = 0; r < var.c_; r++){

		c.sendData(initmsg);
		counter = 0;
		if((c.receive(32) == "OKAY")){

			msg = "";
			while(msg != "ACCESS ACCEPTED"){

				msg = Bot(var);
				c.sendData(msg);
				msg = c.receive(32);
				counter++;
			}



	/*
		for(int x = 0; x < var.c; x++){ //loop to send newly generated passwords to server a user-defined amount of times
			msg = Bot(var);
			c.sendData(msg);
			//cout << "Attempt number: " << counter << endl;
			//cout << "client sends: " << msg << endl;
			msg = c.receive(32);
		//	cout << "client received: " << msg << endl;
			counter++;
			if(msg == "ACCESS ACCEPTED"){
				c.sendData("BYEBYE");

				cout << "Hack successful after " << counter-1 << " attempts." << endl;
				break;
			}

		}*/
		cout <<  counter << endl;
		}else{
			cout << "try again!" << endl;
		}
	}

		}

	/*	msg = Bot(var);

		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);*/

//	}


string pwdGen(int strLen, int symbLen){ // random password generator to produce guesses of the password saved in the server
	int symbolIdx;
	const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
		string pwdGuess = string("");
		char *SymbArray_ = new char [symbLen + 1];
			strncpy(SymbArray_, SYMBOLS.c_str(), symbLen+1);

		for(int i=0; i < strLen; i++){
			symbolIdx = rand() % symbLen;
			pwdGuess += SymbArray_[symbolIdx];
		}

		return pwdGuess;

}

/*string pwdGen_02(int strLen, int symbLen){
	int symbolIdx;
		const string SYMBOLS = "ABCDEFGHIJKLMNOPQRTSTUVWXYZabcdefghijklmopqrstuvwxyz0123456789";
			string pwdGuess = string("");
			char *SymbArray_ = new char [symbLen + 1];
				strncpy(SymbArray_, SYMBOLS.c_str(), symbLen+1);
				string duplicate = "";

			while(duplicate == "TRUE"){
			for(int i=0; i < strLen; i++){
				symbolIdx = rand() % symbLen;
				pwdGuess += SymbArray_[symbolIdx];
			}
			for(int n =0; n< 10000; n++){
				if(pwdGuess == string(Membox[n])){
					duplicate = "TRUE";
					break;
				}else{
					duplicate = "";
				}
			}

			}

			Membox[counter] = pwdGuess;


			return pwdGuess;


}
*/


Vars variables(){ //asks user for input to save the values for Password length, symbol length and guess attempts
					//returns Object of class Vars which contains the 3 integers
	int pwdLen, symb, runs;


			cout << "Use Command makepwd![pwdLength, symbols, runs] to create password" << endl;

			int check = scanf("makepwd![%i,%i, %i]", &pwdLen, &symb, &runs);
			//cout << "in variables: "<< pwdLen << symb << runs << endl;

			Vars a;
			a.a_ = pwdLen;
			a.b_ = symb;
			a.c_ = runs;

			//string var = "";
			//var[0] = pwdLen;
			//var.append(0,pwdLen);
			//var.append(1, symb);
			//var.append(2, runs);
			return a;



}

string Bot(Vars a){ // Returns the guessed password generator by the random password generator

			return pwdGen(a.a_,a.b_);

}
/*
string Bot_02(Vars a){

	return pwdGen_02(a.a,a.b);
}

*/
