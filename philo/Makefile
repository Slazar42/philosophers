
NAME = philo

SRCS = philo.c routine.c utils.c

OBJS = $(SRCS:.c=.o)

FLAGS = -Wall -Wextra -Werror

CCe = cc $(FLAGS)

all: $(LIBFT) $(NAME)

%.o : %.c
	$(CCe) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS) philo.h
	$(CCe) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re