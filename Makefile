# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ykhadiri <ykhadiri@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/24 18:54:21 by ykhadiri          #+#    #+#              #
#    Updated: 2022/08/14 01:10:24 by ykhadiri         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLK = \033[0;30m
RED = \033[0;31m
GRN = \033[0;32m
YEL = \033[0;33m
BLU = \033[0;31m
MAG = \033[0;35m
CYN = \033[0;36m
WHT = \033[0;37m
NAME = minishell
CC = cc 
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -f

SRC = minishell.c \
	used_functions/minishell_start.c \
	used_functions/ft_strlen.c \
	used_functions/is_validated.c \
	used_functions/ft_strtrim.c \
	used_functions/ft_strcmp.c \
	used_functions/ft_strncmp.c \
	used_functions/ft_atoi.c \
	used_functions/ft_strdup.c \
	used_functions/ft_strjoin_space.c \
	used_functions/ft_strjoin.c \
	used_functions/ft_isalnum.c \
	used_functions/ft_islast.c \
	used_functions/ft_isdigit.c \
	used_functions/ft_substr.c \
	used_functions/ft_strndup.c \
	used_functions/add_back.c \
	parsing/initialize_tokens.c \
	parsing/tokenizing.c \
	parsing/tokenizing_utils_1.c \
	parsing/tokenizing_utils_2.c \
	parsing/tokenizing_utils_3.c \
	parsing/check_syntax.c \
	parsing/check_syntax_utils.c \
	parsing/parser.c \
	parsing/parser_utils_1.c \
	parsing/parser_utils_2.c \
	parsing/expander.c\
	parsing/expander_utils.c\
	used_functions/ft_split.c \
	used_functions/ft_itoa.c \
	used_functions/ft_strrchr.c \
	used_functions/execution_other_builtins.c \
	used_functions/execution.c \
	used_functions/rdr_execution.c \
	used_functions/cmd_founded_y_n.c \
	used_functions/for_cmd_founded_y_n.c \
	used_functions/builtins_execution.c \
	used_functions/for_export_1.c \
	used_functions/for_export_2.c \
	used_functions/ft_lstsize.c \
	redirections/output_rdr_std_appnd.c \
	redirections/input_rdr_std_appnd.c \
	builtins/export.c \
	pipes/pipe.c \
	pipes/for_pipe.c \
	builtins/echo.c \
	used_functions/for_echo.c \
	builtins/cd.c \
	builtins/pwd.c \
	builtins/unset.c \
	builtins/env.c \
	builtins/exit.c \
	interactive_modes/ctrl-D.c \
	interactive_modes/ctrl-C.c \
	interactive_modes/ctrl-slash.c \
	garbage/garbage_collector.c \

OBJ = $(SRC:.c=.o)

%.o: %.c minishell.h
	@$(CC) $(CFLAGS) -I $(shell brew --prefix readline)/include -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -L $(shell brew --prefix readline)/lib -lreadline -o $(NAME)
	@echo "${YEL}Done!"

all : $(NAME)

clean :
	@$(RM) $(OBJ)
	@echo "${RED}Done!"

fclean : clean
	@$(RM) $(NAME)

re: fclean all
