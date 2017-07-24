COMPIL = gcc
FLAG = -Wall
LINK = nrio.c nralloc.c nrarith.c
NAME = tp1

all: $(NAME)

$(NAME): $(NAME).c
	$(COMPIL) -o $(NAME) $(NAME).c $(LINK) $(FLAG)

clean:
	rm $(NAME) *.o
