nerd-test: with.o main.o
	$(CC) -o $@ $^
clean:
	rm -f nerd-test *.o
