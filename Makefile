SRC = \
		ft_split.c main.c

OBJ = $(SRC:.c=.o)

MINILIBX = mlx-linux/libmlx_Linux.a

CFLAGS = -Wall -Wextra -Werror

AR = ar rcs

NAME = FDF

all : $(NAME)

$(NAME): $(OBJ)
	@echo "compiling $(NAME)"
	@$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
	@sleep 1
	@echo "$(NAME) compiled successfully."

%.o: %.c
	@$(CC) $(CFLAGS) -I/usr/include -Imlx_linux -O3 -Imlx -c $< -o $@

fclean : clean
	@echo full cleaning of $(NAME) ...
	@$(RM) -f $(NAME)
	@sleep 0.5
	@echo $(NAME) cleaned.

clean :
	@echo cleaning $(NAME) ...
	@$(RM) -f $(OBJ)
	@sleep 0.5
	@echo $(NAME) cleaned.

re : fclean all