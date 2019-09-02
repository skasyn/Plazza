##
## EPITECH PROJECT, 2019
## PROJECT NAME
## File description:
## UNBELIEVABLE DESCRIPTION
##

SRC		=		./Core/main.cpp					\
				./Core/Interpretor.cpp				\
				./Core/IPC.cpp					\
				./Core/KitchenManager.cpp			\
				./Reception/Reception.cpp			\
				./Kitchen/Kitchen.cpp				\

TSRCS		:=	$(SRC)

TSRCS		+=	

TNAME		=	plazza.test

OBJ		=	$(addsuffix .o, $(basename $(SRC)))

NAME		=	plazza

CC		=	g++

FLAGS		=

CFLAGS		=	-Wall -Wextra -I./Core -I./Reception -I./Kitchen \
				-I./global_material -g3

LDLIBS		=	-lpthread

MAKEDIR		=	make --no-print-directory -C

all:	core

tests_run:
	@echo -e "[32m\n==== [92mCOMPILING TESTS[32m ====[0m"
	@$(MAKE) -s re
	@$(CC) $(TFLAGS) -o $(TNAME) $(TSRCS)
	@./$(TNAME)

core:	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDLIBS)
	@echo -e "[32m\n==== [92mCOMPLETED[32m ====[0m"

debug: CFLAGS += -DDEBUG
debug:	$(OBJ)
	@$(CC) -o $(NAME) $(OBJ) $(LDLIBS)
	@echo -e "[32m\n==== [92mCOMPLETED[32m ====[0m"


clean:
	@$(RM) $(OBJ)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [CLEANING][0m"

clean_tobjs:	clean
	@$(RM) $(wildcard *.gcda)
	@$(RM) $(wildcard *.gcno)
	@$(RM) $(wildcard *.c.gcov)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [CLEANING TESTS][0m"

fclean:	clean clean_tobjs
	@$(RM) $(NAME)
	@$(RM) $(TNAME)
	@echo -en "[32m[OK][0m"
	@echo -e "[91m [FCLEANING][0m"

re:	fclean all

%.o:	%.cpp
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $< \
	&& echo -e "[32m[OK]\e[1m[32m" $< "[0m" || echo -e "ERROR" $<

.PHONY: all clean fclean re tests_run clean_tobjs
