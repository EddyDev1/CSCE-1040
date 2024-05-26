PLibrary: Patron.o LibraryItem.o Loan.o Loans.o Patrons.o LibraryItems.o DVD.o Book.o AudioCD.o main.o
	g++ -o PLibrary main.o LibraryItem.o Patron.o Loan.o LibraryItems.o Patrons.o Loans.o DVD.o Book.o AudioCD.o

main.o: main.cpp LibraryItem.h Loan.h Patron.h Loans.h LibraryItems.h Patrons.h
	g++ -c main.cpp

DVD.o: DVD.cpp DVD.h
	g++ -c DVD.cpp

Book.o: Book.cpp Book.h
	g++ -c Book.cpp

AudioCD.o: AudioCD.cpp AudioCD.h
	g++ -c AudioCD.cpp

LibraryItem.o: LibraryItem.cpp LibraryItem.h
	g++ -c LibraryItem.cpp

Patron.o: Patron.cpp Patron.h
	g++ -c Patron.cpp

Loan.o: Loan.cpp Loan.h
	g++ -c Loan.cpp

LibraryItems.o: LibraryItems.cpp DVD.h Book.h AudioCD.h LibraryItem.h LibraryItems.h
	g++ -std=c++14 -c LibraryItems.cpp

Loans.o: Loans.cpp Loan.h Loans.h
	g++ -std=c++14 -c Loans.cpp

Patrons.o: Patrons.cpp Patron.h Patrons.h
	g++ -std=c++20 -c Patrons.cpp

clean:
	rm *.o *.gch PLibrary a.out

