BIN			=	sfml_in_lua

SRC			=	main.cpp\
				Window.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	=	-Wall -Wextra --std=c++20

LDFLAGS		=	-lluaincpp -L. -llua -ldl -lcsfml-graphics -lcsfml-window

all:		$(OBJ)
			g++ -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
			rm -rf $(OBJ)
