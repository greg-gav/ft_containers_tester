NAME =	containers_test

CC = clang++

OBJ_PATH = ./obj
SRC_PATH = ./tests
SRC_FILES =	main.cpp pair_tests.cpp test_utils.cpp				\
			equal_compare_tests.cpp	enable_integral_tests.cpp	\
			vector_tests.cpp stack_tests.cpp 					\
			map_tests.cpp set_tests.cpp							\

OBJS = ${addprefix ${OBJ_PATH}/,${SRC_FILES:.cpp=.obj}}

CXXFLAGS = -Wall -Werror -Wextra -MMD -I${SRC_PATH} -I. -std=c++98 -pedantic

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

${OBJ_PATH}/%.obj : ${SRC_PATH}/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ 

${OBJ_PATH}/%.obj : %.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CXXFLAGS) -c $< -o $@ 

-include $(addprefix ${OBJ_PATH}/,${SRC_FILES:.cpp=.d})

clean:
	@rm -rf ${OBJ_PATH}

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
