#include "../headers/LogToFile.h"

int logToFile(std::string &s){
    setlocale(LC_ALL, "rus");
    std::string outputFileName {"TCP_log.txt"};
    std::ofstream output(outputFileName, std::ios::app);
    if (!output.is_open()) std::cout<<"Faled to open WRITE-file: "<< outputFileName << std::endl;
    else{
        output << getTime() << '\t' << s << '\n';
    }
    output.close();
    return 0;
}
