#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
struct record
{
    char time[6];
    char place[25];
    char note[500];
};

struct reminder
{
      //birthday annviversary gettoghether  bachelor party to do list
    char title[100];
    char brief[100];
    int date ,month, year;
    struct reminder *next;
};
/*****************************
check for empty head in the reminder function
****************************/


char view_reminder(struct reminder **head,int date,int month,int year,int n)
{int flag=0;
char ch;
  //  printf("%d\n",year);
  struct reminder *ptr=*head;
  if(head==NULL)
  {
   if (n==1 )
  	printf("\nNO REMINDER FOUND !!\n");
  	return;
  }

     while( ptr!=NULL && ptr->month < month)

		  ptr=ptr->next;
			  while(ptr!=NULL && ptr->month==month  && ptr->date<date)
			   ptr=ptr->next;

   while(ptr != NULL && ptr->month==month  && (ptr->date)==date )
    {  if (n==1 )
    return 'R';

	flag=1;

   printf("%d/%d/%d\n\n%s\n%s",ptr->date,ptr->month,ptr->year,ptr->brief,ptr->title);  // printf the reminder of the day
        ptr=ptr->next;

    }

    if(flag==0)
    { if (n==0 )
    	printf("\nNO REMINDER FOUND THAT MATCHES YOUR CHOICE!!");
    else return ' ';
	}
 if (n==0 )
    printf("\nVIEWED..\n");
}

/**************************
just find the right place to add the reminder and insert the node

*****************************/

void create_reminder(struct reminder **h,int date ,int month,int year )
{ int month_copy;
    struct reminder *r1,*temp,*ptr;

    r1=(struct reminder *)malloc(sizeof(struct reminder));
    r1->date =date;
    r1->month=month;
    r1->year=year; r1->next=NULL;
    printf("Enter the Title of Reminder:-\n");
    fflush(stdin);
    fgets(r1->title,100,stdin);
    printf("\nDescription of the reminder:-\n");
    fflush(stdin);
    fgets(r1->brief,100,stdin);
    if(*h == NULL)
    {
        *h = r1;
    }
    else
    { if ((*h)->month >= month)
        {
		temp=*h;
        *h=r1;
        r1->next=temp;


		}
        else
		{ptr =*h;
             while( ptr->next!=NULL && ptr->next->month < month)
			   ptr=ptr->next;
			  while(ptr->next !=NULL && ptr->next->month==month  && ptr->next->date<date)
			   ptr=ptr->next;

            temp=ptr->next;
            ptr->next=r1;
            r1->next=temp;
		}
    }
    ptr=*h;
//while(ptr!=NULL)
//{ printf("\n%d %d %d\n%s %s",ptr->date,ptr->month,ptr->year,ptr->title,ptr->brief);
//ptr=ptr->next;}
    printf("\n\n\t\tREMINDER  CREATED !!\n\n");
}
/*****************************
this function takes in the head of the year and the year's int value
then converts that in tyear into file name
opens the file by that name.
if file doesnt exist we give head=NULL
else we will form the linked list of all the reminders of that year using malloc

*****************************/
void openfilegetdata(struct reminder **h,int year)
{
    struct reminder *temp,*ptr=*h;char buffer[10];
  itoa(year,buffer,10);
  strcat(buffer,".txt");
  FILE *ptr_r=fopen(buffer,"r");
   /*while(ptr !=NULL)
 {   printf("1");
		     ptr=ptr->next;
} */
if (ptr_r ==NULL)
{
    return;
}

 while(1)
	  { //printf("1");
	  temp=(struct reminder*)malloc(sizeof(struct reminder));
	  	fscanf(ptr_r,"%d %d %d",&temp->date ,&temp->month,&temp->year);
	  	if(fgets(temp->title,100,ptr_r)==NULL)break;
		fgets(temp->brief,100,ptr_r);
	    temp->next=NULL;
      //  printf("\n*****%d %d %d\n%s %s",temp->date,temp->month,temp->year,temp->title,temp->brief);
		if (*h == NULL)
		{ //printf("3");
		  *h=temp; ptr=temp;}
		else
		{
			//  printf("4");
		    ptr->next=temp;
			ptr=ptr->next; }

		}
	     fclose(ptr_r);
	     ptr=*h;
//while(ptr!=NULL)
//{ printf("\n%d %d %d\n%s %s",ptr->date,ptr->month,ptr->year,ptr->title,ptr->brief);
//ptr=ptr->next;

	//	 }


	    // printf("\nOPENED...\n");

}

/************************************8888
no need for year data type
**********************************/
void packup( struct reminder **h,int year)
{
char buffer[10];
struct reminder *ptr=*h;

itoa(year,buffer,10);   // here 10 means decimal

strcat(buffer,".txt");

  FILE *p=fopen(buffer,"w");
  //printf("HERE2");
	while(ptr!=NULL)
{//printf("HERE4");
fprintf(p,"%d %d %d%s%s",ptr->date,ptr->month,ptr->year,ptr->title,ptr->brief);
ptr=ptr->next;
}
//printf("HERE5");
fclose(p);


printf("PACKED....\n")
;}



void reminder_setting()
{ struct reminder *head=NULL;
char slash_dummy;
 int n,date, month ,year,z;
do
{
printf("Enter your choice\n");
printf("\n0)Exit \n1)Create New Reminder \n2)View Reminder ");
printf("\nEnter your choice\n");
scanf("%d",&n);
/*if (n!=0)
{
printf("\nEnter the Date in DD/MM/YYYY format:-\n");
scanf("%d%c%d%c%d",&date,&slash_dummy,&month,&slash_dummy,&year);
openfilegetdata(&head,year);
}*/
switch(n)
    {
case 1:
    printf("\nEnter the Date in DD/MM/YYYY format:-\n");
    scanf("%d%c%d%c%d",&date,&slash_dummy,&month,&slash_dummy,&year);
    openfilegetdata(&head,year);
	create_reminder(&head,date,month,year);
    packup(&head,year);
    break;
case 2:
   {z=0;
        //printf("%d\n",head->date);
        printf("\nEnter the Date in DD/MM/YYYY format:-\n");
        scanf("%d%c%d%c%d",&date,&slash_dummy,&month,&slash_dummy,&year);
        openfilegetdata(&head,year);
       slash_dummy= view_reminder(&head,date,month,year,z);
       //printf("********/n");
        break;
    }

case 0:
	free(head);
   return;
   break;

default :
	printf("\n----WRONG CHOICE TRY AGAIN\n");
	break;
}


}while(n);

}
void month(int,int,int,int);
void year();
void holiday();
void adddiary();
void diary_entry();
void viewdiary();
int y,i=1,md[12];
void func(int d[],int c,int da);
int editdiary();

void main()
 {
     time_t t;
     struct tm *info;
     system("color 9F");
     int choice;
     char login[15],pass[15],ch;
     int i=0;
     printf("\n\t\t\t\t\t\t\t\tJAYPEE INSTITUTE OF INFORMATION TECHNOLOGY\n");
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     printf("\n\t\t\t\t\t\t\t\t\t   PROJECT CALENDRIO\n");
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     r:
        // system("cls");
         system("color 0F");
     i=0;
     printf("\t\t\t\t\t\t\t\t\t   LOGIN ID:    ");
     fflush(stdin);
     gets(login);
     //printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     printf("\n");
     printf("\t\t\t\t\t\t\t\t\t   PASSWORD:    ");

     fflush(stdin);
     ch=_getch();
     //printf("@@@@@@@@\n");
     while(ch!=13)
     {
        if(i<0)
            i=0;
         //printf("%%%%%\n");
        if(ch==8)
            i--;
         else
         {
            //fflush(stdin);
            printf("*");
            pass[i]=ch;
            i++;
         }
         fflush(stdin);
         ch=_getch();
     }
     pass[i]='\0';
     printf("\n------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     printf("\n");
     if(strcmp(login,"CALENDRIO")!=0 || strcmp(pass,"SARK")!=0)
     {
         system("color 0C");
        printf("\t\t\t\t\t\t\t\t\tAUTHENTICATION FAILURE!!!\n\t\t\t\t\t\t\t\t\tPRESS ANY KEY(EXCEPT 0)TO RETRY\n\t\t\t\t\t\t\t\t\tPRESS 0 TO CLOSE PROJECT\n\t\t\t\t\t\t\t\t\t");
        scanf("%d",&choice);
        if(choice==0)
            exit(0);
        else
            system("cls");

            goto r;
     }
     else
     {
         int j;
         system("color 0A");



        printf("\n\t\t\t\t\t\t\t\t\tLOADING...PLEASE WAIT...!!!\n");
        Sleep(2000);
     }

       system("color FC");
  system("cls");
    time(&t);
    info=localtime(&t);
    system("cls");
do
{
    printf("\tLOG-IN DATE:  %d-%d-%d\t\t\t\t\tLOGGED IN SUCCESSFULLY\t\t\t\t\tLOG-IN TIME:  %d:%d:%d\n\n",info->tm_mday,1+info->tm_mon,1900+info->tm_year,info->tm_hour,info->tm_min,info->tm_sec);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     printf("\n");
     printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
     printf("\n");
    sark:

    printf("Enter 1 for display of the year calender\n");
    printf("Enter 2 for Diary Entry\n");
    printf("Enter 3 for Reminder setting\n");
    printf("Enter 4 for List of Holidays\n");
    printf("Enter 0 to Logout\n");
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("\n");
    printf("Enter your choice::");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        system("cls");
        system("color 1F");
        year();
        break;
    case 2:
        system("cls");
        system("color 5F");
        diary_entry();
        break;
    case 3:
        system("cls");
        system("color CF");
        reminder_setting();
        break;
    case 4:
        system("cls");
        system("color 5F");
        printf("Enter the year::");
        scanf("%d",&y);
        holiday(y);
        goto sark;
        break;
    case 0:
        time(&t);
        info=localtime(&t);
        printf("\n\tLOG-OUT DATE:  %d-%d-%d\t\t\t\t\tLOGGED OUT SUCCESSFULLY\t\t\t\t\tLOG-OUT TIME:  %d:%d:%d\n\n",info->tm_mday,1+info->tm_mon,1900+info->tm_year,info->tm_hour,info->tm_min,info->tm_sec);
        printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
        printf("\n");
        exit(0);
    default:
        printf("Wrong choice entered,please enter it correctly\n");
        break;
    }
}while(choice!=0);
  getch();
 }
void year()
{
    int q;
    char ch;
    char m[12][20];
    strcpy(m[0],"JANUARY");
    md[0]=31;
    strcpy(m[1],"FEBRUARY");
    strcpy(m[2],"MARCH");
    md[2]=31;
    strcpy(m[3],"APRIL");
    md[3]=30;
    strcpy(m[4],"MAY");
    md[4]=31;
    strcpy(m[5],"JUNE");
    md[5]=30;
    strcpy(m[6],"JULY");
    md[6]=31;
    strcpy(m[7],"AUGUST");
    md[7]=31;
    strcpy(m[8],"SEPTEMBER");
    md[8]=30;
    strcpy(m[9],"OCTOBER");
    md[9]=31;
    strcpy(m[10],"NOVEMBER");
    md[10]=30;
    strcpy(m[11],"DECEMBER");
    md[11]=31;
    int yy,a,a1,a2,b,b1,b2,ip=0,sm=0,c,d,e,days[12];
    i=0;

  printf("Enter which year you want show the calender-" );
  scanf("%d",&yy);
  if(yy%4==0)
    md[1]=29;
  else
    md[1]=28;
  yy=yy-1;
  a=yy%400;
  b=yy/400;
  a1=a%100;
  b1=a/100;
  a2=a1/4;
  b2=a1-a2;
  sm=b1*5+a2*2+b2+1;
  sm=sm%7;
  days[ip]=sm;
  func(days,md[ip],days[ip]);
  printf("\n\n                  \t    \t    \t   \t\t\t              %s\n\n",m[ip]);
  month(md[ip],days[ip],ip+1,yy);
  printf("\n\t\t\t\t|               |               |               |               |                |                |                |\n\t\t\t\t|               |               |               |               |               |                |                |\n\t\t\t\t------------------------------------------------------------------------------------------------------------------");
  do
  {
  printf("\nPress x for next Month of the entered year\n");
  printf("Press z for previous Month of the entered year\n");
  printf("Press any other key to stop scrolling\n");
  printf("Enter your choice:");
  fflush(stdin);
  scanf("%c",&ch);
  switch(ch)
  {
  case 'x':
      system("cls");
      ip++;
      if(ip<12)
      {
      printf("\n\n\n\n                  \t    \t    \t   \t\t\t              %s\n\n",m[ip]);
      month(md[ip],days[ip],ip+1,yy);
      printf("\n\t\t\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\n\t\t\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\n\t\t\t\t------------------------------------------------------------------------------------------------------------------");
      }
      else
      {
          ip=11;
          printf("Please enter the next year\n");
      }
      break;
  case 'z':
      system("cls");
      ip--;
      if(ip>=0)
      {
      printf("\n\n\n\n                  \t    \t    \t   \t\t\t              %s\n\n",m[ip]);
      month(md[ip],days[ip],ip+1,yy);
      printf("\n\t\t\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\n\t\t\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\t\t|\n\t\t\t\t------------------------------------------------------------------------------------------------------------------");
      }
      else
      {
          ip=0;
          printf("Please enter the previous year\n");
      }
      break;
  default:
    break;
  }

  }while(ch=='x' || ch=='z');
  system("cls");
 }
void month(int c,int d,int m,int year)
 {
  char s[10],ma[4],ya[7],h[10];

 char a=' ',b=' ',e=' '; struct reminder*head=NULL;
 openfilegetdata(&head,year+1);

  int i,j,k,n;
 // ////printf("                                    Sun   Mon   Tue   Wed   Thu   Fri   Sat\n\n");
  printf("\n\t\t\t\t-----------------------------------------------------------------------------------------------------------------\n\t\t\t\t|     SUN       |     MON       |     TUE       |     WED       |     THU       |     FRI       |     SAT       |\n\t\t\t\t-----------------------------------------------------------------------------------------------------------------\n");
  for(i=0;i<=d;i++)
  {

  if(i>=d)
  {
   for(j=1;j<=c;j++)
   {
    if(i%7==0)
   {
   printf("\n\t\t\t\t|               |               |               |               |               |               |               |\n\t\t\t\t|               |               |               |               |               |               |               |\n\t\t\t\t------------------------------------------------------------------------------------------------------------------\n\t\t\t\t|               |               |               |               |               |               |               |\n");
    printf("\t\t\t\t|");
   }

    n=1;
    a=view_reminder(&head,j,m,year+1,n);

  itoa(j,s,10);
  itoa(m,ma,10);
  itoa(year+1,ya,10);
  strcat(s,"-");
  strcat(s,ma);
  strcpy(h,s);
  strcat(s,"-");
  strcat(s,ya);
strcat(h,".txt");  //printf("%s",s);
    FILE *ptr=fopen(s,"rb");
    if(ptr==NULL)
      {//printf("##");
      	b=' ';
	  }
	  else b='D';
	  FILE *ptr1=fopen(h,"r");
    if(ptr1==NULL)
      {//printf("##");
      	e=' ';
	  }
	  else e='H';


   // printf("%c",a);
	printf("%8d %c %c %c |",j,a,b,e);
	fclose(ptr);
	fclose(ptr1);
    i++;
   }
  }
  else
    if(i==0)
   printf("\t\t\t\t|");
   printf("\t\t|");

  }
 }
 void diary_entry()
 {
    char i;
    int ch;
    printf("\t*DIARY ENTRY*\n");
  do
    {
        printf("\n\t\tMENU:");
        printf("\n\t1.ADD RECORD");
        printf("\n\t2.VIEW RECORD");
        printf("\n\t3.EDIT IN THE RECORD");
        printf("\n\t4.BACK TO MAIN MENU");
        printf("\n\n\tENTER YOUR CHOICE:");
        scanf("%d",&ch);
    switch(ch)
    {
        case 1:
            adddiary();
            break;
        case 2:
            viewdiary();
            break;
        case 3:
            editdiary();
            break;
        case 4:
            return;
            break;
        default:
            printf("\n\tYOU ENTERED WRONG CHOICE..");
    }
    printf("\nDo you want to continue diary writing(Y/N):");
    fflush(stdin);
    scanf("%c",&i);
   system("cls");

    }while(i=='y'||i=='Y');
        //return 0;
}
void adddiary()
{
FILE *fp ;
char ch,time[10];
struct record temp;
char filename[15];
int t;
    printf("\n\n\tENTER DATE OF YOUR RECORD:[DD-MM-YYYY]:");
    fflush(stdin);
    gets(filename);
    fp=fopen(filename,"ab+") ;
    if (fp==NULL)
    {
      //fp=fopen(filename,"wb+");
            printf("\n...MEMORY ERROR...");
            return ;
    }
    else
    {
        t=0;
        fflush(stdin);
        printf("\n\tENTER TIME:[hh:mm]:");
        scanf("%s",time);
        rewind(fp);
        while(fread(&temp,sizeof(temp),1,fp)==1)
        {
          if(strcmpi(temp.time,time)==0)
            {
            printf("\n\tTHE RECORD ALREADY EXISTS.\n");
            t=1;
            break;
            }
        }
        if(t==0)
        {
            strcpy(temp.time,time);
            fflush(stdin);
            printf("\tENTER PLACE:");
            gets(temp.place);
            fflush(stdin);
            printf("\tNOTE:");
            gets(temp.note);
            fwrite(&temp,sizeof(temp),1,fp);
            printf("\nCONGRALTULATIONS! YOUR RECORD IS ADDED SUCCESSFULLY...\n");
        }
    }

    fclose(fp);
}
void viewdiary()
{
FILE *fp1;
struct record temp;
char time[6],filename[14];
int ch;
    printf("\n\tENTER THE DATE OF RECORD TO BE VIEWED:[DD-MM-YYYY]:");
    fflush(stdin);
    gets(filename);
    fp1=fopen(filename,"rb+");
    if (fp1==NULL)
    {
       puts("\nTHE RECORD DOES NOT EXIST...\n");
       return ;
    }
    else{
            rewind(fp1);
         printf("\nTHE WHOLE RECORD FOR %s IS:",filename);
            while (fread(&temp,sizeof(temp),1,fp1)!=0)
            {
                printf("\n");
                printf("\n\nTIME: %s",temp.time);
                printf("\n\nPLACE: %s\n\n",temp.place);
                puts(temp.note);
                printf("\n");
            }
       }
fclose(fp1);
}

int editdiary()
{
    int flag=0;
    FILE *fp;
    struct record temp;
    int num;
    char time[6],filename[14];

      printf("\n\tENTER THE DATE OF DIARY TO BE EDITED:[dd-mm-yyyy]:");
      fflush(stdin);
      gets(filename);
      printf("\n\tENTER TIME:[hh:mm]:");
      gets(time);
    fp=fopen(filename,"rb+");
    if(fp==NULL)
    {
       printf("\nRECORD DOES NOT EXISTS:");
       return;
    }
while(fread(&temp,sizeof(temp),1,fp)==1)
{
    if(strcmpi(temp.time,time)==0)
    {
        printf("\n\n\t\tWHAT WOULD YOU LIKE TO EDIT..");
        printf("\n1.TIME.");
        printf("\n2.PLACE.");
        printf("\n3.NOTE.");
        printf("\n4.WHOLE RECORD.");
        printf("\n5.GO BACK TO MAIN MENU.");

        printf("\n\tENTER YOUR CHOICE:");
        fflush(stdin);
        scanf("%d",&num);
        fflush(stdin);
        switch(num)
        {
            case 1:
                    printf("\nENTER NEW TIME:[hh:mm]:");
                    gets(temp.time);
                    break;
            case 2:
                    printf("\nENTER THE NEW PLACE:");
                    gets(temp.place);
                    break;
            case 3:
                    printf("\nENTER THE NEW NOTE:");
                    gets(temp.note);
                    break;
            case 4:  printf("\nENTER THE NEW DATA:");
                    printf("\nNEW TIME:[hh:mm]:");
                    gets(temp.time);
                    printf("\nNEW PLACE:");
                    gets(temp.place);
                    printf("\nNOTE:");
                    gets(temp.note);
                    break;
            case 5:
                    break;
            default:
                printf("\nINVALID CHOICE\n");
        }

        fseek(fp,-sizeof(temp),SEEK_CUR);
        fwrite(&temp,sizeof(temp),1,fp);
        flag=1;
        break;
    }
}
if(flag==1)
{
    printf("\n\t\tEDITING COMPLETED...\n");
    fclose(fp);
}
else
  printf("\n::SORRY! RECORD EDITING IS UNSUCCESSFUL AS RECORD DOES NOT EXIST YET::\n");
  fclose(fp);
}
void holiday(int year)
{
    int i=year;
    printf("\n*******************************************List Of Holidays For %d**********************************************\n",i);
    printf("                                           _____________________\n\n");
    printf("        January  %d\n",i);
    printf("01-01-%d    =>  New Year\n14-01-%d    =>  Makar Sankranti / Pongal \n23-01-%d    =>  Netaji Subhas Chandra Bose Jayanti\n26-01-%d    => Republic day\n\n\n",i,i,i,i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        February %d\n",i);
    printf("10-02-%d    => Guru Ravidas Jayanti\n19-02-%d    => Chatrapati Shivaji Jayanti\n21-02-%d    =>  Maharishi Dayanand Saraswati Jayanti\n\n\n",i,i,i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        March %d\n",i);
    printf("15-03-%d    =>  Kanshi Ram Jayanti\n\n\n",i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        April %d\n",i);
    printf("09-04-%d    =>  Mahavir Jayanti\n14-04-%d    =>  Dr. B.R. Ambedkar Jayanti\n\n\n",i,i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        May %d\n",i);
    printf("09-05-%d    =>  Rabindranath Tagore Jayanti\n\n\n",i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        June %d\n",i);
    printf("15-06-%d    =>  Maharana Pratap Jayanti\n\n\n",i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        August %d\n15-08-%d   => Independence Day\n\n\n",i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        October %d\n2-10-%d    => Mahatama Gandhi Jayanti/Lal Bahadur Jayanti\n31-10-%d    =>  Sardar Patel Jayanti\n\n\n",i,i,i,i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        November %d\n04-11-%d   => Guru Nanak Jayanti\n\n\n",i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
    printf("        December %d\n07-12-%d    =>  Armed Forces Flag Day\n25-12-%d   =>  Christmas\n",i,i,i,i);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------------------------------");
}
void func(int days[],int c,int d)
{
    if(i<12)
    {
	    days[i]=(c+d)%7;
        //printf("%d\t",days[i]);
        i++;
        func(days,md[i-1],days[i-1]);
    }
}
