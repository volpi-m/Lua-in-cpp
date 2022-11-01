BIN_TEST	=		yeet

SHARED_NAME	=		libluaincpp.so

STATIC_NAME	=		libluaincpp.a

SRC_TEST	=		src/main.cpp\
					src/Lua.cpp\
					src/BaseFunction.cpp\
					src/VoidFunction.cpp\
					src/NonVoidFunction.cpp\
					src/LuaFunction.cpp

OBJ_TEST	=		$(SRC_TEST:.cpp=.o)

SRC			=		src/Lua.cpp\
					src/BaseFunction.cpp\
					src/VoidFunction.cpp\
					src/NonVoidFunction.cpp\
					src/LuaFunction.cpp

OBJ			=		$(SRC:.cpp=.o)

OBJ_SHARED	=		$(SRC:.cpp=_shared.o)

CXXFLAGS	=		-W -Wall -Wextra --std=c++20

LDFLAGS		=		-llua -ldl

all:				$(BIN_TEST) $(SHARED_NAME) $(STATIC_NAME)

%_shared.o:			%.cpp
					g++ $(CXXFLAGS) -fPIC -c -o $@ $<

$(BIN_TEST):		$(OBJ_TEST)
					g++ -o $@ $< $(LDFLAGS)

$(SHARED_NAME):		$(OBJ_SHARED)
					g++ -shared -o $@ $< $(LDFLAGS)

$(STATIC_NAME):		$(OBJ)
					ar rc $@ $<

sfml:

clean:
					rm -rf $(OBJ_TEST)
					rm -rf $(OBJ)
					rm -rf $(OBJ_SHARED)

fclean:				clean
					rm -rf $(BIN_TEST)
					rm -rf $(SHARED_NAME)
					rm -rf $(STATIC_NAME)

re:					fclean $(BIN_TEST)
