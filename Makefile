NAME = pipex

LIBFT = ./libft/libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

RM = rm -rf

SRC_DIR = src/
OBJ_DIR = obj/

SRC_FILES = pipex pipex_utils

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))

HEAD = ./include/

all : $(LIBFT) $(NAME)

$(NAME) : $(OBJ)
	@echo "\033[0;33m\nCOMPILING PIPEX...\n"
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[1;32m./pipex created\n"

$(LIBFT)	:
	@echo "\033[0;33m\nCOMPILING LIBFT\n"
	@make -C ./libft
	@echo "\033[1;32mLIBFT created\n"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I $(HEAD) -c $< -o $@

clean :
	$(RM) ./libft/*.o
	$(RM) $(OBJ_DIR)

fclean : clean
	$(RM) ./libft/libft.a
	$(RM) $(NAME)

re : fclean all