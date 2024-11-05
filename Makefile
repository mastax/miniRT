NAME = miniRT
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_DIR = mandatory

OBJ_DIR = objects

DEPS = $(SRC_DIR)/parsing/parsing1.c $(SRC_DIR)/parsing/parsing.c $(SRC_DIR)/parsing/parsing_utils.c $(SRC_DIR)/vectors/vec2r.c $(SRC_DIR)/vectors/vec2r1.c $(SRC_DIR.c)/vectors/vec_mangnitude.c \
	$(SRC_DIR)/vectors/addition_substra.c main.c $(SRC_DIR)/colors/colors.c

HEADERS = miniRT.h

OBJ = $(DEPS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)  -lmlx \
		-framework Cocoa -framework OpenGL -framework AppKit libmlx.a

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c	$(HEADERS)	|	$(OBJ_DIR)
	$(CC)	$(CFLAGS)	-o	$@	-c	$<


$(OBJ_DIR):
	mkdir $@

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME)

re: fclean all