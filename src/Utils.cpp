#include "Utils.h"
#include <fstream>

void Utils::logToCSV(const std::string& filepath, const std::string& data) {
    std::ofstream file(filepath, std::ios::app);
    file << data << std::endl;
    file.close();
}
