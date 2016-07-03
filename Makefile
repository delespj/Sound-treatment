NAME		=	visualizer

CXX		?=	g++

INCLUDES	+=	-I ./includes

LINKER		=	-lSDL2

CPPFLAGS	=	$(INCLUDES) -Wall -Werror -Wextra

RM		=	rm -f

SRCS		=	srcs/main.cpp \
			srcs/visualizer.cpp

OBJS		=	$(SRCS:.cpp=.o)

all:		$(OBJS)
		$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS) $(LINKER)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
