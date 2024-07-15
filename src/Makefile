CC = g++
CFLAGS = -std=c++17 -O3 
SRC = main.cpp code.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = tsp

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)