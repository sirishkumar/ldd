# include <fcntl.h>
# include <sys/types.h>
# include <unistd.h>
# include <sys/file.h>

main(){
	int fd,loc_res;
	struct flock lock;
	fd = open("/media/test.c",O_RDWR);
	//loc_res=flock(fd,LOCK_EX); //lock 6 bytes

  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 100;

  lock.l_type = F_RDLCK;

  if((fcntl(fd,F_SETLK,&lock)) != 0)
		perror("fcntl : ");
	printf(" result of locking = %d\n",loc_res);
	getchar();
}
