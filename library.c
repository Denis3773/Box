#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<locale.h>
#define N 100

struct taken{
	char book_ISBN[N];
	char tr_student[N];
	char date[N];
	struct taken *next;	
};

struct taken *add_taken(struct taken *head, char isbn[], char student[], char date[]){
	if (head == NULL){
		head = (struct taken *)malloc(sizeof(struct taken));
		strcpy(head->book_ISBN, isbn);
		strcpy(head->tr_student, student);
		strcpy(head->date, date);
		head->next = NULL;
	}	
	else{
		head->next = add_taken(head->next, isbn, student, date);
	}
	return head;
}

struct book{
	char ISBN[N];
	char author[N];
	char title[N];
	char quantity[3];
	char available[3];
	struct book *next;
};

struct book *add(struct book *head, char isbn[], char author[], char title[], char quantity[], char available[]){
	if (head == NULL){
		head = (struct book *)malloc(sizeof(struct book));
		strcpy(head->ISBN, isbn);
		strcpy(head->author, author);
		strcpy(head->title, title);
		strcpy(head->quantity, quantity);
		strcpy(head->available, available);
		head->next = NULL;
	}
	else{
		head->next = add(head->next, isbn, author, title, quantity, available);
	}
	return head;
};

struct taken *back_book(struct taken *head, char isbn[], char student[]){
	int k=0;
	if (head == NULL){
		return head;
	}
	if ( ( strcmp(isbn, head->book_ISBN) == 0 ) && ( strcmp(student, head->tr_student) == 0 ) ){
		if(head->next == NULL){
			head = NULL;
			return head;
		}
		else{
			head = head->next;
			k=1;
		}
	}
	if (k==1){
		head = back_book(head, isbn, student);
	}
	else{
		head->next = back_book(head->next, isbn, student);
	}
	return head;
}

int read_isbn_books(char input_isbn[]){
	FILE *books;
	books = fopen("books.csv", "r");	
	int row=0;
	int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;]s", ISBN);
			fscanf(books,"%[^;]s", author);
			fscanf(books,"%[^;]s", title);
			fscanf(books,"%[^;]s", number);
			fscanf(books,"%[^\n]s", available);
			if ((strcmp(ISBN, input_isbn)) == 0){
				return 1;
			}
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		return 0;
}
		


void add_book(){
	
	int i;
	char ISBN[9];
	printf("Book's ISBN:");
	scanf("%s", ISBN);
	getchar();
	for(i=0; i<10; i++){
		if((ISBN[i] < '0') || (ISBN[i] > '9')){
			printf("ISBN is invalid...\n");
			return;
		}
	}
	int j;
	j = read_isbn_books(ISBN);
	if (j==1){
		printf("ISBN is already exist...\n");
		return;
	}
	FILE *books;
	books = fopen("books.csv","a");
	fputs(ISBN, books);
	fputs(";", books);
	char author[N];
	printf("Book's author:");
	scanf("%[^\n]", author);
	getchar();
	fputs(author, books);
	fputs(";", books);
	char title[N];
	printf("Book's title:");
	scanf("%[^\n]", title);
	fputs(title, books);
	fputs(";", books);
	char num[3];
	printf("Quantity:");	
	scanf("%s", num);
	fputs(num, books);
	fputs(";", books);
	fputs(num, books);
	fputs("\n", books);
	fclose(books);
	printf("The book has been added...\n");
}


struct book *delete_isbn(struct book *head, char isbn[]){
	int k=0;
	if (head == NULL){
		return head;
	}
	if (strcmp(isbn, head->ISBN) == 0){
		if(head->next == NULL){
			head == NULL;
			return head;
		}
		else{
			head = head->next;
			k=1;
		}
	}
	if (k==1){
		head = delete_isbn(head, isbn);
	}
	else{
		head->next = delete_isbn(head->next, isbn);
	}
	return head;
}

void delete_book(){
	FILE *books;
	FILE *check;
	int brow=0;	
	int row=0;
	int i;
	char ISBN[9];
	char author[N];
	char title[N]; 
	char number[3];
	char available[3];
	struct book *head; 
	head = NULL;
	char c_ISBN[9];
	char c_trans[6];
	char date[N];
	printf("Book's ISBN:");
	char del_isbn[9];
	scanf("%s", del_isbn);
		check = fopen("student_books.csv", "r");
			while(!feof(check)){
				if( (getc(check)) == '\n' ){
					++brow;
				}
			}
		fclose(check);
		check = fopen("student_books.csv", "r");
			for(i=0; i<brow; i++){
				fscanf(check,"%[^;];%[^;];%[^\n]\n", c_ISBN, c_trans, date);
				if (strcmp(c_ISBN, del_isbn) == 0){
					printf("Students have this book...\n");
					return;
				}
			}
		fclose(check);
	books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		head = delete_isbn(head, del_isbn);
		books = fopen("books.csv", "w");
	while(head!=NULL){
		fputs(head->ISBN, books);
		fputs(";", books);
		fputs(head->author, books);
		fputs(";", books);
		fputs(head->title, books);
		fputs(";", books);	
		fputs(head->quantity, books);
		fputs(";", books);
		fputs(head->available, books);
		fputs("\n", books);
		head = head->next;
	}
	fclose(books);
	printf("The book has been deleted...\n");
}

void backup(){
		FILE *books;
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		FILE *backup;
		long long int s_time;
		struct tm *l_time;
		char name[N];
		s_time = time (NULL);
		l_time = localtime (&s_time);
		strftime (name, N, "books_%Y.%m.%d_%H-%M-%S.csv", l_time);	
		backup = fopen(name, "w");
		if (backup == NULL){
			printf("Failure...\n");
			return;
		}
		while(head!=NULL){
			fputs(head->ISBN, books);
			fputs(";", books);
			fputs(head->author, books);
			fputs(";", books);
			fputs(head->title, books);
			fputs(";", books);	
			fputs(head->quantity, books);
			fputs(";", books);
			fputs(head->available, books);
			fputs("\n", books);
			head = head->next;
		}
		fclose(backup);
		printf("Successfully completed...\n");
}

void recovery(){
		char name[N];
		FILE *recovery;
		printf("Example: books_1990.01.01_12-00-00.csv\n");
		printf("Name of file: ");
		scanf("%s", name);
		recovery = fopen(name, "r");
		if (recovery == NULL){
			printf("File is not found...\n");
			return;
		}
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		while(!feof(recovery)){
			if((getc(recovery)) == '\n'){
				++row;
			}
		}
		fclose(recovery);
		recovery = fopen(name, "r");
		for(i=0; i < row; i++){	
			fscanf(recovery,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(recovery);
		recovery = fopen("books.csv", "w");
		while(head!=NULL){
			fputs(head->ISBN, recovery);
			fputs(";", recovery);
			fputs(head->author, recovery);
			fputs(";", recovery);
			fputs(head->title, recovery);
			fputs(";", recovery);	
			fputs(head->quantity, recovery);
			fputs(";", recovery);
			fputs(head->available, recovery);
			fputs("\n", recovery);
			head = head->next;
		}
		fclose(recovery);
		printf("Successfully completed...\n");
}

void search_author(){
		FILE *books;
	books = fopen("books.csv", "r");	
	int row=0;
	int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		printf("Author's name or pseudonym: ");
		char human[N];
		scanf("%s", human);
		int j=1;
		printf ("This author's books:\n");
		printf ("----------------------------------------------------------------------------------------------\n");
		while(head!=NULL){
			if (strcmp(human, head->author) == 0){
				printf ("| Book %d | %s | %s | %s | %s |\n", j, head->ISBN, head->title, head->quantity, head->available);	
				++j;
				printf ("----------------------------------------------------------------------------------------------\n");
			}
			head = head->next;
		}
		if(j==1){
			printf("No books of this author...\n");
			printf ("----------------------------------------------------------------------------------------------\n");
		}
}

void show_all_books(){
		FILE *books;
	books = fopen("books.csv", "r");	
	int row=0;
	int i,k;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		char all[N][N];
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^\n]\n", all[i]);
		}
		fclose(books);
		for (i=0; i<(row-1); i++){
			for (k=(row-1); k>i; k--){
				if (strcmp(all[k-1], all[k]) > 0){
					char t[N];
					strcpy(t, all[k-1]);
					strcpy(all[k-1], all[k]);
					strcpy(all[k], t);
				}
			}
		}
		books = fopen("books.csv", "w");
		for(i=0; i<row; i++){
			fputs(all[i], books);
			fputs("\n", books);
		}
		fclose(books);
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		int j=1;
		printf("----------------------------------------------------------------------------------------------\n");
	while(head!=NULL){
		printf("| Book %d | %s | %s | %s | %s | %s |\n", j, head->ISBN, head->author, head->title, head->quantity, head->available);
		printf("----------------------------------------------------------------------------------------------\n");
		++j;
		head = head->next;
	}
}

void show_one_book(){
	FILE *books;
	books = fopen("books.csv", "r");	
	int row=0;
	int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		char find_isbn[9];
		printf("Book's ISBN: ");
		scanf("%s", find_isbn);
		books = fopen("books.csv", "r");
		int j = 1;
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			if (strcmp(find_isbn, ISBN) == 0){
				j = 0;
				printf("----------------------------------------------------------------------------------------------\n");
				printf("| %s | %s | %s | %s | %s |\n", ISBN, author, title, number, available);
				printf("----------------------------------------------------------------------------------------------\n");
			}
			}
		fclose(books);
		if(j){
			printf("----------------------------------------------------------------------------------------------\n");
			printf("The book is not found...\n");
			printf("----------------------------------------------------------------------------------------------\n");
			return;
		}
		FILE *check;
	int brow=0;
	char c_ISBN[9];
	char c_trans[5];
	char date[N];
		check = fopen("student_books.csv", "r");
		while(!feof(check)){
				if( (getc(check)) == '\n' ){
					++brow;
				}
			}
		fclose(check);
		int k = 1;
		printf("Student having the book:\n");
		check = fopen("student_books.csv", "r");
			for(i=0; i<brow; i++){
				fscanf(check,"%[^;];%[^;];%[^\n]\n", c_ISBN, c_trans, date);
				if (strcmp(c_ISBN, find_isbn) == 0){
					FILE *stud;
					int crow=0;
					char trans[5];
					char surname[N];
					char name[N];
					char patronymic[N];
					char faculty[N];
					char speciality[N];
					stud = fopen("students.csv", "r");
					while(!feof(stud)){
						if((getc(stud)) == '\n' ){
							++crow;
						}
					}
					fclose(stud);
					stud = fopen("students.csv", "r");
					int r;
					for(r=0; r < crow; r++){
						fscanf(stud, "%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", trans, surname, name, patronymic, faculty, speciality);
						if(strcmp(c_trans, trans) == 0){
							k = 0;
							printf ("----------------------------------------------------------------------------------------------\n");
							printf ("| %s | %s | %s | %s | %s | %s | %s |\n", c_trans, date, surname, name, patronymic, faculty, speciality);
							printf ("----------------------------------------------------------------------------------------------\n");
						}
					}
					fclose(stud);
				}
			}
		fclose(check);
	if(k){
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Nobody have this book...\n");
		printf("----------------------------------------------------------------------------------------------\n");
	}
}

void change_data(){
		FILE *books;
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		char change[9];
		int j = 1;
		printf("Book's ISBN: ");
		scanf("%s", change);
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			if (strcmp(change, ISBN) == 0){
				j = 0;
				printf("New author: ");
				scanf("%s", author);
				printf("New title: ");
				scanf("%s", title);
				printf("New quantity: ");
				scanf("%s", number);
				strcpy(available, number);
			}
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		if (j){
			printf("The book is not exist...\n");
			return;
		}
		books = fopen("books.csv", "w");
		while(head!=NULL){
			fputs(head->ISBN, books);
			fputs(";", books);
			fputs(head->author, books);
			fputs(";", books);
			fputs(head->title, books);
			fputs(";", books);	
			fputs(head->quantity, books);
			fputs(";", books);
			fputs(head->available, books);
			fputs("\n", books);
			head = head->next;
		}
		fclose(books);
		printf("Successfully completed...\n");
}

void change_quantity(){
		FILE *books;
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		char change[9];
		int j = 1;
		printf("Book's ISBN: ");
		scanf("%s", change);
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			if (strcmp(change, ISBN) == 0){
				j = 0;
				int quant;
				int avail;
				int raz;
				quant = atoi(number);
				avail = atoi(available);
				raz = quant - avail;
				printf("New quantity: ");
				scanf("%s", number);
				int new_quant;
				int new_avail;
				new_quant = atoi(number);
				new_avail = new_quant - raz;
				printf("Available books: %d\n", new_avail);
				if (new_avail < 0){
					printf("Operation is impossible...\n");
					return;
				}
				itoa(new_avail, available, 10);
			}
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		if (j){
			printf("The book is not exist...\n");
			return;
		}
		books = fopen("books.csv", "w");
		while(head!=NULL){
			fputs(head->ISBN, books);
			fputs(";", books);
			fputs(head->author, books);
			fputs(";", books);
			fputs(head->title, books);
			fputs(";", books);	
			fputs(head->quantity, books);
			fputs(";", books);
			fputs(head->available, books);
			fputs("\n", books);
			head = head->next;
		}
		fclose(books);
		printf("Successfully completed...\n");
}

void give_book(){
		FILE *books;
		FILE *give;
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		char change[9];
		char trans[5];
		int j = 1;
		printf("Book's ISBN: ");
		scanf("%s", change);
		printf("Student's transcript number: ");
		scanf("%s", trans);
		int r;
		r = read_trans(trans);
		if (r == 0){
			printf("The student is not exist...");
			return;
		}
		books = fopen("books.csv", "r");
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			if (strcmp(change, ISBN) == 0){
				j = 0;
				int avail;
				avail = atoi(available);
				--avail;
				if (avail < 0){
					int brow = 0;
					int m;
					printf("Sorry... No books more...\n");
					printf("The nearest date of returning: ");
					char b_isbn[9];
					char b_trans[6];
					char min_day[]="31";
					char min_month[]="12";
					char min_year[]="4000";
					char day[2];
					char month[2];
					char year[4];
						give = fopen("student_books.csv", "r");
						while(!feof(give)){
							if((getc(give)) == '\n'){
								++brow;
						}
						}
						fclose(give);
						give = fopen("student_books.csv", "r");
						for(m = 0; m < brow; m++){
							fscanf(give,"%[^;];%[^;];%[^.].%[^.].%[^\n]\n", b_isbn, b_trans, day, month, year);
							if (strcmp(b_isbn, change) == 0){
								if ( (atoi(year)) < (atoi(min_year)) ){
									strcpy(min_year, year);
									strcpy(min_month, month);
									strcpy(min_day, day);
								}
								else if ( (atoi(month)) < (atoi(min_month)) ){
									strcpy(min_year, year);
									strcpy(min_month, month);
									strcpy(min_day, day);
								}
								else if ( (atoi(day)) < (atoi(min_day)) ){
									strcpy(min_year, year);
									strcpy(min_month, month);
									strcpy(min_day, day);
								}
							}
							
						}
						printf("%s.%s.%s\n", min_day, min_month, min_year);
						
						fclose(give);
						return;
				}
				printf("Books left: %d\n", avail);
				itoa(avail, available, 10);
			}
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		if (j){
			printf("The book is not exist...\n");
			return;
		}
		books = fopen("books.csv", "w");
		while(head!=NULL){
			fputs(head->ISBN, books);
			fputs(";", books);
			fputs(head->author, books);
			fputs(";", books);
			fputs(head->title, books);
			fputs(";", books);	
			fputs(head->quantity, books);
			fputs(";", books);
			fputs(head->available, books);
			fputs("\n", books);
			head = head->next;
		}
		fclose(books);
		printf("Example: 01.01.1900\n");
		printf("Date of returning: ");
		char date[N];
		scanf("%s", date);
		give = fopen("student_books.csv", "a");
			fputs(change, give);
			fputs(";", give);
			fputs(trans, give);
			fputs(";", give);
			fputs(date, give);
			fputs("\n", give);
		fclose(give);
		printf("Successfully completed...\n");
}

void take_book(){
		FILE *give;
		FILE *books;
		int row=0;
		int i;
		char ISBN[9];
		char author[N];
		char title[N]; 
		char number[3];
		char available[3];
		struct book *head; 
		head = NULL;
		books = fopen("books.csv","r");
		while(!feof(books)){
			if((getc(books)) == '\n'){
				++row;
			}
		}
		fclose(books);
		books = fopen("books.csv", "r");
		char change[9];
		char trans[5];
		int j = 1;
		printf("Book's ISBN: ");
		scanf("%s", change);
		printf("Student's transcript number: ");
		scanf("%s", trans);
		int r;
		r = read_trans(trans);
		if (r == 0){
			printf("The student is not exist...");
			return;
		}
		for(i=0; i < row; i++){	
			fscanf(books,"%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, number, available);
			if (strcmp(change, ISBN) == 0){
				j = 0;
				int quant;
				int avail;
				quant = atoi(number);
				avail = atoi(available);
				++avail;
				if (avail > quant){
					printf("Unaccounted book...\n");
					++quant;
					printf("New quantity: %d\n", quant);
					itoa(quant, number, 10);
				}
				printf("Books in the library now: %d\n", avail);
				itoa(avail, available, 10);
			}
			head = add(head, ISBN, author, title, number, available);
			}
		fclose(books);
		if (j){
			printf("The book is not exist...\n");
			return;
		}
		books = fopen("books.csv", "w");
		while(head!=NULL){
			fputs(head->ISBN, books);
			fputs(";", books);
			fputs(head->author, books);
			fputs(";", books);
			fputs(head->title, books);
			fputs(";", books);	
			fputs(head->quantity, books);
			fputs(";", books);
			fputs(head->available, books);
			fputs("\n", books);
			head = head->next;
		}
		fclose(books);
		int brow = 0;
		give = fopen("student_books.csv", "r");
		while(!feof(give)){
			if((getc(give)) == '\n'){
				++brow;
			}
		}
		fclose(give);
		char b_isbn[9];
		char b_trans[5];
		char date[N];
		int m;
		struct taken *t_head;
		t_head = NULL;
		give = fopen("student_books.csv", "r");
		for(m=0; m<brow; m++){
			fscanf(give,"%[^;];%[^;];%[^\n]\n", b_isbn, b_trans, date);
			t_head = add_taken(t_head, b_isbn, b_trans, date);
		}
		fclose(give);
		t_head = back_book(t_head, change, trans);
		give = fopen("student_books.csv", "w");
		while(t_head != NULL){
			fputs(t_head->book_ISBN, give);
			fputs(";", give);
			fputs(t_head->tr_student, give);
			fputs(";", give);
			fputs(t_head->date, give);
			fputs("\n", give);
			t_head = t_head->next;
		}
		fclose(give);
		printf("Successfully completed...\n");
}

//-----------------------------------------------------------------------

struct student{
	char transcript[N];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *next;
};

struct student *add_stud(struct student *head, char trans[], char sur[], char name[], char patro[], char fac[], char spec[]){
	if (head == NULL){
		head = (struct student *)malloc(sizeof(struct student));
		strcpy(head->transcript, trans);
		strcpy(head->surname, sur);
		strcpy(head->name, name);
		strcpy(head->patronymic, patro);
		strcpy(head->faculty, fac);
		strcpy(head->speciality, spec);
		head->next = NULL;
	}
	else{
		head->next = add_stud(head->next, trans, sur, name, patro, fac, spec);
	}
	return head;
};

int read_trans(char input_trans[]){
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *head;
	head = NULL;
	int i;
	int row = 0;
	FILE *stud;
	stud = fopen("students.csv", "r");
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		if ( strcmp(transcript, input_trans) == 0){
			return 1;
		} 
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	return 0;
}

void add_student(){
	FILE *stud;
	stud = fopen("students.csv", "a");
	char add_trans[5];
	printf("Student's transcript number: ");
	scanf("%s", add_trans);
	int i;
	for(i=0; i<6; i++){
		if( !( (add_trans[i] >= '0') && (add_trans[i] <= '9') ) && !( (add_trans[i] >= 'a') && (add_trans[i] <= 'z') ) && !( (add_trans[i] >= 'A') && (add_trans[i] <= 'Z') ) ){
			printf("Transcript number is invalid...\n");
			return;
		}
	}
	int j;
	j = read_trans(add_trans);
	if (j==1){
		printf("This number is already exist...\n");
		return;
	}
	fputs(add_trans, stud);
	fputs(";", stud);
	char add_sur[N];
		printf("Student's surname: ");
	scanf("%s", add_sur);
	fputs(add_sur, stud);
	fputs(";", stud);
		printf("Student's name: ");
	char add_name[N];
	scanf("%s", add_name);
	fputs(add_name, stud);
	fputs(";", stud);
		printf("Student's patronymic: ");
	char add_patro[N];
	scanf("%s", add_patro);
	fputs(add_patro, stud);
	fputs(";", stud);
		printf("Student's faculty: ");
	char add_fac[N];
	scanf("%s", add_fac);
	getchar();
	fputs(add_fac, stud);
	fputs(";", stud);
		printf("Student's speciality: ");
	char add_spec[N];
	scanf("%[^\n]", add_spec);
	fputs(add_spec, stud);
	fputs("\n", stud);
	fclose(stud);
	printf("The student added\n");	
}

struct student *del_stud(struct student *head, char input_trans[]){
	int k = 0;
	if (head == NULL){
		return head;
	}
	if ( strcmp(input_trans, head->transcript) == 0 ) {
		if(head->next == NULL){
			head = NULL;
			return head;
		}
		else{
			head = head->next;
			k = 1;
		}
	}
	if (k==1){
		head = del_stud(head, input_trans);
	}
	else{
		head->next = del_stud(head->next, input_trans);
	}
	return head;
};

void delete_student(){
	FILE *stud;
	stud = fopen("students.csv", "r");
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	FILE *check;
	struct student *head;
	head = NULL;
		printf("Student's transcript number: ");
	char delete_trans[5];
	scanf("%s", delete_trans);
	int i;
	int row = 0;
	int brow=0;
	char c_ISBN[9];
	char c_trans[5];
	char date[N];
		check = fopen("student_books.csv", "r");
		while(!feof(check)){
				if( (getc(check)) == '\n' ){
					++brow;
				}
			}
		fclose(check);
		check = fopen("student_books.csv", "r");
			for(i=0; i<brow; i++){
				fscanf(check,"%[^;];%[^;];%[^\n]\n", c_ISBN, c_trans, date);
				if (strcmp(c_trans, delete_trans) == 0){
					printf("This student have books...\n");
					return;
				}
			}
		fclose(check);
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	head = del_stud(head, delete_trans);
	stud = fopen("students.csv", "w");
	while (head!=NULL){
		fputs(head->transcript, stud);
		fputs(";", stud);
		fputs(head->surname, stud);
		fputs(";", stud);
		fputs(head->name, stud);
		fputs(";", stud);
		fputs(head->patronymic, stud);
		fputs(";", stud);
		fputs(head->faculty, stud);
		fputs(";", stud);
		fputs(head->speciality, stud);
		fputs("\n", stud);
		head = head->next;
	}
	fclose(stud);
	printf("The book has been deleted...\n");
}

void backup_stud(){
	long long int s_time;
	struct tm *l_time;
	char file_name[N];
	s_time = time (NULL);
	l_time = localtime (&s_time);
	strftime (file_name, N, "students_%Y.%m.%d_%H-%M-%S.csv", l_time);	
	FILE *stud;
	stud = fopen("students.csv", "r");
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *head;
	head = NULL;
	int i;
	int row = 0;
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	FILE *backup;
	backup = fopen(file_name, "w");
	if (backup == NULL){
		printf("Failure...\n");
		return;
	}
	while (head!=NULL){
		fputs(head->transcript, stud);
		fputs(";", stud);
		fputs(head->surname, stud);
		fputs(";", stud);
		fputs(head->name, stud);
		fputs(";", stud);
		fputs(head->patronymic, stud);
		fputs(";", stud);
		fputs(head->faculty, stud);
		fputs(";", stud);
		fputs(head->speciality, stud);
		fputs("\n", stud);
		head = head->next;
	}
	fclose(backup);
	printf("Successfully completed...\n");
}

void recovery_stud(){
	char file_name[N];
		printf("Example: students_1990.01.01_12-00-00.csv\n");
		printf("Name of file: ");
	scanf("%s", file_name);
	FILE *stud;
	stud = fopen(file_name, "r");
	if(stud == NULL){
		printf("File is not found...\n");
		return;
	}
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *head;
	head = NULL;
	int i;
	int row = 0;
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	stud = fopen(file_name, "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	FILE *recovery;
	recovery = fopen("students.csv", "w");
	if (recovery == NULL){
		printf("Failure...\n");
		return;
	}
	while (head!=NULL){
		fputs(head->transcript, stud);
		fputs(";", stud);
		fputs(head->surname, stud);
		fputs(";", stud);
		fputs(head->name, stud);
		fputs(";", stud);
		fputs(head->patronymic, stud);
		fputs(";", stud);
		fputs(head->faculty, stud);
		fputs(";", stud);
		fputs(head->speciality, stud);
		fputs("\n", stud);
		head = head->next;
	}
	fclose(recovery);
	printf("Successfully completed...\n");
}

void search_surname(){
	printf("Student's surname: ");
	char human[N];
	scanf("%s", human);
	FILE *stud;
	stud = fopen("students.csv", "r");
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *head;
	head = NULL;
	int i;
	int row = 0;
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	printf("Students with this surname:\n");
	printf ("----------------------------------------------------------------------------------------------\n");
	int j=1;
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		if (strcmp(surname, human) == 0){
			printf("| Student %d | %s | %s | %s | %s | %s |\n", j, transcript, name, patronymic, faculty, speciality);
			printf ("----------------------------------------------------------------------------------------------\n");
			++j;
		}
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	if (j==1){
		printf("No student with this surname...\n");
		printf ("----------------------------------------------------------------------------------------------\n");
		return;
	}
}

void change_student(){
	FILE *stud;
	stud = fopen("students.csv", "r");
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	struct student *head;
	head = NULL;
	int i;
	int row = 0;
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	char change[5];
	printf("Student's transcript number: ");
	scanf("%s", change);
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		if(strcmp(change, transcript) == 0){
			printf("New surname: ");
			scanf("%s", surname);
			printf("New name: ");
			scanf("%s", name);
			printf("New patronymic: ");
			scanf("%s", patronymic);
			printf("New faculty: ");
			scanf("%s", faculty);
			printf("New speciality: ");
			scanf("%s", speciality);
		}
		head = add_stud(head, transcript, surname, name, patronymic, faculty, speciality);
	}
	fclose(stud);
	stud = fopen("students.csv", "w");
	while (head!=NULL){
		fputs(head->transcript, stud);
		fputs(";", stud);
		fputs(head->surname, stud);
		fputs(";", stud);
		fputs(head->name, stud);
		fputs(";", stud);
		fputs(head->patronymic, stud);
		fputs(";", stud);
		fputs(head->faculty, stud);
		fputs(";", stud);
		fputs(head->speciality, stud);
		fputs("\n", stud);
		head = head->next;
	}
	fclose(stud);
	printf("Successfully completed...\n");
}

void show_student(){
	FILE *stud;
	stud = fopen("students.csv", "r");
	char transcript[5];
	char surname[N];
	char name[N];
	char patronymic[N];
	char faculty[N];
	char speciality[N];
	int i;
	int row = 0;
	while(!feof(stud)){
		if( (getc(stud)) == '\n' ){
			++row;
		}
	}
	fclose(stud);
	char find_student[5];
	printf("Student's transcript number: ");
	scanf("%s", find_student);
	int j = 1;
	stud = fopen("students.csv", "r");
	for (i=0; i<row; i++){
		fscanf(stud,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]\n", transcript, surname, name, patronymic, faculty, speciality);
		if(strcmp(find_student, transcript) == 0){
			printf ("----------------------------------------------------------------------------------------------\n");
			printf ("| %s | %s | %s | %s | %s | %s |\n", transcript, surname, name, patronymic, faculty, speciality);
			printf ("----------------------------------------------------------------------------------------------\n");
			j = 0;
		}
	}
	fclose(stud);
	if(j){
		printf ("----------------------------------------------------------------------------------------------\n");
		printf ("The student is not exist...\n");
		printf ("----------------------------------------------------------------------------------------------\n");
		return;
	}
	FILE *check;
	int brow=0;
	char c_ISBN[9];
	char c_trans[5];
	char date[N];
		check = fopen("student_books.csv", "r");
		while(!feof(check)){
				if( (getc(check)) == '\n' ){
					++brow;
				}
			}
		fclose(check);
		int k = 1;
		printf("Student's books:\n");
		check = fopen("student_books.csv", "r");
			for(i=0; i<brow; i++){
				fscanf(check,"%[^;];%[^;];%[^\n]\n", c_ISBN, c_trans, date);
				if (strcmp(c_trans, find_student) == 0){
					FILE *books;
					int crow = 0;
					char ISBN[9];
					char author[N];
					char title[N];
					char quantity[N];
					char available[N];
					books = fopen("books.csv", "r");
					while(!feof(books)){
						if( (getc(books)) == '\n' ){
							++crow;
						}
					}
					fclose(books);
					int r;
					books = fopen("books.csv", "r");	
					for(r=0; r<crow; r++){	
						fscanf(books, "%[^;];%[^;];%[^;];%[^;];%[^\n]\n", ISBN, author, title, quantity, available);
						if(strcmp(ISBN, c_ISBN) == 0){
							k = 0;
							printf ("----------------------------------------------------------------------------------------------\n");
							printf ("| %s | %s | %s | %s |\n", c_ISBN, author, title, date);
							printf ("----------------------------------------------------------------------------------------------\n");
						}
					}
				}
			}
		fclose(check);
	if(k){
		printf("----------------------------------------------------------------------------------------------\n");
		printf("Student have no books...\n");
		printf("----------------------------------------------------------------------------------------------\n");
	}
}

//----------------------------------------
struct users{
	char login[N];
	char password[N];
	char access_book[2];
	char access_student[2];
	struct users *next;
};

struct users *add_user(struct users *head, char log[], char pass[], char book[], char student[]){
	if (head == NULL){
		head = (struct users *)malloc(sizeof(struct users));
		strcpy(head->login, log);
		strcpy(head->password, pass);
		strcpy(head->access_book, book);
		strcpy(head->access_student, student);
		head = head->next;
	}
	else{
		head->next = add_user(head->next, log, pass, book, student);
	}
	return head;
}

int access(char* input_log, char* input_pass){
	int row=0;
	int i;
	char log[N];
	char pass[N];
	char book[2];
	char student[2];
	struct users *head;
	head = NULL;
	FILE *users;
	users = fopen("users.csv", "r");
	while(!feof(users)){
		if((getc(users)) == '\n'){
			++row;
		}
	}
	fclose(users);
	users = fopen("users.csv", "r");
	for(i=0; i < row; i++){	
		fscanf(users,"%[^;];%[^;];%[^;];%[^\n]\n", log, pass, book, student);
		if( (strcmp(input_log, log) == 0) && (strcmp(input_pass, pass)) == 0 ){
			if(book[0] == '1'){
				if(student[0] == '1'){
					printf("You have unlimited access...\n");
					return 3;
				}
				else{
					printf("You only have access to books...\n");
					return 1;
				}
			}
			if(student[0] == '1'){
				printf("You only have access to students...\n");
				return 2;
			}
		}
		head = add_user(head, log, pass, book, student);
	}
	fclose(users);
	return 0;
}

void main_menu_ad(){
	printf("+------------------------+\n");
	printf("|          Menu          |\n");
	printf("+------------------------+\n");
	printf("| 0 | Exit               |\n");
	printf("+------------------------+\n");
	printf("| 1 | Books menu         |\n");
	printf("+------------------------+\n");
	printf("| 2 | Students menu      |\n");
	printf("+------------------------+\n");
	int i;
		printf("Choose an action: ");
		scanf("%d", &i);
		while(i!=0){
		switch(i){
			case 0:
				exit(0);
			break;
			case 1:
				book_menu_ad();
			break;
			case 2:
				student_menu_ad();
			break;
			default:
				printf("Unknown operation\n");
		}
	}
}
void book_menu_ad(){
	printf("+-----------------------------------+\n");
	printf("|            Books menu             |\n");
	printf("+----+------------------------------+\n");
	printf("| 0  | Back to main menu            |\n");
	printf("+----+------------------------------+\n");
	printf("| 1  | Add the new book             |\n");
	printf("+----+------------------------------+\n");	
	printf("| 2  | Delete the book              |\n");
	printf("+----+------------------------------+\n");
	printf("| 3  | Backup copy                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 4  | Recovery                     |\n");
	printf("+----+------------------------------+\n");
	printf("| 5  | Search by author             |\n");
	printf("+----+------------------------------+\n");
	printf("| 6  | Show all books               |\n");
	printf("+----+------------------------------+\n");
	printf("| 7  | Show information about book  |\n");
	printf("+----+------------------------------+\n");
	printf("| 8  | Change information           |\n");
	printf("+----+------------------------------+\n");
	printf("| 9  | Change quantity of books     |\n");
	printf("+----+------------------------------+\n");
	printf("| 10 | Give a book                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 11 | Take a book                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 12 | Exit                         |\n");
	printf("+----+------------------------------+\n");
	int act;
	while(act!=12){
	printf("Choose an action: ");
	scanf ("%d", &act);
	switch(act){
		case 0:
			printf("You finished working with books...\n");
			main_menu_ad();
		case 1: 
			add_book();
		break;
		case 2:
			delete_book();
		break;
		case 3:
			backup();
		break;
		case 4:
			recovery();
		break;
		case 5:
			search_author();
		break;
		case 6:
			show_all_books();
		break;
		case 7:
			show_one_book();
		break;
		case 8:
			change_data();
		break;
		case 9:
			change_quantity();
		break;
		case 10:
			give_book();
		break;
		case 11:
			take_book();
		break;
		case 12:
			exit(0);
		break;
		default:
		printf("Unknown operation!\n");		
	}
	}
}

void student_menu_ad(){
	printf("+--------------------------------------+\n");
	printf("|             Students menu            |\n");
	printf("+---+----------------------------------+\n");
	printf("| 0 | Back to main menu                |\n");
	printf("+---+----------------------------------+\n");
	printf("| 1 | Add the new student              |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 2 | Delete the student               |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 3 | Backup copy                      |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 4 | Recovery                         |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 5 | Search by surname                |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 6 | Change information about student |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 7 | Show a student                   |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 8 | Exit                             |\n");
	printf("+---+----------------------------------+\n");
	int act;
	while(act!=8){
	printf("Choose an action: ");
	scanf ("%d", &act);
	switch(act){
		case 0:
			printf("You finished working with students...\n");
			main_menu_ad();
		break;
		case 1:
			add_student();
		break;
		case 2:
			delete_student();
		break;
		case 3:
			backup_stud();
		break;
		case 4:
			recovery_stud();
		break;
		case 5:
			search_surname();
		break;
		case 6:
			change_student();
		break;
		case 7:
			show_student();
		break;
		case 8:
			exit(0);
		break;
		default:
		printf("Unknown operation!\n");
}
}
}




void book_menu(){
	printf("+-----------------------------------+\n");
	printf("|            Books menu             |\n");
	printf("+----+------------------------------+\n");
	printf("| 1  | Add the new book             |\n");
	printf("+----+------------------------------+\n");	
	printf("| 2  | Delete the book              |\n");
	printf("+----+------------------------------+\n");
	printf("| 3  | Backup copy                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 4  | Recovery                     |\n");
	printf("+----+------------------------------+\n");
	printf("| 5  | Search by author             |\n");
	printf("+----+------------------------------+\n");
	printf("| 6  | Show all books               |\n");
	printf("+----+------------------------------+\n");
	printf("| 7  | Show information about book  |\n");
	printf("+----+------------------------------+\n");
	printf("| 8  | Change information           |\n");
	printf("+----+------------------------------+\n");
	printf("| 9  | Change quantity of books     |\n");
	printf("+----+------------------------------+\n");
	printf("| 10 | Give a book                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 11 | Take a book                  |\n");
	printf("+----+------------------------------+\n");
	printf("| 12 | Exit                         |\n");
	printf("+----+------------------------------+\n");
	int act;
	while(act!=12){
	printf("Choose an action: ");
	scanf ("%d", &act);
	switch(act){
		case 1: 
			add_book();
		break;
		case 2:
			delete_book();
		break;
		case 3:
			backup();
		break;
		case 4:
			recovery();
		break;
		case 5:
			search_author();
		break;
		case 6:
			show_all_books();
		break;
		case 7:
			show_one_book();
		break;
		case 8:
			change_data();
		break;
		case 9:
			change_quantity();
		break;
		case 10:
			give_book();
		break;
		case 11:
			take_book();
		break;
		case 12:
			exit(0);
		break;
		default:
		printf("Unknown operation!\n");		
	}
	}
}

void student_menu(){
	printf("+--------------------------------------+\n");
	printf("|             Students menu            |\n");
	printf("+---+----------------------------------+\n");
	printf("| 0 | Back to main menu                |\n");
	printf("+---+----------------------------------+\n");
	printf("| 1 | Add the new student              |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 2 | Delete the student               |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 3 | Backup copy                      |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 4 | Recovery                         |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 5 | Search by surname                |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 6 | Change information about student |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 7 | Show a student                   |\n");	
	printf("+---+----------------------------------+\n");
	printf("| 8 | Exit                             |\n");
	printf("+---+----------------------------------+\n");
	int act;
	while(act!=8){
	printf("Choose an action: ");
	scanf ("%d", &act);
	switch(act){
		case 1:
			add_student();
		break;
		case 2:
			delete_student();
		break;
		case 3:
			backup_stud();
		break;
		case 4:
			recovery_stud();
		break;
		case 5:
			search_surname();
		break;
		case 6:
			change_student();
		break;
		case 7:
			show_student();
		break;
		case 8:
			exit(0);
		break;
		default:
			printf("Unknown operation!\n");
}

}
}




int main(){
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	FILE *books;
	if ((books = fopen("books.csv","r")) == NULL){
		printf("File \"books.csv\" is not found...\n");
		return 404;
	}
	fclose(books);
	FILE *students;
	if ((students = fopen("students.csv","r")) == NULL){
		printf("File \"students.csv\" is not found...\n");
		return 404;
	}
	fclose(students);
	FILE *users;
	if ((users = fopen("users.csv","r")) == NULL){
		printf("File \"users.csv\" is not found...\n");
		return 404;
	}
	if ((users = fopen("student_books.csv","r")) == NULL){
		printf("File \"student_books.csv\" is not found...\n");
		return 404;
	}
	fclose(users);
	char login[N];
	char password[N];
	printf("Your login: ");
	scanf("%s", login);
	printf("Your password: ");
	scanf("%s", password);
	int acc;
	acc = access(login, password);	
	if (acc == 0){
		printf("Sorry... You have no access...");
		return 502;
	}
	int choose;
	if(acc == 3){
		main_menu_ad();
	}
	if(acc == 1){
		book_menu();
	}
	if(acc == 2){
		student_menu();
	}
	return 0;
}
