NAME		= libft.a
CC		= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -I includes

SRC		= \
		src/ft_c/ft_atoi.c \
		src/ft_c/ft_atol.c \
		src/ft_c/ft_bzero.c \
		src/ft_c/ft_calloc.c \
		src/ft_c/ft_cmp_str_asc.c \
		src/ft_c/ft_cmp_str_desc.c \
		src/ft_c/ft_isalnum.c \
		src/ft_c/ft_isalpha.c \
		src/ft_c/ft_isascii.c \
		src/ft_c/ft_isdigit.c \
		src/ft_c/ft_isprint.c \
		src/ft_c/ft_isspace.c \
		src/ft_c/ft_itoa.c \
		src/ft_c/ft_ltoa.c \
		src/ft_c/ft_memchr.c \
		src/ft_c/ft_memcmp.c \
		src/ft_c/ft_memcpy.c \
		src/ft_c/ft_memmove.c \
		src/ft_c/ft_memset.c \
		src/ft_c/ft_putchar_fd.c \
		src/ft_c/ft_putendl_fd.c \
		src/ft_c/ft_putnbr_fd.c \
		src/ft_c/ft_putstr_fd.c \
		src/ft_c/ft_split.c \
		src/ft_c/ft_str_endswith.c \
		src/ft_c/ft_str_isspace.c \
		src/ft_c/ft_str_startswith.c \
		src/ft_c/ft_strchr.c \
		src/ft_c/ft_strcmp.c \
		src/ft_c/ft_strdup.c \
		src/ft_c/ft_striteri.c \
		src/ft_c/ft_strjoin.c \
		src/ft_c/ft_strlcat.c \
		src/ft_c/ft_strlcpy.c \
		src/ft_c/ft_strlen.c \
		src/ft_c/ft_strmapi.c \
		src/ft_c/ft_strncmp.c \
		src/ft_c/ft_strndup.c \
		src/ft_c/ft_strnstr.c \
		src/ft_c/ft_strrchr.c \
		src/ft_c/ft_strreplace.c \
		src/ft_c/ft_strtrim.c \
		src/ft_c/ft_substr.c \
		src/ft_c/ft_tolower.c \
		src/ft_c/ft_toupper.c \
		src/ft_lst/ft_lst_foreach.c \
		src/ft_lst/ft_lst_removeif.c \
		src/ft_lst/ft_lst_sort.c \
		src/ft_lst/ft_lstadd_back.c \
		src/ft_lst/ft_lstadd_front.c \
		src/ft_lst/ft_lstclear.c \
		src/ft_lst/ft_lstdelone.c \
		src/ft_lst/ft_lstiter.c \
		src/ft_lst/ft_lstlast.c \
		src/ft_lst/ft_lstmap.c \
		src/ft_lst/ft_lstnew.c \
		src/ft_lst/ft_lstsize.c \
		src/ft_arr/ft_arr_sort.c \
		src/ft_arr/ft_arradd.c \
		src/ft_arr/ft_arrdup.c \
		src/ft_arr/ft_arrfree.c \
		src/ft_arr/ft_arrlen.c

OBJ		= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
