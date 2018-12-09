#include "pch.h"
#include <iostream>
#include <string.h>

void read_vvod(int args,char *vvod[]);

char str[100];
char **lib = (char**)malloc(100*sizeof(char*));
char **lib_begin = lib;
int counter = 0;
FILE* filetowrite;

int main(int argc,char *argv[])
{	
	if (!strcmp(argv[1], "HELP")) {
		printf("***List of commands*** -n:Numeration, -b:Numeration without spaces, -E:$ before string, -s:Trim all repeats, -T:Tabulation shown like ^|, -p:Just print, -+:Associate files into a file that goes last");
	}
	else
	{
		read_vvod(argc,argv);
	}
}

void read_vvod(int args,char *vvod[]) {
	int counter = 0;
	int count_origin_strings = 0;
	int count = 0;
	int trimmed_counter = 0;
	int flag = 0;
	if (!strcmp(vvod[1], "-+")) {
		filetowrite = fopen(vvod[args - 1], "w");
	}
	for (int i = 2;i < args;i++) {
		if (i == args - 1) {
			if (!strcmp(vvod[1], "-+")) {
				break;
			}
		}
		FILE* file;
		if (file = fopen(vvod[i], "r")) {
			while (fgets(str, 100, file)) {
				counter++;
				if (!strcmp(vvod[1], "-n")) {
					printf("%d %s", count, str);
					count++;
				}
				if (!strcmp(vvod[1], "-b")) {
					if (strcmp(str, "")) {
						printf("%d %s", trimmed_counter, str);
						trimmed_counter++;
					}
					else
					{
						printf("%s", str);
					}
				}
				if (!strcmp(vvod[1], "-$")) {
					printf("$ %s", str);
				}
				if (!strcmp(vvod[1], "-s")) {
					counter++;
					if (count_origin_strings > 100) {
						lib = (char**) realloc(lib_begin,count_origin_strings*sizeof(char*));
					}
					
					for (int i = 0;i < count_origin_strings;i++) {
						if (!strcmp(str, (*lib))) {
							flag = 1;
						}
						*lib++;
					}
					if (!flag) {
						printf("%s", str);
						(*lib) = (char*)malloc(100 * sizeof(char));
						strcpy((*lib), str);
						count_origin_strings++;
					}
					flag = 0;
					lib = lib_begin;
				}
				if (!strcmp(vvod[1], "-T")) {
					char c1;
					char c2;
					int number_of_tabs = 0;
					int flag = 0;
					for (int j = 0; j < strlen(str) + number_of_tabs; j++) {
						if (str[j] == '\t') {
							number_of_tabs++;
							str[j] = '^';
							c2 = str[j + 1];
							str[j + 1] = '|';
							for (int k = j + 2; k < strlen(str) + number_of_tabs;k++) {
								if (flag % 2 == 0) {
								c1 = str[k];
								str[k] = c2;
								}
								else
									{
										c2 = str[k];
										str[k] = c1;
									}
									flag++;
							}
							flag = 0;
						}
					}
					printf("%s", str);
				}
				if (!strcmp(vvod[1], "-p")) {
					printf(str);
				}
				if (!strcmp(vvod[1], "-+")) {
					fprintf(filetowrite, str);
				}
			}
		}
		else {
			printf("%s %s\n","No file with this path:", vvod[i]);
		}
	}
}
