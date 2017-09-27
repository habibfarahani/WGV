
#include <stdio.h>

#include "RefString.h"




int main(char *argv[], int argc)
{
  
    printf("First unique number is \n");

    RefString firstString;
    RefString secondString("Second String");
    RefString thirdString(secondString);
    RefString forthString;    

    forthString =  secondString + "---";
    forthString += thirdString;
    printf("First string using default const:         ");
    firstString.print();
    printf("Second string using overloaded const:     ");
    secondString.print();
    printf("Third string using copy const:            ");
    thirdString.print();

    printf("Forth string using + and = operators:     ");
    forthString.print();
    
    RefString movedString = std::move(forthString);
//    movedString.move(forthString);
    
    printf("Forth string being moved using move cont: ");
    forthString.print();
    printf("Moved from forthString:                   ");
    movedString.print();

    
    
    return 0;
}