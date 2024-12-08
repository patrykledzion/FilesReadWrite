// Day1_FilesReadWrite.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include "File.h"

int main()
{
    std::cout << "Hello World!\n";
    File* file = new File("test.txt");
    std::cout << file->GetSize()<<std::endl;
    file->Show();
    std::cout << std::endl << file->GetContent();

    File* file_r = new File("test1.txt");

    std::cout << "show 1";
    file_r->Show();
    file_r->Write(file->GetContent(),0, (size_t)file->GetSize() - 1);
    std::cout << "show 2";
    file_r->Show();
    std::cout << file_r->GetContent();
    delete file;
    delete file_r;

    return 0;
}