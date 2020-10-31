#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*variável responsável por dizer ao programa se houve ou não erro*/
int erro = 0;
/*declaração de tipo boolean personalizado utilizando typedef*/
typedef enum boolean {
    false,
    true,
} bool;

/*função powered que eleva 'num' a 'pot'*/
long double powered(double num, int pot) {
    int i = 0;
    long double ret = num;

    if (pot > 0) {
        for (i = 1; i < pot; i++) {
            ret *= num;
        }

        return ret;
    }
    else if (pot < 0) {
        ret = 1;
        for (i = 1; i <= -pot; i++) {
            ret /= num;
        }

        return ret;
    }

    return 1.0;
}

/*função que converte 'original_value' na base 'base' para a base 10*/
long double toBaseTen(char* original_value, unsigned int base)
{
    /*declaração de variáveis*/
    char value[100] = "";
    char result[100] = "";
    char aux[100] = "";
    int limit = base + 54;
    int x = 0, i = 0, j = 0;
    int commaPos = 0;
    long double soma = 0;
    bool isNegative = false;

    /*inicializando de forma apropriada as strings*/
    strcpy(aux, "");
    strcpy(value, "");
    strcpy(result, "");


    /*verifica se o número é negativo*/
    if (original_value[0] == '-') {
        isNegative = true;
        for (j = 0; j <= strlen(original_value); j++) {
            value[j] = original_value[j + 1];
        }
    }
    else
        strcpy(value, original_value);

    /*verifica se o número tem ','. Se possuir '.' no lugar da mesma, o programa aponta erro*/
    if (strchr(original_value, ',') != NULL || strchr(original_value, '.') != NULL) {
        for (j = 0; j < strlen(value); j++) {
            if (value[j] == ',') {
                commaPos = j;
                break;
            }
            if (value[j] == '.') {
                printf("\nUtilize , em vez de .");
                erro = 1;
                return 1;
            }
        }

        /*verifica se o número é alphanumeric e converte o mesmo para base 10 se for*/
        for (i = 0; i < commaPos; i++) {
            if (isalpha(value[i])) {
                if (islower(value[i]))
                    value[i] = toupper(value[i]);

                x = value[i];
                if (x > limit)
                {
                    printf("\nBase nao correspondente ao valor!");
                    erro = 1;
                    return 1;
                }
                soma += (x - 55) * powered(base, commaPos - i - 1);
            }
            else
                soma += ((unsigned int)value[i] - 48) * powered(base, commaPos - i - 1);
        }

        /*verifica se o número é alphanumeric e converte o mesmo para base 10 se for*/
        for (j = commaPos + 1; j < strlen(value); j++) {
            if (isalpha(value[j])) {
                if (islower(value[j]))
                    value[j] = toupper(value[j]);

                x = value[j];
                if (x > limit)
                {
                    printf("\nBase nao correspondente ao valor!");
                    erro = 1;
                    return 1;
                }
                soma += (x - 55) * powered(base, commaPos - j);
            }
            else
                soma += ((unsigned int)value[j] - 48) * powered(base, commaPos - j);
        }
    }
    else {
        /*verifica se o número é alphanumeric e converte o mesmo para base 10 se for*/
        for (i = 0; i < strlen(value); i++) {
            if (isalpha(value[i])) {
                if (islower(value[i]))
                    value[i] = toupper(value[i]);

                x = value[i];
                if (x > limit)
                {
                    printf("\nBase nao correspondente ao valor!");
                    erro = 1;
                    return 1;
                }
                soma += (x - 55) * powered(base, strlen(value) - i - 1);
            }
            else
                soma += ((unsigned int)value[i] - 48) * powered(base, strlen(value) - i - 1);
        }
    }

    /*adiciona sinal de '-' se o número for negativo*/
    if (isNegative)
        soma = -soma;

    return soma;
}

/*converte 'original_value' na base 10 para a base 'base'*/
char* fromBaseTen(long double original_value, unsigned int base) {
    /*declaração de variáveis*/
    char value[100] = "";
    char ret[100] = "";
    char aux[100] = "";
    char charDec[2] = "";
    char charInt[2] = "";
    int decdec = 0;
    int i = 0, j = 0;
    int resultado = 0;
    int resto = 0;
    int cont = 0;
    int len = 0;
    long double decimal = 0;
    bool isNegative = false;

    /*se um erro já tiver sido apontado, a função é abortada*/
    if (erro == 1)
    {
        return "1";
    }

    /*inicializando de forma apropriada as strings*/
    strcpy(aux, "");
    strcpy(ret, "");
    strcpy(value, "");
    strcpy(charDec, "");
    strcpy(charInt, "");
    sprintf(value, "%llf", original_value);


    /*verifica se o número é negativo*/
    if (value[0] == '-') {
        isNegative = true;
        for (j = 0; j <= strlen(value); j++) {
            value[j] = value[j + 1];
        }
    }

    /*verifica se o número possui casas decimais*/
    if (strchr(value, '.') != NULL) {
        if (isNegative)
            original_value *= -1;
        
        resultado = original_value;
        while (resultado != 0) {
            resto = resultado - ((int)(resultado / base) * base);
            resultado = resultado / base;

            /*se o número for maior do que 9, converte o mesmo para alphanumeric*/
            if (resto > 9)
            {
                resto = resto + 55;
                sprintf(charInt, "%c", resto);
            }
            else
                sprintf(charInt, "%d", resto);

            strcat(aux, charInt);
            cont++;
        }

        /*inverte os números*/
        len = strlen(aux) - 1;
        for (cont = 0; cont <= len; cont++) {
            ret[cont] = aux[len - cont];
        }

        strcat(ret, ".");

        resultado = original_value;
        decimal = original_value - resultado;
        cont = 0;
        strcpy(charDec, "");

        while (decimal != 0 && cont < 6) {

            /*se o número for maior do que 9, converte o mesmo para alphanumeric*/
            if ((int)(decimal * base) > 9)
            {
                decdec = (int)(decimal * base);
                decdec = decdec + 55;
                sprintf(charDec, "%c", decdec);
            }
            else
                sprintf(charDec, "%d", (int)(decimal * base));

            decimal = decimal * base - (int)(decimal * base);
            strcat(ret, charDec);
            cont++;
        }
    }
    /*se o último caractere de 'ret' for '.', ele é removido*/
    if (ret[strlen(ret) - 1] == '.')
        ret[strlen(ret) - 1] = ' ';

    /*adiciona sinal de '-' caso o número seja negativo*/
    if (isNegative)
    {
        strcpy(aux, ret);
        strcpy(ret, "-");
        strcat(ret, aux);

        return ret;
    }

    return ret;
}

int main()
{
    /*declaração de variáveis*/
    char str_value[100] = "";
    char str[100] = "";
    unsigned int original_base;
    unsigned int final_base;
    int i = 0;
    int qtdComma = 0;
    int qtdMin = 0;

    /*inicializando de forma apropriada as strings*/
    strcpy(str, "");
    strcpy(str_value, "");


    /*exige digitação do valor a ser convertido*/
    printf("Type a value (use , instead of . for real numbers): ");
    fflush(stdout);
    scanf("%s", &str_value);
    fflush(stdin);

    for (i = 0; i < strlen(str_value); i++)
    {
        /*verifica se o número é de fato um número*/
        if (!isalnum(str_value[i]) && str_value[i] != ',' && str_value[i] != '-')
        {
            printf("Escreva um numero");
            return 1;
        }
        else
        {
            /*caso haja ',', define um limite de uma somente*/
            if (str_value[i] == ',')
            {
                qtdComma++;
                if (qtdComma > 1)
                {
                    printf("Escreva um numero");
                    return 1;
                }
            }
            /*caso haja '-', define um limite de um somente*/
            if (str_value[i] == '-')
            {
                qtdMin++;
                if (qtdMin > 1)
                {
                    printf("Escreva um numero");
                    return 1;
                }
            }
        }
    }


    /*exige a digitação da base original do número já digitado*/
    printf("Type the original base: ");
    fflush(stdout);
    scanf("%i", &original_base);
    fflush(stdin);

    /*verifica se a base é válida*/
    if (original_base > 36 || original_base < 2)
    {
        printf("Digite uma base de 2 a 36");
        return 1;
    }


    /*exige a digitação da base para a qual o número será convertido*/
    printf("Type the final base: ");
    fflush(stdout);
    scanf("%i", &final_base);
    fflush(stdin);

    /*verifica se a base é válida*/
    if (final_base > 36 || final_base < 2)
    {
        printf("Digite uma base de 2 a 36");
        return 1;
    }



    /*coleta o resultado e o copia em uma string*/
    strcpy(str, fromBaseTen(toBaseTen(str_value, original_base), final_base));
    /*caso um erro seja apontado, o programa é abortado*/
    if (erro == 1)
        return 1;

    printf("\n%s", str);
    fflush(stdout);
}