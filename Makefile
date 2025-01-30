# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 09:32:32 by dpoveda-          #+#    #+#              #
#    Updated: 2025/01/30 19:26:32 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror
TARGET = fdf
NAME_BONUS = .bonus
NAME = .name
SRC = fdf.c ft_split.c color.c draw.c clean.c print_grid.c draw_utiliz.c helper_function.c
BOF = fdf_bonus.c ft_split.c
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

