MySmtp_Client:MySmtp_Client.o main.o
	g++ MySmtp_Client.o main.o -o MySmtp_Client
MySmtp_Client.o:MySmtp_Client.h MySmtp_Client.cpp
	g++ -c MySmtp_Client.cpp
main.o : MySmtp_Client.h main.cpp
	g++ -c main.cpp
clean:
	rm -f *.o MySmtp_Client
