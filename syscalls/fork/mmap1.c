/* Check /proc/pid/map for fork system call
Version : 1.0
Author : Team -C
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>
#include <sys/wait.h>


main(){
	int fd,i;
	unsigned char *filedata= NULL,*temp;
	fd = open("./test.file",O_RDWR);
	filedata = (char *) mmap((void*)0,125,PROT_READ|PROT_WRITE,\
			MAP_PRIVATE,fd,0);	
	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}
	temp = filedata;

        memset(temp,'g',125);

        pid_t pid = fork();

        if(pid == 0)
        {
            printf("\n In Child");
            memset(temp,'k',125);
            temp[10]='a';

            int i =0;
            while(i<=125){
                temp[i++] = 'b';
            }
        }
        else
        {
            printf("In Parent");
             int i =0;
            while(i<=125){
                temp[i++] = 'k';
            }
            memset(temp,'h',125);
            int status;
            getchar();
            wait(&status);
        }

}
