CC=g++
CFLAGS=-Wall
FILES=./*.cpp

all: doom hexen zdoom

doom:
	$(CC) $(CFLAGS) $(FILES) -DDOOM -o doomconvert

hexen:
	$(CC) $(CFLAGS) $(FILES) -DHEXEN -o hexenconvert

zdoom:
	$(CC) $(CFLAGS) $(FILES) -DZDOOM -o zdoomconvert