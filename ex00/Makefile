SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj

NAME = btc
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98 -ggdb3
SRC_FILES =\
	main.cpp\
	BitcoinExchange.cpp\

INC_FILES =\
	BitcoinExchange.hpp\

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_FILES = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))
INCS = $(addprefix $(INCLUDE_DIR)/, $(INC_FILES))

OBJS = $(SRCS:.cpp=.o)
RM = rm -rf

all: $(NAME)

$(NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_FILES)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCS) | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCLUDE_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	$(RM) $(OBJ_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re