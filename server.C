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

using namespace TASK1;

class myTCPServer : public TCPserver{
public:
	myTCPServer(int portNmb, int maxDataSizeRcv) : TCPserver(portNmb, maxDataSizeRcv){
	box_ = nullptr;
};

protected:
	string myResponse(string input);

	BlackBoxSafe *box_;


};
string myTCPServer::myResponse(string input){
	if(input == string("ABC")){
		if(box_ != nullptr){
			delete box_;
			box_ = new BlackBoxSafe(5,5);
			return string("OKAY");
		}
	}else{
		if(box_ != nullptr){
			return(box_ ->input(input));
		}else{
			return string("INIT BOX FIRST");
		}

	}



	/*std::string befehl = input.substr(0, input.find(" "));
	std::string ret = "";
	if(befehl == "LOGIN"){
		ret = "LOGIN VERSUCHT";
	}else if(befehl == "NEUESPASSWORT"){
			ret = "LOGIN VERSUCHT";
		}else{
			ret = "Befehl unbekannt";
	}
	return ret;
*/
	return string ("neue Daten");
};

int main(){
	srand(time(nullptr));
	myTCPServer srv(2022,25);
	srv.run();
}
