#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N sizeof(int)

//ARRAY ALOCATION
char ** malloc_array(int size_a, int size_b){
    char **pole;
    int i;

    pole = malloc(size_a * sizeof( *pole ));

    for (i = 0; i < size_a; i++) {
        pole[i] = malloc( size_b * sizeof(pole[0]) );
    }
    return pole;
}

//PRINTS MAIN ARRAY (CROSSWORD) IN ITS ACTUAL STATE
void print_array(char *array[], int height, int lenght){
    int i,j;
    putchar('\n');
    for(i=0; i<height; i++){
        for(j=0; j<lenght; j++){
            printf("%c",array[i][j]);
        }
        putchar('\n');
    }
    printf("\n=======================\n");
}

//FUNTION THAT SAVES COORDINATES OF LETTERS FROM ARRAY
void fill_coord( int *coord[], char c, int x, int y, int count[] ){
    int alphabet_order = c-'A' , entry_count;

    if(coord[alphabet_order]==NULL)
        coord[alphabet_order]=malloc(2*N);

    entry_count = count[alphabet_order];

    coord[alphabet_order] = realloc(coord[alphabet_order],(entry_count+2) * N);
    coord[alphabet_order][entry_count] = x;
    coord[alphabet_order][entry_count+1] = y;

    count[alphabet_order]+=2;
}

//FUNCTION THAT TRIES TO FIND INPUTED WORD IN MAIN ARRAY
int find_word(char input_word[], int input_word_len, int *coord[], char *array[], int height, int lenght, int count[]){
    int i, j, prve_p = input_word[0]-'A', coord_x, coord_y, found=0;

    for(j=0; j<count[prve_p]; j+=2){

        coord_y = coord[prve_p][j];
        coord_x = coord[prve_p][j+1];

        //WEST
        if(coord_x + input_word_len <= lenght){
            for(i=1; i<input_word_len; i++)
                if(!(toupper(array[coord_y][coord_x+i]) == input_word[i]))
                    break;

            if(i == input_word_len){
               for(i=0; i<input_word_len; i++)
                array[coord_y][coord_x+i] = tolower(array[coord_y][coord_x+i]);

            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //SOUTH-WEST
        if(coord_y + input_word_len <= height  &&  coord_x + input_word_len <= lenght){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y+i][coord_x+i]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y+i][coord_x+i] = tolower(array[coord_y+i][coord_x+i]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //SOUTH
        if(coord_y + input_word_len <= height){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y+i][coord_x]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y+i][coord_x] = tolower(array[coord_y+i][coord_x]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //SOUTH-EAST
        if(coord_y+input_word_len <= height  &&  coord_x - input_word_len+1 >= 0){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y+i][coord_x-i])==input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y+i][coord_x-i] = tolower(array[coord_y+i][coord_x-i]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //EAST
        if(coord_x - input_word_len+1 >= 0){

            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y][coord_x-i]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y][coord_x-i] = tolower(array[coord_y][coord_x-i]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found=1;
            }
        }

        //NORTH-EAST
        if(coord_y - input_word_len+1 >= 0  &&  coord_x - input_word_len+1 >= 0){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y-i][coord_x-i]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y-i][coord_x-i] = tolower(array[coord_y-i][coord_x-i]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //NORTH
        if(coord_y - input_word_len+1 >= 0){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y-i][coord_x]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y-i][coord_x] = tolower(array[coord_y-i][coord_x]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

        //NORTH-WEST
        if(coord_y - input_word_len+1 >=0  &&  coord_x + input_word_len <= lenght){
            for(i=1; i<input_word_len; i++){
                if(!(toupper(array[coord_y-i][coord_x+i]) == input_word[i]))
                    break;
            }
            if(i == input_word_len){
               for(i=0; i<input_word_len; i++){
                array[coord_y-i][coord_x+i] = tolower(array[coord_y-i][coord_x+i]);
               }
            printf("%s",input_word);
            print_array(array,height,lenght);
            found = 1;
            }
        }

    }

    if(found)
        return 1;
    else
        return 0;
}

//FUNCTION PRINTS HIDDEN MESSAGE FROM THE CROSSWORD
void print_secret(char **array, int height, int lenght){
    int i, j, exist = 0;
    putchar('\n');
    printf("Secret: ");

    for(i=0;i<height;i++)
        for(j=0;j<lenght;j++)
            if(isupper(array[i][j])){
                printf("%c",array[i][j]);
                exist=1;
            }

    putchar('\n');
    if(!exist)
        printf("The secret is empty");
}

//FUNCTION ALLOCATES SPACE AND FILLS ARRAY OF UNFOUND WORDS
char **unfound_add(char **unfound, char input_word[], int *unfound_count){
    int i;

    unfound = realloc(unfound, (*(unfound_count)+1) * sizeof(char*) );
    unfound[*unfound_count] = malloc(100*sizeof(char));

    for(i=0; i<=strlen(input_word); i++)
        unfound[*unfound_count][i] = input_word[i];

    (*unfound_count)++;

    return unfound;
}

int main()
{
    FILE *fr;
    int height, lenght, i = 0, k = 0, j = 0, total_chars, c, unfound_count = 0, count[26] = {0}, *coord[26] = {NULL};
    char ** array, **unfound = NULL, input_word[100] = {'\0'};

    if((fr = fopen("osemsmerovka.txt","r")) == NULL){
        printf("The file could not be opened");
        return 404;
    }

    fscanf(fr,"%d %d", &height, &lenght);

    total_chars = ( height * (lenght+1) );
    array = malloc_array(height, lenght);

    //FILL CROSSWORD ARRAY
    while(i++ <= total_chars){
        c = getc(fr);
        if(c != '\n')
            array[k][j++] = c;
        if(j == lenght){j=0;k++;}
    }

    //FILL COORDINATE TABLE
    for(i=0; i<height; i++){
        for(j=0; j<lenght; j++){
            c = array[i][j];
            if(c != '\n')
                fill_coord(coord,c,i,j,count);
        }
    }

    //READ AND FIND WORD
    while(fgets(input_word,99,fr) != NULL){
        if(input_word[strlen(input_word)-1] == '\n')
            input_word[strlen(input_word)-1] = '\0';
        if(!find_word(input_word, strlen(input_word), coord, array, height, lenght, count))
            unfound = unfound_add(unfound, input_word, &unfound_count);
    }

    print_secret(array, height, lenght);

    //PODLA ZADANIA BY TO TAKTO BYT NEMALO ALE JE LEPSIE VYPISAT VSETKY NARAZ
    if(unfound_count){
        printf("Unfound: ");
        for(i=0; i<unfound_count; i++){
            printf("%s, ",unfound[i]);
        }
        putchar('\n');
    }

    //FREE ALL ARRAYS
    for(i=0; i<26; i++){
        if(i < height)
            free(array[i]);
        if(i < unfound_count)
            for(j=0; j<100; j++)
                free(unfound[i]);
        free(coord[i]);
    }
    printf("\n\nPRESS ENTER TO EXIT!");
    getchar();

    return 0;
}
