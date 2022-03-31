#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "Direction.hpp"
using namespace std;

namespace ariel{
    
   
    class Notebook
    {
        unordered_map<int , unordered_map<int , char[100] >> main_map;
        

        public:

            void write( int page ,int row , int col , Direction dir , string input);
            string read( int page ,int row , int col , Direction dir , int length);
            void erase(int page , int row, int col, Direction dir, int length);
            void show(int page);

        
       
    
       

    };
}
