/*
 * server.C
 *
 *  Created on: 11.09.2019
 *      Author: aml
 */
#include <cstdio> // standard input and output library
#include <cstdlib> // this includes functions regarding memory allocation
#include <cstring> // contains string functions
#include <cerrno> //It defines macros for reporting and retrieving error conditions through error codes
#include <ctime> //contains various functions for manipulating date and time

#include <unistd.h> //contains various constants
#include <sys/types.h> //contains a number of basic derived types that should be used whenever appropriate
#include <arpa/inet.h> // defines in_addr structure
#include <sys/socket.h> // for socket creation
#include <netinet/in.h> //contains constants and structures needed for internet domain addresses

#include "SIMPLESOCKET.H"
#include "TASK1.H"
#include <iostream>
#include <string>
using namespace std;
using namespace TASK1;


class myTCPServer : public TCPserver{
public:
	myTCPServer(int portNmb, int maxDataSizeRcv) : TCPserver(portNmb, maxDataSizeRcv){ //constructor
		box_ = nullptr; // makes the pointer to class BlackBoxSafe a nullpointer
}

protected:
	string myResponse(string input);

	BlackBoxSafe *box_; // pointer to the (or of the class type) class BlackBoxSafe


};
int LENGTH = 0; // global variable necessary for myResponse method

/**
 *
 * \brief processes the messages that the server receives from the client and returns a suitable response
 *
 */
string myTCPServer::myResponse(string input){

	int b = 0;
	int res;
if(input.compare(0,8,string("makepwd!")) == 0){
	res = sscanf(input.c_str(), "makepwd![%i,%i]", &LENGTH, &b); // saves the input variables in LENGTH and b
}

if((input.compare(0,8, string("makepwd!")) == 0) && res != 2){ //if previous input saving was unsuccessful, send error message
	return string("Missing Input Variables");
}else if((res == 2) && (input.compare(0,8, string("makepwd!")) == 0)){ //if previous input saving was successful, continue;
	if(LENGTH == 0 || b == 0){											// if either variable is 0, send error message
		return string("Missing Input Variables");
	}else{
			delete box_;						// deletes current BlackBox Object and creates a new one,
			box_ = new BlackBoxSafe(LENGTH,b);  //
			cout << "OKAY" << endl;
			cout << box_->pwd_ << endl;

			return string("OKAY");		// returns message indicating success

	}


	}else{						//if incoming message is not "makepwd!... then assume it is a potential password
		if(box_ != nullptr){	// makes sure there is a Blackbox with a saved password


			return(box_ ->safeInput(input,LENGTH));
		}else{

			return string("INIT BOXES FIRST"); //error message if the BlackBox is still a null Pointer
		}

	}



};

int main(){
	srand(time(nullptr));
	myTCPServer srv(2022,25);
	srv.run();
}
