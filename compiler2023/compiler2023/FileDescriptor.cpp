#include "FileDescriptor.h"

FileDescriptor::FileDescriptor()
{
}

void FileDescriptor::close()
{
}

char FileDescriptor::getChar()
{
	return 0;
}

void FileDescriptor::reportError(char* msg) {

}
void FileDescriptor::ungetChar(char c) {

}

char* FileDescriptor::getFileName()
{
	return nullptr;
}

bool FileDescriptor::isOpen()
{
	return false;
}

char* FileDescriptor::getCurrLine()
{
	return nullptr;
}

int FileDescriptor::getLineNum()
{
	return 0;
}

int FileDescriptor::getCharNum()
{
	return 0;
}

FileDescriptor::FileDescriptor(char* FileName)
{
}

FileDescriptor::~FileDescriptor()
{
}
