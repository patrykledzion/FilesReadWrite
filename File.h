#pragma once
#include <iostream>
#include <fstream>

class File
{
private:
	char* buffer;
	std::ostream::pos_type fileSize;
	std::fstream* fp;
	void _CheckSize();
	void _ReadFromFile();
	std::string filename;
public:
	File(std::string filename);
	~File();
	std::ostream::pos_type GetSize();
	void Show();
	void Write(char* content);
	void Write(char* content, size_t from, size_t to);
	char* GetContent();
};

