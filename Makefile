.PHONY: all re fclean clean

NAME = libjson.a
TESTNAME = test

CC = clang++
CPPFLAGS = -Wall -Wextra -Werror -std=c++98 -Wc++11-extensions -Wpedantic -g

OBJDIR = .obj
SRCDIR = src
HEADERS = Array.hpp  AType.hpp  Boolean.hpp  JSON.hpp  Null.hpp  Number.hpp  Object.hpp  String.hpp  Utils.hpp  
SOURCES = Array.cpp  AType.cpp  Boolean.cpp  JSON.cpp  Null.cpp  Number.cpp  Object.cpp  String.cpp  Utils.cpp
OBJECTS = $(addprefix ${OBJDIR}/, $(SOURCES:.cpp=.o))
FULL_HEADERS = $(addprefix ${SRCDIR}/, ${HEADERS})

all: objdir $(NAME)

objdir:
	@if ! [ -d ${OBJDIR} ] ; then mkdir ${OBJDIR} ; fi

test: all test2.cpp
	$(CC) $(CPPFLAGS) test2.cpp -ljson -L. -I ${SRCDIR} -o $(TESTNAME)

$(NAME): $(OBJECTS) $(FULL_HEADERS)
	ar rc $@ $^

${OBJDIR}/%.o: ${SRCDIR}/%.cpp ${FULL_HEADERS}
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	@rm -f main.o
	@rm -rf ${OBJDIR}
	@rm -rf ${TESTNAME}

fclean: clean
	@rm -rf $(NAME)

re: fclean all
