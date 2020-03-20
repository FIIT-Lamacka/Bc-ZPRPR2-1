#include <stdio.h>
#include <stdlib.h>
#define N 2
char ** malloc_array(int size_a, int size_b){
    char **pole;
    int i;

    pole = malloc(size_a * sizeof(*pole));

    for (i = 0; i < size_a; i++) {
        pole[i] = malloc(size_b * sizeof(pole[0]));
    }
    return pole;
}
/*int ** fill_coord(char **original){
    int i,j;
    char **coord;
    coord = malloc(26 * sizeof(int *));

    for (i = 0; i < 26; i++) {
        coord[i] = malloc(1 * sizeof(int *));
    }

    for(i=0;i<26;i++){
        for(j=0;j<5;j++){
           coord[i][j]=5;
        }}
    for(i=0;i<26;i++){
        for(j=0;j<5;j++){
           printf("%c",coord[i][j]);
        }}

}*/
void fill_coord(int *coord[],char c, int x, int y, int count[]){
    int i,pos=c-'A',counter;
    if(coord[pos]==NULL){
        coord[pos]=malloc(2*sizeof(int));
    }
    counter=count[pos];

    coord[pos][counter]=x;
    coord[pos][counter+1]=y;
    count[pos]++;
    printf("%d%d ",coord[pos][counter],coord[pos][counter+1]);


}
int main()
{
    FILE *fr;
    int height,lenght,i=0,k=0,j=0,total_chars,c;
    char ** array;
    int *coord[26]={NULL};
    int count[26]={0};


    if((fr=fopen("osemsmerovka.txt","r"))==NULL){   //OTVORENIE SUBORU
        printf("The file could not be opened");
        return 404;
    }

    fscanf(fr,"%d %d",&height, &lenght); //NACITANIE ROZMERU

    total_chars=(height*(lenght+1));
    array=malloc_array(height, lenght);

    while(i++<=total_chars){
        c=getc(fr);
        if(c!='\n')
            array[k][j++]=c;
        if(j==lenght){j=0;k++;}
    }


    for(i=0;i<height;i++){
        for(j=0;j<lenght;j++){
            c=array[i][j];
            if(c!='\n')
                fill_coord(coord,c,i,j,count);
        }
    }


    putchar('\n');
    for(i=0;i<height;i++){
        for(j=0;j<lenght;j++){
            printf("%c",array[i][j]);
        }
        putchar('\n');
    }





    return 0;
}
