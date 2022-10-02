NAME		= philo

FLAGS		=  -I./$(HEADER)
FLAGS		+= -Wall -Wextra -Werror

SRC			= main.c  ft_isstr_digit.c ft_atoi.c ft_init.c\
			ft_time.c ft_pthread.c ft_free_var.c ft_isdigit.c\
			ft_memset.c ft_bzero.c ft_calloc.c

			
HEADER		= header/

OBJ			= $(SRC:.c=.o) 

%.o: %.c Makefile ./header/philo.h
		gcc -g $(FLAGS) -Imlx  -c $<  -o $@

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJ)
		gcc -g -lpthread $^  -o $@
		
clean:
		rm -f $(OBJ) 

fclean: clean
		rm -f $(NAME) 

re: fclean all

.PHONY:	all clean fclean re bonus

.SILENT:
