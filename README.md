# C

Code created while reading [The C programming language](https://en.wikipedia.org/wiki/The_C_Programming_Language) by Brian KERNIGHAN and Dennis RITCHIE, as well as code created while attending a training about UNIX/Linux system programming.

## References

* [Advanced Linux Programming](http://advancedlinuxprogramming.com/alp-folder/)
* [RedHat documentation](https://access.redhat.com/documentation/en-US/Red_Hat_Enterprise_Linux/7/html/System_Administrators_Guide/index.html)

## Useful commands

diplay binary content of object file: `od -x compil.o` || `objdump -t compil.o`

create static lib: `gcc -c fic1.c fic2.c && ar rcs libfic.a fic1.o fic2.o`  
print static library content: `ar -t libfic.a` || `nm -s libfic.a`

create shared lib: `gcc -fPIC -shared -Wl,-soname,libfic.so.1 -o lib/libfic.so.1.0 fic01.c fic02.c`  
compile binary using lib : `gcc -L./lib ficmain.c -o ficmain -lfic`  
list the shared libs used by a binary: `ldd̀`  
list the functions of a shared lib: `objdump -T lib.so`  
updating shared libs (after updating */etc/ld.so.conf.d/*): `ldconfig`

trace a library: `ltrace`

get functions safe to call from signal handlers: `man 7 signal`
