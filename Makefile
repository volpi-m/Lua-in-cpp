BIN_TEST	=	yeet

SHARED_NAME	=	libluaincpp.so

STATIC_NAME	=	libluaincpp.a

SRC_TEST	=	src/main.cpp\
				src/Lua.cpp\
				src/BaseFunction.cpp\
				src/VoidFunction.cpp\
				src/NonVoidFunction.cpp\
				src/LuaFunction.cpp

OBJ_TEST	=	$(SRC_TEST:.cpp=.o)

SRC			=	src/Lua.cpp\
				src/BaseFunction.cpp\
				src/VoidFunction.cpp\
				src/NonVoidFunction.cpp\
				src/LuaFunction.cpp

OBJ			=	$(SRC:.cpp=.o)

CXXFLAGS	=	-W -Wall -Wextra --std=c++20

LDFLAGS		=	-llua -ldl

all:		yeet

yeet:		$(OBJ_TEST)
			g++ -o $(BIN_TEST) $(OBJ_TEST) $(LDFLAGS)

shared:		$(OBJ)
			g++ -shared -o $(SHARED_NAME) $(OBJ) $(LDFLAGS)

static:		$(OBJ)
			ar rc $(STATIC_NAME) $(OBJ)

sfml:

clean:
			rm -rf $(OBJ_TEST)

fclean:		clean
			rm -rf $(BIN_TEST)
			rm -rf $(SHARED_NAME)
			rm -rf $(STATIC_NAME)

re:			fclean yeet
