//Daniel Abramov - 204621627
//Sahar Biton - 316992392

#define _CRT_SECURE_NO_WARNINGS //printf and scanf are not secure - the secure way is to write printf_s and scanf_s (we are using basic c with scanf and printf)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "functions.h"


//user functions
void adduser(user* head, user* new)
{
	user* t = head;
	if (head == NULL)
	{
		head = new;
		return;
	}
	while (t->next != NULL)
		t = t->next;
	t->next = new;
	new->prev = t;
	new->next = NULL;
	return;
}

int checkid(user* head)
{
	user* t = head;
	char username[16];
	char pw[16];
	int k = 0, s = 0, a = 0; // k is for comaring usernames. s is for count of mistakes in pw.
	FILE* log = fopen(LOG_FILE, "a");
	while (a < 3)
	{
		printf("enter your username please\n");
		fprintf(log,"enter your username please\n");
		scanf("%s", username);
		fprintf(log,"%s\n", username);
		strcpy(username, BufferingSpaces(username, 16));
		while (t != NULL)
		{
			while (k < 15)
			{
				if ((username[k]) == (t->username[k]))
					k++;
				else break;
			}
			if (k == 15)
			{
				while (s < 3)
				{
					printf("enter your password please : \n");
					fprintf(log,"enter your password please : \n");
					scanf("%s", pw);
					fprintf(log, "%s\n", pw);
					strcpy(pw, BufferingSpaces(pw, 16));
					k = 0;
					while (k < 15)
					{
						if ((pw[k]) == (t->pw[k]))
							k++;
						else
						{
							printf("password you entered is wrong!\n");
							fprintf(log,"password you entered is wrong!\n");
							s++;
							break;
						}
					}
					if (k == 15)
					{
						fclose(log);
						return t->lvl;
					}
				}
				if (s == 3)
				{
					printf("you wrong 3 times , program closes now\n");
					fprintf(log,"you wrong 3 times , program closes now\n");
					fclose(log);
					return 0;
				}
			}
			else
				t = t->next;
		}
		printf("wrong user name, pleae try again:\n");
		fprintf(log,"wrong user name, pleae try again:\n");
		t = head;
		a++;
	}
	printf("wrong username 3 times please open again the program and try again\n");
	fprintf(log,"wrong username 3 times please open again the program and try again\n");
	fclose(log);
	return 0;
}

user* makenewuser()
{
	user* new = (user*)malloc(sizeof(user));
	char username[16];
	char pw[16];
	int lvl;
	char fullname[21];
	FILE* log = fopen(LOG_FILE, "a");
	printf("please enter new details\n");
	fprintf(log,"please enter new details\n");
	printf("enter user name please :\n");
	fprintf(log,"enter user name please :\n");
	scanf("%s", username);
	fprintf(log,"%s\n", username);
	strcpy(username, BufferingSpaces(username, 16));
	strcpy(new->username, username);
	printf("enter password please :\n");
	fprintf(log,"enter password please :\n");
	scanf("%s", pw);
	fprintf(log, "%s\n", pw);
	strcpy(pw, BufferingSpaces(pw, 16));
	strcpy(new->pw, pw);
	printf("enter level please :\n");
	fprintf(log,"enter level please :\n");
	scanf("%d", &lvl);
	fprintf(log, "%d\n", lvl);
	new->lvl = lvl;
	printf("enter fullname please :\n");
	fprintf(log,"enter fullname please :\n");
	gets(fullname);
	scanf("%[^\n]s", fullname);
	fprintf(log, "%s\n", fullname);
	strcpy(fullname, BufferingSpaces(fullname, 21));
	strcpy(new->fullname, fullname);
	return new;
}

user* removeuser(user* head)// must return head if the user removed the first user in the list
{
	user* t = head;
	user* next;
	user* prev;
	int k = 0;
	char username[16];
	FILE* log = fopen(LOG_FILE, "a");
	printf("Enter the username you want to delete\n");
	fprintf(log,"Enter the username you want to delete\n");
	scanf("%s", username);
	fprintf(log,"%s", username);
	strcpy(username, BufferingSpaces(username, 16));
	while (t != NULL)
	{
		if (t->username[k] == username[k])
		{
			k++;
			if (k == 15)
				break;
		}
		else t = t->next;
	}
	if (t == NULL)
	{
		printf("wrong username try again \n");
		fprintf(log,"wrong username try again \n");
		fclose(log);
		return head;
	}
	if (t->next == NULL)
	{
		prev = t->prev;
		prev->next = NULL;
		free(t);
		fclose(log);
		return head;
	}
	else
	{
		if (t->prev == NULL)
		{
			next = t->next;
			next->prev = NULL;
			free(t);
			fclose(log);
			return next;//this node is new head
		}
		else
		{
			next = t->next;
			prev = t->prev;
			next->prev = prev;
			prev->next = next;
			free(t);
			fclose(log);
			return head;
		}
	}
}

user* updateuser(user* head)
{
	int a, i, k = 0; // a is for choise by the user what to update.
	char username[16];
	char pw[16];
	int lvl;
	char fullname[21];
	user* temp = head;
	FILE* log = fopen(LOG_FILE, "a");
	printf("Enter the username you want to update:\n");
	fprintf(log,"Enter the username you want to update:\n");
	scanf("%s", username);
	fprintf(log,"%s\n", username);
	strcpy(username, BufferingSpaces(username, 16));
	while (temp != NULL)
	{
		if (temp->username[k] == username[k])
		{
			k++;
			if (k == 15)
				break;
		}
		else temp = temp->next;
	}
	while (1)
	{
		printf("what you want to update in this user :\n1-username\n2-passward\n3-level\n4-fullname\n5-exit from update\n");
		fprintf(log,"what you want to update in this user :\n1-username\n2-passward\n3-level\n4-fullname\n5-exit from update\n");
		scanf("%d", &a);
		fprintf(log,"%d\n", a);
		switch (a)
		{
		case(1):
		{
			printf("Enter the new username:\n");
			fprintf(log,"Enter the new username:\n");
			scanf("%s", username);
			fprintf(log, "%s\n", username);
			strcpy(username, BufferingSpaces(username, 16));
			for (i = 0; i < 15; i++)
				temp->username[i] = username[i];
			break;
		}
		case(2):
		{
			printf("Enter new Paswword please(Maximum 15 characters) :\n");
			fprintf(log,"Enter new Paswword please(Maximum 15 characters) :\n");
			scanf("%s", pw);
			fprintf(log, "%s\n", pw);
			strcpy(pw, BufferingSpaces(pw, 16));
			for (i = 0; i < 15; i++)
				temp->pw[i] = pw[i];
			break;
		}
		case(3):
		{
			printf("Enter new level :\n");
			fprintf(log,"Enter new level :\n");
			scanf("%d", &lvl);
			fprintf(log, "%d\n", lvl);
			temp->lvl = lvl;
			break;
		}
		case(4):
		{
			printf("enter new full name please :\n");
			fprintf(log,"enter new full name please :\n");
			gets(fullname);
			scanf("%[^\n]s", fullname);
			printf(log, "%s\n", fullname);
			strcpy(fullname, BufferingSpaces(fullname, 21));
			for (i = 0; i < 20; i++)
				temp->fullname[i] = fullname[i];
			break;
		}
		case(5):
		{
			fclose(log);
			return head;
		}
		}
	}
}

void print_users(user* head)
{
	user* temp = head;
	FILE* log = fopen(LOG_FILE, "a");
	printf("Username       Password       L Fullname            \n");
	fprintf(log,"Username       Password       L Fullname            \n");
	while (temp !=NULL)
	{
		printf("%s%s%d %s\n", temp->username, temp->pw, temp->lvl, temp->fullname);
		fprintf(log,"%s%s%d %s\n", temp->username, temp->pw, temp->lvl, temp->fullname);
		temp = temp->next;
	}
	fclose(log);
}

void userlevelone(parit* head, FILE* path_pritim)
{
	int a;//a is choose of user what he want to do 
	parit *t = head;
	parit* temp;
	char temp_price[12];
	char* test = ' ';
	FILE* pritim,*log;
	while (1)
	{
		log = fopen(LOG_FILE, "a");
		printf("hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-show stock\n4-close program\n");
		fprintf(log,"hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-show stock\n4-close program\n");
		scanf("%d", &a);
		fprintf(log, "%d\n",a);
		fclose(log);
		switch (a)
		{
			case(1):
				head = search_by_choice(t);
				t = head;
				break;
		
			case(2):
				t=makenewparit(head);
				addparit(head, t);
				sort_pritim_byID(head);
				t = head;
				break;

			case(3):
				print_pritim(head);
				break;

			case(4):
				temp = head;
				pritim = fopen(path_pritim, "w");
				fprintf(pritim, "ID   Model     Part           Avaliability   Price      Date      \n");
				while (temp != NULL)
				{
					if (temp->availabilty == true)
					{
						strcpy(temp_price, price_double_to_str(temp->price));
						fprintf(pritim, "%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
					}
					else
					{
						strcpy(temp_price, price_double_to_str(temp->price));
						fprintf(pritim, "%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
					}
					temp = temp->next;
				}
				fclose(pritim);
				free_linked_pritim(head);
				return;
		}
	}
}

void userleveltwo(parit* head_pritim, FILE* path_pritim)
{
	int a,i;
	parit* t = head_pritim;
	parit* temp;
	char temp_price[12];
	FILE* pritim,*log;
	while (1)
	{
		log = fopen(LOG_FILE, "a");
		printf("hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-update item\n4-remove item\n5-show stock\n6-close program\n");
		fprintf(log,"hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-update item\n4-remove item\n5-show stock\n6-close program\n");
		scanf("%d", &a);
		fprintf(log, "%d\n", a);
		fclose(log);
		switch (a)
		{
		case(1):
			head_pritim = search_by_choice(t);
			t = head_pritim;
			log = fopen(LOG_FILE, "a");
			printf("you want to update one from this items ?\n1-Yes\n0-No\n");
			fprintf(log,"you want to update one from this items ?\n1-Yes\n0-No\n");
			scanf("%d", &i);
			fprintf(log, "%d\n", i);
			fclose(log);
			if (i == 1)
			{
				updateparit(t);
				sort_pritim_byID(head_pritim);
			}
			break;
		case(2):
			t = makenewparit(t);
			addparit(head_pritim, t);
			sort_pritim_byID(head_pritim);
			t = head_pritim;
			break;
		case(3):
			updateparit(head_pritim);
			sort_pritim_byID(head_pritim);
			break;
		case(4):
			head_pritim=removeparit(head_pritim);
			break;
		case(5):
			print_pritim(head_pritim);
			break;
		case(6):
			temp = head_pritim;
			pritim = fopen(path_pritim, "w");
			fprintf(pritim, "ID   Model     Part           Avaliability   Price      Date      \n");
			while (temp != NULL)
			{
				if (temp->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(temp->price));
					fprintf(pritim, "%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(temp->price));
					fprintf(pritim, "%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				}
				temp = temp->next;
			}
			fclose(pritim);
			free_linked_pritim(head_pritim);
			return;
		}
	}
}

void userlevelthree(parit* head_pritim, user* head_users,FILE* path_users,FILE* path_pritim)
{
	int a,i;
	parit* t = head_pritim;
	user* h;
	user* temp1;
	parit* temp;
	char temp_price[12];
	FILE* pritim,*users,*log;
	while (1)
	{
		log = fopen(LOG_FILE, "a");
		printf("hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-update item\n4-remove item\n5-show stock\n6-show users list\n7-update user\n8-remove user\n9-add user\n10-close program\n");
		fprintf(log,"hello, please choose what you want to do :\n1-search parit\n2-Add new item to stock\n3-update item\n4-remove item\n5-show stock\n6-show users list\n7-update user\n8-remove user\n9-add user\n10-close program\n");
		scanf("%d", &a);
		fprintf(log, "%d\n", a);
		fclose(log);
		switch (a)
		{
		case(1):
			head_pritim=search_by_choice(t);
			t = head_pritim;
			log = fopen(LOG_FILE, "a");
			printf("you want to update one from this items ?\n1-Yes\n0-No\n");
			fprintf(log, "you want to update one from this items ?\n1-Yes\n0-No\n");
			scanf("%d", &i);
			fprintf(log, "%d\n", i);
			fclose(log);
			if (i == 1)
			{
				updateparit(t);
				sort_pritim_byID(head_pritim);
			}
			break;
		case(2):
			t = makenewparit(t);
			addparit(head_pritim, t);
			sort_pritim_byID(head_pritim);
			t = head_pritim;
			break;
		case(3):
			updateparit(head_pritim);
			sort_pritim_byID(head_pritim);
			break;
		case(4):
			head_pritim =removeparit(head_pritim);
			break;
		case(5):
			print_pritim(head_pritim);
			break;
		case(6):
			print_users(head_users);
			break;
		case(7):
			head_users = updateuser(head_users);
			break;
		case(8):
			head_users = removeuser(head_users);
			break;
		case(9):
			h = makenewuser();
			adduser(head_users, h);
			break;
		case(10):
			temp = head_pritim;
			pritim = fopen(path_pritim, "w");
			fprintf(pritim, "ID   Model     Part           Avaliability   Price      Date      \n");
			while (temp != NULL)
			{
				if (temp->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(temp->price));
					fprintf(pritim, "%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(temp->price));
					fprintf(pritim, "%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				}
				temp = temp->next;
			}
			fclose(pritim);
			free_linked_pritim(head_pritim);
			users = fopen(path_users, "w");
			temp1 = head_users;
			fprintf(users,"Username       Password       L Fullname            \n");
			while (temp1 != NULL)
			{
				fprintf(users, "%s%s%d %s\n", temp1->username, temp1->pw, temp1->lvl, temp1->fullname);
				temp1 = temp1->next;
			}
			fclose(users);
			free_linked_users(head_users);
			return;
		}
	}
}


//parit functions
void addparit(parit* head, parit* new)
{
	parit* t = head;
	parit* newhead = head;
	while (t->next != NULL)
		t = t->next;
	t->next = new;
	new->prev = t;
	new->next = NULL;
}

parit* makenewparit(parit* head)
{
	parit* new = (parit*)malloc(sizeof(parit));
	parit* newhead = head;
	FILE* log = fopen(LOG_FILE, "a");
	char text1[11];
	char text2[16];
	int availabilty;
	char date[11];
	printf("Enter id :\n");
	fprintf(log,"Enter id :\n");
	scanf("%d", &new->id);
	fprintf(log,"%d\n", new->id);
	printf("Enter model :\n");
	fprintf(log, "Enter model :\n");
	gets(text1);
	scanf("%[^\n]*c", text1);
	fprintf(log, "%s\n",text1);
	strcpy(text1, BufferingSpaces(text1, 11));
	strcpy(new->text1, text1);
	printf("Enter Part :\n");
	fprintf(log,"Enter Part :\n");
	gets(text2);
	scanf("%[^\n]*c", text2);
	fprintf(log, "%s\n", text2);
	strcpy(text2, BufferingSpaces(text2, 16));
	strcpy(new->text2, text2);
	printf("Enter price :\n");
	fprintf(log,"Enter price :\n");
	scanf("%lf", &new->price);
	fprintf(log,"%lf\n", new->price);
	printf("Enter availabilty:\n1-availabilty\n0-not availabilty\n");
	fprintf(log,"Enter availabilty:\n1-availabilty\n0-not availabilty\n");
	scanf("%d", &availabilty);
	fprintf(log,"%d\n", availabilty);
	if (availabilty == 1)
		new->availabilty = true;
	else new->availabilty = false;
	printf("Enter date like that dd/mm/yyyy\n");
	fprintf(log,"Enter date like that dd/mm/yyyy\n");
	scanf("%s", date);
	fprintf(log, "%s\n", date);
	strcpy(date, BufferingSpaces(date, 11));
	strcpy(new->date, date);
	new->next = NULL;
	new->prev = NULL;
	fclose(log);
	return new;
}

parit* removeparit(parit* head)
{
	parit* prev;
	parit* next;
	parit* del = head;
	FILE* log = fopen(LOG_FILE, "a");
	int id;
	printf("please enter id of parit you want to remove:\n");
	fprintf(log,"please enter id of parit you want to remove:\n");
	scanf("%d", &id);
	fprintf(log, "%d\n", id);
	while (del != NULL)
	{
		if (del->id == id)
			break;
		else
			del = del->next;
	}
	if (del->prev == NULL)//if head
	{
		next = del->next;
		next->prev = NULL;
		head = next;//its new head
		free(del);
		fclose(log);
		return head;
	}
	else
	{
		if (del->next == NULL)//last
		{
			prev = del->prev;
			prev->next = NULL;
			free(del);
			fclose(log);
			return head;
		}
		else
		{
			prev = del->prev;
			next = del->next;
			prev->next = next;
			next->prev = prev;
			free(del);
			fclose(log);
			return head;
		}
	}
}

void updateparit(parit* head)
{
	char text1[11];
	char text2[16];
	char date[11];
	parit* t = head;
	FILE* log = fopen(LOG_FILE, "a");
	int a, bol;
	printf("enter the item id you want to change:\n");
	fprintf(log,"enter the item id you want to change:\n");
	scanf("%d", &a);
	fprintf(log, "%d\n",a);
	while (t != NULL)
	{
		if (a == t->id)
			break;
		else t = t->next;
	}
	if (t == NULL)
	{
		printf("Wrong id try again\n");
		fprintf(log,"Wrong id try again\n");
		return;
	}
	while (1)
	{
		printf("please choose what you want to change :\n1-id\n2-model\n3-part\n4-price\n5-availavilty\n6-date\n7-close update\n");
		fprintf(log,"please choose what you want to change :\n1-id\n2-model\n3-part\n4-price\n5-availavilty\n6-date\n7-close update\n");
		scanf("%d", &a);
		fprintf(log, "%d\n", a);
		switch (a)
		{
		case(1):
		{
			printf("enter new id:\n");
			fprintf(log,"enter new id:\n");
			scanf("%d", &t->id);
			fprintf(log, "%d\n", t->id);
			break;
		}
		case(2):
		{
			printf("enter new Model:\n");
			fprintf(log,"enter new Model:\n");
			gets(text1);
			scanf("%[^\n]*c", text1);
			fprintf(log, "%s\n", text1);
			strcpy(text1, BufferingSpaces(text1, 11));
			strcpy(t->text1, text1);
			break;
		}
		case(3):
		{
			printf("enter new Part:\n");
			fprintf(log,"enter new Part:\n");
			gets(text2);
			scanf("%[^\n]*c", text2);
			fprintf(log, "%s\n", text2);
			strcpy(text2, BufferingSpaces(text2, 16));
			strcpy(t->text2, text2);
			break;
		}
		case(4):
		{
			printf("Enter new price :\n");
			fprintf(log,"Enter new price :\n");
			scanf("%lf", &t->price);
			break;
		}
		case(5):
		{
			printf("To update availabilty choose : \n1-availabilty \n0-not availabilty\n");
			fprintf(log,"To update availabilty choose : \n1-availabilty \n0-not availabilty\n");
			scanf("%d", &bol);
			fprintf(log, "%d\n", bol);
			if (bol == 1)
				t->availabilty = true;
			else
				t->availabilty = false;
			break;
		}
		case(6):
		{
			printf("Enter new date like that : dd/mm/yyyy\n");
			fprintf(log,"Enter new date like that : dd/mm/yyyy\n");
			scanf("%s", date);
			fprintf(log, "%s\n", date);
			strcpy(date, BufferingSpaces(date, 11));
			strcpy(t->date, date);
			break;
		}
		case(7):
			fclose(log);
			return;
		}
	}
}

void print_pritim(parit* head)
{
	parit* temp = head;
	FILE* log = fopen(LOG_FILE, "a");
	char temp_price[12];
	printf("ID   Model     Part           Avaliability   Price      Date      \n");
	fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
	while (temp != NULL)
	{
		if (temp->availabilty == true)
		{
			strcpy(temp_price, price_double_to_str(temp->price));
			printf("%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2,temp_price,temp->date);
			fprintf(log,"%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
		}
		else
		{
			strcpy(temp_price, price_double_to_str(temp->price));
			printf("%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
			fprintf(log,"%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
		}
		temp = temp->next;
	}
	fclose(log);
}

void search_parit_id(parit* head)
{
	parit* temp_h = head, * index = head;//temp for not loosing the start of list, index is the id value 
	int temp_id, choice = 0;
	char temp_price[12];
	FILE* log = fopen(LOG_FILE, "a");
	printf("please enter a choice for the search by ID.\n1-the actual ID\n2-greater then the ID\n3-lower then the ID\n");
	fprintf(log,"please enter a choice for the search by ID.\n1-the actual ID\n2-greater then the ID\n3-lower then the ID\n");
	scanf("%d", &choice);
	fprintf(log, "%d\n", choice);
	printf("please enter the relevant id\n");
	fprintf(log,"please enter the relevant id\n");
	scanf("%d", &temp_id);
	fprintf(log, "%d\n", temp_id);
	switch (choice)
	{
	case(1):
	{
		while (index != NULL)
		{
			if (index->id == temp_id)
				break;
			index = index->next;
		}
		if (index == NULL)
		{
			printf("the selected id is not in the pritim list\n");
			fprintf(log,"the selected id is not in the pritim list\n");
		}
		else
		{
			strcpy(temp_price, price_double_to_str(index->price));
			if (index->availabilty == true)
			{
				printf("ID   Model     Part           Avaliability   Price      Date      \n");
				fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
				printf("%04d %s%strue           %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
				fprintf(log,"%04d %s%strue           %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
			}
			else
			{
				printf("ID   Model     Part           Avaliability   Price      Date      \n");
				fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
				printf("%04d %s%sfalse          %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
				fprintf(log,"%04d %s%sfalse          %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
			}
		}
		break;
	}
	case(2):
	{
		while (index != NULL)
		{
			if (index->id == temp_id)
				break;
			index = index->next;
		}
		if (index == NULL)
		{
			printf("the selected id is not in the pritim list\n");
			fprintf(log,"the selected id is not in the pritim list\n");
		}
		else
		{
			index = index->next;
			printf("ID   Model     Part           Avaliability   Price      Date      \n");
			fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
			while (index != NULL)
			{
				strcpy(temp_price, price_double_to_str(index->price));
				if (index->availabilty == true)
				{
					printf("%04d %s%strue           %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
					fprintf(log,"%04d %s%strue           %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
				}
				else
				{
					printf("%04d %s%sfalse          %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", index->id, index->text1, index->text2, temp_price, index->date);
				}
				index = index->next;
			}
		}
		break;
	}
	case(3):
	{
		while (index != NULL)
		{
			if (index->id == temp_id)
				break;
			index = index->next;
		}
		if (index == NULL)
		{
			printf("the selected id is not in the pritim list\n");
			fprintf(log,"the selected id is not in the pritim list\n");
		}
		else
		{
			printf("ID   Model     Part           Avaliability   Price      Date      \n");
			fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
			while (temp_h != index)
			{
				strcpy(temp_price, price_double_to_str(index->price));
				if (temp_h->availabilty == true)
				{
					printf("%04d %s%strue           %s%s\n", temp_h->id, temp_h->text1, temp_h->text2, temp_price, temp_h->date);
					fprintf(log, "%04d %s%strue           %s%s\n", temp_h->id, temp_h->text1, temp_h->text2, temp_price, temp_h->date);
				}
				else
				{
					printf("%04d %s%sfalse          %s%s\n", temp_h->id, temp_h->text1, temp_h->text2, temp_price, temp_h->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", temp_h->id, temp_h->text1, temp_h->text2, temp_price, temp_h->date);
				}
				temp_h = temp_h->next;
			}
		}
		break;
	}
	}
	fclose(log);
}

void search_parit_bool(parit* head)
{
	parit* temp = head;
	char temp_price[12];
	int choice=0;
	FILE* log = (LOG_FILE, "a");
	printf("please enter a choice for avaliability\n1-avaliable\n2-not avaliable\n");
	fprintf(log,"please enter a choice for avaliability\n1-avaliable\n2-not avaliable\n");
	scanf("%d", &choice);
	fprintf(log, "%d\n", choice);
	if (choice == 1)
	{
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (temp != NULL)
		{
			if (temp->availabilty == true)
			{
				strcpy(temp_price, price_double_to_str(temp->price));
				printf("%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				fprintf(log,"%04d %s%strue           %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
			}
			temp = temp->next;
		}
	}
	else
	{
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (temp != NULL)
		{
			if (temp->availabilty == false)
			{
				strcpy(temp_price, price_double_to_str(temp->price));
				printf("%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
				fprintf(log,"%04d %s%sfalse          %s%s\n", temp->id, temp->text1, temp->text2, temp_price, temp->date);
			}
			temp = temp->next;
		}
	}
	fclose(log);
}

void search_parit_by_text(parit* head)
{
	parit* t = head;
	int a, k = 0, c1 = 0, c2 = 0;
	char text1[11];
	char text2[16];
	char temp_price[12];
	FILE* log = fopen(LOG_FILE, "a");
	printf("please choose how you want to search:\n1-by Model only\n2-by Part only\n3-by Model and Part\n");
	fprintf(log,"please choose how you want to search:\n1-by Model only\n2-by Part only\n3-by Model and Part\n");
	scanf("%d", &a);
	fprintf(log, "%d\n", a);
	switch (a)
	{
	case(1):
		printf("enter Model please: \n");
		fprintf(log,"enter Model please: \n");
		gets(text1);
		scanf("%[^\n]*c", text1);
		fprintf(log, "%s\n", text1);
		strcpy(text1, BufferingSpaces(text1, 11));
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (t != NULL)
		{
			for (k = 0; k < 11; k++)
			{
				if (tolower(text1[k]) == tolower(t->text1[k]))
					c1++;
				else break;
			}
			if (c1 == 11)
			{
				if (t->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
			}
			c1 = 0;
			t = t->next;
		}
		break;
	case(2):
		printf("Enter Part (if you want to enter sides please write like that:\nrighr-R.\nleft L.\nrear-R.\nfront-F.\nfor example if you want to write door back left : door R.L.:\n");gets(text2);
		fprintf(log,"Enter Part (if you want to enter sides please write like that:\nrighr-R.\nleft L.\nrear-R.\nfront-F.\nfor example if you want to write door back left : door R.L.:\n");
		scanf("%[^\n]*c", text2);
		fprintf(log, "%s\n", text2);
		strcpy(text2, BufferingSpaces(text2, 16));
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (t != NULL)
		{
			for (k = 0; k < 16; k++)
			{
				if (tolower(text2[k]) == tolower(t->text2[k]))
					c2++;
				else break;
			}
			if (c2 == 16)
			{
				if (t->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
			}
			c2 = 0;
			t = t->next;
		}
		break;
	case(3):
		printf("enter Model please:\n");
		fprintf(log,"enter Model please:\n");
		gets(text1);
		scanf("%[^\n]*c", text1);
		fprintf(log, "%s\n", text1);
		strcpy(text1, BufferingSpaces(text1, 11));
		printf("Enter Part (if you want to enter sides please write like that:\nrighr-R.\nleft L.\nrear-R.\nfront-F.\nfor example if you want to write door back left : door R.L.:\n");
		fprintf(log,"Enter Part (if you want to enter sides please write like that:\nrighr-R.\nleft L.\nrear-R.\nfront-F.\nfor example if you want to write door back left : door R.L.:\n");
		gets(text2);
		scanf("%[^\n]*c", text2);
		fprintf(log, "%s\n", text2);
		strcpy(text2, BufferingSpaces(text2, 16));
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (t != NULL)
		{
			for (k = 0; k < 11; k++)
			{
				if (tolower(text1[k]) == tolower(t->text1[k]))
					c1++;
				else break;
			}
			if (c1 == 11)
			{
				for (k = 0; k < 16; k++)
				{
					if (tolower(text2[k]) == tolower(t->text2[k]))
						c2++;
					else break;
				}
				if (c2 == 16)
				{
					if (t->availabilty == true)
					{
						strcpy(temp_price, price_double_to_str(t->price));
						printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					}
					else
					{
						strcpy(temp_price, price_double_to_str(t->price));
						printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					}
				}
			}
			c1 = 0;
			c2 = 0;
			t = t->next;
		}
		break;
	}
	fclose(log);
}

void search_parit_by_date(parit* head)
{
	parit* t = head;
	int dayuser, monthuser, yearuser;
	int daylist, monthlist, yearlist;
	char day[2];
	char month[2];
	char year[4];
	char temp_price[12];
	FILE* log = fopen(LOG_FILE, "a");
	int a;
	printf("we start search by date , please enter this details :\n");
	printf("please enter day (for example for this date 06/06/1996 enter 06)\n");
	fprintf(log,"we start search by date , please enter this details :\n");
	fprintf(log,"please enter day (for example for this date 06/06/1996 enter 06)\n");
	scanf("%d", &dayuser);
	fprintf(log, "%d\n", dayuser);
	printf("please enter month (for example for this date 06/06/1996 enter 06)\n");
	fprintf(log,"please enter month (for example for this date 06/06/1996 enter 06)\n");
	scanf("%d", &monthuser);
	fprintf(log, "%d\n", monthuser);
	printf("please enter year (for example for this date 06/06/1996 enter 1996)\n");
	fprintf(log,"please enter year (for example for this date 06/06/1996 enter 1996)\n");
	scanf("%d", &yearuser);
	fprintf(log, "%d\n", yearuser);
	printf("please choose what you want to serach :\n1-For all item above this date\n2-For all item under this date\n");
	fprintf(log,"please choose what you want to serach :\n1-For all item above this date\n2-For all item under this date\n");
	scanf("%d", &a);
	fprintf(log, "%d\n", a);
	switch (a)
	{
	case(1):
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (t != NULL)
		{
			day[0] = t->date[0];
			day[1] = t->date[1];
			daylist = atoi(day);
			month[0] = t->date[3];
			month[1] = t->date[4];
			monthlist = atoi(month);
			year[0] = t->date[6];
			year[1] = t->date[7];
			year[2] = t->date[8];
			year[3] = t->date[9];
			yearlist = atoi(year);
			if (yearuser < yearlist)
			{
				if (t->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
			}
			else
			{
				if (yearuser == yearlist)
				{
					if (monthuser < monthlist)
					{
						if (t->availabilty == true)
						{
							strcpy(temp_price, price_double_to_str(t->price));
							printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
							fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						}
						else
						{
							strcpy(temp_price, price_double_to_str(t->price));
							printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
							fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						}
					}
					else
					{
						if (monthuser == monthlist)
						{
							if (dayuser < daylist)
							{
								if (t->availabilty == true)
								{
									strcpy(temp_price, price_double_to_str(t->price));
									printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
									fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
								}
								else
								{
									strcpy(temp_price, price_double_to_str(t->price));
									printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
									fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
								}
							}
						}
					}
				}
			}
			t = t->next;
		}
		break;
	case(2):
		printf("ID   Model     Part           Avaliability   Price      Date      \n");
		fprintf(log,"ID   Model     Part           Avaliability   Price      Date      \n");
		while (t != NULL)
		{
			day[0] = t->date[0];
			day[1] = t->date[1];
			daylist = atoi(day);
			month[0] = t->date[3];
			month[1] = t->date[4];
			monthlist = atoi(month);
			year[0] = t->date[6];
			year[1] = t->date[7];
			year[2] = t->date[8];
			year[3] = t->date[9];
			yearlist = atoi(year);
			if (yearuser > yearlist)
			{
				if (t->availabilty == true)
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
				else
				{
					strcpy(temp_price, price_double_to_str(t->price));
					printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
					fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
				}
			}
			else
			{
				if (yearuser == yearlist)
				{
					if (monthuser > monthlist)
					{
						if (t->availabilty == true)
						{
							strcpy(temp_price, price_double_to_str(t->price));
							printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
							fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						}
						else
						{
							strcpy(temp_price, price_double_to_str(t->price));
							printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
							fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
						}
					}
					else
					{
						if (monthuser == monthlist)
						{
							if (dayuser > daylist)
							{
								if (t->availabilty == true)
								{
									strcpy(temp_price, price_double_to_str(t->price));
									printf("%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
									fprintf(log,"%04d %s%strue           %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
								}
								else
								{
									strcpy(temp_price, price_double_to_str(t->price));
									printf("%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
									fprintf(log,"%04d %s%sfalse          %s%s\n", t->id, t->text1, t->text2, temp_price, t->date);
								}
							}
						}
					}
				}
			}
			t = t->next;
		}
		break;
	}
	fclose(log);
}

parit* search_by_choice(parit* head)//need to check level before editing
{
	int choice;
	FILE* log = fopen(LOG_FILE, "a");
	printf("Search menu:\n");
	fprintf(log,"Search menu:\n");
	printf("please enter a choice for the search.\n1-by Model/Part or both\n2-by ID\n3-by avaliability\n4-by Date\n");
	fprintf(log,"please enter a choice for the search.\n1-by Model/Part or both\n2-by ID\n3-by avaliability\n4-by Date\n");
	scanf("%d", &choice);
	fprintf(log, "%d\n", choice);
	fclose(log);//stop add log
	switch (choice)
	{
	case(1):
		search_parit_by_text(head);
		break;
	case(2):
	{
		search_parit_id(head);
		break;
	}
	case(3):
	{
		search_parit_bool(head);
		break;
	}
	case(4):
		search_parit_by_date(head);
		break;
	}
	return head;

}


//main
void main(int argc,char* argv[])
{
	user* head_users;
	parit* head_pritim;
	int current_lvl;
	FILE* log = fopen(LOG_FILE, "w");
	fclose(log);
	head_users = import_users_to_list(argv[1]);
	head_pritim = import_pritim_to_list(argv[2]);

	if (head_pritim == NULL)
	{
		log = fopen(LOG_FILE, "a");
		printf("Missing pritim file.\n");
		fprintf(log,"Missing pritim file.\n");
		fclose(log);
		return;
	}
	current_lvl = checkid(head_users);
	switch (current_lvl)
	{
	case(1):
		free_linked_users(head_users);
		userlevelone(head_pritim, argv[2]);
		break;
	case(2):
		free_linked_users(head_users);
		userleveltwo(head_pritim, argv[2]);
		break;
	case(3):
		userlevelthree(head_pritim, head_users, argv[1], argv[2]);
		break;
	}
}
