#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
void srtarr(int * arr[]) {
    //selection sort 
    int i, key, j;
    for (i = 1; i < 20; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}


  

int main(int argc, const char * argv[]) {
    int * tharr [20];
    int fds[2];
    pipe(fds); // create 2 pipes
    for (int i = 0 ; i < 20 ; i++) { // create random array
        tharr[i] = (int) rand()%100;
    }
    
    pid_t x = fork(); // splits prosses
    
    if (x == 0) {
        srtarr(tharr);
        dup2(fds[1],STDOUT_FILENO); // sets the child output to write pipe
        close(fds[0]); //closes pipes
        close(fds[1]); //closes pipes
        printf("%d\n",tharr[0]); // prints the smallest
        printf("%d\n",tharr[19]); //prints the largest
    }
    else {
        wait(NULL);
        int min,max;
        dup2(fds[0],STDIN_FILENO); // sets the father in to the pipe input
        close(fds[1]); // closes pipes
        close(fds[0]); // closes pipes
        scanf("%d",&min); // waits to get the values from the consule of the son
        scanf("%d",&max);
        printf("i got %d %d ",min,max);
    }
    int status;
      pid_t wpid = waitpid(x, &status, 0); return wpid == wpid &&
    WIFEXITED(status) ? WEXITSTATUS(status) : -1; // cleans up all the file descriptors
    return 0;
}

