#include "CsvLoader.h"

#include <fstream>
#include <sstream>

std::vector<std::vector<int>> CsvLoader::Load(const std::string& _filename)
{
    std::vector<std::vector<int>> data;

    std::ifstream file(_filename);

    if (!file.is_open())
    {
        return data;
    }

    bool firstLine = true;

    std::string line;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;

            if (line.size() >= 3 &&
                static_cast<unsigned char>(line[0]) == 0xEF &&
                static_cast<unsigned char>(line[1]) == 0xBB &&
                static_cast<unsigned char>(line[2]) == 0xBF)
            {
                line.erase(0, 3);
            }
        }

        std::vector<int> row;
        std::stringstream ss(line);

        std::string value;

        while (std::getline(ss, value, ','))
        {
            row.push_back(std::stoi(value));
        }

        data.push_back(row);
    }

    return data;
}