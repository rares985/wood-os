# wood-os
Implementation of an operating system for i386 systems

Resources used:
 - https://www.cs.bham.ac.uk/~exr/lectures/opsys/10_11/lectures/os-dev.pdf
 - https://github.com/cfenollosa/os-tutorial
 - https://littleosbook.github.io/book.pdf
 - https://web.archive.org/web/20160326062945/http://jamesmolloy.co.uk/tutorial_html/1.-Environment%20setup.html
 - https://wiki.osdev.org/Main_Page
 - https://github.com/tuhdo/os01/files/4711780/Operating_Systems_From_0_to_1.pdf
 - http://www.osdever.net/
 
 How everything is set up:
 - Boot sector, disk loading, GDT, switch to 32-bit mode, kernel entry and common interrupt handlers are written in assembly
 - Everything else is written in C
