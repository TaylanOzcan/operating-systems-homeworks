#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#define PROT_READ 0x1
#define PROT_WRITE 0x2
#define MAP_SHARED 0x01

int main( int argc, char* argv[] ) {
	int fdone[2], fdone2[2], fdone3[3];
	pid_t childid, childid2;
	char readBuff[50], readBuff2[50], readBuff3[50];
	char writeBuff[50];
	int readCounter;
	void* ptr;
	int shm_fd;
	char READY_MSG[9] = "I am done";

	pipe(fdone);
	pipe(fdone2);
	pipe(fdone3);
 
	if(argc < 3){
		printf("At least need 2 params");
		exit(1);
	}

	int fileOpen = open( argv[1], 0);
	int targetFile = open( argv[2], 0666);

	if(fileOpen == -1 || targetFile == -1){
		printf( "Opening file failed");
		exit(1);
	}
	
	childid = fork();
	if(childid == 0) {
		// inside the child prcocess
		close(fdone[1]);
		read(fdone[0], readBuff, sizeof(readBuff));
		//printf("String received by 1st child via pipe: %s", readBuff);

		shm_fd = shm_open("sm", O_CREAT | O_RDWR, 0666);
		ftruncate(shm_fd, 128);
		ptr = mmap(0, 128, PROT_WRITE, MAP_SHARED, shm_fd, 0);
		sprintf(ptr, "%s", readBuff);
		//printf("String written by 1st child into shared memory: %s", (char*)ptr);

		close(fdone2[0]);
		write(fdone2[1], READY_MSG, strlen(READY_MSG) + 1);
		close(fdone2[1]);

	}else if(childid > 0){
		// inside the parent process
		close(fdone[0]);
		// code to read from a text file
		while((readCounter = read(fileOpen, readBuff, sizeof(readBuff)) > 0)){
			write(fdone[1], readBuff, sizeof(readBuff));
		}
		close(fdone[1]);

		close(fdone2[1]);
		read(fdone2[0], readBuff2, sizeof(readBuff2));
	
		//printf("String received by parent via pipe: %s", readBuff2);

		childid2 = fork();
		if(childid2 == 0){
			shm_fd = shm_open("sm", O_RDONLY, 0666);
			ptr = mmap(0, 128, PROT_READ, MAP_SHARED, shm_fd, 0);
			write(targetFile, (char*)ptr, strlen(ptr) );
			shm_unlink("sm");
			//printf("String read by 2nd child from shared memory: %s", (char*)ptr);

			close(fdone3[0]);
			write(fdone3[1], READY_MSG, strlen(READY_MSG) + 1);
			close(fdone3[1]);

		}else if(childid2 > 0){
			close(fdone3[1]);
			read(fdone3[0], readBuff3, sizeof(readBuff3));

			//printf("String received by parent via pipe: %s", readBuff3);

		}

	}
	return 0;
}
