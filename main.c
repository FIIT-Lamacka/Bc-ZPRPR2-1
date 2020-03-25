#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 2
char ** malloc_array(int size_a, int size_b){ //Alokovanie array
    char **pole;
    int i;

    pole = malloc(size_a * sizeof(*pole));

    for (i = 0; i < size_a; i++) {
        pole[i] = malloc(size_b * sizeof(pole[0]));
    }
    return pole;
}
void print_array(char *array[], int height, int lenght){//Vypise ako vypada krizovka
    int i,j;
    putchar('\n');
    for(i=0;i<height;i++){
        for(j=0;j<lenght;j++){
            printf("%c",array[i][j]);
        }
        putchar('\n');
    }
}
void print_all_c(int *coord[], int count[]){//vypise zoznam pismen ich pozicie
    int i,j;
    putchar('\n');
    for(i=0;i<26;i++){
        printf("%c: ",'A'+i);
        for(j=0;j<count[i];j+=2){
            printf("(%d,%d)",coord[i][j],coord[i][j+1]);
        }
        putchar('\n');
    }

}
void fill_coord(int *coord[],char c, int x, int y, int count[]){
    int pos=c-'A',counter;
    if(coord[pos]==NULL){
        coord[pos]=malloc(2*sizeof(int));
    }
    counter=count[pos];
    coord[pos]=realloc(coord[pos],(counter+2)*sizeof(int));
    coord[pos][counter]=x;
    coord[pos][counter+1]=y;

    count[pos]+=2;
}
int find_word(char slovo[],int slovo_len, int *coord[], char *array[], int height, int lenght, int count[]){
    int i,j,k,l,prve_p = slovo[0]-'A',coord_x,coord_y,najdene=0;

    for(j=0;j<count[prve_p];j+=2){
        coord_y = coord[prve_p][j];
        coord_x = coord[prve_p][j+1];

        k=coord_x;
        l=coord_y;
        //ZAPAD
        if(coord_x+slovo_len<=lenght){

            for(i=1;i<slovo_len;i++){
                if(toupper(array[coord_y][coord_x+i])==slovo[i])
                    ;
                else
                    break;
            }
            if(i==slovo_len){
               for(i=0;i<slovo_len;i++){
                array[coord_y][coord_x+i]=tolower(array[coord_y][coord_x+i]);
               }
            printf("%s",slovo);
            print_array(array,height,lenght);
            printf("\n=======================\n");
            najdene=1;
            }

        }

        //JUH
        if(coord_y+slovo_len<=height){

            for(i=1;i<slovo_len;i++){
                if(toupper(array[coord_y+i][coord_x])==slovo[i])
                    ;
                else
                    break;
            }
            if(i==slovo_len){
               for(i=0;i<slovo_len;i++){
                array[coord_y+i][coord_x]=tolower(array[coord_y+i][coord_x]);
               }
            printf("%s",slovo);
            print_array(array,height,lenght);
            printf("\n=======================\n");
            najdene=1;
            }

        }
        //VYCHOD
        if(coord_x-slovo_len+1>=0){

            for(i=1;i<slovo_len;i++){
                if(toupper(array[coord_y][coord_x-i])==slovo[i])
                    ;
                else
                    break;
            }
            if(i==slovo_len){
               for(i=0;i<slovo_len;i++){
                array[coord_y][coord_x-i]=tolower(array[coord_y][coord_x-i]);
               }
            printf("%s",slovo);
            print_array(array,height,lenght);
            printf("\n=======================\n");
            najdene=1;
            }

        }
        //SEVER
        if(coord_y-slovo_len+1>=0){
            for(i=1;i<slovo_len;i++){
                if(toupper(array[coord_y-i][coord_x])==slovo[i])
                    ;
                else
                    break;
            }
            if(i==slovo_len){
               for(i=0;i<slovo_len;i++){
                array[coord_y-i][coord_x]=tolower(array[coord_y-i][coord_x]);
               }
            printf("%s",slovo);
            print_array(array,height,lenght);
            printf("\n=======================\n");
            najdene=1;
            }
        }
    }
    if(najdene)
        return 1;
    else
        return 0;

}
void vypis_tajnicku(char **array, int height, int lenght){
    int i,j,exist=0;
    putchar('\n');
    printf("Riesenie tajnicky: ");
    for(i=0;i<height;i++){
        for(j=0;j<lenght;j++){
            if(isupper(array[i][j])){
                printf("%c",array[i][j]);
                exist=1;
            }

        }
    }
    putchar('\n');
    if(!exist){
        printf("Tajnicka je prazdna");
    }
}

char **unfound_add(char **unfound, char slovo[], int *unfound_count){
    int i;

    unfound = realloc(unfound, (*(unfound_count)+1)*sizeof(char*));
    unfound[*unfound_count]=malloc(100*sizeof(char));

    for(i=0;i<=strlen(slovo);i++){
        unfound[*unfound_count][i]=slovo[i];
    }
    (*unfound_count)++;


    return unfound;
}
int main()
{
    FILE *fr;
    int height,lenght,i=0,k=0,j=0,total_chars,c,unfound_count=0;
    char ** array;
    int *coord[26]={NULL};
    char **unfound=NULL;
    int count[26]={0};
    char slovo[100]={'\0'};


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

    //print_all_c(coord,count);
    //print_array(array,height,lenght);

    while(fgets(slovo,99,fr)!=NULL){
        if(slovo[strlen(slovo)-1]=='\n')
            slovo[strlen(slovo)-1]='\0';
            if(!find_word(slovo,strlen(slovo),coord,array,height,lenght,count)){
                unfound=unfound_add(unfound,slovo,&unfound_count);
            }

    }

    vypis_tajnicku(array,height,lenght);
    printf("Nenajdene: ");
    for(i=0;i<unfound_count;i++){
        printf("%s, ",unfound[i]);
    }
    putchar('\n');

    for(i=0;i<26;i++){
        if(i<height)
            free(array[i]);
        if(i<unfound_count)
            free(unfound[i]);
        free(coord[i]);
    }


    return 0;
}
