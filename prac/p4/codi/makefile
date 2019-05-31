MAIN_C    = exemple.c
MAIN_O    = exemple.o

TARGET_C  = malloc_best_first_fit.c
TARGET_SO = malloc.so

EXEC      = main

all: $(EXEC)

$(EXEC): $(MAIN_O)
	gcc -o $(EXEC) $(MAIN_O)

$(MAIN_O): $(MAIN_C)
	gcc -c $(MAIN_C)
	gcc -O -shared -fPIC $(TARGET_C) -o $(TARGET_SO)
     
clean:
	rm $(MAIN_O) $(TARGET_SO) $(EXEC)