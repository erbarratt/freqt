#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pwd.h>

int main(int argc, char *argv[]){

	//first ensure there's a config file in the users home dir
		char *homedir;
		if ((homedir = getenv("HOME")) == NULL) {
			homedir = getpwuid(getuid())->pw_dir;
		}
		char * file = strcat(homedir, "/.freqt");

		FILE * fp;
		fp = fopen(file, "r");
		if (fp == NULL){
			fp = fopen(file, "w");
			fputs("freqt config\n", fp);
			fp = fopen(file, "r");
		}

	//get command to run from file from arguments
		char * command = NULL;
		if(argc == 2){
			command = strcat(argv[1], "|");
		}

	if(command == NULL){

		//output file contents
			char * line = NULL;
			size_t len = 0;

			//dump contents of file
				while ((getline(&line, &len, fp)) != -1) {
					printf("%s", line);
				}

	} else {

		//search for the command within the file
		//using malloc instead of char temp[512] so we can add to the pointer to remove the command and "|"
			char * temp;
			temp = (char * ) malloc(512);

			while(fgets(temp, 512, fp) != NULL) {
				if((strstr(temp, command)) != NULL) {
					temp += strlen(command);
					printf("%s\n", temp);
					system(temp);
					break;
				}
			}

	}

	fclose (fp);

	return 0;

}
