#include "File.h"

void File::_CheckSize()
{
	this->fp = new std::fstream(this->filename, std::ios::in | std::ios::binary);
	if (this->fp == NULL)
	{
		this->fileSize = -1;
		return;
	}
	size_t currSeek = this->fp->tellp();
	this->fp->seekp(0, std::ios_base::end);
	this->fileSize = this->fp->tellp();
	this->fp->seekp(currSeek, std::ios_base::beg);
	this->fp->close();
	this->fp = NULL;
}

void File::_ReadFromFile()
{
	this->fp = new std::fstream(this->filename, std::ios::in | std::ios::binary);
	if (this->fp == NULL)return;
	if (this->fileSize < 1)return;
	this->buffer = new char[(size_t)this->fileSize + 1];
	if (this->buffer == NULL)
	{
		return;
	}
	this->fp->read(this->buffer, this->fileSize);
	this->buffer[(size_t)this->fileSize] = '\x0';
	this->fp->close();
	this->fp = NULL;
}

File::File(std::string filename) : filename(std::move(filename))
{
	this->fp = new std::fstream(this->filename);
	if (!*this->fp)
	{
		std::cout << "\nCreating file\n";
		this->fp = new std::fstream();
		this->fp->open(this->filename, std::fstream::in | std::fstream::out | std::fstream::app);
		*this->fp << " ";
		this->fp->close();
		this->fp = new std::fstream(this->filename);
	}

	this->buffer = NULL;
	this->_CheckSize();
	this->_ReadFromFile();
	if(this->fp!=NULL)this->fp->close();
	this->fp = NULL;
}

File::~File()
{
	if (this->buffer != NULL)free(this->buffer);
	if (this->fp != NULL)this->fp->close();

	this->fp = NULL;
	this->buffer = NULL;
}

std::ostream::pos_type File::GetSize()
{
	return this->fileSize;
}

void File::Show()
{
	if (this->buffer == NULL)return;
	std::cout << "\n---------\n";
	std::cout << this->filename;
	std::cout << "\n---------\n";
	std::cout << this->buffer;
	std::cout << "\n---------\n";
}

void File::Write(char* content)
{
	this->fp = new std::fstream(this->filename);
	if (this->fp == NULL)return; 
	size_t contentLen = strlen(content);
	this->fp->write(content, contentLen);
	this->fp->close();
	this->fp = NULL;
	this->_CheckSize();
	this->_ReadFromFile(); 
}

void File::Write(char* content, size_t from, size_t to)
{
	this->fp = new std::fstream(this->filename);
	if (this->fp == NULL)return;
	size_t contentLen = strlen(content);
	if (!(from >= 0 && from <= contentLen && to >= 0 && to <= contentLen))return;
	if (from < to)
	{
		for (long i = from; i <= to; i++)
		{
			*this->fp << content[i];
		}
	}
	else {
		for (long i = from; i >= (long)to; i--)
		{
			*this->fp << content[i];
		}
	}
	this->fp->close();
	this->fp = NULL;
	this->_CheckSize();
	this->_ReadFromFile();
}

char* File::GetContent()
{
	return this->buffer;
}
