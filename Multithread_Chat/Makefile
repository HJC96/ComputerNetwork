all: Server_main Client_main

Server_main:Server.o Server_main.o 
	clang++ Server.o Server_main.o -o Server_main
Server.o:Server.h Server.cpp
	clang++ -c Server.cpp -std=c++11
Server_main.o:Server.h Server.cpp Server_main.cpp
	clang++ -c Server_main.cpp -std=c++11

Client_main:Client.o Client_main.o
	clang++ Client.o Client_main.o -o Client_main
Client.o:Client.h Client.cpp
	clang++ -c Client.cpp -std=c++11

Client_main.o:Client.h Client.cpp Client_main.cpp
	clang++ -c Client_main.cpp -std=c++11

clean:
	rm -f *.o Server_main Client_main 
