# Makefile
# This Makefile builds the executable used by unit_test
# Note that main.cpp does not exist in the current working
# directory; it is created, used, and removed for you during the 
# execution of the unit_test

unit_test: main.o Foo_tests.o
	clang++ main.o Foo_tests.o
	
main.o: main.cpp Foo.h
	clang++ -c main.cpp
	
Foo_tests.o: Foo_tests.cpp Foo.h
	clang++ -c Foo_tests.cpp

clean:
	-@rm -rf *.o *~ core* a.out 2>/dev/null
