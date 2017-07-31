CC=gcc
CFLAGS=-I.

hellomake: test.o VectorRotation.o Utilities.o Quaternion.o 
	$(CC) -o VectorRotationTest test.o VectorRotation.o Utilities.o Quaternion.o -I.