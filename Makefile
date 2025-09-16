CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

# Цели
all: program.out test_student

program.out: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o program.out

test_student: test_student.cpp
	$(CXX) $(CXXFLAGS) test_student.cpp -o test_student.out -lgtest -lgtest_main -pthread
	./test_student.out

clean:
	rm -f program.out test_student.out

.PHONY: all test_student clean
