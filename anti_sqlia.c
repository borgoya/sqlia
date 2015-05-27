#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#define MAX_SIZE 125

// ALL SQL STATEMENT WILL BE GIVEN BY THE USER IS ASSUMED TO BE CAPITAL
// IF FIRST SELECT TOKEN IS NOT MATCHED NO CHANCE FOR TEST OTHERS
// CHECKS THE TOKEN ONE BY ONE
// IF STRING NOT MATCHED TILL THE END TOKEN THEN REJECTED
// IF MATCHED THEN ACCEPTED

char token[0][125];
int select_stmt();
int select_list();
int from_clause();
int where_clause();
int tbl_list();
int bcond();
int comp();
int dbCol();
int inputString();
char *tokenizer();
int inputChecker();
int opChecker();
int split_up();
int idList(char *c);
void appender(char *str,int i);

int split_up(char* string, char* arg[])
{
    char* p = string;
    int argc = 0;

    while(*p != '\0')
    {
        while(isspace(*p))
            ++p;

        if(*p != '\0')
            arg[argc++] = p;
        else
            break;

        while(*p != '\0' && !isspace(*p))
            p++;
        if(*p != '\0')
        {
            *p = '\0';
            ++p;
        }

    }

    return argc;
}

int select_stmt(){
    char token1[10];
    int counter=0;
    strcpy(token1,"SELECT");
    //printf("%s\n",token[0]);
    int flag=strcmp(token[0],token1);
    //printf("FLAG VALUE:%d",flag);
    if(flag==0){
        //printf("\nSELECT MATCHED");
        int slist=select_list();
        if(slist>0){
            ++counter;
            //printf("\n* MATCHED");
            // cannot return the value here because if we return here then no checking for next tokens
            // counter will be increment only when select_list matches
        }
        else{
            return(-99);
        }

        int fromCheck=from_clause();
        if(fromCheck>0){
            ++counter;
            //printf("\nTABLE LIST MATCHED");
        }
        else{
            return(-99);
        }

        int whCheck=where_clause();
        if(whCheck>0){
            ++counter;
            //printf("\nWHERE MATCHED");
            return(counter);
        }

        else{
            return(-99);
        }
    }

    else{
        return(-99);
    }
}

int select_list(){
    char token2[10];
    int flag;
    strcpy(token2,"*");
    //printf("%s",token2);
    flag=strcmp(token[1],token2);
    //printf("\n* FLAG:%d",flag);
    if(flag==0){
        return(1);
    }
    else{
        return(-99);
    }
}

int from_clause(){
    char token3[10];
    int flag=0;
    strcpy(token3,"FROM");
    int tbCheck;
    flag=strcmp(token[2],token3);
    if(flag==0){
        //printf("FROM MATCHED\n");
        int tbCheck=tbl_list();
        if(tbCheck>0){
            return(99);
        }
        else{
            return(-99);
        }
    }
    else{
        return(-99);
    }
}

int tbl_list(){
    int len,c;
    int tf=0;
    char token4[10];
    strcpy(token4,token[3]);
    len=strlen(token4);
    for(c=0;c<len;c++){
        int checker=idList(&token4[c]);
        if(checker>0){
            tf++;
        }
        else{
            tf=0;
            break;
        }
    }

    if(tf==0){
        return(-99);
    }
    else{
        // TABLE LIST MATCHED
        return(99);
    }
}

int idList(char *c){
    if( *c >= 'a' && *c <= 'z' || *c >= 'A' && *c <= 'Z' || *c >= '0' && *c <= '9' ){
            return(99);
        }
    else{
            return(-99);
        }
}


int where_clause(){
    char token5[10];
    int flag=0,counter=0;
    strcpy(token5,"WHERE");
    flag=strcmp(token5,token[4]);
    if(flag==0){
                //printf("\nWHERE MATCHED");
        int logCondCheck=bcond();
        if(logCondCheck>0){
                return(99);
        }
        else{
            return(-99);
        }
    }
    else{
        return(-99);
    }
}

int bcond(){

        int counter=0;
        int checker1 = bterm();
        if(checker1>0){
            ++counter;
        }
        else{
            return(-99);
        }

        int opCheck=opChecker();
        if(opCheck>0){
            ++counter;
        }
        else{
            return(-99);
        }


        int checker2 = bterm();
        if(checker2>0){
            ++counter;
        }
        else{
            return(-99);
        }


        if(counter==3){
            return(99);
        }
        else{
            return(-99);
        }
}


int opChecker(){
    char token9[10];
    int len,c,tf=0;
    strcpy(token9,token[8]);
    int flag=strcmp(token9,"AND");
    if(flag==0){
        return(9);
    }
    else{
        return(9);
    }
}


int bterm(){
        int counter;
        int dbCheck=dbCol();
        if(dbCheck>0){
            ++counter;
            //printf("\nDATABASE ATTRIBUTE MATCHED");
        }
        else{
            return(-99);
        }

        int compCheck=comp();
        if(compCheck>0){
                ++counter;
            //printf("\nCOMPARE MATCHED");
        }
        else{
            return(-99);
        }

        int inputCheck=inputString();
        if(inputCheck>0){
                ++counter;
                //printf("\nINPUT NAME MATCHED");
        }
        else{
            return(-99);
        }

        if(counter==3){
            return(counter);
        }
        else{
            return(-99);
        }


}

int dbCol(){
    char token6[10];
    int c,len,tf=0;
    strcpy(token6,token[5]);
    //printf("%s",token6);
    len=strlen(token6);
    for(c=0;c<len;c++){
        int checker=idList(&token6[c]);
        if(checker>0){
            tf++;
        }
        else{
            tf=0;
            break;
        }
    }

    if(tf==0){
        return(-99);
    }
    else{
        // TABLE LIST MATCHED
        return(99);
    }

}



int comp(){
    char token7[10];
    strcpy(token7,token[6]);
    int flag1= strcmp(token7,"=");
    int flag2= strcmp(token7,"!=");
    int flag3= strcmp(token7,"<");
    int flag4= strcmp(token7,">");
    int flag5= strcmp(token7,">=");
    int flag6= strcmp(token7,"<=");
    if(flag1==0 || flag2==0 || flag3==0 || flag4==0 || flag5==0 || flag6==0){
            return(1);
    }
    else{
        return(-99);
    }

}

int inputString(){
    char token8[10];
    int len,c,tf=0;
    strcpy(token8,token[7]);
    len=strlen(token8);
   	if(token8[0]==34){
        ++tf;
	   	//printf("\nGOT A DOUBLE QUOTATION");
	   	//printf("%c",token8[0]);
	}
	else{
        tf=-1;
        return(tf);
	}

    // for the two double quotes loop starts like this
    // the input is inside the double quote
    for(c=1;c<=len-1;c++){
        char inputChar=token8[c];
        int tf=inputChecker(&inputChar);
        if(tf<0){
            return(-99);
        }
        else{
            return(99);
        }
    }

    if(token8[len]==34){
        ++tf;
        //printf("\nGOT A DOUBLE QUOTATION");
	   	//printf("%c",token8[len]);
    }
    else{
        tf=-1;
        return(tf);
    }

}

int inputChecker(char *c){
    //printf("\n%c",*c);
    if(*c==39){
        return(-9);
    }
    else if(*c==92){
        return(-9);
    }

    else if(*c==47){
        return(-9);
    }

    else if(*c==32){
        return(-9);
    }
    else{
        return(1);
    }
}

int main()
{
    int i;
    char *ch;
    char *av[MAX_SIZE];

    FILE *fp;
    int qLength;
    char sqlQuery[999];

    fp = fopen("sqlQuery.txt" , "r");
    if(fp == NULL) {
      perror("\nError opening file");
      return(-1);
    }

    while(fgets(sqlQuery,sizeof(sqlQuery),fp)!= NULL){

		int ac = split_up(sqlQuery, av);
		for(i = 0; i < ac; i++){
			ch=av[i];
			appender(ch,i);
			}
		printf("\n");
		int checkMain=select_stmt();
		if(checkMain>0){
			printf("=>STRING ACCEPTED\n");
		}
		else{
			printf("=>STRING REJECTED\n");
		}
		printf("\n");
    }

    return 0;
}

void appender(char *str,int i){
    int len=strlen(str);
	printf("%s ",str);
    strcpy(token[i],str);
}
