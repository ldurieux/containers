SRCS-FT		= \
			  main-ft.cpp \

SRCS-STD	= \
			  main-std.cpp \

HEADERS		= \
			  . \

HEADERS := ${addprefix -I ,$(HEADERS)}

BUILDDIR	= .build
OBJS-FT		= $(SRCS-FT:%.cpp=$(BUILDDIR)/%.o)
DEPS-FT		= $(SRCS-FT:%.cpp=$(BUILDDIR)/%.d)
OBJS-STD	= $(SRCS-STD:%.cpp=$(BUILDDIR)/%.o)
DEPS-STD	= $(SRCS-STD:%.cpp=$(BUILDDIR)/%.d)

CXX			= c++ -std=c++98
CXXWFLGS	= -Wall -Wextra -Werror -g3 -fsanitize=address
CXXDBGFLGS	= -fsanitize=address -g3
DEPSFLAGS	= -MMD -MP
RM			= rm -Rf
MAKE		= make -C
MKDIR		= mkdir

all : test-ft test-std

test-ft : $(OBJS-FT)
		$(CXX) $(CXXWFLGS) $(DEPSFLAGS) -o test-ft $(OBJS-FT)

test-std : $(OBJS-STD)
		$(CXX) $(CXXWFLGS) $(DEPSFLAGS) -o test-std $(OBJS-STD)

bonus : $(NAME)

clean :
		-$(RM) $(BUILDDIR)

fclean : clean
		-$(RM) test-ft test-std

re : fclean
		$(MAKE) ./

-include $(DEPS-FT)
-include $(DEPS-STD)

$(BUILDDIR)/%.o : %.cpp Makefile $(LIB_PATHS)
		@mkdir -p $(@D)
		$(CXX) $(CXXWFLGS) $(DEPSFLAGS) $(CCDEFSFLGS) $(HEADERS) $(LIB_HEADERS) -c $< -o $@

.PHONY: all clean fclean re bonus
