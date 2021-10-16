.PHONY: all re fclean clean

NAME = libjson.a
TESTNAME = test

CC = clang++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -pedantic -g

OBJDIR = .obj
HEADERS = Array.hpp  AType.hpp  Boolean.hpp  JSON.hpp  Null.hpp  Number.hpp  Object.hpp  String.hpp    
SOURCES = Array.cpp  AType.cpp  Boolean.cpp  JSON.cpp  Null.cpp  Number.cpp  Object.cpp  String.cpp
OBJECTS = $(addprefix ${OBJDIR}/, $(SOURCES:.cpp=.o))

all: objdir $(NAME)

objdir:
	@if ! [ -d ${OBJDIR} ] ; then mkdir ${OBJDIR} ; fi

test: $(NAME) main.cpp
	$(CC) $(CPPFLAGS) main.cpp -ljson -L. -o $(TESTNAME)

$(NAME): $(OBJECTS) $(HEADERS)
	ar rc $@ $^

${OBJDIR}/%.o : %.cpp ${HEADERS}
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -rf ${OBJDIR}
	@rm -rf ${TESTNAME}

fclean: clean
	@rm -rf $(NAME)

re: fclean all
