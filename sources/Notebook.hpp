#include <string>
#include <map>
#include "Direction.hpp"

using namespace std;
namespace ariel{
    class Notebook{
        public:
            static constexpr int rowLen = 100;
            map<int, map<int, string> > notebook;
            Notebook();
            ~Notebook();
            string read(int page, int row, int col, ariel::Direction dir, int len);
            void write(int page, int row, int col, ariel::Direction dir, string const &data);
            void erase(int page, int row, int col, ariel::Direction dir, int len);
            void show(int page);
            static bool check_input(int page, int row, int col);
            void init_new_row(int page, int row);
            bool allready_taken(int page, int row, int col, Direction dir, string const & data);
            static bool is_string_ok(string data);
    };
}