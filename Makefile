CC = cc

ifeq ($(DEBUG), 1)
	CFLAGS = -Wall -Wextra -Werror -g -DDEBUG=1
	export DEBUG
else
	CFLAGS = -Wall -Wextra -Werror -DDEBUG=0
endif

NAME = fdf

SRC = fdf.c \

OBJ = $(SRC:.c=.o)

#LIBFT VARIABLES
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# OS SPECIFICS
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -DMAC_OS=1
	MLX_DIR = minilibx_macos
	LFLAGS = $(LIBFT) $(MLX) -framework OpenGL -framework AppKit
endif
ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX=1
	MLX_DIR = minilibx-linux
	LFLAGS = $(LIBFT) $(MLX) -lXext -lX11 -lm
endif
MLX = $(MLX_DIR)/libmlx.a

IFLAGS = -I$(LIBFT_DIR) -I$(MLX_DIR)

#PREFIX/COLOUR VARIABLES
C_GRAY = \033[1;30m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m
C_CYAN = \033[0;36m
NC = \033[0m

PREFIX = $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

print:
	@echo $(NAME)
	@echo $(CC)
	@echo $(CFLAGS)
	@echo $(LFLAGS)
	@echo $(IFLAGS)
	@echo $(SRC)
	@echo $(OBJ)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	@printf "$(PREFIX) CREATING $(C_CYAN)$(NAME)$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(LIBFT):
	@printf "$(PREFIX) MAKING $(C_CYAN)$(LIBFT)$(NC) ARCHIVE\n"
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@printf "$(PREFIX) MAKING $(C_CYAN)$(MLX)$(NC) ARCHIVE\n"
	@$(MAKE) -C $(MLX_DIR)

%.o: %.c
	@printf "$(PREFIX) $(C_GRAY)COMPILING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) $(IFLAGS) -MMD -c $< -o $@

debug: fclean debug_cflags $(NAME)

debug_cflags:
	@$(eval CFLAGS = -Wall -Wextra -Werror -g -DDEBUG=1)
	@$(eval export DEBUG=1)

clean:
	@printf "$(PREFIX) $(C_RED)REMOVING OBJECT FILES$(NC)\n"
	@rm -f $(OBJ)
	@$(MAKE) fclean -C $(LIBFT_DIR)

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug debug_cflags print
