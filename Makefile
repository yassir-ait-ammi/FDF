# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yaait-am <yaait-am@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/22 09:32:32 by dpoveda-          #+#    #+#              #
#    Updated: 2025/02/07 11:03:06 by yaait-am         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc  -Wall -Wextra -Werror
TARGET = fdf
NAME = .name
NAME_BONUS = .bonus
SRC = mandatory/fdf.c mandatory/ft_split.c mandatory/color.c mandatory/draw.c mandatory/clean.c mandatory/print_grid.c mandatory/draw_utiliz.c mandatory/helper_function.c \
	mandatory/ft_strtol.c mandatory/parsing.c mandatory/atoi.c
BOF = bonus/fdf_bonus.c bonus/ft_split_bonus.c bonus/print_grid_bonus.c bonus/color_bonus.c bonus/clean_bonus.c bonus/draw_bonus.c bonus/iso_bonus.c bonus/key_hook_bonus.c \
		bonus/mouse_render_hook_bonus.c bonus/utiliz_bonus.c bonus/ft_strtol_bonus.c bonus/read_bonus.c bonus/parsing_bonus.c bonus/ft_atoi_bonus.c
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

