#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct data {
    char date[30];
    char list[30];
    char type;
    int money;
    int total=0;
}log_money[100];
struct lastbill {
    int index;
    int total;
};
data deposit(char date[], char list[], int depo,int total) {
    data t;
    strcpy(t.date, date);
    strcpy(t.list, list);
    t.money = depo;
    t.total = total+depo;
    return t;
}
data withdraw(char date[], char list[], int with, int total) {
    data t;
    strcpy(t.date, date);
    strcpy(t.list, list);
    t.money = with;
    t.total =total - with;
    return t;
};
void printbill(FILE* fptr,int index) {
   
    fprintf(fptr, "==============================\n         Money diary\n       Data in bill\n==============================\n");
    fprintf(fptr, "date      type   list    p/e  total\n");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }

    //fprintf(fptr, "%d", num);
    int i;
    for (i = 0; i < index; i++) {
        fprintf(fptr, "%s %c %s %d %d\n", log_money[i].date,log_money[i].type, log_money[i].list, log_money[i].money, log_money[i].total);
    }
 
}
lastbill filetostruct(FILE* fptr) {
    int i, j;
    char stringtemp[500];
    char stringstruct[5][100];
    int indexlog = 0;
    int count = 0;
    int indexlogmoney = 0;
    int indexstruct = 0;
    int indexstr = 0;
    lastbill t;
    while (1)
    {
        char c = fgetc(fptr);
        if (c == EOF)
            break;
        else
        {
            if (c != '\n') {
                stringtemp[indexstr] = c;
                indexstr++;
            }
            else {
                char* token = strtok(stringtemp, " ");
                while (token != NULL) {
                    if (indexlog >= 12) {
                     //  printf("%d %s\n", indexstruct, token);
                        strcpy(stringstruct[indexstruct], token);
                        indexstruct++;
                        if (indexstruct > 4) {
                            strcpy(log_money[count].date, stringstruct[0]);
                            log_money[count].type = stringstruct[1][0];
                            strcpy(log_money[count].list, stringstruct[2]);
                            log_money[count].money = atoi(stringstruct[3]);
                            log_money[count].total = atoi(stringstruct[4]);
                            indexstruct = 0;
                            for (i = 0; i < 5; i++) {
                                for (j = 0; j < 100; j++) {
                                    stringstruct[i][j] = '\0';
                                }
                            }
                            count++;
                        }
                    }
                    indexlog++;
                    token = strtok(NULL, " ");

                }
                for (i = 0; i < 500; i++) {
                    stringtemp[i] = '\0';
                }
                indexstr = 0;

            }
        }
    }
    //printf("after\n");
    for (int i = 0; i < count; i++) {
        printf("%s %c %s %d %d\n", log_money[i].date,log_money[i].type, log_money[i].list, log_money[i].money, log_money[i].total);
    }
    t.index = count;
    t.total = log_money[count - 1].total;
    return t;
}
int main()
{
    int num,decition=3,total=0,index=0,i,j;
    char next;
    data tempo;
    lastbill lastBill;
    FILE* fptr;
   
    //fprintf(fptr, "%d", num);
    fptr = fopen("./program.txt", "r");
    lastBill = filetostruct(fptr);
    index = lastBill.index;
    total = lastBill.total;
    fclose(fptr);
    system("cls");
    while (1) {
        if (decition == 3) {
            //system("cls");
            printf("Hi What is your order? [1]add list [2]view search &edit [0]exit\n");
            scanf("%d", &decition);
        /*    printf("Hi What is your order? [1]deposit [2]withdraw\n");
            scanf("%d",&decition);
            if (decition==1)
            {
                system("cls");
                printf("Deposit : enter your date (mm/dd/yyyy) list and cost\n");
               
                scanf("%s %s %d", tempo.date, tempo.list, &tempo.money);
                tempo = deposit(tempo.date, tempo.list, tempo.money,total);
                total = tempo.total;
                log_money[index] = tempo;
                index++;
                printf("Your total is %d\n", total);
               
            }
            else if (decition == 2)
            {
                system("cls");
                printf("Withdraw : enter your date (mm/dd/yyyy) list and cost\n");
            
                scanf("%s %s %d", tempo.date, tempo.list, &tempo.money);
                tempo = withdraw(tempo.date, tempo.list, tempo.money, total);
                total = tempo.total;
                log_money[index] = tempo;
                index++;
                printf("Your total is %d\n", total);
                
            }*/
        }
        
        else if (decition == 1) {
            int decitionin;
           // system("cls");
            printf("What is your order? [1]deposit [2]withdraw [0]back\n");
            scanf("%d", &decitionin);
            if (decitionin == 1)
            {
              //  system("cls");
                printf("Deposit : enter your date (mm/dd/yyyy) list and cost\n");

                scanf("%s %s %d", tempo.date, tempo.list, &tempo.money);
                tempo = deposit(tempo.date, tempo.list, tempo.money, total);
                total = tempo.total;
                tempo.type = 'd';
               
                log_money[index] = tempo;
                index++; 
                fflush(stdin);
                printf("Your total is %d\n", total);
             
              
            }
            else if (decitionin == 2)
            {
               // system("cls");
                printf("Withdraw : enter your date (mm/dd/yyyy) list and cost\n");

                scanf("%s %s %d", tempo.date, tempo.list, &tempo.money);
                tempo = withdraw(tempo.date, tempo.list, tempo.money, total);
                total = tempo.total;
                tempo.type = 'w';
                log_money[index] = tempo;
                index++;
                fflush(stdin);
                printf("Your total is %d\n", total);
                
            }
            else if (decitionin == 0)
            {
                decition = 3;
            }
        }
        else if (decition == 2) { 
            int decitionin;
            char datesearch[9];
            printf("What is your order? [1]view [2]search [3]edit [4]delete [0]back\n");
            scanf("%d", &decitionin);
            if (decitionin == 1) {
                printf("date   type  list    p/e   total\n");
                fptr = fopen("./program.txt", "r");
                filetostruct(fptr);
                fclose(fptr);
            }
            if (decitionin == 2) {
                printf("which date to search ?\n");
                scanf("%s", datesearch);
                for (i = 0; i < index; i++) {
                    if (!strcmp(log_money[i].date, datesearch)) {
                        printf("%s %c %s %d %d\n", log_money[i].date, log_money[i].type,log_money[i].list, log_money[i].money, log_money[i].total);
                    }
                }
            }
            if (decitionin == 3) {
                int line;
                data templine;
                printf("which date to edit ?\n");
                scanf("%s", datesearch);
                for (i = 0; i < index; i++) {
                    if (!strcmp(log_money[i].date, datesearch)) {
                        printf("found at line %d : %s %c %s %d %d\n",i, log_money[i].date, log_money[i].type, log_money[i].list, log_money[i].money, log_money[i].total);
                    }
                }
                printf("which line to edit ?\n");
                scanf("%d", &line);
                printf("enter your date (mm/dd/yyyy) type list and cost\n");
                scanf("%s %c %s %d", templine.date, &templine.type, templine.list, &templine.money);
                strcpy(log_money[line].date, templine.date);
                strcpy(log_money[line].list, templine.list);
                 log_money[line].type= templine.type;
                log_money[line].money = templine.money;
                if (line == 0) {
                    if (log_money[line].type =='d')
                    {
                        log_money[line].total = templine.money;
                    }
                    else if (log_money[line].type == 'w')
                    {
                        log_money[line].total = templine.money*-1;
                    }
                }
                else {
                        if (log_money[line].type == 'd')
                        {
                            log_money[line].total = templine.money + log_money[line - 1].total;
                        }
                        else if (log_money[line].type == 'w')
                        {
                            log_money[line].total = log_money[line - 1].total -  templine.money;
                        }
                    
                }
                for ( i = line+1; i < index; i++) {
                    if (log_money[i].type == 'd')
                    {
                        log_money[i].total = log_money[i].money + log_money[i - 1].total;
                    }
                    else if (log_money[i].type == 'w')
                    {
                        log_money[i].total = log_money[i - 1].total - log_money[i].money;
                    }
                }
            }
            else if (decitionin == 4) {
                int line;
                for (i = 0; i < index; i++) {      
                        printf("line %d : %s %c %s %d %d\n", i, log_money[i].date, log_money[i].type, log_money[i].list, log_money[i].money, log_money[i].total);
                }
                printf("which line is deleting?\n");
                scanf("%d", &line);
                if (line != 0) {
                    strcpy(log_money[line].date, log_money[line+1].date);
                    strcpy(log_money[line].list, log_money[line+1].list);
                    log_money[line].type = log_money[line+1].type;
                    log_money[line].money = log_money[line+1].money;
                    if (log_money[line].type == 'd')
                    {
                        log_money[line].total = log_money[line].money + log_money[line - 1].total;
                    }
                    else if (log_money[line].type == 'w')
                    {
                        log_money[line].total = log_money[line - 1].total - log_money[line].money;
                    }
                    for ( i = line + 1; i < index; i++) {
                 
                        strcpy(log_money[i+1].date, log_money[i].date);
                        strcpy(log_money[i+1].list, log_money[i].list);
                        log_money[i+1].type = log_money[i].type;
                        log_money[i+1].money = log_money[i].money;
                        if (log_money[i].type == 'd')
                        {
                            log_money[i].total = log_money[i].money + log_money[i - 1].total;
                        }
                        else if (log_money[i].type == 'w')
                        {
                            log_money[i].total = log_money[i - 1].total - log_money[i].money;
                        }
                    }
                    index--;
                }
                else {
                    strcpy(log_money[line].date, log_money[line + 1].date);
                    strcpy(log_money[line].list, log_money[line + 1].list);
                    log_money[line].type = log_money[line + 1].type;
                    log_money[line].money = log_money[line + 1].money;
                    if (log_money[line].type == 'd')
                    {
                        log_money[line].total = log_money[line].money;
                    }
                    else if (log_money[line].type == 'w')
                    {
                        log_money[line].total = log_money[line].money * -1;
                    }
                    for ( i = line + 1; i < index; i++) {

                        strcpy(log_money[i - 1].date, log_money[i].date);
                        strcpy(log_money[i - 1].list, log_money[i].list);
                        log_money[i - 1].type = log_money[i].type;
                        log_money[i - 1].money = log_money[i].money;
                        if (log_money[i].type == 'd')
                        {
                            log_money[i].total = log_money[i].money + log_money[i - 1].total;
                        }
                        else if (log_money[i].type == 'w')
                        {
                            log_money[i].total = log_money[i - 1].total - log_money[i].money;
                        }
                    }
                    index--;
                }
            }
            else if (decitionin == 0) {
                decition = 3;
            }
        }
        else if(decition==0) {
            fptr = fopen("./program.txt", "w");
            printbill(fptr, index);
            fclose(fptr);
            printf("Done\n");
            break;
        } 
      
    }
    
    /*fptr = fopen("./program.txt", "r");
    filetostruct(fptr);
    fclose(fptr);
    */
    /*FILE* fptr;
    fptr = fopen("./program.txt", "w");
    fprintf(fptr, "==============================\n         Money diary\n       Name : %s\n==============================\n",name);
    fprintf(fptr, "date     list    paid/earn   total");
    if (fptr == NULL)
    {
        printf("Error!");
        exit(1);
    }
   
    //fprintf(fptr, "%d", num);
    fclose(fptr);
    fptr = fopen("./program.txt", "r");
    char buff[255];
    fscanf(fptr, "%[^\n]", buff);
    if (buff != "==============================") {
        fptr = fopen("./program.txt", "w");
        fprintf(fptr, "==============================\n         Money diary\n       Name : %s\n==============================\n", name);
        fprintf(fptr, "date     list    paid/earn   total");
    }
    
    fclose(fptr);
    while (1) {

    }*/
    return 0;
}
// add type d/w;