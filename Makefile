     CC	= cc
     RM	= rm -Rf

CFLAGS	= -O3 -Wall -funroll-loops -I. -DDEBUG
LDFLAGS	= 

   OBJS	= token.o tokentree.o tokentype.o dump.o data.o serialization.o debug.o main.o
   AOUT	= darkjson

all: $(OBJS)
	$(CC) -o $(AOUT) $(OBJS) $(LDFLAGS)

clean:
	$(RM) $(OBJS) $(AOUT)
