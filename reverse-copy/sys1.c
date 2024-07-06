#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 70000
#define PROGRESS_BAR_WIDTH 50

void reverse(char* buffer, int size) {
    char temp;
    for (int i = 0; i < size / 2; i++) {
        temp = buffer[i];
        buffer[i] = buffer[size - i - 1];
        buffer[size - i - 1] = temp;
    }
}

int main(int argc, char *argv[]) {
    if(argc != 3){
        printf("%d Usage: <input_file> <output file>\n", argc);
        return 1;
    }
    // Open input file
    char buf[BUFFER_SIZE];
    char *input_file = malloc(100);
    int input_fd, output_fd;
    int temp;
    
    if ((input_fd = open(argv[1], O_RDONLY)) < 0) {
        perror("Error opening input file");
        return 1;
    }


    if ((output_fd = open(argv[2], O_WRONLY | O_CREAT , 0644)) < 0 ) {
        perror("Error opening output file");
        close(input_fd);
        return 1;
    }

    struct stat file_stat;
    if (fstat(input_fd, &file_stat) == -1) {
        perror("Error getting file size");
        return 1;
    }
    off_t file_size = file_stat.st_size;
    off_t progress = 0;
    
    // Read input file from end to fill buffer
    size_t bytes_read;
    if(file_size < BUFFER_SIZE){
        lseek(input_fd, 0, SEEK_SET);
        bytes_read = file_size;
    }else{
        lseek(input_fd, -BUFFER_SIZE, SEEK_END);
        bytes_read = BUFFER_SIZE;
    }
    char progress_bar[PROGRESS_BAR_WIDTH];
    for(int i = 0; i < PROGRESS_BAR_WIDTH; i++){
        progress_bar[i] = ' ';
    }
    /*
    \e[?25l -> To Hide the cursor
    \r -> To move the cursor to the beginning of the line
    */
    while((temp=read(input_fd, buf, bytes_read)) > 0){
        reverse(buf, bytes_read);
        write(output_fd, buf, bytes_read);
        progress += bytes_read;
        progress_bar[(int)((float)progress / file_size * PROGRESS_BAR_WIDTH)] = '#';
        printf("\e[?25l Progress:[%s] %.3f %%\r", progress_bar, (float)progress / file_size * 100);
        if (file_size - progress < BUFFER_SIZE) {
            bytes_read = file_size - progress;
            lseek(input_fd, 0, SEEK_SET);
            continue;
        }
        lseek(input_fd, -2*bytes_read, SEEK_CUR);
    }
    printf("\nFile size of %s: %lld\n", argv[1], file_size);
    printf("Bytes read: %lld\n", progress);
    printf("\n");
    
    close(input_fd);
    close(output_fd);
    return 0;
}
