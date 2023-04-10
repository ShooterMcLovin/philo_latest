
BK		:= \033[30;1m
R		:= \033[31;1m
G		:= \033[32;1m
Y		:= \033[33;1m
B		:= \033[34;1m
M		:= \033[35;1m
C		:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME = philo
CC = gcc
CFLAGS = -g -Wall -Werror -Wextra -pthread -fsanitize=thread -I -I./$(INCDIR)

SRCS = 	src/check.c src/init.c src/main.c src/philo.c src/utils.c

SRCDIR = src/
OBJDIR = bin/
INCDIR = include/


INC = include/philo.h

OBJS = $(patsubst $(SRCDIR)%.c,$(OBJDIR)%.o,$(SRCS))

$(NAME): lib $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
	@echo "$(Y)SPAGHETTI BOWL FULL$(RESET)"

lib: 
	@mkdir -p bin
	
$(OBJS): $(OBJDIR)%.o : $(SRCDIR)%.c $(INC) | $(OBJDIR)
	@echo "$(G)Compiling: $(B)$<$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)
	
clean:
	@rm -rf $(OBJS)
	@rm -rf bin
	@echo "$(R)Cleaning...$(RESET)"
	
fclean: clean
	@rm -rf $(NAME)
	@echo "$(R)FCleaning...$(RESET)"

re: fclean all
	
