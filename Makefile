NAME = ft_containers
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

COMPILER = clang++
FLAGS = -Wall -Werror -Wextra -MMD -std=c++98
INCLUDES = -I.

%.o : %.cpp
	$(COMPILER) $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	$(COMPILER) $(FLAGS) $(OBJS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)
	rm -f $(DEPS)

fclean:
	$(MAKE) clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

leak_sanitizer:
	$(MAKE) fclean
	$(COMPILER) -Wall -Werror -Wextra -std=c++98 -fsanitize=address -g3 $(SRCS) -o $(NAME)
	ASAN_OPTIONS=detect_leaks=1 ./${NAME} ${LEAK_TEST_CASE}

leak_valgrind:
	$(MAKE) re
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./${NAME}

.PHONY: all clean fclean re

-include $(DEPS)