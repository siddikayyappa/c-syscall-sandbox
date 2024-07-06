#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<string.h>

#pragma GCC poison printf
int main(int argc, char *argv[]){
    struct stat buf;
    int temp;
    if((temp = stat(argv[1], &buf)) == -1){
        perror("stat");
        exit(1);
    }
    mode_t mode = buf.st_mode;
    char buffer[50];
    int ar[7] = {S_IFBLK, S_IFCHR, S_IFDIR, S_IFIFO, S_IFLNK, S_IFREG, S_IFSOCK};
    char *str[7] = {"Block Device", "Character Device", "Directory", "FIFO", "Symbolic Link", "Regular File", "Socket"};
    memset(buffer, 0, sizeof(buffer));
    for(int i = 0; i < 7; i++){
        if((mode & S_IFMT) == ar[i]){
            sprintf(buffer, "File Type: %s\n\n\0", str[i]);
            write(1, buffer, sizeof(buffer));
            break;
        }
    }
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "User Can Read: %s\n", (mode & S_IRUSR) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "User Can Write: %s\n", (mode & S_IWUSR) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "User Can Execute: %s\n\n\0", (mode & S_IXUSR) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Group Can Read: %s\n\0", (mode & S_IRGRP) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Group Can Write: %s\n\0", (mode & S_IWGRP) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Group Can Execute: %s\n\n\0", (mode & S_IXGRP) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Others Can Read: %s\n\0", (mode & S_IROTH) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Others Can Write: %s\n\0", (mode & S_IWOTH) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Others Can Execute: %s\n\0", (mode & S_IXOTH) ? "Yes" : "No");
    write(1, buffer, sizeof(buffer));


    return 0;
}