# Reverse-Copy

## Sys1.c 
- Source code for Copying a file in reverse order.
- Compile using `gcc sys1.c -o sys1`
- Run using `./sys1 <source> <destination>`


## Compare.C
- Source code for comparing two files.
- Compile using `gcc compare.c -o compare`
- Run using `./compare <file1> <file2>`

## Overall Testing
- Reverse a file. Store it in `output.txt`
- Reverse `output.txt` and store it in `output2.txt`
- Compare `output2.txt` and original file. They should be same.

## Creating A large file
- Run `dd if=/dev/zero of=largefile bs=1M count=1024` to create a 1GB file.
- This can be scaled. Change `count` to create a file of desired size.
- file_size = `bs * count`

### Written by:
Siddik Ayyappa