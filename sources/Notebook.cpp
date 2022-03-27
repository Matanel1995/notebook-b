#include <string>
#include <map>
#include "Direction.hpp"
#include "Notebook.hpp"

using namespace std;
using ariel::Notebook;
    // Empty constractor
    Notebook::Notebook(){

    }
    // Destractor for my class
    Notebook::~Notebook(){
        
    }

    string Notebook::read(int page, int row, int col, ariel::Direction dir, int len){
        string read_value;
        // Check input is ok, if not throw exeption 
        if(!check_input(page,row,col)){
            throw std::invalid_argument{"Negative page or row or col value!"};
        }
        if(len <= 0){
            throw std::invalid_argument{"Cant read 0 chars or less!"};
        }
        if(len > rowLen && dir == ariel::Direction::Horizontal){
            throw std::invalid_argument{"Cant read more than 100 cahrs in one line!"};
        }
        if(col+ len > rowLen + 1){
            throw std::invalid_argument{"Col index is more than max!"};
        }
        
        // Init lines before i read
        if(dir == Direction::Horizontal){
            init_new_row(page,row);
        }
        else{
            for(int i=row ; i< row + len; i++){
                init_new_row(page,i);
            }
        }

        // Read the len from the notebook and return it!
        if(dir == Direction::Horizontal){
            for(int i=0; i< len ; i++){
                unsigned int position = (unsigned int)(col+ i);
                read_value +=  this->notebook.at(page).at(row)[position];
            }
        }
        else{
            for(int i=0; i<len; i++){
                unsigned int unCol = (unsigned int)(col);
                read_value += this->notebook.at(page).at(row +i)[unCol];
            }
        }
        return read_value;
    }


    void Notebook::write(int page, int row, int col, ariel::Direction dir, string const &data){
        int dataLen = (int)(data.length());
        // check params and thron exepaction if needed
        if(!check_input(page,row,col)){
            throw std::invalid_argument{"Negative page or row or col value!"};
        }
        if(dataLen == 0 ||!is_string_ok(data)){
            throw std::invalid_argument{"your data contains unvalid chars!"};
        }
        if(dataLen > rowLen - 1 && dir == ariel::Direction::Horizontal){
            throw std::invalid_argument{"Cant write more than 100 cahrs in one line!"};
        }

        // init (if needed) all the rows ill be needed
        if(dir == Direction::Horizontal){
            init_new_row(page,row);
        }
        else{
            for(int i=row ; i< row + dataLen; i++){
                init_new_row(page,i);
            }
        }

        //check if i can write in this spot if i cant throw exeaption!
        if(allready_taken(page,row,col,dir,data)){
            throw std::invalid_argument{"Cant write where its allready written!"};
        }

        //if i got here i can write to my notebook
        if(dir == Direction::Horizontal){
            for(int i=col ; i< col+dataLen; i++){
                unsigned int position = (unsigned int)(i);
                unsigned int dataPos = (unsigned int)(i -col);
                this->notebook.at(page).at(row)[position] = data[dataPos];
            }
        }
        else{
            for(int i=row ; i< row+dataLen;i++){
                unsigned int unCol = (unsigned int)(col);
                unsigned int dataPos = (unsigned int)(i - row);
                this->notebook.at(page).at(i)[unCol] = data[dataPos];
            }
        }
    }

    void Notebook::erase(int page, int row, int col, ariel::Direction dir, int len){
        // check params and thron exepaction if needed
        if(!check_input(page,row,col)){
            throw std::invalid_argument{"Negative page or row or col value!"};
        }
        if(len <= 0){
            throw std::invalid_argument{"Cant delete 0 chars!"};
        }
        if(len >= rowLen && dir==Direction::Horizontal){
            throw std::invalid_argument{"Cant delete more than 100 chars in one line!"};
        }
        if(col+ len >= rowLen + 1 && dir == Direction::Horizontal){
            throw std::invalid_argument{"Col index is more than max!"};
        }

        //Init lines
        if(dir == Direction::Horizontal){
            init_new_row(page,row);
        }
        else{
            for(int i=row ; i< row + len; i++){
                init_new_row(page,i);
            }
        }

        // Delete the data from the notebook
        if(dir == Direction::Horizontal){
            for(int i = col ; i< col+ len; i++){
                unsigned int position = (unsigned int)(i);
                this->notebook.at(page).at(row)[position] = '~';
            }
        }
        else{
            for(int i= row; i < row + len ; i++){
                unsigned int unCol = (unsigned int)(col);
                this->notebook.at(page).at(i)[unCol] = '~';
            }
        }
    }


    void Notebook::show(int page){
        string empty(rowLen,'_');
        string ans;
        if(page< 0){
            throw std::invalid_argument{"Page number cant be negative!"};
        }
        // Print the whole page using iterator
        std::map<int, string> ::iterator itr;
        try{
            for(itr = this->notebook.at(page).begin(); itr != this->notebook.at(page).end(); itr++){
                ans += itr->second;
                ans += '\n';
            }
        }
        catch(exception ex){
            ans =' ';
        }
    }


    bool Notebook::check_input(int page, int row, int col){
        if (page >= 0 && row >= 0 && col >= 0){
            if(col < rowLen){
                return true;
            }
        }
        return false;
    }

    void Notebook::init_new_row(int page, int row){
        //check if page exist with find function
        if(this->notebook.find(page) != this->notebook.end()){
            if(this->notebook[page].find(row) == this-> notebook[page].end()){
                string newLine(rowLen,'_');
                this->notebook[page][row] = newLine;
            }
        }

        if(this->notebook.find(page) == this->notebook.end()){
            if(this->notebook[page].find(row) == this->notebook[page].end()){
                string newLine(rowLen,'_');
                this->notebook[page][row] = newLine;
            }
        }
    }

    bool Notebook::allready_taken(int page, int row, int col, Direction dir,  string const &data){
        int dataLen = data.length();
        // Check direction
        if (dir == Direction::Horizontal){
            // Loop over all cols and return true if somthing is written in them
            string temp = this->notebook.at(page).at(row);
            for(int i=col; i< col + dataLen ; i++){
                unsigned int position = (unsigned int)(i);
                if(temp[position] != '_'){
                    return true;
                }
            }
        }
        else{
            for(int i=row; i < row + dataLen; i++){
                unsigned int position = (unsigned int)(col);
                string temp = this->notebook.at(page).at(i);
                if(temp.at(position) != '_'){
                    return true;
                }
            }
        }
        return false;
    }
    // function to check the data to write
    bool Notebook::is_string_ok(string data){
        for(int i=0; i< data.length(); i++){
            unsigned int position = (unsigned int)(i);
            if(data.at(position) < ' ' || data.at(position) >= '~'){
                return false;
            }
        }
        return true;
    }