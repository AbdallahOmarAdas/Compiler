#include "FileDescriptor.h"
#pragma warning(disable : 4996)
FileDescriptor::FileDescriptor()
{
	char buf[] = "Text.txt";
	line_number = 0;
	char_number = 0;
	file_name = new char[15];
	file_name= buf;
	buf_size = 1024;
	buffer = nullptr;
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
	if (char_number != -1000) {
		if (buffer[char_number] != '\n') {
			return buffer[char_number++];
		}
		else {
			FileDescriptor::getCurrLine();
			return ' ';
		}
	}
	else {
		return EOF;
	}

}

void FileDescriptor::reportError(char* msg) {
	cout << "\033[1;31m";
	cout << "syntax error in line number: " << line_number << " and character number: " << char_number << endl;
	
	for (int i = 0; msg[i] != '\0'; i++) {
    cout << msg[i];
	}
	for (int i = 0; i < char_number;i++) {
		cout << " ";
	}
	cout << "^"<<endl;
	cout << "\033[0m";
}
void FileDescriptor::ungetChar(char c) {
	--char_number;
}

char* FileDescriptor::getFileName()
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
	char_number = 0;
	line_number++;
		;
		if (fgets(buffer, 1024, file_pointer) == NULL) {
			cout << "EOF";
			char_number = -1000;
			return nullptr;
		}
		else {
			return buffer;
		}
}

int FileDescriptor::getLineNum()
{
	return line_number;
}

int FileDescriptor::getCharNum()
{
	return char_number;
}

FileDescriptor::FileDescriptor(char* fileName)
{
	char buf[] = "";
	line_number = 0;
	char_number = 0;
	file_name = fileName;
	buf_size = 1024;
	buffer = new char[buf_size];
	flag = 0;
	file_pointer = fopen(file_name, "r+");

}

FileDescriptor::~FileDescriptor()
{
	delete file_pointer;
	delete buffer;
}
