NAME 		= 	libft.a

NAMECOLOR 	= 	\x1b[31m
COLOR 		= 	\x1b[36m
COLOROK 	= 	\x1b[32m
COLORFILE	= 	\x1b[35m
COLORRESET 	= 	\x1b[0m

SRCSDIR 	= 	srcs
SRCSDIR1 	= 	lst
SRCSDIR2 	= 	mem
SRCSDIR3 	= 	tab
SRCSDIR4 	= 	str
SRCSDIR5 	= 	put
SRCSDIR6 	= 	check
SRCSDIR7 	= 	stdlib

OBJSDIR 	= 	objects

INCLUDES 	= 	includes

CFLAGS 		= 	-Wall -Werror -Wextra
CC 			= 	gcc $(CFLAGS)
HEADER		=	libft.h
HEADERS		=	$(addprefix $(INCLUDES)/, $(HEADER))
SRCLST		=	ft_lstnew.c ft_lstadd.c ft_lstdel.c ft_lstiter.c ft_lstmap.c ft_lstdelone.c
SRCMEM		=	ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
				ft_memdel.c ft_memalloc.c
SRCTAB		=	ft_param_to_tab.c ft_show_tab.c
SRCSTR		=	ft_strdup.c ft_strcpy.c ft_strncpy.c ft_strcat.c ft_strncat.c ft_strlcat.c ft_strchr.c \
				ft_strrchr.c ft_strlen.c ft_sstrlen.c ft_strstr.c ft_strnstr.c ft_strcmp.c ft_strncmp.c \
				ft_strdel.c ft_strnew.c ft_strjoin.c ft_strtrim.c ft_strnequ.c ft_strequ.c \
				ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strsub.c \
				ft_split_whitespaces.c ft_strjoinfree.c ft_strsplit.c ft_strupcase.c ft_strlowcase.c \
				ft_toupper.c ft_tolower.c

SRCPUT		=	ft_putchar_fd.c ft_putstr_fd.c ft_putnbr.c ft_putnbr_fd.c ft_putchar.c \
				ft_putendl.c ft_putendl_fd.c ft_putstr.c
SRCCHECK	=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c  \
				ft_isspace.c ft_isnegative.c
SRCSTDLIB	=	ft_atoi.c ft_itoa.c

SRCSLST		= 	$(addprefix $(SRCSDIR1)/, $(SRCLST))
SRCSMEM		= 	$(addprefix $(SRCSDIR2)/, $(SRCMEM))
SRCSTAB		= 	$(addprefix $(SRCSDIR3)/, $(SRCTAB))
SRCSSTR		= 	$(addprefix $(SRCSDIR4)/, $(SRCSTR))
SRCSPUT		= 	$(addprefix $(SRCSDIR5)/, $(SRCPUT))
SRCSCHECK	= 	$(addprefix $(SRCSDIR6)/, $(SRCCHECK))
SRCSSTDLIB	= 	$(addprefix $(SRCSDIR7)/, $(SRCSTDLIB))

SRC 		=	$(SRCSLST) $(SRCSMEM) $(SRCSTAB) $(SRCSSTR) $(SRCSPUT) \
				$(SRCSCHECK) $(SRCSSTDLIB)
OBJ 		= 	$(SRC:%.c=%.o)

SRCS 		= 	$(addprefix $(SRCSDIR)/, $(SRC))
OBJS 		= 	$(addprefix $(OBJSDIR)/, $(OBJ))

all: $(NAME)

$(NAME): $(OBJSDIR) $(OBJS)
	@ar rcs $(NAME) $(OBJS)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c $(HEADERS)
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Compiling: $(COLORFILE)$<...$(COLORRESET)"
	@$(CC) -c -o $@ $< -I$(INCLUDES)

$(OBJSDIR):
	@if [ ! -d "$(OBJSDIR)/" ]; then \
		echo "$(NAMECOLOR)$(NAME): $(COLOR)Create objects dir...$(COLORRESET)"; \
		mkdir -p $(OBJSDIR)/$(SRCSDIR1); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR2); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR3); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR4); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR5); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR6); \
		mkdir -p $(OBJSDIR)/$(SRCSDIR7); \
	fi

clean:
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Removing objects dir...$(COLORRESET)";
	@/bin/rm -f $(OBJS);

fclean: clean
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Deleting...$(COLORRESET)"
	@/bin/rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re

.SUFFIXES: .c .o