# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 09:32:32 by dpoveda-          #+#    #+#              #
#    Updated: 2025/01/31 16:18:22 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror
TARGET = fdf
NAME_BONUS = .bonus
NAME = .name
SRC = mandatory/fdf.c mandatory/ft_split.c mandatory/color.c mandatory/draw.c mandatory/clean.c mandatory/print_grid.c mandatory/draw_utiliz.c mandatory/helper_function.c \
	mandatory/ft_strtol.c
BOF = bonus/fdf_bonus.c bonus/ft_split.c
ML_F = -lmlx -lXext -lX11 -Lminilibx_folder
MATH = -lm

all: $(NAME)

$(NAME) : banner
	@touch $(NAME)
	@rm -rf $(NAME_BONUS)
	@$(CC) $(SRC) $(ML_F) $(MATH) -o $(TARGET)

bonus : $(NAME_BONUS)

$(NAME_BONUS) : banner
	@rm -rf $(NAME)
	@touch $(NAME_BONUS)
	@$(CC) $(BOF) $(ML_F) $(MATH) -o $(TARGET)

clean :
	@rm -rf $(NAME_BONUS) $(NAME)

fclean : clean
	@rm -rf $(TARGET)

re : fclean all

.PHONY : all fclean clean re

banner:
	@echo " \033[32m  ____   ____    _____	\033[0m	\033[31m⠛⠛⣿⣿⣿⣿⣿⡷⢶⣦⣶⣶⣤⣤⣤⣀  \033[0m"
	@echo "\033[32m |  ___| |  _ \  |  ___| \033[0m	\033[31m ⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀\033[0m"
	@echo "\033[32m | |     | | | | | |     \033[0m	\033[31m ⠀⠀⠀⠉⠉⠉⠙⠻⣿⣿⠿⠿⠛⠛⠛⠻⣿⣿⣇⠀\033[0m"
	@echo "\033[32m | |     | | | | | |     \033[0m	\033[31m ⠀⠀⢤⣀⣀⣀⠀⠀⢸⣷⡄⠀⣁⣀⣤⣴⣿⣿⣿⣆\033[0m"
	@echo "\033[32m | |__   | | | | | |__   \033[0m	\033[31m ⠀⠀⠀⠀⠹⠏⠀⠀⠀⣿⣧⠀⠹⣿⣿⣿⣿⣿⡿⣿\033[0m"
	@echo "\033[32m |  __|  | | | | |  __|  \033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠛⠿⠇⢀⣼⣿⣿⠛⢯⡿⡟\033[0m"
	@echo "\033[32m | |     | | | | | |     \033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠦⠴⢿⢿⣿⡿⠷⠀⣿⠀\033[0m"
	@echo "\033[32m | |     | | | | | | 	\033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⠙⣷⣶⣶⣤⣤⣤⣤⣤⣶⣦⠃⠀\033[0m"
	@echo "\033[32m | |     | |_| | | |	    \033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⢐⣿⣾⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀\033[0m"
	@echo "\033[32m |_|     |____/  |_|  	\033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀\033[0m"
	@echo "\033[32m                         \033[0m	\033[31m ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠻⢿⣿⣿⣿⠟⠁\033[0m"

