#include "Csv.hpp"
#include "IO.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <csv_file_path>\n";
        return 1;
    }
    Csv csv_question(argv[1]);
    csv_question.parsing_csv();
    IO::input_handelling();
    return 0;
}