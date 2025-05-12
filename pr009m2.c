//Двунаправленная связь через pipe между родительским и дочерним процессом
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#define BYTES1 86
#define BYTES2 94
int main() {
	int fd1[2], fd2[2], result; //fd1 - файловые дескрипторы для передачи информации от родителя к ребенку
				   //fd2 - файловые дескрипторы для передачи информации от ребенка у родителю
	size_t size;
	char resstring1[BYTES1], resstring2[BYTES2]; //resstring1 - строка, полученная ребенком
					      //resstring2 - строка, полученная родителем
	if((pipe(fd1)<0)||(pipe(fd2)<0)) {
		printf("Не удалось создать pipe\n");
		exit(-1);
	}
	result = fork();
	if(result < 0) {
		printf("Ошибка при выполнении fork\n");
		exit(-1);
	}
	else if (result > 0) {
		if ((close (fd1[0]) < 0)||(fd2[1]<0)) {
			printf("Не удалось закрыть входной или выходной поток процесса родителя\n");
			exit(-1);
		}

	size = write(fd1[1], "Информация для дочернего процесса от родителя", BYTES1);
		if(size != BYTES1) {
			printf("Родителю не удалось записать всю строку в pipe\n");
			exit(-1);
		}
		if (close(fd1[1]) < 0){
			printf("Родителю не удалось закрыть выходной поток");
			exit (-1);
		}
	printf("Читаем строку, отправленную процессом ребенком...\n");

	size = read(fd2[0], resstring2, BYTES2);
		if(size < 0) {
			 printf("Родителю не удалось прочитать строку");
			 exit(-1);
		 }
	printf("Прочитанная родителем строка: %s\n", resstring2);
		if (close(fd2[0])<0){
			printf("Не удалось закрыть входной поток процесса-родителя\n");
			exit(-1);
		}
	printf("Процесс родитель завершил работу\n");
	}

	else {
		if ((close(fd1[1])<0)||(close(fd2[0])<0)) {
			printf("Не удалось закрыть входной или выходной поток процесса ребенка\n");
			exit(-1);
		}

	size = read(fd1[0], resstring1, BYTES1);
		if(size < 0) {
			printf("Не удалось прочитать строку процессу ребенку\n");
			exit(-1);
		}
	printf("Строка, написанная дочерним процессом: %s\n", resstring1);
		if (close (fd1[0])<0) {
		printf("Не удалось закрыть входной процесс ребенка\n");
		exit(-1);
		}

	size = write(fd2[1], "Информация для родительского процесса от родителя", BYTES2);
		if(size != BYTES2) {
			printf("Ребенку не удалось записать всю строку в pipe\n");
			exit(-1);
		}
		if (close (fd2[1])<0){
			printf("Не удалось закрыть выходной поток процесса-ребенка\n");
			exit(-1);
		}
		printf("Процессе-ребенок заверщил работу");
	}

	return 0;
}
