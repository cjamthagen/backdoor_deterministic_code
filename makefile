CC=gcc
CFLAGS=-m32 -g

step2: step2.c def.h
	$(CC) $(CFLAGS) -o $@ $<

step1: step1.c def.h
	$(CC) $(CFLAGS) -o $@ $<

assemblybackdoor: assemblybackdoor.c
	$(CC) $(CFLAGS) -o $@ $<

dump:
	objdump -d -mi386 -Mintel step2 

clean:
	rm step1 step2 assemblybackdoor
