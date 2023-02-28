Mysmtp: email.o Mysmtp.o
	g++ email.o Mysmtp.o -o Mysmtp
email.o:email.h email.cpp
	g++ -c email.cpp
Mysmtp.o : email.h Mysmtp.cpp
	g++ -c Mysmtp.cpp
clean:
	rm -f *.o Mysmtp