Section Headers

# Section Headers

- A structured series of bytes telling you its an ELF file, what kind of ELF file it is and where in the file to find all the other contents
- To find out what the format of the executable header is you can look up its type definition in ```/usr/include/elf.h```

- **Can view the contents using ```readelf -h <binary>```**

# Contents
- ## ***e_ident array*** - unsigned char[16]
	- 4 byte magic value - consists of 0x7f, followed by ascii characters ELF
		- EI_PAD - indexes 9 - 15
		