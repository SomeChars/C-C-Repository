#include "pch.h"
#include <iostream>
#include <string.h>

void default_numeration(char string_to_numerate[100][100],int counter);
void trimmed_numeration(char string_to_numerate[100][100],int counter);
void s_kak_dollar(char string_to_numerate[100][100], int counter);
void trim_all_repeats(char string_to_numerate[100][100], int counter);
void tabulation_shown(char string_to_numerate[100][100], int counter);
void just_print(char string_to_numerate[100][100], int counter);
void association(char string_to_numerate[100][100], int counter, FILE* file, char filename[100]);
void read_vvod(char vvod[1000]);

char str[100][100];
int counter = 0;
char operation[10];
char last_filename[100];
FILE* last_file;

int main()
{	
	printf("-%s %s   %s \n", "Command", "Path to file", "***For help enter: HELP***");
	char vvod[1000];
	gets_s(vvod);
	if (!strcmp(vvod, "HELP")) {
		printf("***List of commands*** -n:Numeration, -b:Numeration without spaces, -E:$ before string, -s:Trim all repeats, -T:Tabulation shown like ^|, -p:Just print, -+:Associate files into a file that goes last");
	}
	if (strcmp(vvod, "HELP")) {
		read_vvod(vvod);
		if (operation[0] == '-' && operation[1] == 'n') {
			default_numeration(str, counter);
		}
		if (operation[0] == '-' && operation[1] == 'b') {
			trimmed_numeration(str, counter);
		}
		if (operation[0] == '-' && operation[1] == 'E') {
			s_kak_dollar(str, counter);
		}
		if (operation[0] == '-' && operation[1] == 's') {
			trim_all_repeats(str, counter);
		}
		if (operation[0] == '-' && operation[1] == 'T') {
			tabulation_shown(str, counter);
		}
		if (operation[0] == '-' && operation[1] == 'p') {
			just_print(str, counter);
		}
		if (operation[0] == '-' && operation[1] == '+') {
			association(str, counter, last_file, last_filename);
		}
	}
}

void default_numeration(char string_to_numerate[100][100], int counter) {
	for (int i = 0;i < counter - 1;i++) {
		printf("%d %s",i + 1,string_to_numerate[i]);
	}
}

void trimmed_numeration(char string_to_numerate[100][100], int counter) {
	int trimmed_counter = 1;
	for (int i = 0;i < counter;i++) {
		if (strcmp(string_to_numerate[i], "")) {
			printf("%d %s", trimmed_counter, string_to_numerate[i]);
			trimmed_counter++;
		}
		else
		{
			printf("%s",string_to_numerate[i]);
		}
	}
}

void s_kak_dollar(char string_to_numerate[100][100], int counter) {
	int once = 0;
	for (int i = 0;i < counter;i++) {
		for (int j = 0; j < strlen(string_to_numerate[i])+1; j++) {
			if (string_to_numerate[i][j] == '\n' && once == 0) {
				string_to_numerate[i][j] = '$';
				string_to_numerate[i][j + 1] = '\n';
				string_to_numerate[i][j + 2] = '\0';
				once = 1;
			}
		}
		once = 0;
		printf("%s", string_to_numerate[i]);
	}
}

void trim_all_repeats(char string_to_numerate[100][100], int counter) {
	int flag = 0;
	for (int i = 0; i < counter - 1; i++) {
		for (int j = 0; j < i; j++) {
			if (!strcmp(string_to_numerate[i], string_to_numerate[j])) {
				flag = 1;
			}
		}
		if (!flag) {
			printf("%s", string_to_numerate[i]);
		}
		flag = 0;
	}
	char spec_string[100];
	strcpy(spec_string, string_to_numerate[counter]);
	spec_string[strlen(string_to_numerate[counter])] = '\0';
	for (int k = 0; k < counter - 1; k++) {
		if (!strcmp(string_to_numerate[k], spec_string)) {
			flag = 1;
		}
	}
	if (!flag) {
		printf("%s", string_to_numerate[counter]);
	}
}

void tabulation_shown(char string_to_numerate[100][100], int counter) {
	char c1;
	char c2;
	int number_of_tabs = 0;
	int flag = 0;
	for (int i = 1; i < counter; i++) {
		for (int j = 0; j < strlen(string_to_numerate[i]) + number_of_tabs; j++) {
			if (string_to_numerate[i][j] == '\t') {
				number_of_tabs++;
				string_to_numerate[i][j] = '^';
				c2 = string_to_numerate[i][j + 1];
				string_to_numerate[i][j + 1] = '|';
				for (int k = j + 2; k < strlen(string_to_numerate[i]) + number_of_tabs;k++) {
					if (flag % 2 == 0) {
						c1 = string_to_numerate[i][k];
						string_to_numerate[i][k] = c2;
					}
					else
					{
						c2 = string_to_numerate[i][k];
						string_to_numerate[i][k] = c1;
					}
					flag++;
				}
				flag = 0;
			}
		}
		number_of_tabs = 0;
	}
	for (int i = 0;i < counter;i++) {
		printf("%s", string_to_numerate[i]);
	}
}

void just_print(char string_to_numerate[100][100], int counter) {

	for (int i = 0;i < counter;i++) {
		printf("%s", string_to_numerate[i]);
	}
}

void association(char string_to_numerate[100][100], int counter, FILE* file,char filename[100]) {
	if (file = fopen(filename, "w")) {
		for (int i = 0; i < counter; i++)
		{
			fprintf(file, string_to_numerate[i]);
		}
	}
	else {
		printf("File not found");
	}
}

void read_vvod(char vvod[1000]) {
	int i = 0;
	while (vvod[i] != ' ')
	{
		operation[i] = vvod[i];
		i++;
	}
	i++;

	while (i < strlen(vvod)) {
		char filename[100];
		FILE* file;
		int kek = 0;
		while (vvod[i] != ' ' && vvod[i] != '\n' && i < strlen(vvod)) {
			filename[kek] = vvod[i];
			i++;
			kek++;
		}
		filename[kek] = '\0';
		if (operation[0] == '-' && operation[1] == '+') {
			strcpy(last_filename, filename);
		}
		if (file = fopen(filename, "r")) {
			last_file = file;
			while (fgets(str[counter], 100, file)) {
				counter++;
			}
		}
		else {
			printf("%s %s\n","No file with this path:", filename);
		}
	i++;
	}
}
