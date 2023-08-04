#include "FileDescriptor.h"
#pragma warning(disable : 4996)
FileDescriptor::FileDescriptor()
{
	char buf[] = "Text.txt";
	line_number = 0;
	char_number = 0;
	file_name = new char[15];
	file_name= buf;
	//buf_size = 1024;
	flag = 0;
	file_pointer = fopen(file_name, "r+");
	buf_size = allocatMem(file_pointer);
	file_pointer = fopen(file_name, "r+");
	buffer = new char[buf_size];
	getCurrLine();
}

void FileDescriptor::close()
{
	fclose(file_pointer);
	file_pointer = NULL;
}

char FileDescriptor::getChar()
{
	if (char_number==-1) {
		char_number++;
	}
	if (char_number != -1000) {
		if (buffer[char_number] != '\n') {
			return buffer[char_number++];
		}
		else {
			
			FileDescriptor::getCurrLine();
			return '\r';
		}
	}
	else {
		cout << "this is the end of file *******************" << endl;
		return EOF;
	}

}

void FileDescriptor::reportError(const char* msg, char c) {
	cout << "\033[1;31m";
	cout << "syntax error in line number: " << line_number << " and character number: " << char_number << endl;
	
	for (int i = 0; msg[i] != '\0'; i++) {
		cout << msg[i];
	}
	
	cout << "'" << c << "'";
	
	cout << endl;
	if (msg[0] != 'u') {
		for (int i = 0; buffer[i] != '\0'; i++) {
			cout << buffer[i];
		}
		//cout << endl;
	}
	for (int i = 0; i < char_number;i++) {
		cout << " ";
	}
	cout << "^"<<endl;
	cout << "\033[0m";
	//exit(0);
}
void FileDescriptor::ungetChar() {
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
		
		if (fgets(buffer, buf_size, file_pointer) == nullptr) {
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
	flag = 0;
	file_pointer = fopen(file_name, "r+");
	buf_size=allocatMem(file_pointer);
	file_pointer = fopen(file_name, "r+");
	//buf_size = 1024;
	buffer = new char[buf_size];
	getCurrLine();
}
int FileDescriptor::allocatMem(FILE *file) {
	int ch;
	int count = 0;
	int temp = 0;
	int ch_old;
	while ((ch = fgetc(file)) != EOF) {
		ch_old = ch;
		temp++;
		if (ch == '\n' || ch == EOF) {
			if (temp > count)count = temp;
			temp = 0;
		}
	}
	int mem = 16;
	while (count > mem)mem *= 2;
	cout << "allocated memory for buffer:" << endl;
	cout << "-------------------------------------- " << mem << " --------------------------------------------"<<endl;
	
	if(ch_old !='\n')fputc('\n', file_pointer);
	
	fclose(file);
	return mem;
}
FileDescriptor::~FileDescriptor()
{
	delete file_pointer;
	delete buffer;
}
