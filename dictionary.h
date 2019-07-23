/*
Mike Yoon
CS211

Assignment 2's H file
*/

#ifndef dictionary_H
#define dictionary_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Dictionary
{
 private:
  static bool failure; 
  static bool success; 
  const int maxWordsInDict; 
  const	int maxWordsPerFile; 
  int totalWordsInDict; 
  int numOfWordsInFile[26]; 
  
 public:
  Dictionary(); 
  Dictionary(int dictMaxWords, int fileMaxWords); 
  bool AddAWord(string word); 
  bool DeleteAWord(string word); 
  bool SearchForWord(string word); 
  bool PrintAFileInDict(string fileName); 
  bool SpellChecking(string fileName); 
  bool InsertWordsIntoDict(string fileName); 
  bool maxCheck(string word); 
  bool fileNotFound(string filename);  
  void ProcessTransactionFile(); 
  string getfileName(string word);  
  int getIndex(string word); 
  vector<string> filetoVector(string fileName);  
  string stringtoLower(string word); 
};
#endif 

