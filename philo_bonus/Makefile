NAME		= philo_bonus

FLAGS		=  -I./$(HEADER)
FLAGS		+= -Wall -Wextra -Werror

SRC			= main_bonus.c  ft_isstr_digit.c ft_atoi.c ft_init_bonus.c\
			ft_time.c  ft_isdigit.c ft_monitor_bonus.c

HEADER		= header/

OBJ			= $(SRC:.c=.o) 

%.o: %.c Makefile ./header/philo_bonus.h
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
