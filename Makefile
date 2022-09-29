# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gmehdevi <gmehdevi@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/07 12:30:25 by chchao            #+#    #+#              #
#    Updated: 2022/09/29 16:01:07 by gmehdevi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            = 	cub3d

SRCS            = 	src/controls.c \
					src/main.c \
					src/parsing/colors.c \
					src/parsing/init_map.c \
					src/parsing/verify.c \
					src/parsing/parsing.c \
					src/parsing/textures.c \
					src/compute/angle.c \
					src/compute/operators.c \
					src/compute/compute.c \
					src/render/draw.c \
					src/render/minimap.c \
					src/render/render.c 

OBJS            = 	${SRCS:.c=.o}
CC              = 	clang
CFLAGS          = 	-Wall -Wextra -Werror
RM              = 	rm -rf
INCLUDE			= 	./ 
all: ${NAME}

%.o: %.c
	$(CC) -I/usr/include -I$(INCLUDE) -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft	
	$(CC) $(OBJS)  -lmlx -framework OpenGL -framework AppKit ./libft/libft.a -o  $(NAME)
#$(CC) $(OBJS) -Lmlx_linux -L/usr/lib -Imlx_linux  -lm -lz -lbsd -lmlx  ./libft/libft.a -o  $(NAME)

clean:
	$(MAKE) -C libft fclean
	${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader ${wildcard ./src/*/*.c} ${wildcard ./src/*.c} ${wildcard src/*.h} ${wildcard libft/*.c} ${wildcard libft/*.h}


format:
	python3 -m c_formatter_42 < $(SRCS) src/cub3d.h

bonus: all

.PHONY: clean fclean re all bonus norme
