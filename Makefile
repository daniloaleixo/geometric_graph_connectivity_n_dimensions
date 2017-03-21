CC = gcc
CFLAGS = -Wall -ansi 
LFLAGS = -lm
OUT_C = ep2.C
OUT_S = ep2.S
IN = EP2.c


all: $(OUT_C) $(OUT_S)

Cube: $(OUT_C)

Sphere: $(OUT_S)

clean: 
	rm -f EP2.o $(OUT_C) $(OUT_S) Point.S.o Point.C.o StringOps.o 

$(OUT_S): EP2.o Point.S.o StringOps.o
	$(CC) EP2.o Point.S.o StringOps.o $(CFLAGS) $(LFLAGS) -o $(OUT_S)

$(OUT_C): EP2.o Point.C.o StringOps.o
	$(CC) EP2.o Point.C.o StringOps.o $(CFLAGS) $(LFLAGS) -o $(OUT_C)

ep1.o: $(IN) 
	$(CC) $(IN) $(CFLAGS) -c -o EP2.o

Point.C.o: Point.C.c
	$(CC) Point.C.c $(CFLAGS) -c -o Point.C.o

PointSphere.o: Point.S.c
	$(CC) Point.S.c $(CFLAGS) -c -o Point.S.o

StringOps.o: StringOps.c
	$(CC) StringOps.c $(CFLAGS) -c -o StringOps.o
