CC = cc
# CFLAGS = -Wall -Wextra -Werror

SRC := execute.c redirect.c utils.c

HEADER := execute.h
HEADER_DIR  := ./

OBJ_DIR = ./objects/
SRC_OBJS = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(SRC_OBJS))

# Libft
LIBFT_NAME = libft.a
LIBFT_DIR := ./libft/
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))

NAME = execute

all:
	make $(NAME)

$(NAME): $(LIBFT) $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) $(OBJS) -L./libft -lft -o $(NAME)

$(OBJ_DIR)%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I $(HEADER_DIR) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

$(LIBFT) : $(LIBFT_OBJS)
	@echo "$(COLOUR_GREEN)Create libft.a$(END_COLOUR)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(COLOUR_GREEN)[libft.a was created successfully] >_<\n$(END_COLOUR)"

$(LIBFT_OBJS):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
