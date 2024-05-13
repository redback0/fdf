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

LIBFT = libft
DLIBS = $(LIBFT) $(MLX)
LIBS = ft mlx
FLIBS = $(join $(addsuffix /lib, $(DLIBS)), $(addsuffix .a, $(LIBS)))

LFLAGS = $(addprefix -L, $(DLIBS)) $(addprefix -l, $(LIBS))

# OS SPECIFICS
UNAME := $(shell uname -s)
ifeq ($(UNAME),Darwin)
	CFLAGS += -DMAC_OS
	MLX = minilibx_macos
	LFLAGS += -framework OpenGL -framework AppKit
	export CFLAGS=GL_SILENCE_DEPRECATION
endif
ifeq ($(UNAME),Linux)
	CFLAGS += -DLINUX
	MLX = minilibx-linux
	LFLAGS += -lXext -lX11 -lm
endif


IFLAGS = $(addprefix -I, $(DLIBS))

#PREFIX/COLOUR VARIABLES
C_GRAY = \033[1;30m
C_ORANGE = \033[0;33m
C_RED = \033[0;31m
C_CYAN = \033[0;36m
NC = \033[0m

PREFIX := $(C_ORANGE)<$(NAME)>$(NC)

all: $(NAME)

print:
	@echo $(NAME)
	@echo $(CC)
	@echo $(CFLAGS)
	@echo $(LFLAGS)
	@echo $(IFLAGS)
	@echo $(SRC)
	@echo $(OBJ)
	@echo $(DLIBS)
	@echo $(LIBS)
	@echo $(FLIBS)

$(NAME): $(OBJ) $(FLIBS)
	@printf "$(PREFIX) CREATING $(C_CYAN)$@$(NC)\n"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)

$(FLIBS):
	@printf "$(PREFIX) MAKING $(C_CYAN)$@$(NC) ARCHIVE\n"
	@$(MAKE) -C $(dir $@) --no-print-directory -s

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
	@$(MAKE) fclean -C $(LIBFT) --no-print-directory -s
	@$(MAKE) clean -C $(MLX) --no-print-directory -s
	@$(shell $(addprefix $(MAKE) fclean clean -C, $(DLIBS)))

fclean: clean
	@printf "$(PREFIX) $(C_RED)REMOVING ARCHIVE$(NC)\n"
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re debug debug_cflags print
