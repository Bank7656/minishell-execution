CC = cc
# CFLAGS = -Wall -Wextra -Werror

SRC := execute.c

HEADER := execute.h
HEADER_DIR  := ./

OBJ_DIR = ./objects/
SRC_OBJS = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(SRC_OBJS))

NAME = execute

all:
	make $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
