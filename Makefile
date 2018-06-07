CC=gcc



pacman: pacman.c
	$(CC) -o /bin/pacman pacman.c
	
clean:
	rm /bin/pacman
