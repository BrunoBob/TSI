COMPIL = gcc
FLAG = -lm
LINK = nrio.c nralloc.c nrarith.c
NAME = tp3

all: $(NAME)

$(NAME): $(NAME).c $(NAME).h
	$(COMPIL) -o $(NAME) $(NAME).c $(LINK) $(FLAG)

clean:
	rm $(NAME) -f
