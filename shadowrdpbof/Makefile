BOFNAME := shadowrdp
COMINCLUDE := -I ./include
LIBINCLUDE := -l user32
CC_x64 := x86_64-w64-mingw32-gcc
#CC_x86 := i686-w64-mingw32-gcc
#CC := x86_64-w64-mingw32-clang

all:
	$(CC_x64) -o $(BOFNAME).x64.bof.o $(COMINCLUDE) -Os -fpermissive -c entry.c -DBOF 
	$(CC_x64) -o $(BOFNAME).x64.brc4.o $(COMINCLUDE) -Os -fpermissive -c entry.c -DBRC4
	mv $(BOFNAME)*.o ./dist/