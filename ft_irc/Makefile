CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
SRCS =  main.cpp $(wildcard srcs/*.cpp) $(wildcard srcs/Commands/*.cpp)
OBJS = $(SRCS:%.cpp=obj/%.o)
TARGET = ircserv

$(TARGET):	$(OBJS)
	$(CC)	$(CFLAGS)	-o	$(TARGET)	$(OBJS)

all: $(TARGET)


obj/%.o: %.cpp
	@mkdir -p obj
	@mkdir -p obj/srcs
	@mkdir -p obj/srcs/Commands
	$(CC)	$(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
	rm -rf obj

fclean: clean
	rm -f $(TARGET)

re: fclean all

debug: CFLAGS += -g3 -DDEBUG
debug: clean $(TARGET)

.PHONY: all clean fclean re