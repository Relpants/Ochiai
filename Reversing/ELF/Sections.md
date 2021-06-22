Sections

# Sections

## ***.plt***
## ***.got***
## ***.got.plt***

## ***.data***

- The default values of initialized variables are stored in this section which is marked as writeable since the values of variables may change at runtime

## ***.rodata***

- stands for read only data. is dedicated to storing constant values. IS NOT WRITEABLE

## ***.bss***

- reserves space for uninitialized variables. stands for block started by symbol. This section dosent occupy any bytes in the binary as it exists on disk. it simply a directive to allocate a properly sized block of memory for uninitialized variables when setting up an execution enviornment for the binary. Typically variables that live in .bss are zero initialized, and the section is marked as writeable 

## ***.init***

- Contains executable code that performs initialzation tasks and needs to run before any other code in the binary is executed. Functions like a constructor

## ***.fini***

- is analogous to the .init section, except that it runs after the main program complets, essentially functioning as a destructor

## ***.text***

- Where the main code of the program resides, **will frequently be the main focus of the reverse engineering efforts**. contains user-defined code. Contains a number of standard functions that perform initialization and finalization tasks, such as _start, register_tm_clones, and frame_dummy.
	- **_start**
		- True entry point of the binary, will contain an instruction that moves the address of main into rdi register, which is the register used to pass parameters for function calls on the x64 platform. It then calls a function called _libc_start_main. which resides in the .plt section. this will ultimately finally call the address of main to start execution of user code.
	- **register_tm_clones**
	- **frame_dummy**