#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int id = fork();

	if(id > 0){
		sleep(30);
	}else{
		exit(0);
	}

	return 0;
}
