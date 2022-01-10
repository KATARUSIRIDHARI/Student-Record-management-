#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct student{
    int rno;
    char name[20];
    struct subject{
        int scode;
        char name[20];
        int marks;
    }sub[3];
    int total;
    float per;
}student;

void insert(){
        student *s;
       FILE *fp;
        int n,i,j;// i for each student and j for each subject

        printf("Enter how many students you want to enter : ");
        scanf("%d",&n);
        s = (student*)calloc(n,sizeof(student));
        fp = fopen("mystudents1.txt","ab+");

        for(i=0;i<n;i++){
            s[i].total=0;
            s[i].per=0;
            printf("Enter RollNo : ");
            scanf("%d",&s[i].rno);
            printf("Enter the name of student: ");
            fflush(stdin);
            scanf("%[^\n]s",s[i].name);
            for(j=0;j<3;j++){
                printf("Enter Marks of Sub%d : ",j+1);//sub means subject
                scanf("%d",&s[i].sub[j].marks);
                s[i].total += s[i].sub[j].marks;
            }
            s[i].per = s[i].total / 3.0;

            fwrite(&s[i],sizeof(student),1,fp);
        }
         printf("Record(s) added successfully\n\n\n\n");
        fclose(fp);
}

void search(){
    int  j, found=0;
    student s1;
    FILE *fp;
    int rno;
    printf("Enter RollNo to Search : ");
    scanf("%d",&rno);

    fp = fopen("mystudents1.txt","r");
    printf("\nR.No  Name\t\t   S1  S2  S3   Total   Percentage\n");
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found = 1;
            printf("\n%-5d%-20s",s1.rno,s1.name);
            for(j=0;j<3;j++){
                printf("%4d",s1.sub[j].marks);
            }
            printf(" %5d    %7.2f",s1.total,s1.per);
        }
    }
    if(found==0)
        printf("\n Record Not Found\n");
    fclose(fp);
}

void update(){
    int  j, found=0;
    student s1;
    FILE *fp, *fp1;
    int rno;
    printf("Enter RollNo to Update : ");
    scanf("%d",&rno);

    fp = fopen("mystudents1.txt","r");
    fp1 = fopen("temp.txt","w");
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found = 1;
            s1.total=0;
            s1.per=0;
            printf("Enter New Name : ");
            fflush(stdin);
            scanf("%[^\n]s",s1.name);
            for(j=0;j<3;j++){
                printf("Enter New Marks of Sub%d : ",j+1);
                scanf("%d",&s1.sub[j].marks);
                s1.total += s1.sub[j].marks;
            }
            s1.per = s1.total / 3.0;
        }
        fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);


    if(found){
            fp = fopen("mystudents1.txt","w");
            fp1 = fopen("temp.txt","r");

            while(fread(&s1,sizeof(student),1,fp1)){
                fwrite(&s1,sizeof(student),1,fp);
            }
            printf("UPDATED SUCCESSFULLY");
            fclose(fp);
            fclose(fp1);
    }
    else
        printf("\n Record Not Found\n");
}


void delete_rec(){
    int found=0;
    student s1;
    FILE *fp, *fp1;
    int rno;
    printf("Enter RollNo to Delete : ");
    scanf("%d",&rno);

    fp = fopen("mystudents1.txt","r");
    fp1 = fopen("temp.txt","w");
    while(fread(&s1,sizeof(student),1,fp)){
        if(s1.rno == rno){
            found = 1;
        }
        else
            fwrite(&s1,sizeof(student),1,fp1);
    }
    fclose(fp);
    fclose(fp1);


    if(found){
            fp = fopen("mystudents1.txt","w");
            fp1 = fopen("temp.txt","r");

            while(fread(&s1,sizeof(student),1,fp1)){
                fwrite(&s1,sizeof(student),1,fp);
            }
            printf("DELETED SUCCESSFULLY");
            fclose(fp);
            fclose(fp1);
    }
    else
        printf("\nNot Found.....\n");
}


void noofrec(){
       // student s1;
        FILE *fp;
        fp = fopen("mystudents1.txt","r");
        fseek(fp,0,SEEK_END);
        int n = ftell(fp)/sizeof(student);
        printf("\nNo of Records = %d\n",n);
        fclose(fp);
}
void display(){
        student s1;
        FILE *fp;
        int j;
        fp = fopen("mystudents1.txt","r");
         printf("\nR.No   Name\t\t   S1  S2  S3   Total   Percentage\n");
        while(fread(&s1,sizeof(student),1,fp))
        {
            printf("\n%-5d %-20s",s1.rno,s1.name);
            for(j=0;j<3;j++){
                printf("%4d",s1.sub[j].marks);
            }
            printf(" %5d    %7.2f",s1.total,s1.per);
        }
        fclose(fp);
}

int main(){
    int ch;
    FILE *fp;
    do{
            printf("\n\t\t\t**********************************************************************************************\n\n");
        printf("\n1.INSERT");
        printf("\n2.DISPLAY");
        printf("\n3.NO OF RECORDS");
        printf("\n4.SEARCH");
        printf("\n5.UPDATE");
        printf("\n6.DELETE");
        printf("\n0.EXIT");
        printf("\nEnter Your Choice : ");
        scanf("%d",&ch);
        switch(ch){
        case 1:
                insert();
            break;
        case 2:
                display();
            break;
        case 3:
                noofrec();
        break;
        case 4:
                search();
        break;
        case 5:
                update();
            break;
        case 6:
                delete_rec();
            break;
        case 0:
            printf("\t\t\t********************\n");
                printf("\n\n\t\t\tThank  You\n\n");
            printf("\t\t\t*******************\n\n");
        }
        }while(ch!=0);

    return 0;
}
