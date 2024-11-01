NAME = miniRT

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = mandatory

OBJ_DIR = objects

DEPS = $(SRC_DIR)/.c $(SRC_DIR)/.c $(SRC_DIR)/.c $(SRC_DIR)/.c $(SRC_DIR)/.c $(SRC_DIR.c)/.c \
	$(SRC_DIR)/.c $(SRC_DIR)/.c $(SRC_DIR)/.c

HEADERS = $(SRC_DIR)/.h

OBJ = $(DEPS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)  -lmlx \
		-framework Cocoa -framework OpenGL -framework AppKit libmlx.a

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	$(HEADERS)	|	$(OBJ_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<


$(OBJ_DIR):
	mkdir $@

$(OBJ_DIR_BONUS):
	mkdir $@

clean:
	rm -f $(OBJ_DIR)/*.o $(OBJ_DIR_BONUS)/*.o

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)

bonus: $(NAME_BONUS)

re: fclean all