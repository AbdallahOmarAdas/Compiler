#include "FileDescriptor.h"
#pragma warning(disable : 4996)
FileDescriptor::FileDescriptor()
{
	char buf[] = "";
	line_number = 0;
	char_number = 0;
	file_name = "Text.txt";
	buf_size = 1024;
	buffer = buf;
	flag = 0;
	file_pointer = fopen(file_name, "r+");
}

void FileDescriptor::close()
{
	fclose(file_pointer);
	file_pointer = NULL;
}

char FileDescriptor::getChar()
{
	return 0;
}

void FileDescriptor::reportError(char* msg) {

}
void FileDescriptor::ungetChar(char c) {

}

const char* FileDescriptor::getFileName()
{
	return file_name;
}

bool FileDescriptor::isOpen()
{
	if(file_pointer!=NULL)
		return true;
	else return false;
}

char* FileDescriptor::getCurrLine()
{
	char str[1024];
	return fgets(str, 1000000, file_pointer);
	
}

int FileDescriptor::getLineNum()
{
	return line_number;
}

int FileDescriptor::getCharNum()
{
	return char_number;
}

FileDescriptor::FileDescriptor(const char* fileName)
{
	char buf[] = "";
	line_number = 0;
	char_number = 0;
	file_name = fileName;
	buf_size = 1024;
	buffer = buf;
	flag = 0;
	cout << buffer;
	cout << "hello word from cpp";
	file_pointer = fopen(file_name, "r+");
	//int c;
	//while (1) {
	//	c = fgetc(file_pointer);
	//	if (feof(file_pointer)) {
	//		break;
	//	}
	//	printf("%c", c);
	//}


}

FileDescriptor::~FileDescriptor()
{
	delete file_pointer;
	
}
