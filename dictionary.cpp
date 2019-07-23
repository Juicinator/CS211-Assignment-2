/*
Mike Yoon
CS211

Assignment 2's cpp file for the H file
*/

#ifndef dictionary_cpp
#define dictionary_cpp

#include<iostream>
#include<iomanip>
#include<fstream>

using namespace std;

#include "dictionary.h"

bool Dictionary::failure = false;
bool Dictionary::success = true;


Dictionary::Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)
{
  totalWordsInDict = 0;	
  for(int i=0; i<25; i++) 
  numOfWordsInFile[i] = 0; 
}

Dictionary::Dictionary(int dictMaxWords, int fileMaxWords):maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)
{
  /* This routine sets the following values to the following attributes
     maxWordsInDict = dictMaxWords;
     maxWordsPerFile = fileMaxWords;
     totalWordsInDict = 0;	
     numOfWordsInFile[0] = 0; referring to A.txt
     numOfWordsInFile[1] = 0; referring to B.txt
     numOfWordsInFile[25] = 0; referring to Z.txt
  */
}

bool Dictionary::AddAWord(string word) 
{
  //This variable contains the index of the word that will be added.
  int index = getIndex(word); 
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  
  maxCheck(word); 
  word = stringtoLower(word); 
  
  if(SearchForWord(word)==success)  //Check if the word exists in the dictionary.
    {
      
      cout << "The following word already exists in " << fileName << ": " << word  << endl;
      return failure; 
    }
  else  //Add the word to the dictionary if it is not found.
    {
      totalWordsInDict++; 
      numOfWordsInFile[index]++; 
      
      ofstream fout; 
      if(!fout) 
	{
	  fileNotFound(fileName); 
 	}
      fout.open(fileName.data(), ios::app);  	
      fout << word << " " << endl; 
      fout.close(); 
      return success; 
    }
}

bool Dictionary::DeleteAWord(string word) 
{
  cout << "\nDELETING: " << word << endl;
  int deleteCount = 0;
  //This variable contains the index of the word that will be added.  
  int index = getIndex(word); 
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  
  ofstream fout; 
  if(!fout) 
    {
      fileNotFound(fileName); //Display an error message if the file does not exist.
      return failure;  
    }
  else
    {  
      fout.open(fileName.data());  //Read a vector and save it to a file.
      
	  for(int i=0; i<originalFile.size(); i++)  
	{	
	  //Compare the element word to an element of vector originalFile.
	  if(word == originalFile[i]) 
	    {
	      originalFile[i] = " "; 
	      fout << originalFile[i]  << " "; 
	      totalWordsInDict--; 
	      numOfWordsInFile[index]--; 	
	      deleteCount++;
	      cout << endl;
	    }
	  else
	    {
	      fout << originalFile[i] << " "; 
	    }
	}
      fout.close(); 
    }
  if(deleteCount==0)
    {	
      cout << "\'" << word << "\'" << " was not found and could not be deleted." << endl; //Inform the user nothing was deleted.
      return success;
    }
}

bool Dictionary::SearchForWord(string word) 
{
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  word = stringtoLower(word); //Convert the word to lowercase.
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
	  //Compare the element word to an element of vector originalFile.
      if(word == originalFile[i]) 
	{
	  return success;
	}
    }
  return failure; 
}

bool Dictionary::PrintAFileInDict(string fileName) 
{
  cout << "\nPRINTING: " << fileName << endl;
  int count = 0; 
  string word;
  ifstream fin;
  fin.open(fileName.data());   
  
  if(!fin)
    {
      fileNotFound(fileName);  
      return failure;
    }
  else
    {
      while(fin>>word) 
	{ 
	  cout << word << " " ; 
	  count++; 
	  
	  if(count>4) 
	    {
	      count = 0; 
	      cout << endl; 
	    }
	}
      cout << endl;
    }					
  return success; 
}

bool Dictionary::SpellChecking(string fileName) 
{
  cout << "SPELLCHECKING:" << endl;
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
	 //Compare an element of originalFile vector to the dictionary files.
      if(SearchForWord(originalFile[i])==failure) 
	{
	  //If the element is not found, it is incorrect and an error is displayed.
	  cout << "The following word is spelled incorrectly: "<< originalFile[i]  << endl; 
	}
    }
  return success;
}

bool Dictionary::InsertWordsIntoDict(string fileName) 
{ 
  vector<string> originalFile = filetoVector(fileName);  
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
      AddAWord(originalFile[i]); 
    }
  return success;
}

bool Dictionary::maxCheck(string word) 
{
  if(totalWordsInDict >= maxWordsInDict) 
    {
      cout << "Sorry, your entry has exceeded the maximum number of words in the dictionary." << endl;
      return failure;
    }
  
  int index = getIndex(word);
  if((numOfWordsInFile[index]) > maxWordsPerFile) 
    {
      cout << "Sorry, your entry has exceeded the maximum number of words in the file." << endl;
      return failure;
    }
  return success;
}

bool Dictionary::fileNotFound(string filename)
{
  cout << ">>>>> THE FILE " << filename << " WAS NOT FOUND." << endl; 
}

void Dictionary::ProcessTransactionFile() 
{
  string input;
  string cmd;
  string fileName;
  string word;
  cout << "Please enter the name of your transaction file: ";
  cin >> input;
  
  ifstream fin;
  fin.open(input.data());
  
  if(!fin)
    {
      fileNotFound(input); 
    }
  else
    {
      while(!fin.eof())
	{
	  fin >> cmd;
	  if(cmd=="AddW") 
	    {
	      fin >> word;  
	      AddAWord(word);
	    }
	  else if(cmd=="DeleteW") 
	    {
	      fin >> word; 
	      DeleteAWord(word);
	    }
	  else if( cmd=="InsertF") 
	    {
	      fin >> word;
	      InsertWordsIntoDict(word);
	    }
	  else if( cmd=="PrintF") 
	    {
	      fin >> fileName;
	      PrintAFileInDict(fileName);
	    }
	  else if( cmd=="SearchW") 
	    {
	      fin >> word;
	      cout << "\nSEARCHING FOR: " << word << endl;
	      if(SearchForWord(word)==success)
		{
		  cout << "\'" << word << "\'" << " was found." << endl;
		}
	      else
		{
		  cout << "\'" << word << "\'" << " was not found." << endl;
		}
	    }
	  else if( cmd=="SpellCheck") 
	    {
	      fin >> fileName;
	      SpellChecking(fileName);
	    }
	}
    }
}


string Dictionary::getfileName(string word)
{
  string fileName = "#.txt";  
  fileName[0] = toupper(word[0]);  
  return fileName;
}

int Dictionary::getIndex(string word)
{
  char ch = word[0]; 
  ch = toupper(ch);  
  int index = ch -'A'; 
  return index;
}

vector<string> Dictionary::filetoVector(string fileName) 
{
  vector<string> originalFile; 
  
  ifstream fin;
  fin.open(fileName.data()); 
  string wordtoVector;
  
  if(!fin) 
    {
      fileNotFound(fileName); 
    }
  else
    {
      while(fin>>wordtoVector) 
	{
	  originalFile.push_back(wordtoVector); 
	}
      fin.close(); 
   }
  return originalFile; 
}

string Dictionary::stringtoLower(string word)
{
  for(int i=0; i<word.size(); i++)
    {
      char ch = word[i]; 
      ch = tolower(ch); 
      word[i] = ch; 
   }
  return word;
}
#endif 

