NAME			= 	ft_ls

NAMECOLOR 		= 	\x1b[31m
COLOR 			= 	\x1b[36m
COLORFILE		= 	\x1b[35m
COLOROK 		= 	\x1b[32m
COLORRESET 		= 	\x1b[0m

SRCSDIR 		= 	srcs
SRCSDIR1		= 	print
SRCSDIR2		= 	init
SRCSDIR3		= 	core
SRCSDIR4		= 	display

LIBFTDIR 		= 	libft
OBJSDIR 		= 	objects

INCLUDES 		= 	includes
HEADER	 		= 	ft_ls.h

CFLAGS 			= 	-g -Wall -Werror -Wextra
LDFLAGS 		= 	-L$(LIBFTDIR) -lft

CC 				= 	gcc $(CFLAGS)

LIB 			= 	libft.a


SRCINIT			=	ft_arg.c ft_arg2.c ft_init.c ft_init2.c
SRCPRINT		=	ft_color.c ft_print.c ft_print2.c ft_print3.c ft_space.c
SRCCORE			=	ft_ls.c main.c ft_free.c ft_err.c ft_err2.c ft_sort.c ft_merge.c
SRCDISPLAY		=	ft_display.c ft_display2.c ft_display_init.c ft_display_rec.c\
					ft_display_rec2.c ft_display_init_rec.c

SRCSPRINT 		=	$(addprefix $(SRCSDIR1)/, $(SRCPRINT))
SRCSINIT		= 	$(addprefix $(SRCSDIR2)/, $(SRCINIT))
SRCSCORE 		=	$(addprefix $(SRCSDIR3)/, $(SRCCORE))
SRCSDISPLAY 	=	$(addprefix $(SRCSDIR4)/, $(SRCDISPLAY))

SRC 			=	$(SRCSINIT) $(SRCSPRINT) $(SRCSCORE) $(SRCSDISPLAY)
OBJ 			= 	$(SRC:%.c=%.o)

SRCS 			= 	$(addprefix $(SRCSDIR)/, $(SRC))
OBJS 			= 	$(addprefix $(OBJSDIR)/, $(OBJ))
HEADERS			= 	$(addprefix $(INCLUDES)/, $(HEADER))

all: $(NAME)

$(NAME): $(LIBFTDIR)/$(LIB) $(OBJSDIR) $(OBJS)
	@$(CC) $(LDFLAGS) $(OBJS) -o $(NAME)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Compiling: $(COLORFILE)$<...$(COLORRESET)"
	@$(CC) -c -o $@ $< -I$(INCLUDES)

$(OBJSDIR):
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Create objects dir...$(COLORRESET)";
	@mkdir -p $(OBJSDIR)/$(SRCSDIR1);
	@mkdir -p $(OBJSDIR)/$(SRCSDIR2);
	@mkdir -p $(OBJSDIR)/$(SRCSDIR3);
	@mkdir -p $(OBJSDIR)/$(SRCSDIR4);

$(LIBFTDIR)/$(LIB):
	@make -C $(LIBFTDIR)/

clean:
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Removing objects dir...$(COLORRESET)"
	@/bin/rm -f $(OBJS)
	@make clean -C $(LIBFTDIR)/

fclean: clean
	@echo "$(NAMECOLOR)$(NAME): $(COLOR)Deleting...$(COLORRESET)"
	@/bin/rm -f $(NAME)
	@/bin/rm -rf $(NAME).dSYM
	@make fclean -C $(LIBFTDIR)/

re: fclean all

norme: forbidden
	@echo "$(NAMECOLOR)Libft: $(COLOR)Norme check... $(COLORRESET)"
	@norminette -R $(LIBFTDIR)/srcs | grep -i error || echo "$(COLOROK)Libft OK$(COLORRESET)"
	@norminette -R $(LIBFTDIR)/includes | grep -i error || echo "$(COLOROK)Libft header OK$(COLORRESET)"
	@echo "$(NAMECOLOR)Source files: $(COLOR)Norme check... $(COLORRESET)"
	@norminette -R $(SRCSDIR) | grep -i error || echo "$(COLOROK)Source file OK$(COLORRESET)"
	@echo "$(NAMECOLOR)Header files: $(COLOR)Norme check... $(COLORRESET)"
	@norminette -R $(INCLUDES) | grep -i error || echo "$(COLOROK)Header file OK$(COLORRESET)"

forbidden:
	@grep -Hn "printf" $(SRCS) || echo "$(COLOROK)no printf function OK$(COLORRESET)"

.PHONY: all, clean, fclean, re, norme, forbidden

.SUFFIXES: .c .o .h
