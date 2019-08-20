

#include "parser.h"
#include "sdl_helper.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <functional>
using namespace std;
int main(){
  string name = "/Users/qinziyue/Desktop/temp.txt";

  std::vector<std::string> info_storage;
    thread t1(parser, std::ref(info_storage), name);
    t1.detach();
    /*
    for (int i = 0; i< 100; i++){
    info_storage.push_back("awsl");
    info_storage.push_back("2333");
    info_storage.push_back("666");
    info_storage.push_back("okok");
    }
     */
  initialize_initial_window(info_storage);
    

}

