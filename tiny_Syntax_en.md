# The TINY sample language and it’s scanner

## 1. The TINY Language

### Syntax description

- **A program** is a sequence of statements separated by semicolons.
- **Declarations:** No procedures and no declarations.
- **Data Type:** All variables are integer variables, and variables are declared by assigning values to them.
- **Statement:** Two control statements: if-statement and repeat-statement, read and write statements.
- **Expression:** Boolean and integer arithmetic expressions.
- **Comment:** Comments are allowed within curly brackets.

### Example

```tiny
{sample program in TINY language- computes factorial}
read x;  { input an integer }
if 0<x then  { don’t compute if x<=0 }
    fact:=1;
    repeat
        fact := fact*x;
        x := x-1;
    until x=0;
write fact; {output factorial of x}
end
```

## 2. Implementation of a TINY Scanner

### 2.1 Implementing a Scanner for the Sample Language TINY

| **Reserved Words**                        | **Special ymbols**                            | **Other**        |
|:-----------------------------------------:|:-----------------------------------------------:|:-----------------:|
| if then else end repeat until read write  | +      -     *     / =      <  ( )     ;    :=  | number identifier |

Construct a DFA for the scanner directly

![DFA](.docs/DFA.png)

Explanation:

- All accepting states are collected into one state “DONE”, the different token recognized is saved in a variable

- Construct a table of reserved words, reserved words are considered only after an identifier has been recognized, and then to look up the identifier in the table

- The implementation of the DFA uses the doubly nested case analysis
