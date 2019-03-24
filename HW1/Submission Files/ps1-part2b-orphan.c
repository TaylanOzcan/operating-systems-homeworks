#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(){
	int id = fork();

	if(id > 0){

	}else if(id == 0){
		sleep(30);
	}

	return 0;
}
