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

string pwdGen(int strLen,int symbLen);





class Vars{
public:
	int a,b,c;
};
Vars variables();

string Bot(Vars a);


int main() {
	srand(time(NULL));
	TCPclient c;
	string host = "localhost";
	string msg;

	//connect to host
	c.conn(host , 2022);



	int i=0;
	int counter = 0;
	bool goOn=1;
	//while(goOn){ // send and receive data
		Vars var;
		var = variables();

		string initmsg = "makepwd![]";
		string convert;
		stringstream ss;
		ss << var.a << "," << var.b;
		ss >> convert;

		initmsg.insert(9, convert);

		//initmsg[9] = convert[0];
		//initmsg[11] = convert[1];

		c.sendData(initmsg);
		if((c.receive(32) == "OKAY")){
		for(int x = 0; x < var.c; x++){ //loop to send newly generated passwords to server a user-defined amount of times
			msg = Bot(var);
			c.sendData(msg);
			cout << "client sends: " << msg << endl;
			msg = c.receive(32);
			cout << "client received: " << msg << endl;
			counter++;
			if(msg == "ACCESS ACCEPTED"){

				cout << "Hack successful after " << counter << " attempts." << endl;
				break;
			}

		}
		cout << "Bot finished after " << counter << " attempts." << endl;
		}else{
			cout << "try again!" << endl;
		}

	//	}
	/*	msg = Bot(var);

		cout << "client sends:" << msg << endl;
		c.sendData(msg);
		msg = c.receive(32);
		cout << "got response:" << msg << endl;
		sleep(1);*/

	}


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

Vars variables(){ //asks user for input to save the values for Password length, symbol length and guess attempts
					//returns Object of class Vars which contains the 3 integers
	int pwdLen, symb, runs;


			cout << "Use Command makepwd![pwdLength, symbols, runs] to create password" << endl;

			int check = scanf("makepwd![%i,%i, %i]", &pwdLen, &symb, &runs);
			//cout << "in variables: "<< pwdLen << symb << runs << endl;

			Vars a;
			a.a = pwdLen;
			a.b = symb;
			a.c = runs;

			//string var = "";
			//var[0] = pwdLen;
			//var.append(0,pwdLen);
			//var.append(1, symb);
			//var.append(2, runs);
			return a;



}

string Bot(Vars a){ // Returns the guessed password generator by the random password generator

			return pwdGen(a.a,a.b);


}
