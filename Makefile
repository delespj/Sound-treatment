NAME		=	visualizer

CXX		?=	g++

INCLUDES	+=	-I ./includes -I ./fmod_include/

LINKER		=	-lSDL2 ./libfmodex64-4.44.32.so

CPPFLAGS	=	$(INCLUDES) -Wall -Wextra

RM		=	rm -f

SRCS		=	srcs/main.cpp \
			srcs/visualizer.cpp \
			srcs/SoundSystem.cpp

OBJS		=	$(SRCS:.cpp=.o)

all:		$(OBJS)
		$(CXX) $(CPPFLAGS) -o $(NAME) $(OBJS) $(LINKER)

clean:
		$(RM) $(OBJS)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
