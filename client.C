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
#include "Algorithm" // contains algorithm that return every possible permutation of a given string through recursive methods (not used here)


using namespace std;




/**
 * \function pwdGen
 * \brief random password Generator to produce different password guesses based on input parameters
 */
string pwdGen(int strLen,int symbLen);


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

//Vars variables(); --no longer in use, explanation at definition

string Bot(Vars a);


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

	sscanf(argv[1], "%i", &var.a_); // "copies" command line arguments (int) into members of Object var of Class Vars
	sscanf(argv[2], "%i", &var.b_); //
	sscanf(argv[3], "%i", &var.c_); //

	if((var.a_ < 4) || (var.b_ <= 0) || (var.c_ <= 0)){ //error handling in case of incorrect input
		cout << "Incorrect values for command line parameters.\n\n1. Argument needs to be 4 or larger.\n2. and 3. Argument needs to be greater than 0.\n" << endl;
		cout << "TRY AGAIN!" << endl;
		exit(0);

	}

	string initmsg = "makepwd![]"; // initialising message to send to server ("makepwd![int, int]" informs the server to create and save a password)
	string convert;
	stringstream ss;
	ss << var.a_ << "," << var.b_; //using stringstream to write integers into string without losing their values
	ss >> convert;
	initmsg.insert(9, convert); //inserts the variables into the brackets of initmsg




	for(int r = 0; r < var.c_; r++){ // Entire process of creating a password and habing the client guess it is run a user defined amount of times (runs)

		c.sendData(initmsg);// sends the initialising message to server
		int counter = 0; //counter to count attempts needed to crack password

		if((c.receive(32) == "OKAY")){ // response from server indicated successful password creation
			msg = "";

			while(msg.compare(0,15, "ACCESS ACCEPTED") != 0){ // loop to run PwdGen Bot until the correct password is guessed

				msg = Bot(var);
				//cout << msg << endl;
				c.sendData(msg);
				msg = c.receive(32);
				counter++;
			}

			cout << counter << endl;

		}else{
			cout << "Communication Error!" << endl; // Error handling in case Password wasnt created in server, indicates server issue
			exit(0);
		}



}
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

/* -- initial method of getting user input, no longer used as command line argument are easier to use

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
*/

string Bot(Vars a){ // Returns the guessed password generator by the random password generator

			return pwdGen(a.a_,a.b_);

}

