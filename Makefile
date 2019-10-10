NAME = minishell
FLAG = -Wall -Wextra -Werror
SOURCE = minishell.c getinput.c expand.c display.c execute.c setenv.c cd.c \
	unsetenv.c echo.c util_gen.c util_get.c util_pwd.c util_sys.c util_tab.c
LIBFT_DIR = libft/
COMP_OBJ = ./obj/*.o
OBJ_DIR = ./obj
SRC_DIR = ./src
INCLUDE = ./inc
GGCOLORCYAN = \033[96m
GGCOLORGREEN = \033[32m
GGCOLORRED = \033[31m
GGMAG = \033[1;35m
GGRESET = \033[39m
SRC = $(addprefix $(SRC_DIR)/, $(SOURCE))
OBJ = $(addprefix $(OBJ_DIR)/, $(subst .c,.o, $(SOURCE)))

all: comp
	@mkdir -p $(OBJ_DIR)
	@make $(NAME)

comp:
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@gcc $(FLAG) $(COMP_OBJ) -I $(INCLUDE) -L $(LIBFT_DIR) -lft  -o $(NAME)
	@echo "$(GGCOLORCYAN)Creation$(GGRESET) du binaire $(GGMAG)./minishell$(GGRESET)..."
	@echo "$(GGCOLORGREEN)Success!$(GGRESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "[$(GGCOLORGREEN)✔$(GGRESET)] "$(subst .c,,$<)
	@mkdir -p $(dir $@) && gcc $(FLAG) -I $(INCLUDE) -o $@ -c $<

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(GGCOLORRED)Suppresion$(GGRESET) de minishell..."

re: fclean all

.PHONY: clean fclean re all
