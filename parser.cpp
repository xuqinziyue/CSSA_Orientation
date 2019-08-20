#include "parser.h"


#include <iostream>
#include <fstream>
#include <unistd.h>

#include <sys/file.h>

using namespace std;
int parser( vector<std::string>& info_storage, string file_name){
  
  ifstream input_file(file_name.c_str(), ios::in);    
  if (!input_file){
    cout<<"fail to open the file specified\n";
    return 1;
  }

  size_t seek = 0;
	while(1){
   
    string input;
		if (input_file.peek() == EOF) {
			
			input_file.clear();
			input_file.seekg(seek, ios::beg);
      
			sleep(1);
      
			continue;
		}
 
		getline(input_file, input);
    if (input_file.eof()){
      cout<<"the line is not ready yet\n";
      continue;
      
    }
		cout<<"Allow \"" << input<< "\" to be sent? Y/N"<<endl;
    char allow_bit;
    cin>>allow_bit;
    if (allow_bit == 'Y' || allow_bit == 'y'){
      cout<<input<< " is stored"<<endl;
      info_storage.push_back(input);

    }
    cin.ignore(1000, '\n');
		seek = input_file.tellg();
    
    
    
	}
	input_file.close();

}
