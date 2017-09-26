#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define MAX_LINE 80 /* The maximum lenth command */

int main(void)
{
char *args[MAX_LINE/2 + 1]; /*command line argument */
int should_run = 1; /*flag to determine when to exit program */
pid_t pid;
char input_buffer[MAX_LINE];
char* token;
int i=0;
	while (should_run) {
	printf("osh> ");
	fflush(stdout);
	fgets(input_buffer,MAX_LINE + 1, stdin);
	token = strtok(input_buffer," ");
 	for(i = 0; token != NULL; ++i){
	/* printf(" %s\n", token);*/
	 args[i] = token;
	 printf("%s\n", args[i]);
	 token = strtok(NULL," ");
	}


	/* After reading user input, the steps are:*/

	/* (1) fork a child process using fork()*/
	pid = fork();
	/* (2) the child process will invoke execvp()*/
	if(pid == 0){

	}else{

	}
	/* (3) if command included &, parent will invoke wait()*/

	}

	return 0;

}
