# COLORS
RESET	= "\033[0m"
RED 	= "\033[31m"
GREEN	= "\033[32m"

# MAIN
CXX = c++
NAME = btc
RM = rm -f


SRCDIR = src
OBJDIR = obj

# FLAGS
CXXFLAGS = -Wall -Wextra -Werror -std=c++98

# SOURCES
SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')

		
OBJS = $(SRCS:.cpp=.o)

# RULES
all: $(NAME)

$(NAME): $(OBJS)
	@echo $(GREEN)"...linking $(NAME)..."$(RESET)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	

%.o: %.cpp
	@echo $(GREEN)"...compiling $<..."$(RESET)
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo $(RED)"...cleaning $(NAME) object files..."$(RESET)
	$(RM) $(OBJS)

fclean: clean
	@echo $(RED)"...cleaning $(NAME)..."$(RESET)
	$(RM) $(NAME)

compile:
	./$(NAME)

exec: all compile fclean

leaks:
	valgrind --leak-check=full ./$(NAME)


valgrind: all leaks fclean
	
re: fclean all