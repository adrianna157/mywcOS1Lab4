#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#define MAX_LINE 80

#define BUFFER_SIZE 1000
#define DELIMETER "\n\t "

void print_commands(char str[]);


void print_commands(char str[])
{
    printf("%s\n -h: display a command options and exit \n -c: display the number of characters \n -w: display the number of words in the input\n -l: display the number lines in the input \n -f filename: use file as input, defaults to stdin \n", str);
}

int main (int argc, char **argv)
{
  int cflag = 0;
  int wflag = 0;
  int lflag = 0;
  char *filename = NULL;
  FILE *iFile = NULL;
  //int indexw;
  int c;
  char buffer[BUFFER_SIZE];
  // int totalRead = 0;
  int ccount = 0;
  int wcount = 0;
  int lcount = 0;
  // char *words, *ptr;
  char *token = NULL;




  // int opterr = 0;

  while ((c = getopt (argc, argv, "hlwcf:")) != -1) {
    switch (c)
      {
      case 'h':
        print_commands(argv[0]);
        //aflag = 1;
        exit(0);
      case 'c':
        cflag = 1;
        break;
      case 'w':
        //cvalue = optarg;
        wflag = 1;
        break;
      case 'l':
        //cvalue = optarg;
        lflag = 1;
        break;
      case 'f':
        filename = optarg;
        break;  
      case '?':
        fprintf (stderr,
                   "Unknown option character `\\x%x'.\n",
                   optopt);
        return 1;
      default:
        exit (1);
      }
   }
    if(filename == NULL) {
        iFile = stdin;
    }
    else {
        iFile = fopen(filename, "r");
        if (iFile == NULL) {
            fprintf(stderr, "File not opened. Input valid filename!");
            exit(2);
        }
    }

    if (cflag == 0 && wflag == 0 && lflag == 0) {
        cflag = wflag = lflag = 1;
    }

    while(fgets(buffer, BUFFER_SIZE, iFile) != NULL) 
    {
       lcount++;
       ccount += strlen(buffer);
       token = strtok(buffer, DELIMETER);
       while (token != NULL) {
           wcount++;
           token = strtok(NULL, DELIMETER);

        }
    } 
    
    if(lflag)
  {
    printf("there were %d lines in the file \n",lcount);
  }
    if(cflag)
  {
    printf("there were %d characters in the file \n",ccount);
  }
    if(wflag)
  {
    printf("there were %d words in the file \n",wcount);
  }
    if(filename == optarg)
    {
      printf("The file name is %s", filename);

    fclose(iFile);
    }
 return 0;   
}
   
  

    



 
