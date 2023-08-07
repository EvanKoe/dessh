SRC = $(wildcard src/*.c) \
	$(wildcard lib/*.c)

OBJ = $(SRC:.c=.o)

NAME = shell

CFLAGS = -g -Wextra -Wall

all: cstring $(NAME)

cstring:
	make -C ./lib/cstd_string

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME) -L ./lib/cstd_string -l cstdstring -lreadline

clean:
	rm -f $(OBJ)
	make clean -C ./lib/cstd_string

fclean: clean
	rm -f $(NAME)
	make fclean -C ./lib/cstd_string

re: fclean all
