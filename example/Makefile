# Makefile
# Matt Russell
# COMP 15 lab 1

# This Makefile builds the executable used by unit_test
# Note that the unit_test_driver.cpp does not exist in the current working
# directory; it is copied, used, and removed for you during the execution of the
# unit_test script

CXX = clang++
CXXFLAGS = -std=c++11 -Wall -Wextra

unit_test: unit_test_driver.cpp Foo_tests.cpp Foo.h
	$(CXX) $(CXXFLAGS) unit_test_driver.cpp Foo_tests.cpp

clean:
	-@rm -rf *.o *~ core* a.out 2>/dev/null
