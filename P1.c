#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE  256
#define BUFFERSIZE  50

int tokenize(char [], char*[], int*);
int execute(pid_t, char* args[], int);
void displayHistory();

int count = 0;
char lineGlobal[MAXLINE];
char history [10][BUFFERSIZE];
char* hist=history[0];
int main(){
int shouldRun=1;
char line [MAXLINE];
char* args[MAXLINE/2 +1];
int concurrent;
pid_t pid;
int TokenStatus, ExecStatus;
int i,j,c;
while (shouldRun=1)
{
	ExecStatus = 0;
	printf("osh> ");
	fflush(stdout);
	if (fgets(line, MAXLINE, stdin)==NULL){
		
		continue;}
	strcpy(lineGlobal,line);
	TokenStatus = tokenize(line, args, &concurrent);
	if(TokenStatus!=1){	
		{if(TokenStatus==-1)
			{shouldRun=0;
			return;}}
	continue;
	}
	
	pid=fork();
	ExecStatus = execute(pid, args, concurrent);
	if(ExecStatus == -1)
	{
	return 1;
	}
	if(ExecStatus==0)
		continue;
	
	
}
return  0;
}
int tokenize(char line[], char*args[], int*concurrent){
	 int i, currentToken = 0, tokenIndex = 0, shouldRun = 1;
	char line_copy[MAXLINE];
	strcpy(line_copy,line);
	
	for (i = 0; shouldRun == 1; ++i) {
		if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' || line[i] == '\0') {
			if (line[i] == '\0') {
				shouldRun = 0;}
			line[i] = '\0';
			if (i - tokenIndex > 0) {
				args[currentToken] = &line[tokenIndex];
				++currentToken;
			}
			tokenIndex = i + 1;
		}
	}
		if(currentToken==0){
			return 0;}
		if(strcmp(args[0], "exit") == 0)
			{return -1;}
		if(strcmp(args[currentToken - 1], "&" )==0)

		{
			*concurrent=1;
			currentToken--;
		}
		else
		{
			*concurrent=0;
		}
		if(strcmp(args[0], "history")==0)
		{
			if(count>0){
				displayHistory();}
			else
				printf("\nNo Commands in History\n");
		return 1;
		}
		else if(args[0][0]-'!'==0)
		{
		 int x = args[0][1]-'0';
       		 int y = args[0][2]-'0';
			if(x>count)
			{	
				printf("\nNo such command\n");
				strcpy(line, "Wrong Command");
	;				
			}
			else if(x== 1 && y==0 && count == 10)
			{
				
				strcpy(line, history[0]);
			}
			else if(y!=-48)
			{
				printf("\nNo such command\n");
				strcpy(line, "Wrong Command");
			}	
			else
			{
				if(x==-15){
					strcpy(line, history[0]);
						}
				else if(x==0)	
				{	
					printf("\nNo such command\n");
					strcpy(line, "Wrong Command");
				}
				else if (x>=1){
					strcpy(line, history[count - x]);}
			}
		}
	for(i=9;  i>0 ; i--)
		{strcpy(history[i], history [i-1]);}
	if(strcmp(line, "Wrong command")==0)
{	strcpy(history[0], line);}
	else
{	strcpy(history[0],line);}
	count++;
	if(count>10)
		{count=10;}
	args[currentToken] = NULL;
	return 1;
}
int execute(pid_t pid, char* args[], int concurrent)
{
	if(pid<0)
	{
		printf("\nFork not successful\n");
		return -1;
	}
	else if(pid==0)	{	
		execvp(args[0], args);
	if(strcmp(lineGlobal,"history\n")!=0)
		{printf("No such command\n");
		strcpy(history[0], "Wrong command");}
	return 0;
}
else if(concurrent == 0 ){
	{
		waitpid(pid, NULL, 0);
	}return 1;
}
return 1;
}

void displayHistory()
{
	printf("\nShell command history:\n");
	int i;
	int j=0;
	int histCount = count;

	for(i=0; i<10;i++)
	{
		printf("%d. ", histCount);
		while(history[i][j] != '\n'&& history[i][j]!='\0')
		{
			printf("%c", history[i][j]);
			j++;
		}
		printf("\n");
		histCount--;
		j=0;
		if(histCount==0)
			{break;}
	}
	printf("\n");
}
