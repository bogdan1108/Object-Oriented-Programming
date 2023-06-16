OBJS	= complex_number.o complex_test.o tester.o
SOURCE	= complex_number.cpp complex_test.cpp tester.cpp
HEADER	= complex_number.h complex_test.h
OUT	= tester
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

complex_number.o: complex_number.cpp
	$(CC) $(FLAGS) complex_number.cpp 

complex_test.o: complex_test.cpp
	$(CC) $(FLAGS) complex_test.cpp 

tester.o: tester.cpp
	$(CC) $(FLAGS) tester.cpp 


clean:
	rm -f $(OBJS) $(OUT)