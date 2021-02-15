#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
#define MAX 10
struct node
{
	int counter; //nodeun esik degerini asip asmadigimizi olcmek icin kullanilan sayac
	char word[MAX]; //nodeun sakladigi string
	struct node *prev; //onceki node
	struct node *next; //sonraki node
};

struct node *head=NULL;
struct node *temp;


void printList() /* PRINTING CACHE BUFFER */
{  
	struct node *p=head;
	while(p!=NULL)
	{
		printf("%s,%d - ",p->word,p->counter);
		p=p->next;
	}
}
void deleteList(struct node **head) /*CLEANING CACHE BUFFER*/
{ 
	struct node *p=*head;
	struct node *next;
	while(p!=NULL)
	{
		next=p->next;
		free(p);
		p=next;
	}
	*head=NULL;
}

int main(){
	FILE *dosya;
	int sec=1;
	int deleteAnswer; // 1 to DELETE / 0 TO CONTINUE / -1 TO TERMINATE
	int counterLimit; // LIMIT OF EACH CACHE BUFFER
	int listLimit;	//	CAPACITY OF CACHE BUFFER
	int listCounter;// COUNTER TO CALCULATE THE CAPACITY OF CACHE BUFFER BY THE STRING USER ENTERED
	char kelime[MAX]; // INPUT STRING
	printf("-1 TO TERMINATE\n");
	printf("CAPACITY of the CACHE BUFFER:");
	scanf("%d",&listLimit);
	if(listLimit==-1){
		printf("PROGRAM TERMINATED...\n");
		return 0;
	}
	printf("LIMIT of the CACHE BUFFER:");
	scanf("%d",&counterLimit);
	if(counterLimit==-1)
	{
		printf("PROGRAM TERMINATED...\n");
		return 0;	
	}
	printf("\n");
	printf("1 for STD INPUT / 0 for READING from FILE:");
	scanf("%d",&sec);
	if(sec==1)
	{
		int endFlag;
		endFlag=1;	
		while(endFlag==1)
		{
			printf("ENTER THE WORD: (TYPE exit to TERMINATE)"); 
			scanf("%s",kelime);
			char cik[MAX];
			strcpy(cik,"exit");
			if(strcmp(kelime,cik)==0)
			{
				return 0;
			}
			printf("\n");
			if(head==NULL)
			{	//FIRST FORM of the LIST and FORM AFTER DELETION PROCESS
				head=(struct node*)malloc(sizeof(struct node));
				strcpy(head->word,kelime);
				head->counter=1;
				head->next=NULL;
				head->prev=NULL;
				listCounter=1;
				if(listCounter>listLimit)
				{ //	CASE : LIMIT=0
					struct node *temp=head;
					head->next=NULL;
					head->prev=NULL;
					free(temp);
				}
			}
			else
			{ //		CASE : LIST HAS AT LEAST 1 NODE
				struct node *indis=head;
				char str1[MAX], str2[MAX];
				strcpy(str1,kelime);
				strcpy(str2,indis->word);
				int stringCompareReturn=strcmp(str1,str2);
				while(stringCompareReturn!=0 && indis!=NULL)
				{ 
					strcpy(str2,indis->word);
					stringCompareReturn=strcmp(str1,str2);	
					indis=indis->next;			
				}
				if(stringCompareReturn==0)
				{ //	CASE: THE STRING HAS ALREADY IN A NODE IN LIST
					if(indis==head)
					{ //CASE: STRING FOUND IN FIRST NODE
						indis->counter++;
					}
					else if(indis==NULL)
					{//	CASE: STRING FOUND IN LAST NODE
						indis=head;		 
						while(indis->next!=NULL)
						{
							indis=indis->next;
						}
						indis->counter++;
					}
					else
					{
						indis=indis->prev; 
						indis->counter++;   
					}
					
					if(indis->counter>counterLimit)
					{ 
						if(indis!=head && indis->next!=NULL)
						{ // CHECKING IF THE COUNTER IS GREATER THAN LIMIT
															
							indis->next->prev=indis->prev;
							indis->prev->next=indis->next;
							indis->next=head;
							indis->prev=NULL;
							head->prev=indis;
							head=indis;
						}
						else if(indis!=head && indis->next==NULL)
						{//	CHECKING LAST NODE IS GREATER THAN LIMIT
							indis->prev->next=NULL;
							indis->next=head;
							indis->prev=NULL;
							head->prev=indis;
							head=indis;							
						}
					}
				}											
				else
				{		//IF THE INPUT STRING IS NOT ONE OF THE NODES
					struct node *bas=(struct node*)malloc(sizeof(struct node)); // CREATING NEW NODE WITH INPUT STRING AND MAKING IT HEAD NODE
					char str3[MAX];
					strcpy(str3,kelime);
					strcpy(bas->word,str3);
				
					bas->counter=1;	
					bas->next=head;
					bas->prev=NULL;
					head->prev=bas;
					head=bas;
					listCounter=0;
					struct node *indis=head;
					while(indis!=NULL)
					{
						listCounter++;			//COUNTER FOR NODES
						indis=indis->next;
					}
					if(listCounter>listLimit)
					{ // CHECKING THE CACHE BUFFER (FULL or ABLE to ADD)
						indis=head;
						while(indis->next!=NULL)
						{ //DELETING LAST NODE
							indis=indis->next;
						}
						struct node *p=indis->prev;
						free(indis);
						p->next=NULL;
					}
				}	
			}
			printList(); 
			printf("\n");
			int deleteFlag=0;
			while(deleteFlag==0)
			{
			
				printf("1 to CLEAN ALL LIST / 0 to CONTINUE without CLEANING / -1 to TERMINATE:\n");
				scanf("%d",&deleteAnswer); //silme onayi icin tanimlanan degisken
				if(deleteAnswer==1 || deleteAnswer==-1 || deleteAnswer==0)
				{
					deleteFlag=1;
				}
				else printf("INPUT ERROR!\t");
			}
			
			if(deleteAnswer==-1)
			{
				printf("PROGRAM TERMINATED...\n");
				return 0;
			}
			else if(deleteAnswer==1)
			{
				deleteList(&head); //liste siliniyor
				printf("THE LIST IS DELETED.\n");
				printList(); 
				printf("\n");
			}		
		}
	}
	else
	{
		if ((dosya=fopen("text.txt","r"))==NULL)
		{
				printf("FILE ERROR!\n");
				exit(1);
		}
		else
		{
			struct node *head=NULL;
			while(fgets(kelime,sizeof(kelime),dosya)!=NULL)
			{
				kelime[strcspn(kelime,"\n")]='\0';
				if(head==NULL)
				{		//FIRST FORM of the LIST and FORM AFTER DELETION PROCESS
					head=(struct node*)malloc(sizeof(struct node));
					strcpy(head->word,kelime);
					head->counter=1;
					head->next=NULL;
					head->prev=NULL;
					listCounter=1;
					if(listCounter>listLimit)
					{ //CASE : LIMIT=0
						struct node *temp=head;
						head->next=NULL;
						head->prev=NULL;
						free(temp);
					}
				}
				else
				{		//		CASE : LIST HAS AT LEAST 1 NODE
					struct node *indis=head;
					char str1[MAX], str2[MAX];
					strcpy(str1,kelime);
					strcpy(str2,indis->word);
					int stringCompareReturn=strcmp(str1,str2);
					while(stringCompareReturn!=0 && indis!=NULL)
					{ 
						
						strcpy(str2,indis->word);
						stringCompareReturn=strcmp(str1,str2);	
						indis=indis->next;			
					}
					if(stringCompareReturn==0)
					{ //	CASE: THE STRING HAS ALREADY IN A NODE IN LIST
						if(indis==head)
						{ //	CASE: STRING FOUND IN FIRST NODE
						
							indis->counter++;
						}
						else if(indis==NULL)
						{//		CASE: STRING FOUND IN LAST NODE
							indis=head;		 
							while(indis->next!=NULL)
							{
								indis=indis->next;
							}
								indis->counter++;
						}
						else
						{	
							indis=indis->prev; 
							indis->counter++;  
						}
						if(indis->counter>counterLimit)
						{ 
							if(indis!=head && indis->next!=NULL)
							{ 	// CHECKING IF ONE OF THE MIDDLE NODES IS GREATER THAN LIMIT
																
								indis->next->prev=indis->prev;
								indis->prev->next=indis->next;
								indis->next=head;
								indis->prev=NULL;
								head->prev=indis;
								head=indis;
							}
							else if(indis!=head && indis->next==NULL)
							{//	CHECKING IF LAST NODE IS GREATER THAN LIMIT
								indis->prev->next=NULL;
								indis->next=head;
								indis->prev=NULL;
								head->prev=indis;
								head=indis;		
							}
						}
					}											
					else
					{		//IF THE INPUT STRING IS NOT ONE OF THE NODES
						struct node *bas=(struct node*)malloc(sizeof(struct node)); // CREATING NEW NODE WITH INPUT STRING AND MAKING IT HEAD NODE
						char str3[MAX];
						strcpy(str3,kelime);
						strcpy(bas->word,str3);
						bas->counter=1;	
						bas->next=head;
						bas->prev=NULL;
						head->prev=bas;
						head=bas;
						listCounter=0;
						struct node *indis=head;
						while(indis!=NULL)
						{
							listCounter++;			//COUNTER FOR NODES
							indis=indis->next;
						}
						if(listCounter>listLimit)
						{ //IF THE CACHE BUFFER IS FULL
							indis=head;
							while(indis->next!=NULL)
							{ //DELETING LAST NODE
								indis=indis->next;
							}
							struct node *p=indis->prev;
							free(indis);
							p->next=NULL;
						}
					}	
				}
					struct node *p=head;
					while(p!=NULL)
					{
						printf("%s,%d - ",p->word,p->counter);
						p=p->next;
					} 			
					printf("\n");
			}
		fclose(dosya);
		}
	}
	return 0;
} 



	
