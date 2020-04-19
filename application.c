#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#define MAXIMUM_NUMLEN 20
typedef char num[MAXIMUM_NUMLEN];
typedef struct{
    int n;
    num *numbers; 
}KType;
typedef KType key[26];
void readMe(char *);
void readKey(FILE *,key);
char *get_Number(char,key);
char getLetter(char *,key);
void encryptFile(FILE *plaintextfile, FILE *En_Dec_textfile, key KeyArray) {
    int StreamingChar;
     while((StreamingChar=getc(plaintextfile))!=EOF){
        if(isalpha(StreamingChar)){
            fprintf(En_Dec_textfile,"%s ",get_Number(tolower(StreamingChar),KeyArray));
        }
    else if(isdigit(StreamingChar)){
        fprintf(En_Dec_textfile,"{%c}",StreamingChar); }
    else if(StreamingChar=='\n'){ 
        fprintf(En_Dec_textfile," -1\n");
    } 
    else{
    fprintf(En_Dec_textfile,"%c",StreamingChar);    
    } 
    }
}
void decryptFile(FILE *plaintextfile, FILE *En_Dec_textfile, key KeyArray) {
    int StreamingChar,position,Lcharacter,Xcharacter;
     char BLOCK[100],Pcharacter;
      while((StreamingChar=getc(plaintextfile))!=EOF){
        position=0; 
        if(isdigit(StreamingChar)){
            BLOCK[position++]=StreamingChar;
            StreamingChar=getc(plaintextfile);
            while((isdigit(StreamingChar))&&(StreamingChar!=EOF)){
                BLOCK[position++]=StreamingChar;
                StreamingChar=getc(plaintextfile); 
                }
            if(StreamingChar!=' ') 
                ungetc(StreamingChar,plaintextfile);
            BLOCK[position]='\0'; 
            Pcharacter=getLetter(BLOCK,KeyArray); 
            if(Pcharacter) 
                putc(Pcharacter,En_Dec_textfile); 
            else 
                fprintf(En_Dec_textfile,"Can't Find!");
}
else if(StreamingChar=='-'){
    Lcharacter=getc(plaintextfile); 
    if(Lcharacter=='1'){
        Xcharacter=getc(plaintextfile); 
        if(Xcharacter=='\n'){
            fprintf(En_Dec_textfile,"\n");
            continue; 
            }
        else {
 
        ungetc(Xcharacter,plaintextfile);
        ungetc(Lcharacter,plaintextfile); }
    }
    else{
        ungetc(Lcharacter,plaintextfile); 
        putc(StreamingChar,En_Dec_textfile); 
        continue;
    }
    putc(StreamingChar,En_Dec_textfile); 
}
else if(StreamingChar=='{'){ 
    Lcharacter=getc(plaintextfile); 
    if(isdigit(Lcharacter)){
        Xcharacter=getc(plaintextfile); 
        if(Xcharacter=='}'){
            putc(Lcharacter,En_Dec_textfile);
            continue; }
        else{ 
            ungetc(Xcharacter,plaintextfile); 
            ungetc(Lcharacter,plaintextfile);
        } 
    }
    else {
        ungetc(Lcharacter,plaintextfile); 
        putc(StreamingChar,En_Dec_textfile); 
        continue;
    }
    putc(StreamingChar,En_Dec_textfile); 
    }

else putc(StreamingChar,En_Dec_textfile); }
}
int main(int argc,char *argv[]) {
    key KeyArray;
    int FLAG_ENC=1;
    int SWITCH=0;
    FILE *FileWithKey, *plaintextfile, *En_Dec_textfile; 
    if((argc!=4)&&(argc!=5))
        readMe(argv[0]); 
    else{
        if((argv[1])[0]=='-'){ 
            SWITCH=1; 
            if(strlen(argv[1])!=2)
                readMe(argv[0]); 
            else {
                if(tolower((argv[1])[1])=='e'); 
            else if(tolower((argv[1])[1])=='d')
                FLAG_ENC=0; 
            else readMe(argv[0]);
            } 
            }
        if(SWITCH&(argc!=5)) readMe(argv[0]);

            //read-write file calls 
            if((FileWithKey=fopen(argv[1+SWITCH],"r"))==NULL){
            fprintf(stderr,"Error opening key file.\n");
            exit(1); 
        }
    if((plaintextfile=fopen(argv[2+SWITCH],"r"))==NULL){ 
        fprintf(stderr,"Error opening input file.\n");
        exit(1);
    } 
   
   if((En_Dec_textfile=fopen(argv[3+SWITCH],"w"))==NULL){
    fprintf(stderr,"Error opening output file.\n");
    exit(1); 
    }
    }

    readKey(FileWithKey,KeyArray);
    fclose(FileWithKey);
    srand(time(NULL));
    if(FLAG_ENC) encryptFile(plaintextfile,En_Dec_textfile,KeyArray); 
    else decryptFile(plaintextfile,En_Dec_textfile,KeyArray); 
    fclose(plaintextfile);

    fclose(En_Dec_textfile);
}

void readMe(char *name) {
    printf("readMe: %s -e FileWithKey plaintextfile En_Dec_textfile\n",name); 
    printf("\n-e is the encrypt mode\n");
    printf("\n-d is the decrypt mode\n");
    printf("\nFileWithKey has 26 lines for 26 alphabets\n");
    printf("\nEach line in KeyWithFile choices of substitutions for each letter");
    exit(1);
    }

char *get_Number(char letter,key KeyArray) {
        int tempr;
        char *result;
        tempr=rand();
        tempr%=KeyArray[letter-'a'].n; result=(char*)KeyArray[letter-'a'].numbers[tempr]; 
        return(result);
}
 
char getLetter(char *number,key KeyArray) {
    int i,j; for(i=0;i<26;i++)
    for(j=0;j<KeyArray[i].n;j++) if(!(strcmp(number,KeyArray[i].numbers[j])))
    return(i+'a'); 
    return('\0');
}

void readKey(FILE *FileWithKey,key KeyArray) {
    int i,j,n; 
    for(i=0;i<26;i++){
        fscanf(FileWithKey,"%d",&n); KeyArray[i].n=n; KeyArray[i].numbers=calloc(n,sizeof(num)); 
        for(j=0;j<n;j++)
            fscanf(FileWithKey,"%s",KeyArray[i].numbers[j]); 
    }
}
