#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

void login();
void signup();
void pwd_re_enter(char[], char[], char [],char []);
void adddetails(char [],char [], char []);
int checker(char[1000], char[100] );
void first_page();
void homepage();
void search_books();
void profile(char [100000]);
void genre();
void title();
void author();
void book_borrow_details(int);
void saving_details(char book_no[1000], char book_name[1000], char author_name[1000], char availability[1000], char pblished_date[1000], char borrowed_date[1000], char return_date[1000]);
void display_book_details(int choice, int genre);
void display_books_of_genre_number(int genre);
void title_search();

char user_name[1000];
FILE *fp_bb;

void homepage()
{
	printf("\n");
	printf("\n\t\t********************* HOMEPAGE *********************\n\n");
	printf("\t1.Search for Books\n\n\t2.Profile\n\n\t3.Logout\n\n");
	printf("\tEnter 1,2 or 3: ");
	int option;
	
	while(option!=1&&option!=2&&option!=3)
	{
		scanf("%d", &option);
		switch(option)
		{
			case 1:search_books();
				   break;
			case 2:profile(user_name);
				   break;
			case 3:printf("\tYou have successfully logged out!\n");
				   first_page();					 
				   break;
			default:printf("\tWrong option!\n\tEnter 1,2 or 3: ");
				   break;
		}
	}
}

void login()
{
	printf("\n\t\t********************* LOGIN *********************\n");
	printf("\n\n");
	char password[100];
	printf("\tEnter Username : ");
	scanf("%s",&user_name);
	printf("\n\tEnter Password : ");
    scanf("%s",&password);
	printf("\n");
		
	FILE *p = fopen("signup_details.txt","r");
	char ch[50000];
	int flag=0;
	
	while(fgets(ch,50000,p)!= NULL && flag ==0)
	{
		
		char * token = strtok(ch, "-->");
		
		while(token!=NULL) 
		{
			
			if (strcmp(user_name,token) == 0)
			{
				token=strtok(NULL, "-->");	
				if (strcmp(password,token) == 0) 
				{
					flag=1;
					homepage();
										
				}
				else
				{
					printf("\tWrong Password. Try again!");
					login();					
				}
				
			}
			else
			{
				token=strtok(NULL, "-->");
			}
			
		}
		printf("\n");
	}
	
	if (flag==0)
	{
		printf("\tWrong username. Try again!");
		login();
				
	}
		
	
	fclose(p);
}
	
void first_page()
{
	printf("\n\n\n");
	printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############                  COSMIC LIBRARY                   ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
	printf("\n\n\n");
	printf("\t1) LOGIN\n\n\t2) SIGN-UP\n\n\t3) EXIT\n\n");
	int choice;
		
    while(choice!=1&&choice!=2&&choice!=3)
    {
		printf("\tEnter your choice :  ");
	    scanf("%d",&choice);
		switch(choice)
		{
			case 1:
			{
				login();
				 break;
			}
			case 2:
			{
				signup();
				break;
			}
			case 3:
			{
				exit(0);
				break;
			}
			default:
			{
				printf("\n\tWrong option!\n\tGive 1,2 or 3 only\n\n");
				break;
			}
		}
	}
}

void adddetails(char user_name[1000], char password[1000], char email[1000])
{
	
	FILE *fptr;
	char data_to_append[1000];
	fptr=fopen("signup_details.txt","a");
	if(fptr==NULL)
	{
		
		login();
	}
	//data_to_append=user_name+"-->"+password+"-->"+email;
	fputs(user_name, fptr);
	fputs("-->", fptr);
	fputs(password, fptr);
	fputs("-->", fptr);
	fputs(email, fptr);
	fputs("\n", fptr);
	fclose(fptr);
	login();
	
}

void pwd_re_enter(char user_name[100], char email[100], char password[100],char conf_password[100])
{
	
	int x=checker(user_name, email);
	
	if (x==2 || x==3)
	{
		printf("\n\tInvalid e-mail Id!\n\t");
		signup();
	}
	else if(x==1)
	{
		signup();
	}
	else
	{
		printf("\tEnter Password : ");
        scanf("%s[^\n]", password);
		printf("\n\tConfirm Password : ");
		scanf("%s[^\n]", conf_password);		
		int compare=strcmp(password,conf_password);
		
		if(compare==0)
		{
			printf("\n\t\t\t\t********  YOU HAVE SUCCESSFULLY SIGNED UP!  ********\n\n");
			adddetails(user_name, password, email);
		}
		else
		{
			printf("\tThe set password and confirm password do not match!\n");
			printf("\tTry again!\n\n");
			pwd_re_enter(user_name, email, password, conf_password); //recursion 
		}
	}
}

int checker(char username[1000], char email[100] )
{
	FILE *p = fopen("signup_details.txt","r");
	char ch[50000];
	while(fgets(ch,50000,p))
	
	{
		char *token = strtok(ch, "-->");
		
		
		while(token!=NULL) 
		{
			if (strcmp(username,token)==0)
			{
				printf("\tUsername already taken! Try again.\n");
				return 1;
			}
			else
			{
				break;
			}
		}
	}
	
	if  (strstr(email, ".com"))
	{
		if(strstr(email, "@"))
		{
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 3;
	}	
	
}

void signup()
{
	printf("\n\t\t********************* SIGN-UP *********************\n\n");
	char user_name[100], email[100], password[100], conf_password[100];
	printf("\tEnter Username : ");
	scanf("%s",&user_name);
	printf("\n");
	printf("\tEnter e-mail Id : ");
	scanf("%s",&email);
	printf("\n");
	
	pwd_re_enter(user_name,email,password, conf_password);
	
}

void search_books()
{
	printf("\n\t\t********************* SEARCH PAGE *********************\n\n");
	printf("\tSearch for books based on:-\n\n");
	printf("\t1.Title\n\n\t2.Genre\n\n\t3.Author\n\n");
	printf("\tEnter 1,2 or 3: ");
	int search;
	while(search!=1&&search!=2&&search!=3)
	{
		scanf("%d", &search);
		switch(search)
		{
			case 0: homepage();
				   break;
			case 1:title();
				   break;
			case 2:genre();
				   break;
			case 3:author();	
				   break;
			default:printf("\tWrong option!\n\tEnter 1,2 or 3: ");
				   
		}
	}

	
}

void title()
{
	title_search();
}

void genre()
{
	
	printf("\n\t\t********************* SEARCHING BY GENRE *********************\n\n");
	printf("Code		Genre\n");
	printf("01	LGBT\n02	Gothic\n03	Classic\n04	Fiction\n05	Non-fiction\n06	Thriller\n07	Romance\n08	Comedy\n09	Horror\n10	Fantasy\n11	Nautical\n12	Satire\n13	Adventure\n14	Science Fiction\n15	Mystery\n16	Psychological\n17	Historical fiction\n18	Time travel\n19	Chivalric romance\n20	Contemporary Romance\n21	Contemporary Literature\n22	Travel Literature\n23	Psychological\n24	Young Adult Fiction\n25	Erotic Literature\n26	Fantasy Fiction\n27	Autobiography\n28	Memoir\n29	Math\n30	Textbook\n31	Physics\n");
	printf("\tEnter the number of the genre you want to search: \n");
	printf("\tOR\n");
	printf("\tEnter 0 to go back to previous page:- \n");
	int gen=1;
	while(gen!=0)
	{
		scanf("%d", &gen);
		switch (gen) 
		{
        case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10: case 11: 
		case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19: case 20: case 21: 
		case 22: case 23: case 24: case 25: case 26: case 27: case 28: case 29: case 30: case 31:
            display_books_of_genre_number(gen);
            break;
        case 0:
            search_books();
            break;
        default:
            printf("\tWrong option!\n\tEnter a number from the above list only: ");
		}
	}	
}

void book_borrow_details(int ch)
{
	time_t t = time(NULL); int conf_ch;
	struct tm tm = *localtime(&t);
	FILE *fp; int temp;
	fp=fopen("book_data_old.txt", "r");
	char books[10000];
	char *book_no;
	char *title;
	char *author_name;
	char *status;
	char *gen;
	char *pub;
	int i=0;
	printf("\n\t\t********************* SEARCH RESULTS *****123****************\n\n");
	while(fgets(books, 10000, fp) != NULL)
	{
		
		book_no = strtok(books, "-->"); // book no
		title = strtok(NULL,"-->"); //title 
		author_name = strtok(NULL,"-->"); //author 
		status = strtok(NULL,"-->"); //status 		
		gen = strtok(NULL,"-->"); // genre
		pub = strtok(NULL,"-->"); // pub
		if(ch == atoi(book_no))
			{	
				break;
			}
	}
				fclose(fp);
				if (strcmp(status,"\nNot Available!")==0)
				{
					printf("\n\n\tOops! The book you are looking for is unavailable!\n");
					printf("\n\tGoing back to search page...\n\n");
					search_books();
					
				}
				printf("Title:- %s\n",title);
				printf("Author:- %s\n", author_name);
				printf("Status:- %s\n", status);
				printf("Published Date:- %s\n", pub);
				printf("Date borrowed:- %02d-%02d-%02d\t", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
				printf("At:- %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
				int dd,mm,yy,d,e,f;
				dd=tm.tm_mday;
				mm=tm.tm_mon + 1;
				yy=tm.tm_year + 1900;
				char bd[100]; char bm[100]; char by[100];
				sprintf(bd,"%d",dd);
				sprintf(bm,"%d",mm);
				sprintf(by,"%d",yy);
				strcat(bd, "/"); strcat(bd, bm); strcat(bd, "/"); strcat(bd, by);
				if (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12 )
				{
					if (dd<18)
					{

					dd+=14;
					}
					else if (dd>=18 && mm!=12)
					{
					mm+=1;
					d=31-dd;
					e=14-d;
					dd=1+e;
					}
					else
					{
					mm==1;
					d=31-dd;
					e=14-d;
					dd=1+e;
					yy=yy+1;
					}

				}
				else if (mm==2)
				{
					if (yy%4==0 && yy%100!=0 || yy%400==0)
					{

						if (dd<16)
						{

						dd+=14;
						}
						else
						{
						mm+=1;
						d=29-dd;
						e=14-d;
						dd=1+e;
						}
					}
					else
					{

						if (dd<15)
						{
						dd+=14;
						}
						else
						{
						mm+=1;
						d=28-dd;
						e=14-d;
						dd=1+e;
						}

					}
				}
				else
				{

					if (dd>17)
					{
					mm+=1;
					d=30-dd;
					e=14-d;
					dd=1+e;

					}
					else
					{
					dd+=1;
					}

				}
					   
				printf("Return Date:- %02d-%02d-%02d\t", dd, mm,yy);
				printf("At:- %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
				printf("\n\n\n");
				char rd[100]; char rm[100]; char ry[100];
				sprintf(rd,"%d",dd);
				sprintf(rm,"%d",mm);
				sprintf(ry,"%d",yy);
				strcat(rd, "/"); strcat(rd, rm); strcat(rd, "/"); strcat(rd, ry);

				do
				{
					printf("\nEnter 0 to go back\n");
					printf("Enter 1 to confirm your choice. \n");
					scanf("%d",&conf_ch);
					if (conf_ch==0)
					{
						author();
						break;
					}
					else if(conf_ch==1)
					{
						printf("Outside1 saving_details fn");
						saving_details(book_no, title, author_name, status, pub, bd, rd);
						printf("saving your details....");
						
						break;
					}
					else
					{
						printf("Wrong Choice! Try again!!\n");
					}
				}while(conf_ch!=0 && conf_ch!=1);

	}

void author()
{	
	printf("\n\t********** SEARCHING BY AUTHOR **********\n\n");
	printf("\tEnter the author you want to search for (xxx to go back to previous page): ");
	char auth[1000] = {0}, 	line[1000] = {0};
	int a = 0;
	
	getchar();
	scanf("%[^\n]s", auth); 
	//getchar();
	
	char *book_no;
	char *title;
	char *author_name;
	char *status;
	char *gen;
	char *pub;
	int book_no_matching_the_genre[10000];
	FILE *p = fopen("book_data_old.txt","r");
	
	while(fgets(line,10000,p))
	{
		book_no = strtok(line, "-->"); // book no
		title = strtok(NULL,"-->"); //title 
		author_name = strtok(NULL,"-->"); //author 
		gen = strtok(NULL,"-->"); // genre
		status = strtok(NULL,"-->"); //status 
		pub = strtok(NULL,"-->"); // pub
		
		if(strcmp(auth, author_name) == 0)
		{
			a++;
			printf("\n\tBOOK DETAILS:-\n\n\tBook code:- %s\n\tTitle:- %s\n\tAuthor:- %s\n\tStatus:- %s\n\tGenre:- %s\n\tPublished Date:- %s\n",book_no, title, author_name, gen, status, pub);
		}
		if(strcmp(auth, "XXX") == 0 || strcmp(auth, "xxx") == 0) {
			printf("\t<--Going back to previous page......\n");
			search_books();
			
		}
	}
	if(a==0)
	{
		printf("\tAuthor not found!!\n");				
		author(); 
	}
	
	int choice;
	printf("\n\tEnter 0 to go to the previous page\n");
	printf("\tOR Enter book code to borrow the book\n");
	printf("\tEnter your choice: ");
	scanf("%d",&choice);
	
	if (choice==0)
	{
		printf("\t<--Going back to previous page......\n");
		author();
	}
	else if(choice >= 1 && choice <=97)
	{
		book_borrow_details(choice);	
	}
	else
		printf("\n\tYou have entered a code that does not match with the book list shown to you.");
}

void saving_details(char book_no[1000], char book_name[1000], char author_name[1000], char availability[1000], char pblished_date[1000], char borrowed_date[1000], char return_date[1000])
{	
	printf("\nInside saving_edtails fn\n");
	fp_bb = fopen("borrowed_history.txt","a");
	fputs(user_name,fp_bb);
	fputs("-->",fp_bb);
	fputs(book_name,fp_bb);
	fputs("-->",fp_bb);
	fputs(borrowed_date,fp_bb);
	fputs("-->",fp_bb);
	fputs(return_date, fp_bb);
	fputs("\n",fp_bb);
		
	printf("\n\tYou have borrowed the book.\n");
	printf("\tKeep up with the due date.\n\tHAVE FUN READING! \n\n");
	printf("\t<--Re-Directing to HomePage...\n\n");
	fclose(fp_bb);
	
	homepage();
	
}

void display_book_details(int choice, int genre_no)
{
	time_t t = time(NULL); 
    	struct tm tm = *localtime(&t);
	FILE *fp; int temp;
	//fp=fopen("genres.txt","r");
	char *genre_name; char *token;
    //printf("Date and time: %d-%02d-%02d %02d:%02d:%02d\n",tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
	fp=fopen("book_data.txt", "r");
	char books[10000];
	char *book_no;
	char *book_name;
	char *author_name;
	char *availability;
	char *genre_from_data;
	char *pblished_date;
	int i=0;
	int value; int prev_bookno;
	
	while(fgets(books, 10000, fp))
	{
		book_no=strtok(books,"-->");
		book_name=strtok(NULL,"-->");
		author_name=strtok(NULL,"-->");
		availability=strtok(NULL,"-->");
		genre_from_data=strtok(NULL,"-->");
		pblished_date=strtok(NULL,"-->");
		if(atoi(book_no)==choice)
		{
			break;
		}
	}
	fclose(fp);
	printf("\n\t********** CONFIRMATION PAGE **********\n\n");
	if (strcmp(availability,"Not Available")==0)
	{
		printf("\tOops! The book you are looking for is unavailable to borrow!\n");
		printf("\tTry another book?\n\n");
		if(genre_no == 0)
			title();
		else
			display_books_of_genre_number(genre_no);
	}
	
	printf("\tTitle:-  %s\n",book_name);
	printf("\tAuthor:- %s\n", author_name);
	printf("\tPublished Date:- %s\n", pblished_date);
	//char borrowed_date[1000]=
	printf("\tDate borrowed:-  %02d-%02d-%02d\t", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
	printf("\tAt:- %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	int dd,mm,yy,d,e,f;
	dd=tm.tm_mday;
	mm=tm.tm_mon + 1;
	yy=tm.tm_year + 1900;
	char bd[100]; char bm[100]; char by[100];
	sprintf(bd,"%d",dd);
	sprintf(bm,"%d",mm);
	sprintf(by,"%d",yy);
	strcat(bd, "/"); strcat(bd, bm); strcat(bd, "/"); strcat(bd, by);
	//printf("%s",bd);
	if (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12 )
	{
		if (dd<18)
		{
			
			dd+=14;
		}
		else if (dd>=18 && mm!=12)
		{
			mm+=1;
			d=31-dd;
			e=14-d;
			dd=1+e;
		}
		else
		{
			mm==1;
			d=31-dd;
			e=14-d;
			dd=1+e;
			yy=yy+1;
		}
		
	}
	else if (mm==2)
	{
		if (yy%4==0 && yy%100!=0 || yy%400==0)
		{
			
				if (dd<16)
				{
					
					dd+=14;
				}
				else
				{
					mm+=1;
					d=29-dd;
					e=14-d;
					dd=1+e;
				}
			
			
		}
		else
		{
			
				if (dd<15)
				{
					dd+=14;
				}
				else
				{
					mm+=1;
					d=28-dd;
					e=14-d;
					dd=1+e;
				}
			
		}
	}
	else
	{
		
			if (dd>17)
			{
				mm+=1;
				d=30-dd;
				e=14-d;
				dd=1+e;
				
			}
			else
			{
				dd+=1;
			}
		
	}
        
	printf("\tReturn Date:- %02d-%02d-%02d\t", dd, mm,yy);
	printf("\tAt:- %02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
	printf("\n\n\n");
	char rd[100]; char rm[100]; char ry[100];
	sprintf(rd,"%d",dd);
	sprintf(rm,"%d",mm);
	sprintf(ry,"%d",yy);
	strcat(rd, "/"); strcat(rd, rm); strcat(rd, "/"); strcat(rd, ry);
	
	int choice_2;
	do
	{
	printf("\tEnter 0 to go back\n");
	printf("\tEnter 1 to confirm your choice. \n");
	scanf("%d",&choice_2);
	if (choice_2==0)
	{
		if(genre_no == -1)
		{
			search_books();
			break;
		}
		else
		{
			display_books_of_genre_number(genre_no);
		}
	}
	else if(choice_2==1)
	{
		printf("Outside2 saving_details fn");
		saving_details(book_no, book_name, author_name, availability, pblished_date, bd, rd);
		break;
	}
	else
	{
		printf("\tWrong Choice! Try again!!\n");
	}
	}while(choice_2!=0 && choice_2!=1);
	
}

void display_books_of_genre_number(int genre_no)
{
	
	FILE *fp_gen; int temp;
	fp_gen=fopen("genres.txt","r");
	char ch[1000]; char *genre_name; char *token;
	
	
	while(fgets(ch, 1000, fp_gen))
	{
		int line_length = strlen(ch);
		if (line_length >= 999) 
		{
			printf("Too long input!!\n");
			continue;
		}
		token=strtok(ch,"-->");
		temp=atoi(token);
		if (genre_no==temp)
		{
			genre_name=strtok(NULL,"-->");
			break;
		}
		
	}
	
	fclose(fp_gen);
	
	int xx, yy = 0;  
	yy = strlen(genre_name);     
	for(xx= 0;xx < yy; xx++)
	{  
		if (genre_name[xx]=='\n')
			genre_name[xx]='\0';			 
	}
	
	FILE *fp_book;
	fp_book=fopen("book_data.txt", "r");
	
	
	if(fp_book == NULL)
		printf("Error opening the file!!");
	char books[10000];
	char *book_no;
	char *book_name;
	char *author_name;
	char *availability;
	char *genre_from_data;
	char *pblished_date;
	int book_no_matching_the_genre[10000];
	int i=0;
	int value; int prev_bookno = -1;
	
	printf("\n\t**************** SEARCH RESULT *****567*****\n\n");
	while(fgets(books, 10000, fp_book))
	{
		book_no=strtok(books,"-->");
		book_name=strtok(NULL,"-->");
		author_name=strtok(NULL,"-->");
		availability=strtok(NULL,"-->");
		genre_from_data=strtok(NULL,"-->");
		pblished_date=strtok(NULL,"-->");
		//printf("%s  \n", genre_name);    
		value = strcmp(genre_from_data,genre_name);
		
		//printf("%d \t", value);
		//printf("%d %d %d\n", atoi(book_no), strlen(genre_name), strlen(genre_from_data));
		
		
		if(value==0 && prev_bookno!=atoi(book_no))
		{
			printf("%s\t",book_no);
			prev_bookno=atoi(book_no);
			printf("%70s\t",book_name);
			printf("%40s\t",author_name);
			printf("%10s\t",availability);
			printf("%10s\t",genre_from_data);
			//printf("%10s\t",pblished_date);
			book_no_matching_the_genre[i]=atoi(book_no);
			i=i+1;
			printf("\n");
			
		}
		
		
	}
	
	if (ferror(fp_book)) {
		printf("Error reading from book_data.txt!\n");
    // Handle the error
	}
	fclose(fp_book);
	printf("\n\n\n");
	
	printf("\tEnter 0 to go back to the previous page.\n");
	printf("\tOR\n");
	printf("\tEnter the book code to borrow the book\n");
	printf("\tEnter your choice : ");
	int choice_1 = 1;
	scanf("%d",&choice_1);
	if (choice_1==0)
	{
		printf("<--Going back to previous page......\n");
		genre();		
	}
	else
	{
		for(int j=0; j<i+1; j++)
		{
			if (choice_1==book_no_matching_the_genre[j])
			{	
				
				display_book_details(choice_1, genre_no);
				break;
				
			}
		}
		printf("\tYou have entered a code that does not match with the book list shown to you. Try again!\n\n");
		display_books_of_genre_number(genre_no);	
	}	
}

void title_search()
{
	int k[100];
	printf("\n\t********** SEARCHING BY TITLE **********\n");
	printf("\tEnter the title : \n");
	char title[1000];
	getchar();
	scanf("%[^\n]s",&title);
	
	FILE *bf; int temp;
	char *genre_name;
	bf=fopen("book_data.txt", "r");
	if (bf == NULL) 
	{
		perror("Error opening file");
		exit(EXIT_FAILURE);
	}
	char books[10000];
	char *book_no;
	char *book_name; char *book_name_temp;
	char *author_name;
	char *availability;
	char *genre_from_data;
	char *pblished_date;
	int i=0; char *token;
	int value; int prev_bookno;
	
	printf("\n        Search Results       \n");
	
	
	int book_no_matching_title[10000];
	int xyz=0; int flag=0;
	while(fgets(books, 10000, bf))
	{
		book_no=strtok(books,"-->");
		book_name=strtok(NULL,"-->");
		author_name=strtok(NULL,"-->");
		availability=strtok(NULL,"-->");
		genre_from_data=strtok(NULL,"-->");
		pblished_date=strtok(NULL,"-->");
		//printf("%d %d\n", strlen(book_name), strlen(title));
		//printf("book_name %s", book_name);
		if(strcmp(book_name,title)==0)
		{
			flag=1;
			break;
		}
		
	}
	fclose(bf);
	if (flag==1)
	{
		printf("%s\t",book_no);
		prev_bookno=atoi(book_no);
		printf("%s\t",book_name);
		printf("%s\t",author_name);
		printf("%s\t",availability);
		printf("%s\t",genre_from_data);
		//printf("%s\t",pblished_date);
		printf("\n");
	}
	else
	{
		printf("Oops! The book you are looking for is not present in our library!\n");
		printf("Sorry about that!!");
		printf("\n\n");
		printf("<--Redirecting to main search page....");
		search_books();
	}	
	
	int choice_1;
	do
	{
	printf("\n\n\n");
	printf("\tEnter 0 to go back to the previous page.\n");
	printf("\tOR\n");
	printf("\tEnter 1 to borrow the book\n");
	printf("\tEnter your choice : "); 
	
	scanf("%d",&choice_1); 
	if (choice_1==0)
	{
		printf("\n\t<--Going back to previous page......\n");
		search_books();
		
	}
	else if (choice_1==1)
	{
		display_book_details(atoi(book_no),0);
	}
	else
	{
		printf("\n\tWrong Choice! Enter 0 or 1.\n");
	}
	}while(choice_1!=0);
		
		
	
	
}

void profile(char ch[112346])
{
	
	char lines2[1000];char lines1[1000];
    FILE* fg=fopen("signup_details.txt","r");
	while(fgets(lines1,1000,fg)!=NULL)
	{
		char *qw=strtok(lines1,"-->");
		if(strcmp(ch,qw)==0)
		{   
	        printf("\t********** PROFILE **********\n\n\n");
			printf("\t*********************************************************************");
			printf("\n\t USERNAME : %s\t\t",qw);
			qw=strtok(NULL,"-->");
			qw=strtok(NULL,"-->");

			printf("\tEMAIL : %s         \n\n",qw);
			//qw=strtok(NULL,"-->");
			//printf("\t** NAME : %6s\t\t\t\t\t\t\t **",qw);
		}
		
	}
	
	
	FILE* fp=fopen("borrowed_history.txt","r");
	while(fgets(lines2,1000,fp)!=NULL)
	{
		char *un=strtok(lines2,"-->");
		//printf("%s\n",un);//shar and thor
		if(strcmp(ch,un)==0)
		{   
			un=strtok(NULL,"-->");
			printf("\n\n\t BOOK : %s\t\t\t\t\t ",un);
			un=strtok(NULL,"-->");
			printf("\n\n\t DATE BORROWED : %6s\t\t",un);
			un=strtok(NULL,"-->");
			printf("\tRETURN DATE : %s \n\n",un);
			printf("\t*********************************************************************");
		}	
			
		
	}
	fclose(fp);
	fclose(fg);
	homepage();
    
}

void main()
{   
	first_page();
	
}