NAME			=	ircserv

HPP				=	./hpp/
BIN				=	./src/bin

RESET			=	\033[0m
GREEN			=	\033[32m
YELLOW			=	\033[33m
BLUE			=	\033[34m
RED				=	\033[31m

SRCS			=	$(shell find src -type f -name "*.cpp")
INCS			=	$(shell find hpp -type f -name "*.hpp")
OBJS			=	$(SRCS:src/%.cpp=src/bin/%.o)
HOBJS			=	$(INCS:hpp/%.hpp)

CC				=	@c++
RM				=	@rm -rf
CPPFLAGS		=	-Wall -Wextra -Werror -std=c++98

all:			$(NAME)

$(BIN):
	@mkdir $(BIN)

$(NAME):	$(BIN) $(OBJS) $(HOBJS)
			@$(CC) $(CPPFLAGS) $(OBJS) -o $(NAME)
			@echo "$(GREEN)Compilation Finished! $(RESET)"

clean:
			@echo "$(RED)Deleting...$(RESET)"
			@$(RM) $(OBJS) $(HOBJS)
			@$(RM) $(BIN)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean $(NAME)

$(BIN)%.o: src/%.cpp
	@mkdir -p $(shell dirname $@)
	@$(CC) $(CPPFLAGS) -c $< -o $@ -I$(HPP)

norm:
				norminette *.[ch]

.PHONY:			all clean fclean re bonus
