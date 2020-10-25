//*********************************************************
// Alexa Ceja
// Operating Systems
// Project #2: Simple Island Shell 
//*********************************************************

//*********************************************************
// Includes and Defines
//*********************************************************
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <signal.h>
#include <string.h>
#include <cstdlib>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string>
//Included csignal for C++ purposes //
#include <csignal>
//Included fcntl for redirect purposes //
#include <fcntl.h>
#include <fstream>

using namespace std;

// Signal Global Variables to keep track of signal handling // 
static int sigIntCounter = 0;
static int sigQuitCounter = 0;
static int sigTstpCounter = 0;

//********************************************************
// Using hist Clas Provided by Dr. Kar
//********************************************************
class hist {
   private:
     string commands[10];
     int begin;
     int number;

   public:
     hist() {
       begin = 0;
       number = 0;
     }

     void append(string x) {
         commands[(begin + number) % 10] = x;
         if (number == 10)
             begin = (begin + 1) % 10;
         else
            if (number < 10)
               number++;
         return;
     }

     string retrieve(int n)
     {
         return commands[(begin + n - 1)%10];
     }

     int size()
     {
         return number;
     }
};
//********************************************************
// Signal Handling Function 
// - Function uses if statements to increase interrupts counters
// 		by 1 everytime they are input in the command.
//********************************************************
void signal_CallBack(int signum)
{
	if (signum == SIGINT)
	{
		sigIntCounter++;
	}
	else if (signum == SIGQUIT)
	{
		sigQuitCounter++;
	}
	else if (signum == SIGTSTP)
	{
		sigTstpCounter++;
	}
};
//*********************************************************
// Main Function - code provided by Dr. Kar has been indicated in comments
//*********************************************************
int main(int argc, char *argv[])
{
	//Local Variables by Dr.Kar //
	int ii;
	int retval;
	pid_t pid;
	char path[80];
	char str[200];
	char **argvc;
	int i;
	string cmd_str;
	hist   myhist; 
	char **args;
	char *token;
	
	//Args and Argvc provided by Dr. Kar //
	args = new char* [20*sizeof(*args)];
	argvc = new char* [20*sizeof(*argvc)];
	for (i = 0; i < 20; ++i)
		argvc[i] = new char [80];
	
	//Initialize local variables by Dr. Kar //
	ii = 0;
	retval = 0;
	
	//Signal Registration and Handling//
	signal(SIGINT, signal_CallBack);
	signal(SIGQUIT, signal_CallBack);
	signal(SIGTSTP, signal_CallBack);
	
	//Main Loop //
	while(true)
	{
		//Provided by Dr. Kar //
		cout << "[guish$]";
				
		// Get Commands and Arguments by Dr. Kar
		if(fgets(str, 200, stdin) == NULL)  //Read a line
		{
			printf("Error\n");
			return 0;
		} 
		
		str[strlen(str) - 1] = '\0';       //Replace newline ch with null
		myhist.append(str);	
		
		// Returns first token with delimiter space by Dr. Kar //
		token = strtok(str, " ");
		
		// Keep extracting tokens by Dr. Kar //
		i = 0;
		while (token != NULL) 
		{ 
			strcpy(argvc[i], token);
			token = strtok(NULL, " ");  
			++i;
		} 
		strcpy(argvc[i],"");   // copy NULL in last arg
	
		
		// Check if it is hist command by Dr. Kar //
		if (strcmp(argvc[0], "hist") == 0 && strcmp(argvc[1],"") ==0)
		{
			for (i = 1; i <= myhist.size(); ++i)
				cout << i <<". " << myhist.retrieve(i) << endl;
			strcpy(argvc[0],"");            // no need to use execv() function
			continue;
		}
		
		// If loop to check r command by Dr. Kar // 
		// not working properly //
		if (strcmp(argvc[0], "r") == 0)
		{
			if (strcmp(argvc[1], "")== 0 && myhist.size() > 0)  // command:  r
			i = myhist.size();
			
			if (strcmp(argvc[1],"")!= 0 && strcmp(argvc[2],"")==0)  // command: r   n
			i = atoi(argvc[1]);
			
			if (i >= 1 || i <= myhist.size())
			{
				cmd_str = myhist.retrieve(i);
				strcpy(str, cmd_str.c_str());  // get tokens from retrived command
				token = strtok(str, " ");
				
				// Keep extracting tokens by Dr. Kar
				i = 0;
				
				while (token != NULL)
				{
					printf("%s\n", token);   // show each
					strcpy(argvc[i], token);
					token = strtok(NULL, " ");
					++ i;
				}
				
				strcpy(argvc[i],"");
			}
		}
		
		i = 0;
		while (strcmp(argvc[i],"") != 0)
		{
			args[i] = argvc[i];
			++ i;
		}
		args[i] = NULL; 
		
		//Code to allow exit to work from first guish.cpp file //
		//Edited to add signal handling counters //
		if(!strcmp( argvc[0], "exit" ))
		{
			printf ("Signal Handling (SIGINT): CTRL + C - was tried %d times \n", sigIntCounter);
			printf ("Signal Handling (SIGQUIT): CTRL + / - was tried %d times \n", sigQuitCounter);
			printf ("Signal Handling (SIGTSTP): CTRL + Z - was tried %d times \n", sigTstpCounter);
			break;
		}
		
/* 		//I/O Redirection Process //
		int a = 0;
		cmd += args[a];
		cmd += " ";
		if(!strcmp(argvc[0], "<"))
		{
			in = a;
		}
		else if (!strcmp(argvc[0], ">"))
		{
			out = a;
		}
		
		if(in != 0)
		{
			in_Redirection(args, in);
		}
		else if (out != 0)
		{
			out_Redirection(args, out);
		} */
		
		
		// Check whether to execute command by Dr. Kar //
		if(args[0] != NULL)
		{
			//I/O Redirection Process //
			int a = 0;
			string cmd;
			cmd += args[a];
			cmd += " ";
			if(!strcmp(argvc[0], "<"))
			{
				in = a;
			}
			else if (!strcmp(argvc[0], ">"))
			{
				out = a;
			}
			
			if(in != 0)
			{
				in_Redirection(args, in);
			}
			else if (out != 0)
			{
				out_Redirection(args, out);
			}
			//Fork Process by Dr. Kar //
			else if((pid = fork())< 0)
			{
				printf("Fork error"); exit(0) ;
			}
			
			else  if (pid == 0)   // child process
			{
				strcpy(path, "/bin/");
				strcat(path, args[0]);
				execv(path, args);   // returns if there is error
				printf("Command failed\n");
				return 0;
			}
		}
		else 
		{
			wait(NULL);    // wait for child      
		}

/* //UNIX REDIRECITON ///////////////////////////////////
	//Unix Redirection by Dr. Kar //
	int out = open("cout.log", O_RDWR|O_CREAT|O_APPEND, 0600);
	if (out == -1) { perror("opening cout.log"); return 255;}
	
	int err = open("cerr.log", O_RDWR|O_CREAT|O_APPEND, 0600);
	if (err == -1) { perror("opening cerr.log"); return 255; }
	
		//Save //
	int save_out = dup(fileno(stdout));
	int save_err = dup(fileno(stderr));
	
		//Assign//
	if (dup2(out, fileno(stdout)) == -1) {{ perror("cannot redirect stdout"); return 255; }
    	if (dup2(err, fileno(stderr)) == -1) { perror("cannot redirect stderr"); return 255; }

	puts("doing an ls or something now");
	system("ls -l");
	fflush(stdout); close(out);
	fflush(stderr); close(err);
	
		//Restore//
	dup2(save_out, fileno(stdout));
	dup2(save_err, fileno(stderr));
	
	close(save_out);
	close(save_err);
	
	puts("back to normal output");
//End UNIX REDIRECITON	//////////////////////////////////////////////////// */

	}

	return 0;
}