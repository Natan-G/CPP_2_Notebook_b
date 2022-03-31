#include "Notebook.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <exception>

constexpr int MIN_CHAR = 32;
constexpr int MAX_CHAR = 125;
constexpr int MAX_LINE = 99;
constexpr int next_print = 25;
using namespace std;

namespace ariel
{

    void Notebook::write(int page, int row, int col, Direction dir, string input)
    {

        // checks for bad inputs
        if (page < 0 || row < 0 || col < 0 || input.length() < 0)
        {
            throw invalid_argument("cannot insert negative argument!");
        }

        if (col > MAX_LINE)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }

        if (dir == Direction::Horizontal && (col + (int)input.length()) > MAX_LINE)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }

        for (unsigned int i = 0; i < input.length(); i++)
        {
            if(input.at(i)=='~'){
                throw invalid_argument("cannot write ~");
            }
            if (input.at(i) < MIN_CHAR || input.at(i) > MAX_CHAR)
            {
                throw invalid_argument("insert valid characters!");
            }
        }

        

        if (dir == Direction::Horizontal)
        {
            int start_col = col;
            for (unsigned int i = 0; i < input.length(); i++)
            {
                // check if we write on erased place
                if (main_map[page][row][start_col] == '~')
                {
                    throw runtime_error("cannot write on erased place");
                }
                // check if we write on empty char
                if (main_map[page][row][start_col] >= MIN_CHAR && main_map[page][row][start_col] <= MAX_CHAR)
                {

                    if (main_map[page][row][start_col] == '_')
                    {
                        main_map[page][row][start_col] = input.at(i);
                        start_col++;
                    }
                    else
                    {
                        throw runtime_error("this place already written!");
                    }
                }
                else
                {
                    main_map[page][row][start_col] = input.at(i);
                    start_col++;
                }
            }
        }
        
        // Vertical write
        else{
            int start_row = row;
            for (unsigned int i = 0; i < input.length(); i++)
            {
                // check if we write on erased place
                if (main_map[page][start_row][col] == '~')
                {
                    throw runtime_error("cannot write on erased place");
                }
                // check if we write on empty char
                if (main_map[page][start_row][col] >= MIN_CHAR && main_map[page][start_row][col] <= MAX_CHAR)
                {

                    if (main_map[page][start_row][col] == '_')
                    {
                        main_map[page][start_row][col] = input.at(i);
                        start_row++;
                    }
                    else
                    {
                        throw runtime_error("this place already written!");
                    }
                }
                else
                {
                    main_map[page][start_row][col] = input.at(i);
                    start_row++;
                }
            }
        }
    }

    string Notebook::read(int page, int row, int col, Direction dir, int length)
    {

        // checks for bad inputs
        if (page < 0 || row < 0 || col < 0 || length < 0)
        {
            throw invalid_argument("cannot insert negative argument!");
        }

        if (col > MAX_LINE)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }


        if (dir == Direction::Horizontal && (col + length) > MAX_LINE+1)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }

        string ans;

        if(dir == Direction::Vertical){
            for(int i=row ; i<row+length ; i++){
                if(main_map[page][i][col] >= MIN_CHAR && main_map[page][i][col] <= (MAX_CHAR+1)){
                    ans += main_map[page][i][col];
                }
                else{
                    ans += "_";
                }
            }
        }


        //Horizontal read
        else{
            for(int i=col ; i<col+length ; i++){
                if(main_map[page][row][i] >= MIN_CHAR && main_map[page][row][i] <= (MAX_CHAR+1)){
                    ans += main_map[page][row][i];
                }
                else{
                    ans += "_";
                }
            }
        }

        return ans;
    }

    void Notebook::erase(int page, int row, int col, Direction dir, int length)
    {
        // checks for bad inputs
        if (page < 0 || row < 0 || col < 0 || length < 0)
        {
            throw invalid_argument("cannot insert negative argument!");
        }

        if (col > MAX_LINE)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }


        if (dir == Direction::Horizontal && (col + length) > MAX_LINE)
        {
            throw invalid_argument("the maximum characters in line is 100!");
        }

        if(dir == Direction::Horizontal){
            for(int i=col ; i<col+length ; i++){
                main_map[page][row][i]='~';
            }
        }
        else{
            for(int i=row ; i<row+length ; i++){
                main_map[page][i][col]='~';
            }
        }
    }

    void Notebook::show(int page)
    {
        if(page<0){
            throw invalid_argument("insert valid page number");
        }
       

        cout << "Page number: " << page << endl;
        bool flag = true;
        int start=0;
        int end=next_print;
        
        while (flag)
        { 
            for(int i=start ; i<end ; i++){
                for(int j=0 ; j<MAX_LINE+1 ; j++){
                    if(main_map[page][i][j]>=MIN_CHAR && main_map[page][i][j]<=(MAX_CHAR+1)){
                        cout << main_map[page][i][j];
                    }
                    else{
                        cout << "_";
                    }
                }
                cout << endl;           
            
            }
            if(page==3){
                break;
            }
            string temp;
            cout << "press 1 for next rows 0 to exit"<< endl;
            cin >> temp;
            if(temp=="0"){
                flag =false;
            }
            else{
                start+=next_print;
                end+=next_print;
            }
        }   
    }
}