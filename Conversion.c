#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef
enum boolean {
    false,
    true,
} bool;

long double pow(double num,int pot) { 
    int i;
    long double ret = num;

    if(pot > 0)
    {
        for(i = 1; i < pot; i++) {
            ret *= num;
        }
        return ret;
    }
    else if(pot < 0)
    {
        double ret2 = 1;
        for(i = 1; i <= -pot; i++) {
            ret2 /= ret;
        }
        return ret2;
    }

    return 1.0; 
}

long double toBaseTen(char* original_value, unsigned int base) 
{
    bool isNegative = false;
    long double soma = 0;

    //RUIM. Consegue dinamico?
    char result[100];
    //RUIM tambem
    char aux[100];

    //quebrado
    int commaPos;
    char value[100];
    
    //char* intPart;
    //char* decPart;

    if(original_value[0] == '-')
    {
        isNegative = true;
        for(int j = 0; j <= strlen(original_value); j++)
        {
            value[j] = original_value[j+1];
        }
    }
    else 
        strcpy(value, original_value);

    if(strchr(original_value, ',') != NULL)
    {
        int i, j;
        for(j = 0; j < strlen(value); j++)
        {
            if(value[j] == ',')
            {         
                commaPos = j;
                break;
            }
        }

        for(i = 0; i < commaPos; i++) 
        {
            soma += ((unsigned int)value[i] - 48) * pow(base, commaPos - i - 1);
        }
        sprintf(result, "%llf", soma);
        strcat(result, ",");
        //soma = 0;
        for(j = commaPos+1; j < strlen(value); j++)
        {
            soma += ((unsigned int)value[j] - 48) * pow(base, commaPos - j);
        }
        sprintf(aux, "%llf", soma);
        strcat(result, aux);
    } 
    else 
    {
        int i;
        for(i = 0; i < strlen(value); i++) 
        {
            soma += ((unsigned int)value[i] - 48) * pow(base, strlen(value) - i - 1);
        }
        sprintf(result, "%llf", soma);
    }

    if(isNegative)
    {
        soma = -soma;
        strcpy(aux, "-");
        strcat(aux, result);
        strcpy(result, aux);
    } 

    return soma;
}

int main() 
{
    char str_value[100];
    unsigned int original_base;
    unsigned int final_base;

    // printf("Type a value: ");
    // fflush(stdout);

    // scanf("%s", &str_value);
    // fflush(stdin);

    // printf("Type the original base: ");
    // fflush(stdout);

    // scanf("%i", &original_base);
    // fflush(stdin);

    // printf("Type the final base: ");
    // fflush(stdout);

    // scanf("%i", &final_base);
    // fflush(stdin);

    //printf("%s %i %i\n", toBaseTen(str_value, original_base), original_base, final_base);
    char* value;
    value = (char*)malloc(100*sizeof(char));
    strcpy(value, "-1001");
    //strcpy(value, str_value);
    //printf("%llf", toBaseTen(value, 2));
    int a = 'A';
    printf("%d", a);
    fflush(stdout);
}