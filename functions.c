//Daniel Abramov - 204621627
//Sahar Biton - 316992392

#define _CRT_SECURE_NO_WARNINGS //printf and scanf are not secure - the secure way is to write printf_s and scanf_s (we are using basic c with scanf and printf)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

user* makeuser(char username[], char pw[], int lvl, char fullname[])//make user after make get details 
{
	user* new = (user*)malloc(sizeof(user));
	strcpy(new->username, username);
	strcpy(new->pw, pw);
	new->lvl = lvl;
	strcpy(new->fullname, fullname);
	new->next = NULL;
	new->prev = NULL;
	return new;
}

user* import_users_to_list(FILE* path)
{
	char username[16], pw[16], fullname[21];
	char line[54];
	int lvl;
	user* head, * temp_user, * temp_pntr;
	FILE* open_file_users = fopen(path, "r");
	if (!open_file_users)
	{
		open_file_users = fopen(path, "w");
		fprintf(open_file_users, "Username       Password       L Fullname            \n");
		fprintf(open_file_users, "admin          admin          3 System Manager      \n");
		head = makeuser("admin          ", "admin          ", 3, "System Manager      ");
		fclose(open_file_users);
		return head;
	}
	else
	{
		fgets(line, 54, open_file_users); //the header of the users
		fgets(line, 54, open_file_users);
		strncpy(username, line, 15);
		username[15] = '\0';
		strncpy(pw, line + 15, 15);
		pw[15] = '\0';
		lvl = line[30] - 48; //ascii table trans to int
		strncpy(fullname, line + 32, 20);
		fullname[20] = '\0';
		head = makeuser(username, pw, lvl, fullname);
		temp_pntr = head;
		while (fgets(line, 54, open_file_users) > 0)
		{
			strncpy(username, line, 15);
			username[15] = '\0';
			strncpy(pw, line + 15, 15);
			pw[15] = '\0';
			lvl = line[30] - 48; //ascii table trans to int
			strncpy(fullname, line + 32, 20);
			fullname[20] = '\0';
			temp_user = makeuser(username, pw, lvl, fullname);
			temp_pntr->next = temp_user;
			temp_user->prev = temp_pntr;
			temp_pntr = temp_user;
		}
		memset(line, 32, 53);
		fclose(open_file_users);
		return head;
	}
}

parit* makeparit(int id, char text1[], char text2[], double price, bool availabilty, char date[])
{
	parit* new = (parit*)malloc(sizeof(parit));
	new->id = id;
	strcpy(new->text1, text1);
	strcpy(new->text2, text2);
	new->price = price;
	new->availabilty = availabilty;
	strcpy(new->date, date);
	new->next = NULL;
	new->prev = NULL;
	return new;
}

bool check_bool_value(char str)
{
	if (str=='t')
		return true;
	else return false;
}

parit* import_pritim_to_list(FILE* path)
{
	char id_s[5],text1[11], text2[16],price_s[11],avaliab[15], date[11]; // +1 letter text1 text2 and date vars, for '\0'
	char* ptr;// for the strtod func
	char line[68];
	int id;
	double price;
	bool availabilty;
	parit* head, * temp_parit,* temp_pntr;
	FILE* open_file_pritim = fopen(path, "r");
	FILE* log;
	if (!open_file_pritim)
	{
		log = fopen(LOG_FILE, "a");
		printf("Couldnt open pritim file!\n");
		fprintf(log,"Couldnt open pritim file!\n");
		fclose(log);
		return NULL;
	}
	fgets(line, 68, open_file_pritim);
	fgets(line, 68, open_file_pritim);
	strncpy(id_s, line, 5);
	id = atoi(id_s);//converting string to int
	strncpy(text1, line + 5, 10);
	text1[10] = '\0';
	strncpy(text2, line + 15, 15);
	text2[15] = '\0';
	strncpy(avaliab, line + 30, 15);
	availabilty = check_bool_value(avaliab[0]);
	strncpy(price_s, line + 45, 11);
	price = strtod(price_s, &ptr); // converting string to double
	strncpy(date, line + 56, 10);
	date[10] = '\0';
	head = makeparit(id, text1, text2, price, availabilty, date);
	temp_pntr = head;
	while (fgets(line, 68, open_file_pritim) > 0)
	{
		strncpy(id_s, line, 5);
		id = atoi(id_s); //converting string to int
		strncpy(text1, line + 5, 10);
		text1[10] = '\0';
		strncpy(text2, line + 15, 15);
		text2[15] = '\0';
		strncpy(avaliab, line + 30, 15);
		availabilty = check_bool_value(avaliab[0]);
		strncpy(price_s, line + 45, 11);
		price = strtod(price_s, &ptr); // converting string to double
		strncpy(date, line + 56, 10);
		date[10] = '\0';
		temp_parit = makeparit(id, text1, text2, price, availabilty, date);
		temp_pntr->next = temp_parit;
		temp_parit->prev = temp_pntr;
		temp_pntr = temp_parit;
	}
	fclose(open_file_pritim);
	return head;
}

char* BufferingSpaces(char org[],int len)
{
	int i = 0, j;
	while (org[i] != '\0')
		i++;
	for (j = i; j < len; j++)
		org[j] = ' ';
	org[len - 1] = '\0';
	return org;
}

void free_linked_pritim(parit* head_p)
{
	while (head_p->next != NULL)
	{
		head_p = head_p->next;
		free(head_p->prev);
	}
	free(head_p);//last node
}

void free_linked_users(user* head_u)
{
	while (head_u->next != NULL)
	{
		head_u = head_u->next;
		free(head_u->prev);
	}
	free(head_u);//last node
}

void sort_pritim_byID(parit* head)
{
	parit* current, * index;
	char temp_text1[11], temp_text2[16], temp_date[11];
	int temp_id;
	bool temp_avaliablity;
	double temp_price;
	FILE* log;
	if (head == NULL)
	{
		log = fopen(LOG_FILE, "a");
		printf("The pritim list is empty!\n");
		fprintf(log,"The pritim list is empty!\n");
		fclose(log);
		return;
	}
	for (current = head; current->next != NULL; current = current->next)
	{
		for (index = current->next; index != NULL; index = index->next)
		{
			if (current->id > index->id)
			{
				temp_id = current->id;
				strcpy(temp_text1, current->text1);
				strcpy(temp_text2, current->text2);
				temp_price = current->price;
				temp_avaliablity = current->availabilty;
				strcpy(temp_date, current->date);

				current->id = index->id;
				strcpy(current->text1,index->text1);
				strcpy(current->text2,index->text2);
				current->price = index->price;
				current->availabilty = index->availabilty;
				strcpy(current->date, index->date);

				index->id = temp_id;
				strcpy(index->text1,temp_text1);
				strcpy(index->text2,temp_text2);
				index->price = temp_price;
				index->availabilty = temp_avaliablity;
				strcpy(index->date,temp_date);
			}
		}
	}
}

char* price_double_to_str(double price_d)
{
	char temp_price[12];
	int price, resedue;
	price = (int)price_d;
	resedue = (int)((price_d - price) * 100);
	sprintf(temp_price, "%d.%d", price, resedue);
	strcpy(temp_price, BufferingSpaces(temp_price, 12));
	return temp_price;
}
