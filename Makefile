     CC	= cc
     RM	= rm -Rf

#CFLAGS	= -O3 -Wall -funroll-loops -I.
 CFLAGS	= -Wall -I.
LDFLAGS	= 

   OBJS	= token.o #debug.o #main.o
   AOUT	= darkjson

all: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(AOUT)
