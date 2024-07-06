#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

# define BUFFER_SIZE 50000

int main(int argc, char* argv[]){
    if(argc != 3){
        printf("%d Usage: <input_file> <output file>\n", argc);
        return 1;
    }
    int file_1, file_2;
    if ((file_1 = open(argv[1], O_RDONLY)) < 0) {
        perror("Error opening input file");
        return 1;
    }
    if((file_2 = open(argv[2], O_RDONLY)) < 0){
        perror("Error opening output file");
        close(file_1);
        return 1;
    }

    struct stat file_stat_1, file_stat_2;
    if (fstat(file_1, &file_stat_1) == -1) {
        perror("Error getting file size");
        return 1;
    }
    if (fstat(file_2, &file_stat_2) == -1) {
        perror("Error getting file size");
        return 1;
    }
    off_t file_size_1 = file_stat_1.st_size;
    off_t file_size_2 = file_stat_2.st_size;
    if(file_size_1 != file_size_2){
        printf("Files are not equal\n");
        return 1;
    }
    char progress_bar[51];
    for(int i = 0; i < 50; i++){
        progress_bar[i] = ' ';
    }
    off_t progress = 0;
    size_t bytes_read;
    // progress_bar[(int)((float)progress / file_size * PROGRESS_BAR_WIDTH)] = '=';
    // progress++;
    // printf("\r[%s] %d%%", progress_bar, (int)(progress * 100 / file_size_1));
    char buf_1[BUFFER_SIZE], buf_2[BUFFER_SIZE];
    while((bytes_read = read(file_1, buf_1, BUFFER_SIZE)) > 0){
        read(file_2, buf_2, BUFFER_SIZE);
        for(int i = 0; i < bytes_read; i++){
            if(buf_1[i] != buf_2[i]){
                printf("Files are not equal\n");
                return 1;
            }
        }
        progress += bytes_read;
        progress_bar[(int)((float)progress / file_size_1 * 50)] = '#';
        printf("\e\e[?25l  [%s] %d%%\r", progress_bar, (int)(progress * 100 / file_size_1));
    }

    printf("\nFiles are equal\n");
    printf("Bytes read and compared: %lld\n", progress);
    printf("File size: %lld\n", file_size_1);
    close(file_1);
    close(file_2);
}