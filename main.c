#include <stdio.h>
#include <stdlib.h>
char ** malloc_array(int size_a, int size_b){
    char **pole;
    int i;

    pole = malloc(size_a * sizeof(*pole));

    for (i = 0; i < size_a; i++) {
        pole[i] = malloc(size_b * sizeof(pole[0]));
    }
    return pole;
}
int main()
{
    FILE *fr;
    int height,lenght,i=0,k=0,j=0,total_chars,c;
    char ** array;


    if((fr=fopen("osemsmerovka.txt","r"))==NULL){
        printf("Nepodarilo sa otvorit subor");
        return 404;
    }

    fscanf(fr,"%d %d",&height, &lenght);
    printf("%d %d",height,lenght);



    total_chars=(height*(lenght+1));

    array=malloc_array(height, lenght);

    while(i++<=total_chars){
        c=getc(fr);
        if(c!='\n')
            array[k][j++]=c;
        if(j==lenght){j=0;k++;}
    }

    /*for(i=0;i<height;i++)
        for(j=0;j<lenght;j++)
            array[i][j]='A';*/
    putchar('\n');
    for(i=0;i<height;i++){
        for(j=0;j<lenght;j++){
            printf("%c",array[i][j]);
        }
        putchar('\n');
    }





    return 0;
}
