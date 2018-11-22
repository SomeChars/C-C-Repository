﻿
/*Пример -"имя функции" "имя файла 1" 
(опционально)"имя файла 2" "имя файла 3"
пока доступно - всё что описано здесь: https://losst.ru/komanda-cat-linux*/
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

int main()
{
	int counter = 0;
	char operation[10];
	char filename1[100];
	char filename2[100];
	char filename3[100];
	scanf("%s %s", operation,filename1);
	if (operation[1] == '>') {
		scanf("%s", filename2);
	}
	if (operation[1] == '+') {
		scanf("%s %s", filename2,filename3);
	}
	printf("\n");
	char str[100][100];
	FILE* file1;
	FILE* file2 = NULL;
	FILE* file3 = NULL;
	if (file1 = fopen(filename1, "r")) {
		while (fgets(str[counter], 100, file1)) {
			counter++;
		}
	}
	else {
		printf("File1 not found");
		return 1;
	}
	if (operation[1] == 'n') {
		default_numeration(str,counter);
	}
	if (operation[1] == 'b') {
		trimmed_numeration(str, counter);
	}
	if (operation[1] == 'E') {
		s_kak_dollar(str, counter);
	}
	if (operation[1] == 's') {
		trim_all_repeats(str, counter);
	}
	if (operation[1] == 'T') {
		tabulation_shown(str, counter);
	}
	if (operation[1] == 'p') {
		just_print(str, counter);
	}
	if (operation[1] == '>') {
		if (file2 = fopen(filename2, "r")) {
			while (fgets(str[counter], 100, file2)) {
				counter++;
			}
		}
		else {
			printf("File2 not found");
			return 1;
		}
		just_print(str, counter);
	}
	if (operation[1] == '+') {
		if (file2 = fopen(filename2, "r")) {
			while (fgets(str[counter], 100, file2)) {
				counter++;
			}
		}
		else {
			printf("File2 not found");
			return 1;
		}
		association(str, counter, file3, filename3);
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