NAME		=	ircserv
CXX			=	c++
42FLAGS		=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS	+=	$(42FLAGS)
CXXFLAGS	+=	-g3
IFLAGS		+=	-Iinclude

INC_DIR		=	include

all: $(NAME)

$(NAME):
	$(CXX) $(CXXFLAGS) $(IFLAGS) src/*.cpp -o $(NAME)

.clangd: Makefile
	@echo "Making clangd configuration file"
	@echo -n																\
	"CompileFlags:\n"														\
	"  Compiler: c++\n"													\
	"  Add:\n"																\
	"    - \""$(42FLAGS)"\"\n"	> .clangd
	@for file in $(INC_DIR); do												\
		echo "     - \"-I"$(shell pwd)"/"$$file"\"" >> .clangd;				\
	done ;
	@echo $(GREEN) "Done" $(RESET)

clean:

fclean:
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
