NAME            = cub3d
BONUS           = $(wildcard bonus/*.c)
SRCS            = $(wildcard src/*.c)
files           = $(SRCS) $()
OBJS            = ${files:.c=.o}
CC              = clang
CFLAGS          = -Wall -Wextra -Werror
RM              = rm -rf

all: ${NAME}

%.o: %.c
	$(CC) -I/usr/include -I./ -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft	
	$(CC) $(OBJS) -Lmlx_linux -L/usr/lib -Imlx_linux  -lX11 -lm -lz -lbsd -lmlx -lXext -lX11 ./libft/libft.a -o  $(NAME)

clean:
	$(MAKE) -C libft fclean
	${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader ${wildcard *.c} ${wildcard *.h} ${wildcard libft/*.c} ${wildcard libft/*.h}

bonus: all

.PHONY: clean fclean re all bonus norme
