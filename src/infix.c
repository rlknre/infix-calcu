/* CMSC 21 - Fundamentals of Programming

Project Description:
    Using Infix Expressions, solve for the given equations written
    in a file. Input the answers and the step-by-step solution.

@author: Ralph Kenneth Rea
@date: 2022-06-12 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
# include "initializers.h"

// functionalities: linked list operations
void initialize();
void verify();
void solve();
 
// main program flow
int main() {

    /* NOTE: Conditionals were set to ensure if a file exists or not.
       The user receives a prompt depending on certain conditions.
    */

    // if file to read is in one level of directory above src file
    FILE *fp = fopen("../expressions.in.txt", "r");

    // if file to read is in same directory
    // FILE *fp = fopen("expressions.in.txt", "r");

    printf("\nSearching for file of expressions... \n");

    // condition: file exists
    if (fp != NULL) {

        // retrieve the first line of the file
        char checker[10];
        fscanf(fp, " %[^\n]s", checker);
        // assuming that the file is alway right, there should only be one variable

        int N = convertToInt(checker);  // initialize checker value as integer

        if (N != 0) {   // condition: file is not empty

            printf("== File found! Loading computations. \n");
            printf("\nNumber of expressions to be evaluated: %d ", N);

            // loop until it reaches the EOF element 
            for (int i=0; i<N; i++) {

                struct expression_tag *head = NULL;

                printf("\nExpression %d \n", i+1);

                // scan the lines and store in an array first
                char evaluate[50];
                fscanf(fp, " %[^\n]s", evaluate);
                printf("%s ", evaluate);

                initialize(&head, evaluate);    // place the array elements in a linked list
                verify(&head, evaluate);        // check whether the expression is a valid equation 

                expression *temp = (head);

                // condition: there should only be M operands and M-1 operators
                if((temp->operand_count) != ((temp->operator_count) + 1)) {                    
                    if (temp->operand_count <= temp->operator_count) {
                        printf("\n= Invalid. Insufficient Operands!");
                    } else if (temp->operand_count > temp->operator_count) {
                        printf("\n= Invalid. Insufficient Operators!");
                    }
                } else {

                    solve(&head);   // <- here, the solving part happens

                }
           
                // // reinitialize the contents of line scanner array
                // cleanArray(evaluate);
                printf("\n");                           
            }

        } else printf("== WARNING: Empty file found. Terminating. \n\n"); fclose(fp);        

    } else printf("== WARNING: File not found! Terminating. \n\n");

    printf("\n");
    return 0;
}   // end of main program file


void initialize(struct expression_tag **head, char string[]) {

    // initialize the values for conditionals and placeholders 
    int length = (int)strlen(string) + 1;    // also count the '\0'
    int counter = 0;

    char placeholder[length];
    cleanArray(placeholder);

    // initialize counters for operators and operands
    int operand = 0, operator = 0;  // this will be used for verify functions
    
    // loop until last element was transfered to a linked list
    for (int i=0; i<length; i++) {

        // condition: loop reaches a space and NULL last value
        if (string[i] == ' ' || string[i] == '\0') {

            // here, we now place the placeholder string to the node
            expression *new = (expression*) malloc (sizeof(expression));
            strcpy(new->toEvaluate, placeholder);
            new->next = NULL;
            new->prev = NULL;

            // condition: insert at head
            if((*head) == NULL) {
                (*head) = new;
                new->prev = NULL;
                new->next = NULL;
            } else {
                // insert at middle/tail
                expression *temp = (*head);
                while(temp->next != NULL) {
                    temp = temp->next;
                }
                new->prev = temp;
                temp->next = new;
            }

            // initiliaze the type of variables for later use
            if (isdigit(placeholder[0])) {
                new->type = 0;
            } else if (placeholder[0] == '-' && isdigit(placeholder[1])) {
                new->type = 0;
            } else {
                if(placeholder[0] == '/' || placeholder[0] == '*' || placeholder[0] == '%') {
                    new->type = 1;
                } else if (placeholder[0] == '+' || placeholder[0] == '-') {
                    new->type = 2;
                }
            }

            counter = 0;                // reinitialize as well
            cleanArray(placeholder);    // reinitialize the placeholder array for next use

        } else {

            // coutner acts as the index of the placeholder array, starts at 0
            placeholder[counter] = string[i];
            counter++;          
        }
    }
}


void verify(struct expression_tag **head, char string[]) {

    // initialize counters for operators and operands
    int operand = 0, operator = 0;

    // initailize variables for conditionals
    int counter = 0;
    int length = (int)strlen(string) + 1;

    // initialize the placeholder array
    char placeholder[10];
    cleanArray(placeholder);

    struct expression_tag *temp = (*head);

    // loop throught the input string and get each seperate values, same in initialize()
    for (int i=0; i<length; i++) {
        if (string[i] == ' ' || string[i] == '\0') {

            // increment values of opertors and operands
            if (isdigit(placeholder[0])) operand++;
            else if ((placeholder[0] == '-') && isdigit(placeholder[1])) operand++; 
            else operator++;
            
            // NOTE: to consider negative numbers, we first check if "-" has a value next to it

            counter = 0;
            cleanArray(placeholder);    // reinitialize the values again

        } else {
            placeholder[counter] = string[i];
            counter++;
        }
    }

    //printf("\n Operand = %d \nOperator = %d \n", operand, operator);

    // initialize the number of oeprands and operators of the current linked list
    temp->operand_count = operand;
    temp->operator_count = operator;

    // NOTE: this should be operand (M) and operator (M-1)
}


void solve(struct expression_tag **head) {

    // initialize the holder values and checker
    int answer, valid = 1;
    expression *temp = (*head);

    /* NOTE: Remember, function initialize() ? One part of it initilizes
       the type of variable placed on each node of the linked list:

       e.g. 1-mid-operator, 2-low-operator, 0-operand

       1: mid-operator are for "/", "*", "%"
       2: low-operator are for "+", "-"
       3: operands or the numbers in layman's term    
    */

    while(temp->next != NULL) {

        // get the priority operators first
        while(temp->type != 1) {

            // condition: reaching the last values
            if(temp->next == NULL){
                valid = 0;
                break;
            }
            temp = temp->next;
        }

        if(valid == 0) break;   // make sure to break the loop to avoid sudden stops in terminal

        // initialize the operands to be used in solving the expressions
        struct expression_tag *new = (struct expression_tag *) malloc (sizeof(struct expression_tag));
        int leftNum = convertToInt(temp->prev->toEvaluate);
        int rightNum = convertToInt(temp->next->toEvaluate);
        
        // check what operation each operator node holds, use string compare
        if (strcmp(temp->toEvaluate, "/") == 0) {
            answer = leftNum / rightNum;
        } else if (strcmp(temp->toEvaluate, "*") == 0) {
            answer = leftNum * rightNum;
        } else if (strcmp(temp->toEvaluate, "%") == 0) {
            answer = leftNum % rightNum;
        }

        // we use the snprintf() defined in <stdio.h> for converting integer to string
        char placeholder[50];
        snprintf(placeholder, 10, "%d", answer);
        strcpy(new->toEvaluate, placeholder);
        // reference: https://www.geeksforgeeks.org/snprintf-c-library/

        /* NOTE: Why is it important to covnert the integers to String?
           Since the initialized holder of values in the structure
           are of char type array, we need to convert the integers
           back to character to return it to the linked list for
           future operations.       
        */

        new->type = 0;
        new->prev = NULL;
        new->next = NULL;
        // here, we now start reinitiliazing the linked list

        // condition: insert at head
        if (temp->prev->prev == NULL) { 
            new->prev = NULL;
            new->next = temp->next->next;

            if (temp->next->next != NULL) {
                temp->next->next->prev = new;
            }
            
            (*head) = new;

        } else{ // condition: insert at middle/tail
            new->prev = temp->prev->prev;
            temp->prev->prev->next = new;

            if (temp->next->next != NULL) {
                new->next = temp->next->next;
                temp->next->next->prev = new;

            } else new->next = NULL;
        }

        temp = new;

        // here, we print the finished step for the solution
        expression *tempToStart = (*head);
        printf("\n= ");
        while(tempToStart != NULL){
            printf("%s ", tempToStart->toEvaluate);
            tempToStart = tempToStart->next;
        }
    }

    /* NOTE: The following block of code below follows the same
       format used above, only at this point, we now do the
       other operations.   
    */

    temp = (*head);
    while(temp->next != NULL) {

        // NOTE: 1-mid-operator, 2-low-operator, 0-operand
        while(temp->type != 2) {
            temp = temp->next;
        }

        // initializing the numbers to be used for the solving
        struct expression_tag *new = (struct expression_tag *) malloc (sizeof(struct expression_tag));
        int leftNum = convertToInt(temp->prev->toEvaluate);
        int rightNum = convertToInt(temp->next->toEvaluate);

        // string compare and do the following operations
        if (strcmp(temp->toEvaluate, "+") == 0) {
            answer = leftNum + rightNum;
        } else if (strcmp(temp->toEvaluate, "-") == 0) {
            answer = leftNum - rightNum;
        } 

        // covnersion of integer to string
        char placeholder[50];
        snprintf(placeholder, 10, "%d", answer);
        strcpy(new->toEvaluate, placeholder);   // return value to linked list

        new->type = 0;
        new->prev = NULL;
        new->next = NULL;
        // here, we now start reinitiliazing the linked list

        // condition: insert at head
        if (temp->prev->prev == NULL) { 
            new->prev = NULL;
            new->next = temp->next->next;

            if (temp->next->next != NULL) {
                temp->next->next->prev = new;
            }
            (*head) = new;

        } else { // condition: isert at middle/tail
            new->prev = temp->prev->prev;
            temp->prev->prev->next = new;
            
            if (temp->next->next != NULL) {
                new->next = temp->next->next;
                temp->next->next->prev = new;
            } else new->next = NULL;
        }

        temp = new;
        
        // print finished step for the solution
        expression *tempToStart = (*head);
        printf("\n= ");
        while(tempToStart != NULL){
            printf("%s ", tempToStart->toEvaluate);
            tempToStart = tempToStart->next;
        }
    }
}
