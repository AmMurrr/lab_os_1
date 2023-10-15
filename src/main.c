#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>


int new_proccess() {
    pid_t pid = fork();
    return pid;
}


int main(int argc, char *argv[]){

    int fd1[2]; 
    int fd2[2]; 

    if( pipe(fd1) == -1 || pipe(fd2) == -1) {
         write(STDERR_FILENO, "Something wrong with pipe", 25);
         exit(-1);
    }

    pid_t pid = new_proccess();

    if( pid == -1 ){
        write(STDERR_FILENO, "Something wrong with fork",25);
        exit(-1);
    } else if ( 0 == pid ) {
        close(fd1[1]); 
        dup2(fd1[0],STDIN_FILENO);

        close(fd2[0]);
        dup2(fd2[1],STDOUT_FILENO);

        execvp("./child", argv);
    }
    else {
        char file_name[128];
        read(STDIN_FILENO,file_name, 128);
        int pos = strlen(file_name) - 1;
        if (file_name[pos] == '\n') {
            file_name[pos] = '\0';
        }

        int file = open(file_name, O_RDONLY);
        char numbers[128];
        if (file != -1) {
            read(file, numbers, 128);
        }
        else {
            write(STDERR_FILENO, "The file was not open\n", 23);
            exit(2);
        }
        
        close(fd1[0]);
        write(fd1[1], numbers, 128 );
        close(fd1[1]);

        waitpid(pid, NULL, -1);

        char answer[128] = " ";
        close(fd2[1]);
        read(fd2[0], answer, 128);

        write(STDOUT_FILENO, answer, 128);
        write(STDOUT_FILENO, "\n", 1);

        close(fd2[0]);
    }
        
    return 0;
}
