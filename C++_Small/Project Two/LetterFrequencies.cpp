#include <iostream>
#include <string>
#include <fstream>
std::string does_file_exist(){ // does the file exist and can it be opened?
  std::string filename;
  bool truthValue;
  do{
    std::cout << "Enter\n";
    std::cin >> filename;
    std::ifstream file(filename);
    truthValue = file.good();
    //std::cout << "truthValue: " << truthValue << std::endl; // debug print statement
    if ( truthValue == false ){
      std::cout << "File not found. try again\n";
    }
  } while ( truthValue == false );
  return filename;
}
void count_letter_frequencies ( const std::string& filename, unsigned int letterFrequency[] ){
  for ( int i = 0; i < 26; i++ ){
    letterFrequency[i] = 0;
  }
  std::ifstream inputFile ( filename );
  if ( !inputFile.is_open() ){
    std::cerr << "Error opening file: " << filename << std::endl;
    return;
  }
  char c;
  while ( inputFile.get(c) ){
    if ( ( c >= 'A' && c <= 'Z' ) || ( c >= 'a' && c <= 'z' ) ){
      c = toupper(c); // we only care about uppercase letters, so make all lowercase letters into uppercase
      letterFrequency[c-'A']++;
    }
  }
  inputFile.close();
}
void insertion_sort ( unsigned int letterFrequency[], int length, char the_alphabet[] ) {
  for ( int i=1; i < length; i++ ){
    int key = letterFrequency[i];
    int j = i-1;
    char alphabet_key = the_alphabet[i];
    while ( j >= 0 && letterFrequency[j] > key ){
      letterFrequency[j+1] = letterFrequency[j];
      the_alphabet[j+1] = the_alphabet[j];
      j = j-1;
    }
    the_alphabet[j+1] = alphabet_key;
    letterFrequency[j+1] = key;
  }
}
int main(){
  std::string existingFileName = does_file_exist();
  std::cout << "You entered an existing file: " << existingFileName << std::endl;
  int length = 26;
  unsigned int letterFrequency[length];
  char the_alphabet[length] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
  count_letter_frequencies( existingFileName,letterFrequency );
  std::cout<<"\nIn aphabetical order, the frequency of the letters in this file are:\n";
  for ( int i = 0; i < 26; i++ ) {
    char letter = static_cast<char>('A'+i);
    std::cout << letter << ": " << letterFrequency[i] << std::endl;
  }
  insertion_sort( letterFrequency,length,the_alphabet );
  std::cout << "\nIn ascending order, the frequency of the letters in this file are:\n";
  for ( int i = 0;i < 26; i++ ){
    std::cout << the_alphabet[i] << ": " << letterFrequency[i] << std::endl;
  }
  return 0;
}