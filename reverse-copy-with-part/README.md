# Reverse Copy By Part

## Main.c
- The source code for the probblem. 
- Compile it with `gcc main.c -o main`
- Run it with `./main <input_file_name> <number_of_parts> <part_to_be_reversed>`

## normal_read.c
- The source code for the normal read function.
- Compile it with `gcc normal_read.c -o normal_read`
- Run it with `./normal_read <input_file_name> <number_of_parts> <part_to_be_reversed>`

## Testing and Validation
- Use the reverse copy in the previous section to reverse the output of the normal read.
- Use the compare in the previous section to compare the output of the reverse copy with the output of previous step.
  - `./reverse_by_part random.txt 4 2` -> output.txt
  - `./normal_read random.txt 4 2` -> output_normal.txt
  - `./reverse output.txt  output_reversed.txt` -> output_reversed.txt
  - `./compare output_normal.txt output_reversed.txt` -> Should print "Files are equal"
 
## Written by:
Siddik Ayyappa

## Course and Assignment
Operating Systems and Networks, Assignment 1, Monsoon 2021