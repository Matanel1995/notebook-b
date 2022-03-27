#include "doctest.h"
#include "Notebook.hpp"
#include "Direction.hpp"
#include <stdexcept>

using namespace ariel;
using namespace std;

Notebook notebook;
Direction hor = Direction::Horizontal;
Direction ver = Direction::Vertical;
const string data="abcd";

TEST_CASE("check valid position in notebook"){
    // for write function
    CHECK_THROWS(notebook.write(-1,65,50,hor,"abcd"));
    CHECK_THROWS(notebook.write(65,-1,50,hor,"abcd"));
    CHECK_THROWS(notebook.write(65,65,-1,hor,"abcd"));
    CHECK_THROWS(notebook.write(-65,-65,10,hor,"abcd"));
    CHECK_THROWS(notebook.write(-65,65,-10,hor,"abcd"));
    CHECK_THROWS(notebook.write(-65,-65,-10,hor,"abcd"));
        // for read function
    CHECK_THROWS(notebook.read(-1,65,50,hor,5));
    CHECK_THROWS(notebook.read(65,-1,50,hor,5));
    CHECK_THROWS(notebook.read(65,65,-1,hor,5));
    CHECK_THROWS(notebook.read(65,65,120,hor,5));
    CHECK_THROWS(notebook.read(65,65,120,hor,-5));
        // for erase function
    CHECK_THROWS(notebook.erase(-1,65,50,hor,5));
    CHECK_THROWS(notebook.erase(65,-1,50,hor,5));
    CHECK_THROWS(notebook.erase(65,65,-1,hor,5));
    CHECK_THROWS(notebook.erase(65,65,120,hor,5));
    CHECK_THROWS(notebook.erase(65,65,120,hor,-5));
    // for show function
    CHECK_THROWS(notebook.show(-5));
}

TEST_CASE("write to written or deleted position"){
    // try to write on writen position both horizontal and vertical
    notebook.write(1,0,0,hor,"abcd");
    CHECK_THROWS(notebook.write(1,0,0,hor,"abcd"));
    CHECK_THROWS(notebook.write(1,0,0,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,2,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,3,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,2,hor,"abcd"));
    CHECK_THROWS(notebook.write(1,0,3,hor,"abcd"));
    // try to write on erased position both horizontal and vertical
    notebook.erase(1,0,0,hor,5);
    CHECK_THROWS(notebook.write(1,0,0,hor,"abcd"));
    CHECK_THROWS(notebook.write(1,0,0,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,2,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,3,ver,"abcd"));
    CHECK_THROWS(notebook.write(1,0,2,hor,"abcd"));
    CHECK_THROWS(notebook.write(1,0,3,hor,"abcd"));
}