CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS =    ft_isalnum.c ft_isprint.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c ft_strrchr.c ft_toupper.c \
    ft_atoi.c ft_isalpha.c  ft_itoa.c ft_memmove.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_strtrim.c ft_bzero.c \
    ft_isascii.c  ft_memchr.c ft_memset.c  ft_putstr_fd.c ft_strjoin.c  ft_strncmp.c  ft_substr.c ft_calloc.c \
    ft_isdigit.c  ft_memcmp.c ft_putchar_fd.c ft_split.c ft_strlcat.c ft_strnstr.c ft_tolower.c ft_strmapi.c ft_striteri.c \

SRCSB = ft_lstmap_bonus.c ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
	ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c 

NAME = libft.a

OBJECT = $(SRCS:.c=.o)

OBJECTB = $(SRCSB:.c=.o)

%.o : %.c
	$(CC) $(CFLAGS) -c $^ -o $@

all : $(NAME)

$(NAME) : $(OBJECT) 
	@ar rcs $(NAME) $(OBJECT)

bonus : $(NAME) $(OBJECTB)
	@ar rcs $(NAME) $(OBJECTB) $(OBJECT)

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJECTB) $(OBJECT)

re: fclean all

.PHONY : all fclean clean re

.SECONDARY: $(OBJECTB) $(OBJECT)