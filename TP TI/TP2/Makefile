COMPIL = gcc
FLAG = 
LINK = nrio.c nralloc.c nrarith.c
NAME = tp2

all: $(NAME)

$(NAME): $(NAME).c $(NAME).h
	$(COMPIL) -o $(NAME) $(NAME).c $(LINK) $(FLAG)

clean:
	rm $(NAME) -f
