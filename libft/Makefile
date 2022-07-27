SRCS_PRINT 		= ft_printf/ft_chars.c ft_printf/ft_numbers.c ft_printf/ft_parse.c ft_printf/ft_printf.c ft_printf/ft_tab.c ft_printf/padding.c

SRCS_GNL		= get_next_line/get_next_line.c get_next_line/get_next_line_utils.c

SRCS			=	$(SRCS_PRINT) \
					$(SRCS_GNL) \
					ft_error.c ft_freepp.c ft_strarrsize.c ft_remove_from_strarr.c \
					ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
					ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c ft_strcmp.c \
					ft_itoa.c  ft_itoa_u.c ft_atol.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c ft_memccpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c ft_str_isnum.c\
					ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
					ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
					ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
					ft_abs.c ft_min.c ft_max.c ft_swap.c ft_sign.c\
					
OBJS			= $(SRCS:.c=.o)

NAME		= libft.a

CFLAGS		= -Wall -Wextra -Werror

.PHONY:		all clean fclean bonus

.SILENT: $(NAME) 

all:		${NAME}

${NAME}:	${OBJS}
			ar -rcs $@ $^
bonus: 	
			gcc ${CFLAGS} -c ${BONUS} ${SRCS}  ;ar -rcs ${NAME} ${BONUS_OBJS} 

.c.o:
			gcc ${CFLAGS} -c $< $(INCLUDES) -o  ${@:.c = .o}  

clean:
			rm -f ${OBJS} ./*o

fclean:		clean
			rm -f ${NAME}

re:			fclean all