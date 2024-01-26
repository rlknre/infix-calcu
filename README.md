
# INFIX CALCULATOR 

![C][c-md-badge]

A simple **_terminal-based calculator_** that uses **_doubly linked lists_**. It receives input from a file of infix expressions. Note that it assumes all input are written in the correct format. The output shows a step-by-step computation of each valid expression before printing the resulting value.
- This calculator does not handle parentheses.
- In computation, it prioritizes multiplication, division, and modulo over addition and subtraction.
- It follows a left to right precedence rule.
- Negative values are allowed.
<br />

## Requirements
1. Ensure that your system has C installed. Linux-based operating systems usually have it installed.
    - To check if you have C and its necessary compilers, type in:
      - `gcc --vesion`
      - If it does not return a version number, proceed to installation of compilers.
    - For installation, refer to online references for installation guides.
      - Windows: https://www.freecodecamp.org/news/how-to-install-c-and-cpp-compiler-on-windows/

2. When downloading the files, make sure that this directory tree is followed:

   ```
    infix-calcu
    ├── expressions.in.txt
    ├── src
    │   ├── infix.c
    │   └── initializers.h
    └── README.md
   ```
<br />

## Running Project
1. Before compiling and running the program, check the `expressions.in.txt` file first:
    - The first line should be the **_number of expressions_** to be evaluated.
    - Each expression is separated by a _new line_.
    - Follow this format for the expressions:

      ```
      (num) (op) ... (num N) (op N+1)
      
      Where each expression has N operands and N+1 operators
      ```

2. To run the program, make sure to compile the C files first.
    - If you are in a Linux / Ubuntu environment:
      - Open the terminal and proceed to the `src` folder. Compile by typing `gcc infix.c -o infix`.
      - After successful compiling, run the program by using the command `./infix`.
    - If you are using VSCode (Windows), open the `infix.c` file and perform _Run Code_.
    
3. The terminal will return the results. It also states whether an expression is valid or not.
<br />

##
### Author
- Ralph Kenneth Rea

##
### Note
- This project is in fulfillment of the requirements in CMSC 21: Fundamentals of Programming. UPLB.

[c-md-badge]: https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white
