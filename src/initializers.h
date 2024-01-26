// functionalities: initializers

#include <string.h>

// structure definition
typedef struct expression_tag {
    
    int type;   // 1-mid-operator, 2-low-operator, 0-operand
    int operator_count;
    int operand_count;
    char toEvaluate[20];
    struct expression_tag *next;
    struct expression_tag *prev;

} expression;

int convertToInt(char *string) {

    char VALID_DIGITS[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    // convert the integer to a string
    int integer = 0, converted = 0;
    for (int i=0; i<(strlen(string)); i++) {

        for (int j=0; j<10; j++) {

            if (string[i] == VALID_DIGITS[j]) {
                /* Utilize the ASCII values in initializing values */
                converted = (string[i] - 48);
                integer = (integer * 10) + converted;
                break;
            }
        }
    }
    // condition: the string returned is a negative integer
    if (string[0] == '-') integer = integer * -1;

    //printf("%d = \n", integer);
    
    return integer;
}

void cleanArray(char *array) {
    // loop throughout the array and initialize a NULL element
    int length = (int)strlen(array);
    for(int i=0; i<length; i++) {
        array[i] = '\0';
    }
}