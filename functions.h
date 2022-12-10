//Daniel Abramov - 204621627
//Sahar Biton - 316992392


#include <stdbool.h>

//constants
#define LOG_FILE "log.txt"

//structs
typedef struct
{
	char username[16];
	char pw[16];
	int lvl;
	char fullname[21];
	struct user* next;
	struct user* prev;
	
}	user;
typedef struct
{
	int id;//5 letters in text
	char text1[11];	//Model, 10 letters in text +1 for \0
	char text2[16]; // Part, 15 letters in text +1 for \0
	double price; // 11 letters, 5 before '.' and 2 after in text
	bool availabilty;// 15 letter in text 
	char date[11];//10 letters in text +1 for \0
	struct parit* next;
	struct parit* prev;

}	parit;

//helpfull function 
user* makeuser(char username[], char pw[], int lvl, char fullname[]);//for importing users from file only.
user* import_users_to_list(FILE* path);
parit* makeparit(int id, char text1[], char text2[], double price, bool availabilty, char date[]);
bool check_bool_value(char str);
parit* import_pritim_to_list(FILE* path);
char* BufferingSpaces(char org[], int len);
void free_linked_pritim(parit* head_p);
void free_linked_users(user* head_u);
void sort_pritim_byID(parit* head);
char* price_double_to_str(double price_d);

//main functions
void adduser(user* head, user* new);
int checkid(user* head);
user* makenewuser();//for lvl 3 insertion
user* removeuser(user* head);
user* updateuser(user* head);
void print_users(user* head);
void userlevelone(parit* head, FILE* path_pritim);
void userleveltwo(parit* head_pritim, FILE* path_pritim);
void userlevelthree(parit* head_pritim, user* head_users, FILE* path_users, FILE* path_pritim);

void addparit(parit* head, parit* new);
parit* makenewparit(parit* head);
parit* removeparit(parit* head);
void updateparit(parit* head);
void print_pritim(parit* head);
void search_parit_id(parit* head);
void search_parit_bool(parit* head);
void search_parit_by_date(parit* head);
void search_parit_by_text(parit* head);
parit* search_by_choice(parit* head);

