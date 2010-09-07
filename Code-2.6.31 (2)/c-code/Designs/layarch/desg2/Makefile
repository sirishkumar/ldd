INCLUDE=.
LIBS=./libs
APP: ui.o viml.o gifhandler.o tifhandler.o jpghandler.o bmphandler.o config.o
	gcc -l($LIBS)-I($INCLUDE) ui.o viml.o tifhandler.o jpghandler.o bmphandler.o config.o gifhandler.o -o APP
	echo "APP Build Complete"
ui.o:ui.c
	gcc -c ui.c
	echo "ui.c Compiled"
viml.o:viml.c
	gcc -c viml.c
	echo "viml.c Compiled"
tifhandler.o: tifhandler.c
	gcc -c tifhandler.c
	echo "tifhandler.c Compiled"
gifhandler.o:gifhandler.c
	gcc -c gifhandler.c
	echo "gifhandler.c Compiled"
jpghandler.o:jpghandler.c
	gcc -c jpghandler.c
	echo "jpghandler.c Compiled"
config.o:config.c
	gcc -c config.c
bmphandler.o:bmphandler.c
	gcc -c bmphandler.c
clean:	
	rm -rf *.o

INSTALL:
	cp ./APP /usr/bin
