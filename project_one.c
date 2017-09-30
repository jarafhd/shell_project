/* Filename: project_one.c
*  Programmers:
*  Date:
*  Class:
*  Instructor:
*  Project Name:
*  Description:
*
*
*
*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

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
	 args[i] = token;
         printf(" 1) %s\n",args[i]);
	 token = strtok(NULL," ");
	}
	args[i] = NULL;
	/* After reading user input, the steps are:*/
	printf("forking child now\n");	
	/* (1) fork a child process using fork()*/
	pid = fork();
	/* (2) the child process will invoke execvp()*/

	if(pid < 0){
		printf("ERROR: forking child failed");
		exit(1);
	}
	else if(pid == 0){
	        printf("In Child:%s\n",args[0]);
       		printf("In Child:%s\n",args[1]);
       		printf("In Child:%s\n",args[2]);
		printf("i = %d\n", i);
		if(execvp(*args[0],args) == -1) {
		printf("ERROR: execvp() Failed!\n");
		exit(1);
		}
		printf("Clean Child Exit\n");
		exit(0);
	}else{
		printf("\n");
		/* (3) if command included &, parent will invoke wait()*/
		if(args[i-1] == "&"){
	  	wait();
	 	}
		wait(); 
		printf("Parent Exiting\n");

	 }

	} /* end of while(should_run) */

	return 0;
}
