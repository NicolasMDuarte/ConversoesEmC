#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef
enum boolean {
    false,
    true,
} bool;

long double pow(double num,int pot) { 
    int i;
    long double ret = num;

    if(pot > 0) {
        for(i = 1; i < pot; i++) {
            ret *= num;
        }
        
        return ret;
    } else if(pot < 0) {
        ret = 1;
        for(i = 1; i <= -pot; i++) {
            ret /= num;
        }

        return ret;
    }

    return 1.0; 
}

long double toBaseTen(char* original_value, unsigned int base) 
{
    bool isNegative = false;
    long double soma = 0;
    
    char value[100];
    char result[100];
    char aux[100];

    int commaPos;

    if(original_value[0] == '-') {
        isNegative = true;
        for(int j = 0; j <= strlen(original_value); j++) {
            value[j] = original_value[j+1];
        }
    } else 
        strcpy(value, original_value);

    if(strchr(original_value, ',') != NULL) {
        int i, j;
        for(j = 0; j < strlen(value); j++) {
            if(value[j] == ',') {         
                commaPos = j;
                break;
            }
        }

        for(i = 0; i < commaPos; i++) {   
            int x;
            if(isalpha(value[i])) {
                if(islower(value[i]))
                    value[i] = toupper(value[i]);
                
                x = value[i];
                soma += (x - 55) * pow(base, commaPos - i - 1);
            } else
                soma += ((unsigned int)value[i] - 48) * pow(base, commaPos - i - 1);
        }

        for(j = commaPos+1; j < strlen(value); j++) {
            int x;
            if(isalpha(value[j])) {
                if(islower(value[j]))
                    value[j] = toupper(value[j]);
                
                x = value[j];
                soma += (x - 55) * pow(base, commaPos - j);
            } else
                soma += ((unsigned int)value[j] - 48) * pow(base, commaPos - j);
        }
    } else {
        int i;
        for(i = 0; i < strlen(value); i++) {
            int x;
            if(isalpha(value[i])) {
                if(islower(value[i]))
                    value[i] = toupper(value[i]);
                
                x = value[i];
                soma += (x - 55) * pow(base, strlen(value) - i - 1);
            } else
                soma += ((unsigned int)value[i] - 48) * pow(base, strlen(value) - i - 1);
        }
    }

    if(isNegative)
        soma = -soma;

    return soma;
}

char* fromBaseTen(long double original_value, unsigned int base) {
    return "Make function here";
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

    char* value;
    value = (char*)malloc(100*sizeof(char));
    strcpy(value, "-af9,beea");

    printf("%llf\n", toBaseTen(value, 16));
    fflush(stdout);
}
