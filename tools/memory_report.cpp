#include <fstream>
#include <iostream>
#include <string>


int getAttributeValue(const std::string& line);
void getAllAttribute(std::ifstream& file, int& used, int& size);

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 0;
    } 

    const std::string filename = argv[1];       //debug: (argc > 1) ? argv[1] : "../build/mz2048ech064_rtos_memory.xml";
    const std::string searchWord1 = "<memory";
    const std::string searchWord2 = "name=";
    const std::string searchWord3 = "program";
    const std::string searchWord4 = "data";

    std::ifstream file(filename);
    if (!file.is_open()) 
    {
        std::cerr << "Cannot open file: " << filename << '\n';
        return 1;
    }

    int program_used = 0;
    int program_size = 0;

    int data_used = 0;
    int data_size = 0;

    std::string line;
    int lineNumber = 0;
    while (std::getline(file, line)) 
    {
        ++lineNumber;

        if (line.find(searchWord1) == std::string::npos)
        {
            continue;
        }

        if (line.find(searchWord2) == std::string::npos)
        {
            continue;
        }

        if (line.find(searchWord3) != std::string::npos) 
        {
            getAllAttribute(file, program_used, program_size);
            std::cout << "Program Memory:"
            << " size = " << program_size
            << ", used = " << program_used
            << ", usage = " << (float)(program_used / (float)(program_size) * 100.0f) << "%\n";
            
        }
        else if (line.find(searchWord4) != std::string::npos) 
        {
            getAllAttribute(file, data_used, data_size);
            std::cout << "Data Memory   :"
                      << " size = " << data_size
                      << ", used = " << data_used
                      << ", usage = " << (float)(data_used / (float)(data_size) * 100.0f) << "%\n";
        }
    }

    return 0;
}

void getAllAttribute(std::ifstream& file, int& used, int& size)
{
    // find attribute name
    std::string line;
    while (std::getline(file, line)) 
    {
        // end of memory block
        if (line.find("</memory>") != std::string::npos)
        {
            break;
        }

        if (line.find("<length>") != std::string::npos)
        {
            size += getAttributeValue(line);
        }

        if (line.find("<used>") != std::string::npos)
        {
            used += getAttributeValue(line);
        }
    }
    
}

int getAttributeValue(const std::string& line)
{
    size_t start = line.find('>', 0);
    size_t end = line.find('<', start + 1);
    if (start != std::string::npos && end != std::string::npos) 
    {
        std::string value = line.substr(start + 1, end - start - 1);
        try 
        {
            return std::stoi(value);
        } 
        catch (const std::invalid_argument&) 
        {
            std::cerr << "Invalid number format.\n";
        } 
        catch (const std::out_of_range&) 
        {
            std::cerr << "Number out of range.\n";
        }
    }
    return 0;
}

/*EOF*/
