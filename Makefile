CC=gcc



pacman: pacman.c
	$(CC) -o  pacman pacman.c GRAPH.c

pacmanDebug: pacmanDebug.c
	$(CC) -o pacmanDebug pacmanDebug.c GRAPH.c

clean:
	rm -f pacman pacmanDebug 
