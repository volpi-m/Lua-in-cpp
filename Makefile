EXAMPLE		=		test

SHARED_NAME	=		libluaincpp.so

STATIC_NAME	=		libluaincpp.a

SRC			=		src/Lua.cpp\
					src/BaseFunction.cpp\
					src/VoidFunction.cpp\
					src/NonVoidFunction.cpp\
					src/LuaFunction.cpp

OBJ			=		$(SRC:.cpp=.o)

SRC_EXAMPLE	=		example/main.cpp

OBJ_EXAMPLE	=		$(SRC_EXAMPLE:.cpp=.o)

OBJ_SHARED	=		$(SRC:.cpp=_shared.o)

CXXFLAGS	=		-W -Wall -Wextra --std=c++20 -iquote src

LDFLAGS		=		-llua -ldl

all:				$(BIN_TEST) $(SHARED_NAME) $(STATIC_NAME)

%_shared.o:			%.cpp
					g++ $(CXXFLAGS) -fPIC -c -o $@ $<

$(SHARED_NAME):		$(OBJ_SHARED)
					g++ -shared -o $@ $(OBJ_SHARED) $(LDFLAGS)

$(STATIC_NAME):		$(OBJ)
					ar rc $@ $(OBJ)


$(EXAMPLE):			$(SHARED_NAME) $(OBJ_EXAMPLE)
					g++ -o $(EXAMPLE) $(OBJ_EXAMPLE) -Wall -Wextra -L. -lluaincpp -llua

sfml:

clean:
					rm -rf $(OBJ)
					rm -rf $(OBJ_SHARED)

fclean:				clean
					rm -rf $(SHARED_NAME)
					rm -rf $(STATIC_NAME)
					rm -rf $(EXAMPLE)

re:					fclean $(EXAMPLE)
