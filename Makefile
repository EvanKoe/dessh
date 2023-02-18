SRC = $(wildcard src/*.c) \
	$(wildcard lib/*.c)

OBJ = $(SRC:.c=.o)

NAME = shell

CFLAGS = -g -Wextra -Wall

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -L./include -lcstdstring -lreadline

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
