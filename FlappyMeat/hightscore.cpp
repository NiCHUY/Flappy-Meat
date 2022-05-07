#include "hightscore.h"

void hightscore::GetHightscore()
{std::string line;

    std::ifstream in("D:\\hello.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (getline(in, line))
        {
            std::cout << line << std::endl;
        }

}
}
