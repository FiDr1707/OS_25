//Программа, получающая значение идентификаторов текущего и родительского процесса
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
	pid_t prid, parentprid;
	prid = getpid();
	parentprid=getppid();
	printf("Id текущего процесса: %d\nId родительского процесса: %d\n", prid, parentprid);
	return 0;
}
