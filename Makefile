NAME = minishell

OBJS_PATH = obj/
SRCS_PATH = src/
LIBFT_PATH = libft/

FLAGS = -Wall -Werror -Wextra
INC = -I ./includes/ -I ./libft/includes

SRCS_NAME = builtins.c \
			children.c \
			error.c \
			execute.c \
			ft_cd.c \
			ft_setenv.c \
			ft_unsetenv.c \
			in_path.c \
			intpt.c \
			main.c \
			parse.c \
			sig_handler.c \
			utill.c

SRCS = $(addprefix $(SRCS_PATH), $(SRCS_NAME))
OBJS = $(addprefix $(OBJS_PATH), $(OBJS_NAME))

.PHONY: all, clean, fclean, re

all: $(NAME)

$(NAME): $(OBJS)
	@make -C ./libft
	@gcc -c $(FLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -o $(NAME)

$(OBJS_PATH): $(SRCS_PATH)%.c
	@mkdir -p obj/
	@gcc $(FLAGS) $(INC) -c $< -o $@

clean:
	@make -C ./libft clean
	@/bin/rm -rf obj/

fclean: clean
	@make -C ./libft fclean
	@/bin/rm -f $(NAME)

re: fclean all
