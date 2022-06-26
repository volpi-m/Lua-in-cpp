BIN_TEST	=	test

SRC_TEST	=	main.cpp\
				Lua.cpp

OBJ_TEST	=	$(SRC_TEST:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra --std=c++20

LDFLAGS		=	-llua -ldl

test:		$(OBJ_TEST)
			g++ -o $(BIN_TEST) $(OBJ_TEST) $(LDFLAGS)

sfml:

clean:
			rm $(OBJ_TEST)

fclean:		clean
			rm $(BIN_TEST)
