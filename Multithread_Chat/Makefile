all: Server_main Client_main

Server_main:Server.o Server_main.o 
	g++ Server.o Server_main.o -o Server_main
Server.o:Server.h Server.cpp
	g++ -c Server.cpp
Server_main.o:Server.h Server.cpp Server_main.cpp
	g++ -c Server_main.cpp

Client_main:Client.o Client_main.o
	g++ Client.o Client_main.o -o Client_main
Client.o:Client.h Client.cpp
	g++ -c Client.cpp

Client_main.o:Client.h Client.cpp Client_main.cpp
	g++ -c Client_main.cpp

clean:
	rm -f *.o Server_main Client_main 
