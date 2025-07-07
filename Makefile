# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 12:34:46 by bgoulard          #+#    #+#              #
#    Updated: 2025/07/07 12:34:46 by bgoulard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# add version by git tag
NAME		:=	ircserv
VERSION		:= $(shell git describe --tags --dirty 2> /dev/null || echo "0.0.0")
CXX			:=	c++

.DEFAULT_GOAL	:= $(NAME)

INC_DIR		:=	include
SRC_DIR		:=	src
OBJ_DIR		:=	build

# warnings
42FLAGS		:=	-Wall -Wextra -Werror -std=c++98
WFLAGS_EXTRA:=	-Wmissing-prototypes
WFLAGS		:= $(42FLAGS) $(WFLAGS_EXTRA)
# IFLags -> include flag -> (not good as naming scheme, we dont only want
# 	include but everything that interacts with '#<directives> [arg]' here.
# CPPFlags -> C-style Pre-Processor Flags
# 	compilation steps as a reminder
# 		[code]
# 		-> preprocessor (append files, expand macro, resolve defines, ...) [.i file]
# 		-> compile
# 			-> intermediary representation								[.ll]
# 			-> assembly													[.s]
# 			-> object files												[.o]
# 		-> link															[.exe||.out]
# pre-processor stuff
VARFLAGS	:=	-DIRC_SERVER_VERSION="$(VERSION)"
CPPFLAGS	:=	$(addprefix -I, $(INC_DIR)) -MMD -MP $(VARFLAGS)

DEV_FLAGS	:=	-g3 -glldb -O0	\
				-fno-inline -fno-inline-functions

CXXFLAGS	:=	$(WFLAGS) $(CPPFLAGS)
# todo - rm lin bellow for submition
CXXFLAGS	+=	$(DEV_FLAGS)

SRCS		=	$(shell find $(SRC_DIR) -name '*\.cpp')
SRCS		:=	$(sort $(SRCS))
OBJS		:=	$(patsubst %.cpp, %.o, $(addprefix $(OBJ_DIR)/,$(SRCS)))

# Rules
# Default rule for 'normal' objects
$(OBJ_DIR)/$(SRC_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo -n "making" $@ "from" $<						
	@mkdir -p $(dir $@)								&& \
	$(CXX) $(CXXFLAGS) -c $< -o $@					&& \
	echo -e	"\tSuccess!"							|| \
	echo	"Failure :("


-include $(OBJS:.o=.d)

$(NAME): $(OBJS)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)	&&	\
	echo	"Success!"	||	\
	echo	"Failure :("

# .clangd config file auto-gen - better diagnostics
# 	- "fall back" config if compile_commands.json does not have current file
.clangd: Makefile
	echo -n															\
	"CompileFlags:\n"												\
	"  Compiler: clang\n"											\
	"  Add:\n"														\
	"   - \"-Wall -Wextra -Werror\"\n"								\
	"   - \""$(WFLAGS)"\"\n"										\
	"   - \"-xc\"\n"  > .clangd										&& \
	for file in $(INC_DIR); do										\
		echo "    - \"-I"$(shell pwd)"/"$$file"\"" >> .clangd;		\
	done

# tags file auto-gen - jump cappabilities in nvim
tags: Makefile $(SRCS)
	ctags	-Ra

# compile_commands.json config file auto-gen - even better diagnostics 
# 	- slow to update
compile_commands.json: Makefile $(SRCS)
	bear	--append -- make	re

# Rule to clean objects
clean:
	$(RM) -rf $(OBJ_DIR) 2> /dev/null

# Rule to clean objects and compiled files
fclean: clean
	$(RM) -rf $(NAME) 2> /dev/null

# cleanup dev_env
uclean:
	rm -rf .clangd compile_commands.json tags 2> /dev/null

# Rule to recompile
re:	fclean
	make --no-print-directory

dev_env: .clangd compile_commands.json tags

.PHONY: all clean fclean re
