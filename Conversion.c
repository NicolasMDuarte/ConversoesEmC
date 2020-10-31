#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef
enum boolean {
    false,
    true,
} bool;

long double powered(double num, int pot) { 
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
                soma += (x - 55) * powered(base, commaPos - i - 1);
            } else
                soma += ((unsigned int)value[i] - 48) * powered(base, commaPos - i - 1);
        }

        for(j = commaPos+1; j < strlen(value); j++) {
            int x;
            if(isalpha(value[j])) {
                if(islower(value[j]))
                    value[j] = toupper(value[j]);
                
                x = value[j];
                soma += (x - 55) * powered(base, commaPos - j);
            } else
                soma += ((unsigned int)value[j] - 48) * powered(base, commaPos - j);
        }
    } else {
        int i;
        for(i = 0; i < strlen(value); i++) {
            int x;
            if(isalpha(value[i])) {
                if(islower(value[i]))
                    value[i] = toupper(value[i]);
                
                x = value[i];
                soma += (x - 55) * powered(base, strlen(value) - i - 1);
            } else
                soma += ((unsigned int)value[i] - 48) * powered(base, strlen(value) - i - 1);
        }
    }

    if(isNegative)
        soma = -soma;

    return soma;
}

long double fromBaseTen(long double original_value, unsigned int base) {
    
    char value[100] = "";
    char ret[100] = "";
    char aux[100] = "";
    bool isNegative = false;

    sprintf(value, "%llf", original_value);
    int i, j;
    if(value[0] == '-') {
        isNegative = true;
        for(j = 0; j <= strlen(value); j++) {
            value[j] = value[j+1];
        }
    }
    if(strchr(value, '.') != NULL) {
        if(isNegative)
            original_value*=-1;
        int resultado = original_value;
        int resto = 0;
        int cont = 0;
        int len = 0;
        char charInt[2] = "";
        while(resultado != 0) {
            resto = resultado - ((int)(resultado/base)*base);
            resultado = resultado / base;

            sprintf(charInt, "%d", resto);
            
            strcat(aux, charInt);
            cont++;
        }
        
        len = strlen(aux) - 1;
        for(cont = 0; cont <= len; cont++) {
            ret[cont] = aux[len-cont];
        }
        

        strcat(ret, ".");

        if(isNegative)
            original_value*=-1;
        resultado = original_value; 
        long double decimal = original_value - resultado;
        cont = 0;
        char charDec[2];
        while(decimal != 0 && cont < 6) {
            sprintf(charDec, "%d", (int)(decimal*base));

            decimal = decimal * base - (int)(decimal*base);
            strcat(ret, charDec);
            cont++;
        }
    }
    if(isNegative)
        return -(strtod(ret, NULL));

    return strtod(ret, NULL);
}

int main() 
{
    // VALIDAR TUDO!!!
    // Verificar caso os valores digitado são coerentes com a base de origiem
    char str_value[100];
    unsigned int original_base;
    unsigned int final_base;

    printf("Type a value: ");
    fflush(stdout);

    scanf("%s", &str_value);
    fflush(stdin);

    printf("Type the original base: ");
    fflush(stdout);

    scanf("%i", &original_base);
    fflush(stdin);

    printf("Type the final base: ");
    fflush(stdout);

    scanf("%i", &final_base);
    fflush(stdin);

    printf("\n%llf", fromBaseTen(toBaseTen(str_value, original_base), final_base));

    fflush(stdout);
}
