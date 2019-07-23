/*
Mike Yoon
CS211

The main file that calls the function
*/
#ifndef a2_cpp
#define a2_cpp

#include "dictionary.h"

int main()
{
  Dictionary newDict; 
  newDict.ProcessTransactionFile(); 
  return 0;
}
/*
  Other Comments:
  1)	Do not worry about punctuations. Your program should only consider words and ignore all punctuations.
  2) 	All words should be in lower case before it is placed in the dictionary
  3)	Do not write 26 statements to open/close A.txt to Z.txt files.
  4)	When a file name is a variable, you need to open it as follows:  fin.open(fileName.data());
*/
#endif 

