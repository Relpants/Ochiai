Executable Header

# Executable Header

- A structured series of bytes telling you its an ELF file, what kind of ELF file it is and where in the file to find all the other contents
- To find out what the format of the executable header is you can look up its type definition in ```/usr/include/elf.h```

- **Can view the contents using ```readelf -h <binary>```**

# Contents
- ## ***e_ident array*** - unsigned char[16]
	- 4 byte magic value - consists of 0x7f, followed by ascii characters ELF
		- EI_PAD - indexes 9 - 15
			- set to zero, just padding
		- EI_CLASS 
			- Denotes whether the ELF is 32-bit or 64-bit architecture
				- 1 -> 32bit
				- 2 -> 64bit
		- EI_DATA
			- indicates the endiannes of the binary
				- 1 -> little endian
				- 2 -> big endian
		- EI_VERSION
			- indicates the version of the ELF specification, will always be set to 1
		- EI_OSABI
			- if set to nonzero, means that some ABI or OS specific extensions are used in the ELF file, which can signal the precense of nonstandard sections. Default value of zero indicates that the binary targets the UNIX System V ABI.
		- EI_ABIVERSION
			- denotes the specific version of the ABI indicated in the EI_OSABI byte the the binary targets. Usually set to zero, when default EI_OSABI is used
			
- ## ***e_type*** 
	- specifies the type of the binary, will be denoted as the **Type** in readelf

- ## ***e_machine***
	- denotes the architecture that the binary is intended to run on. Example - `EM_X86_64 -> 64-bit x86 binary`

- ## ***e_version***
	- indicates the version of the ELF specification that was used when creating the binary

- ## ***e_entry***
	- denotes the **entry point** of the binary, the virtual address at which execution should start. Where the interpreter will transfer control after it finishes loading the binary. **Useful starting point for recursive disassembly**

- ## ***e_phoff***
	- indicates the file offset to the beginning of the program header table. This is because the program header table dosent need to be located at any particular offest in the binary file

- ## ***e_shoff***
	- indicates the file offset to the beginning of the section header table. As stated above the section header table also does not need to be located at any particular offset in the binary file

- ## ***e_flags***
	- provides room for flags specific to the architecture for which the binary is compiled. For x86 binaries, e_flags is typically set to zero and not of interest 

- ## ***e_ehsize***
	- specifies the size of the executable header, in bytes. For 64-bit x86 binaries the exectuable header is **always** 64 bytes. while 52 bytes for 32-bit x86 binaries

- ## ***e_phentsize and e_phnum***
	- stores the information of the size of the individual program header in the table and number of headers in each table

- ## ***e_shentsize and e_shnum***
	- stores the information of the size of the section header in the program header table and number of headers in each table


- ## ***e_shstrndx***
	- contains the index ( in the section header table ) of the header associated with a special string table, section called .shstrtab. This is a dedicated section that contains a table of null-terminated ACII strings, which store the names of all the sections in the binary. used by tools such as readelf to correctly show the names of sections.