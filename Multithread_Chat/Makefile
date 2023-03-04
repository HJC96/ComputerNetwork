all: Server Client
Server:Server.o 
	g++ Server.o -o Server
Server.o:Server.h Server.cpp
	g++ -c Server.cpp
Client:Client.o
	g++ Client.o -o Client
Client.o:
	g++ -c Client.cpp

clean:
	rm -f *.o Server Client
