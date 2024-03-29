#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define MAXINDEX 10000000
#define MAXCHAR 2
#define MAXHEX 8

int ***createbit(int ***bit){
    int i,j,y,z;
    bit=(int ***)calloc(MAXINDEX,sizeof(int **));
    if(!bit){
        printf("bitのメモリ不足\n");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<MAXINDEX;i++){
        bit[i]=(int **)calloc(MAXCHAR, sizeof(int *));
        if(!bit[i]){
            printf("bit[%d]のメモリ不足\n",i);
            for(z=0;z<i;z++){
                free(bit[z]);
            }
            free(bit);
            exit(EXIT_FAILURE);
        }
        for(j=0;j<MAXCHAR;j++){
            bit[i][j]=(int *)calloc(MAXHEX,sizeof(int));
            if(!bit[i][j]){
                printf("bit[%d][%d]のメモリ不足\n",i,j);
                for(y=0;y<i;y++){
                    for(z=0;z<j;z++){
                        free(bit[y][z]);
                    }
                    free(bit[y]);
                }
                free(bit);
                exit(EXIT_FAILURE);
            }
        }
    }
    return bit;
}
//ここの処理は後で変更
int ***createstring(int ***bit){
    int bitcal,bitcal2;
    int random;
    int ch;
    int count;
    int i,j,k;
    srand((unsigned)time(NULL));
    for(i=0;i<MAXINDEX;i++){
        bitcal2=1;
        random=rand()%63;
        count=0;
        for(j=0;j<random;j++){
            bitcal=1;
            ch=rand()%26+97;
            //printf("%c",ch);
            for(k=0;k<MAXHEX;k++){
                if(ch&bitcal){
                    bit[i][count][k]|=bitcal2;
                }
                bitcal<<=1;
            }
            if(bitcal2&0x80000000){
                count++;
                bitcal2=1;
            }
            else{
                bitcal2<<=1;
            }
        }
        //printf(":[%d]行目\n",i+1);
    }
    return bit;
}
//ここまで
void output(int ***bit,char *string){
    int bitcal,bitcal2;
    int ch,ch2,cha,chb;
    int count,count2;
    int figure,figure2;
    int i,j;
    bool flag,flag2;
    flag2=true;
    for(i=0;i<MAXINDEX;i++){
        bitcal=1;
        count=0;
        count2=0;
        flag=true;
        do{
            cha=0;
            chb=0;
            bitcal2=1;
            figure=0;
            figure2=0;
            for(j=0;j<MAXHEX;j++){
                ch=0;
                ch2=0;
                if(bit[i][count][j]&bitcal){
                    ch=(int)pow(2.0,(double)j);
                    cha+=ch;
                    figure++;
                }
                ch2=string[count2]&bitcal2;
                if(ch!=ch2){
                    flag=false;
                    break;
                }
                bitcal2<<=1;
            }
            if(cha!=string[count2]){
                flag=false;
                break;
            }
            if(cha==0 && string[count2]=='\0'){
                break;
            }
            else if(cha==0){
                flag=false;
                break;
            }
            else if(string[count2]=='\0'){
                flag=false;
                break;
            }
            if(flag==false){
                break;
            }
            if(bitcal&0x80000000){
                bitcal=1;
                count++;
            }
            else{
                bitcal<<=1;
            }
                count2++;
            }while(true);
            if(flag==true){
                printf("探索結果[%d]行目にありました\n",i+1);
                flag2=false;
            }
        }
    if(flag2==true){
        printf("探索結果はありませんでした\n");
    }
}
char *input(char *string){
    scanf("%s",string);
    return string;
}
int main(int argc, const char * argv[]) {
    // insert code here...
    int ***bit=NULL;
    char *string;
    string=(char *)calloc(32*MAXCHAR,sizeof(char));
    bit=createbit(bit);
    bit=createstring(bit);
    printf("入力OK\n");
    string=input(string);
    output(bit,string);
    
    return EXIT_SUCCESS;
}
