#include<unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>

#define PROGRESS_BAR_WIDTH 50
#define MAX_BUFFER_SIZE 16384


int main(int argc, char* argv[]){
    if(argc != 4){
        printf("Usage: <input_file> <no_of_parts>  <part_to_be_reversed>\n");
        return 1;
    }
    char* input_file = argv[1];
    int no_of_parts = argv[2][0] - '0';
    int part_to_be_reversed = argv[3][0] -  '0';
    int input_fd, output_fd;
    if((input_fd = open(input_file, O_RDONLY)) == -1){
        perror("Error Opening Input File");
        return 1;
    }
    char* buffer = (char*)malloc(MAX_BUFFER_SIZE);
    if((output_fd = open("output_normal.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666)) == -1){
        perror("Error Opening Output File");
        return 1;
    }
    int file_size = lseek(input_fd, 0, SEEK_END);
    int part_size = file_size / no_of_parts;
    int start = (part_to_be_reversed -1) * part_size;
    int end= start + part_size;
    ssize_t bytes_read = MAX_BUFFER_SIZE;
    lseek(input_fd, start, SEEK_SET);
    if(part_size < MAX_BUFFER_SIZE){
        bytes_read = part_size;
    }

    char progress_bar[PROGRESS_BAR_WIDTH + 1];
    for(int i = 0; i < PROGRESS_BAR_WIDTH; i++){
        progress_bar[i] = ' ';
    }
    progress_bar[PROGRESS_BAR_WIDTH] = '\0';
    off_t progress = 0;

    while((bytes_read = read(input_fd, buffer, bytes_read)) > 0){
        write(output_fd, buffer, bytes_read);
        progress += bytes_read;
        progress_bar[(int)((float)progress / part_size * PROGRESS_BAR_WIDTH)] = '#';
        printf("\e[?25l Progress:[%s] %.3f %%\r", progress_bar, (float)progress / part_size * 100);
        if(part_size - progress < MAX_BUFFER_SIZE){
            bytes_read = part_size - progress;
            continue;
        }
    }
    printf("\nBytes Read: %lld\n", progress);

    return 0;
}