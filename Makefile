NAME = ft_containers

CC = clang++
CFLAGS = -Wall -Wextra -Werror -std=c++98 #-g3 -fsanitize=address

OBJS_DIR = ./objs

INC_DIR = ./includes

SRCS =	main.cpp

OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.cpp=.o)))

RM = rm -f

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJS_DIR) :
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o : %.cpp | $(OBJS_DIR)
	@$(CC) $(CFLAGS) -o $@ -I$(INC_DIR) -c $^

clean :
	@$(RM) -r $(OBJS_DIR)

fclean : clean
	@$(RM) $(NAME)

re : fclean all

.PHONY: all clean fclean re
