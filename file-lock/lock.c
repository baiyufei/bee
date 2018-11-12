#include <sys/file.h>
#include <stdio.h>
#include <unistd.h>

int main (void)
{
    FILE *fp = NULL;
    int i = 20;
    if ((fp = fopen("./l", "r+b")) == NULL)
        printf("file open error!\n");

    printf("wait lock\n");
    if (flock(fp->_fileno, LOCK_EX) != 0)
        printf("file lock by others\n");

    printf("get lock\n");
    sleep(20);
    fclose(fp);
    flock(fp->_fileno, LOCK_UN);
    printf("unlock\n");
    return 0;
}
