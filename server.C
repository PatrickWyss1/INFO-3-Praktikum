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
	myTCPServer(int portNmb, int maxDataSizeRcv) : TCPserver(portNmb, maxDataSizeRcv){
		box_ = nullptr;
}

protected:
	string myResponse(string input);

	BlackBoxSafe *box_;


};
int LENGTH = 0;
string myTCPServer::myResponse(string input){

	int b = 0;
	int res;
if(input.compare(0,8,string("makepwd!")) == 0){
	res = sscanf(input.c_str(), "makepwd![%i,%i]", &LENGTH, &b);
}



if((input.compare(0,8, string("makepwd!")) == 0) && res != 2){
	return string("Missing Input Variables");
}else if((res == 2) && (input.compare(0,8, string("makepwd!")) == 0)){
	if(LENGTH == 0 || b == 0){
		return string("Missing Input Variables");
	}else{
			delete box_;
			box_ = new BlackBoxSafe(LENGTH,b);
			cout << "hier ist das passwort:" <<  box_->pwd_ << endl;
			return string("OKAY");
	}


	}else{
		if(box_ != nullptr){

			return(box_ ->safeInput(input,LENGTH));
		}else{
			return string("INIT BOXES FIRST");
		}

	}
if(input.compare(0,7, string("runBot!")) == 0){


}


};

int main(){
	srand(time(nullptr));
	myTCPServer srv(2022,25);
	srv.run();
}
