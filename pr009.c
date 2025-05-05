#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

int fd [2];
size_t size;
char string[] = "IFMITO 3.008.2.24\n", resstring[18];
//Создание pipe
//
if (pipe(fd)<0) {
printf("Не удалось создать pipe\n");
exit(-1);
}

size = write(fd[1], string, 18);

if (size != 18) {
printf("Не удалось записать всю строку в pipe");
exit (-1);
}

if(close(fd[1]) < 0) {
		printf("Не удалось закрыть выходной поток\n");
		exit(-1);
}
size = read(fd[0], resstring, 18);

if(size != 18) {
printf("Не удалось прочитать всю строку из pipe\n");
exit(-1);
}
printf("Прочитанная из pipe строка: %s\n", resstring);
if (close(fd[0]) < 0) {
printf("Не удалось закрыть входной поток\n");
exit(-1);
}
return 0;
}
