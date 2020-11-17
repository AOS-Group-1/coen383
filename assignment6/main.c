#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>

#define READ_PIPE 0
#define WRITE_PIPE 1

struct timeval timer;

char *timestamp() {
    struct timeval currentTime;
    char *time_string = (char *)calloc(11, sizeof(char));
    gettimeofday(&currentTime, NULL);
    int milliseconds = (currentTime.tv_usec-timer.tv_usec)/1000;
    if(milliseconds < 0) {
        milliseconds = ((currentTime.tv_usec+1000000)-timer.tv_usec)/1000;
    }
    int seconds = currentTime.tv_sec-timer.tv_sec;
    snprintf(time_string, 10, "0:%02d.%03d:", seconds, milliseconds);
    return time_string;
}

void fixReadInvalidCharacters(char *timeBuffer, char *buffer, int readValue, FILE *stream) {
    int i;
    fwrite(timeBuffer, sizeof(char), 9, stream);
    for(i = 0; i < readValue; i++) {
        if(buffer[i] == 9 || buffer[i] == 10 || buffer[i] == 13 || (buffer[i] >= 32 && buffer[i] <= 126)) {
            fputc(buffer[i], stream);
        }
        if(i == readValue-1 && buffer[i] != 10 && buffer[i] != 13) {
            if(buffer[i] == 0 && buffer[i-1] != 10 && buffer[i-1] != 13) {
                printf("buffer[i] == %d\n", buffer[i]);
                fputc('\n', stream);
            }
        }
    }
}

void readPipes(int **pipes) {
    struct timeval clock;
    char buffer[1024];
    char *timeBuffer;
    fd_set readSet[5];
    int i;
    int selectValue;
    int readValue;
    time_t startTime = 0;
    FILE *outputFile = fopen("output.txt", "w");
    if(outputFile == NULL) {
        fprintf(stderr, "Could not open output.txt %d\n", errno);
        exit(errno);
    }

    clock.tv_sec = 4;
    clock.tv_usec = 0;
    startTime = time(0);
    gettimeofday(&timer, NULL);

    while(time(0)-startTime < 30) {
        FD_ZERO(&readSet[0]);
        for(i = 0; i < 5; i++) {
            FD_SET(pipes[i][READ_PIPE], &readSet[i]);
            selectValue = select(pipes[i][READ_PIPE]+1, &readSet[i], NULL, NULL, &clock);
            clock.tv_sec = 2;
            clock.tv_usec = 0;
            if(selectValue == -1) {
                fprintf(stderr, "Select failed %d\n", errno);
            } else if(selectValue) {
                // read from a pipe
                if((readValue = read(pipes[i][READ_PIPE], &buffer, 1024)) > 0) {
                    timeBuffer = timestamp();
                    fixReadInvalidCharacters(timeBuffer, buffer, readValue, outputFile);
                    fixReadInvalidCharacters(timeBuffer, buffer, readValue, stdout);
                    memset(buffer, 0, sizeof(char)*1024);
                    free(timeBuffer);
                    timeBuffer = NULL;
                } else {
                    fprintf(stderr, "read failed with errno %d\n", errno);
                }
            } 
        } 
    }
    for(i = 0; i < 5; i++) {
        close(pipes[i][WRITE_PIPE]);
        close(pipes[i][READ_PIPE]);
    }
    fclose(outputFile);
}

void writePipe(int *pipe, int childNum) {
    time_t startTime;
    int sleepVal;
    int count = 0;
    char buffer[1024];
    char *timeBuffer;
    close(pipe[READ_PIPE]);
    srand(0);

    startTime = time(0);
    gettimeofday(&timer, NULL);
    while(time(0)-startTime < 30) {
        count++;
        sleepVal = rand()%(3);
        if(sleepVal != 0) {
            sleep(sleepVal);
        }
        timeBuffer = timestamp();
        snprintf(buffer, 1024, "%s Child %d message %d\n", timeBuffer, childNum, count);
        write(pipe[WRITE_PIPE], buffer, strlen(buffer)+1);
        free(timeBuffer);
        timeBuffer = NULL;
    }

    close(pipe[WRITE_PIPE]);
}

void fifthChild(int *pipe) {
    ssize_t input;
    time_t startTime = time(0);
    char *line = NULL;
    size_t allocated = 0;
    int messageNum = 0;
    char buffer[1024];
    char *timeBuffer;
    close(pipe[READ_PIPE]);

    startTime = time(0);
    gettimeofday(&timer, NULL);
    while(time(0)-startTime < 30) {
        input = getline(&line, &allocated, stdin);
        if(input != -1) {
            messageNum++;
            timeBuffer = timestamp();
            snprintf(buffer, 1024, "%s %s\n", timeBuffer, line);
            write(pipe[WRITE_PIPE], buffer, strlen(buffer+1));
            free(timeBuffer);
            timeBuffer = NULL;
        }
        free(line);
        line = NULL;
    }   
    close(pipe[WRITE_PIPE]);
}

void createChildren(int **pipes) {
    int ids[5];
    for(int i = 0; i < 5; i++) {
        ids[i] = fork();
        if(i == 4 && ids[i] == 0) {
            fifthChild(pipes[i]);
            return;
        } else {
            if(ids[i] == 0) {
                writePipe(pipes[i], i+1);               
                return;
            }
        }
    }
    readPipes(pipes);
    for(int j = 0; j < 5; j++) {
        waitpid(ids[j], NULL, 0);
    }
}

int main(int argc, char *argv[]) {
    int **pipes = (int **) malloc(5*sizeof(int *));
    for(int i = 0; i < 5; i++) {
        pipes[i] = (int *) malloc(2*sizeof(int));
        if(pipe(pipes[i]) == -1) {
            fprintf(stderr, "Pipe failed %d\n", errno);
            exit(errno);
        }
    }

    createChildren(pipes);
    
    for(int i = 0; i < 5; i++) {
        free(pipes[i]);
    }
    free(pipes);
}
