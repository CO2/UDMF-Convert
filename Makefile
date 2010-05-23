CC=g++
CFLAGS=-Wall
SHARED=main.cpp sharedmap.o convertshared.o udmf.o

all: doom hexen zdoom strife

doom: doommap.o convertdoom.o sharedmap.o convertshared.o udmf.o
	$(CC) $(CFLAGS) $(SHARED) doommap.o convertdoom.o -DDOOM -o doomconvert

hexen: hexenmap.o converthexen.o sharedmap.o convertshared.o udmf.o
	$(CC) $(CFLAGS) $(SHARED) hexenmap.o converthexen.o -DHEXEN -o hexenconvert

zdoom: zdoommap.o convertzdoom.o sharedmap.o convertshared.o udmf.o
	$(CC) $(CFLAGS) $(SHARED) zdoommap.o convertzdoom.o -DZDOOM -o zdoomconvert

strife: strifemap.o convertstrife.o sharedmap.o convertshared.o udmf.o
	$(CC) $(CFLAGS) $(SHARED) strifemap.o convertstrife.o -DSTRIFE -o strifeconvert

udmf.o:
	$(CC) $(CFLAGS) -c udmf.cpp -o udmf.o

sharedmap.o:
	$(CC) $(CFLAGS) -c sharedmap.cpp -o sharedmap.o

convertshared.o:
	$(CC) $(CFLAGS) -c convertshared.cpp -o convertshared.o

doommap.o:
	$(CC) $(CFLAGS) -c doommap.cpp -o doommap.o

convertdoom.o:
	$(CC) $(CFLAGS) -c convertdoom.cpp -o convertdoom.o

hexenmap.o:
	$(CC) $(CFLAGS) -c hexenmap.cpp -o hexenmap.o

converthexen.o:
	$(CC) $(CFLAGS) -c converthexen.cpp -o converthexen.o

zdoommap.o:
	$(CC) $(CFLAGS) -c zdoommap.cpp -o zdoommap.o

convertzdoom.o:
	$(CC) $(CFLAGS) -c convertzdoom.cpp -o convertzdoom.o

strifemap.o:
	$(CC) $(CFLAGS) -c strifemap.cpp -o strifemap.o

convertstrife.o:
	$(CC) $(CFLAGS) -c convertstrife.cpp -o convertstrife.o
