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
#define MAX_HISTORY_SIZE 10 /* History buffer size */


void 	printHistory(char history_buffer[][MAX_LINE],int h,int flag){
	int i;
	if(flag == 0){ /* array has not looped around */
	/*printf("in flag 0\n");*/	
	for(i = h-1; i >= 0; --i){
			printf("%d %s \n", i+1, history_buffer[i]);
		}
	}
	else if(flag == 1){
		/*printf("in flag 1\n");*/
		if(h == 0){ h = 10;}
		for(i= h-1;i >= 0;--i){
			printf("%d %s \n", i+10, history_buffer[i]);

		}
		for(i = MAX_HISTORY_SIZE - 1; i >= h; --i){
			printf("%d %s \n", i, history_buffer[i]);
		}
	}
}/* end of print_history */



/* === Main ====================================================================================
===============================================================================================*/

int main(void)
{
char *args[MAX_LINE/2 + 1]; /*command line argument */
int should_run = 1; /*flag to determine when to exit program */
pid_t pid;
char input_buffer[MAX_LINE];
char* token;
int i;
char history_buffer[MAX_HISTORY_SIZE][MAX_LINE];
int h = 0; /* h denotes the mosts current element in the the history array */
int flag = 0; /* flag denotes where or not history array has(1) or hasn't(0) wrapped around */

	while (should_run) {
	printf("osh> ");
	fflush(stdout);
	fgets(input_buffer,MAX_LINE + 1, stdin);
	/*printf("h is %d\n",h);*/
	strncpy(history_buffer[h], input_buffer, MAX_LINE);
	/*printf("history_buffer[h] equals %s\n", history_buffer[h]);*/
	token = strtok(input_buffer,"\n");
	token = strtok(token," ");
 	for(i = 0; token != NULL; ++i){
		args[i] = token;
        	/*printf(" %d) %s\n", i, args[i]);*/
		token = strtok(NULL," ");
	}
	args[i] = NULL;
	
	if(strcmp(args[0],"exit") == 0 ){
		printf("Exiting OSC Shell\n");
		should_run = 0;
		break;
	
	}else if(strcmp(args[0],"history") ==  0){
		printHistory(history_buffer,h,flag);
	}
	/* (1) fork a child process using fork()*/
	pid = fork();
	/* (2) the child process will invoke execvp()*/

	if(pid < 0){
		printf("ERROR: forking child failed");
		exit(1);
	}
	else if(pid == 0){
		if(strcmp(args[0],"history") != 0){
				if(execvp(args[0],args) == -1){ 
				printf("ERROR: execvp() Failed!\n");
				exit(1);
				}
		}
		exit(0);
	} /* end of child process block */ 
	 else if(h < 10){
		++h;
	 }else if(h == 10){
		h = 0;
		flag = 1;
	  }else{
		printf("\n");
		/* (3) if command included &, parent will invoke wait()*/
		if(strcmp(args[i-1], "&") == 0){
			wait(NULL);
	 	}
		/*wait(NULL);*/ 
	  }


	} /* end of while(should_run) */

	return 0;


} /* end of main() */
