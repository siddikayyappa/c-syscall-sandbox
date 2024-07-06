# c-syscall-sandbox
Experimenting various functionalities in C language, with the help of system calls

## File Permissions
To obtain the file permissions, type of a file and print to stdout. 

## Reverse File
To reverse a file and write it to another file. Works on large files (approx 30 seconds for 10GB file). Can Adjust the buffer size to increase the speed. depending upon RAM specs.

## Reverse Part
To reverse a part of a file. Same as above, but with a start and end point.

## Notes
- printf and scanf have not been used. -- They have been poisoned with the help of **Pragma Directive**.
- CLI arguments are used for input.
- Error handling is implemented. 
- System Calls used -- open, read, write, close, lseek, stat
- Done and works on 
  1.  Apple clang version 15.0.0 (clang-1500.3.9.4)
  2. gcc version 14.1.0 (Homebrew GCC 14.1.0_1) 