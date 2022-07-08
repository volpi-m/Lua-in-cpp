BIN_TEST	=	yeet

SRC_TEST	=	main.cpp\
				Lua.cpp\
				BaseFunction.cpp\
				VoidFunction.cpp\
				NonVoidFunction.cpp\
				LuaFunction.cpp

OBJ_TEST	=	$(SRC_TEST:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra --std=c++20

LDFLAGS		=	-llua -ldl

all:		yeet

yeet:		$(OBJ_TEST)
			g++ -o $(BIN_TEST) $(OBJ_TEST) $(LDFLAGS)

sfml:

clean:
			rm -rf $(OBJ_TEST)

fclean:		clean
			rm -rf $(BIN_TEST)

re:			fclean yeet
