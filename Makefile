a.out: with.o main.o
	$(CC) -o $@ $^
clean:
	rm -f a.out *.o
