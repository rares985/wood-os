# wood-os
[![Build Status](https://travis-ci.org/rares985/wood-os.svg?branch=main)](https://travis-ci.org/rares985/wood-os)

woodOS represents a basic operating system for i386 

At the moment it exists purely for educational purposes, but it might evolve.

## Documentation
All the resources presented below, as well as any other information / explanation of how this operating system works is available on the [wiki](https://github.com/rares985/wood-os/wiki) page of the repository.


## Useful resources
 - https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
 - https://github.com/cfenollosa/os-tutorial
 - https://littleosbook.github.io/book.pdf
 - https://web.archive.org/web/20160326062945/http://jamesmolloy.co.uk/tutorial_html/1.-Environment%20setup.html
 - https://wiki.osdev.org/Main_Page
 - https://github.com/tuhdo/os01/files/4711780/Operating_Systems_From_0_to_1.pdf
 - http://www.osdever.net/
 - http://reddit.com/r/osdev/
 - http://www.independent-software.com/category/osdev.html
 - https://www.cs.cmu.edu/~410-s07/
 - http://www.brokenthorn.com/Resources/OSDevIndex.html
 

 ## Environment
 Since the OS is for x86, you need a cross-compiler. See [here](https://github.com/cfenollosa/os-tutorial/tree/master/11-kernel-crosscompiler) for info on how to cross-compile gcc and ld
 ## Building
 First you should install the necessary dependencies: `sudo apt-get install nasm bochs qemu`
 For building the project, it is enough to issue the command `make` in the root directory of the project
 
 ## Debugging
 Debugging is possible either via Bochs internal debugger (usually in the Bootloader phase) or via GDB.
 For GDB, simply run `gdb` in the root directory.
 For Bochs, run `./bochs.sh`
 
 ## Running
 Running is possible either in QEMU (via `./qemu.sh`) or in Bochs (`./bochs.sh`)
 
## Contributors
At the moment, the project has no other contributors than me. If you want to take part, send me a message and I will add you to the contributors team.
