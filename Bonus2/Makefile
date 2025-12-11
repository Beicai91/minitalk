NAME_CB = client_bonus
NAME_SB = server_bonus
CC = cc
CFLAGS = -Wextra -Werror -Wall -fsanitize=address
LIBFT_PATH = ../lib/libft
LIBFT = ../lib/libft/libft.a

SRCS_CB = client_bonus.c 
SRCS_SB = data_process.c \
		  server_bonus_utils.c \
		  server_bonus.c

OBJS_CB = ${SRCS_CB:.c=.o}
OBJS_SB = ${SRCS_SB:.c=.o}

bonus: $(NAME_CB) $(NAME_SB)

$(NAME_CB): $(OBJS_CB) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_CB) -o $@
$(NAME_SB): $(OBJS_SB) $(LIBFT)
	$(CC) $(CFLAGS) -L $(LIBFT_PATH) -lft $(OBJS_SB) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_PATH) -c $< -o $@
	
$(LIBFT):
	make -C $(LIBFT_PATH) all
	make -C $(LIBFT_PATH) bonus

clean:
	make -C $(LIBFT_PATH) fclean
	rm -f $(OBJS_CB) $(OBJS_SB)

fclean:clean
	rm -f $(NAME_CB) $(NAME_SB)

re: fclean all

.PHONY: all bonus clean fclean re