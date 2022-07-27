SRC = window.c keys.c render.c compute.c mouse.c utils.c

OBJ = $(SRC:.c=.o)

NAME = cub3d

FLAGS  = -Wall -Wextra -Werror

CC = gcc

$(NAME): $(OBJ)
	$(CC) $(OBJ)  -lmlx -framework OpenGL -framework AppKit -o $(NAME) #-Lmlx

%.o: %.c
	$(CC) -Wall -Wextra -Werror -Imlx -c $< -o $@

.PHONY:		all clean fclean bonus

.c.o:
			gcc ${FLAGS} -c $< -o  ${@:.c = .o}  

clean:
			rm -f ${OBJ}

fclean:		clean
			rm -f ${NAME}

re:			fclean all