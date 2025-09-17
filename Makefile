# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bgoulard <bgoulard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/07 12:34:46 by bgoulard          #+#    #+#              #
#    Updated: 2025/08/06 14:01:54 by apetitco         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# add version by git tag
NAME		:=	ircserv
VERSION		:= $(shell git describe --tags --dirty 2> /dev/null || echo "0.0.0")
AUTHORS		:= "Baptiste GOULARD, Alessandro PETITCOLLIN"
DEPLOYMENT	:=	prod
CXX			:=	c++

.DEFAULT_GOAL	:= $(NAME)

INC_DIR		:=	include
SRC_DIR		:=	src
OBJ_DIR		:=	build

IS_PROD = $(if $(filter prod,$(DEPLOYMENT)),true,false)

# warnings
42FLAGS		:=	-Wall -Wextra -Werror -Wunused -std=c++98
WFLAGS_EXTRA:=
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

VARFLAGS	:=	-DIRC_SERVER_VERSION=\"$(VERSION)\"	\
				-DIRC_SERVER_AUTHORS=\"$(AUTHORS)\"

ifeq ($(IS_PROD), false)
	VARFLAGS	:=	$(VARFLAGS)	-DTESTS	-DDEV
endif
CPPFLAGS	:=	$(addprefix -I, $(INC_DIR)) -MMD -MP $(VARFLAGS)
# $(DEV_FLAGS) -> dev flags | debug info, no inlining, no optimizations
DEV_FLAGS	:=	-g3 -O0 -fno-inline -fno-inline-functions \
				-fsanitize=address -fsanitize=undefined
# $(PROD_FLAGS) -> prod flags | o2 (speed, stability), lto (link time optimization)
PROD_FLAGS	:=	-O2 -flto

CXXFLAGS	:=	$(WFLAGS) $(CPPFLAGS)
ifeq ($(IS_PROD), false)
	CXXFLAGS	+=	$(DEV_FLAGS)
else
	CXXFLAGS	+=	$(PROD_FLAGS)
endif

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
