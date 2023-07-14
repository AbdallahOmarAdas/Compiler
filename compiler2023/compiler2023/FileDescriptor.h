#pragma once
#ifndef __FILEDESCRIPTOR__H
#define __FILEDESCRIPTOR__H
#define SET 1
#define UNSET 0
#define BUFFER SIZE 256
#include <cstdio>
#include <iostream>
using namespace std;
class FileDescriptor
{
	/* You must fill in these fields */
private:
	FILE* file_pointer;
	int line_number; /* line number in the file */
	int char_number; /* character number in the line */
	int flag; /* to prevents two ungets in a row */
	int buf_size; /* stores the buffer size */
	char* buffer; /* buffer to store a line */
	char *file_name; /* file name, allocate memory for this */
	//int flag2;
	// add other fields or functions if you want
public:
	/* Externally-visible functions: */
	char* getFileName();
	bool isOpen(); // returns true if a file is open without errors, //otherwise returns false
	char* getCurrLine(); // returns a pointer to buffer, null if EOF
	int getLineNum();
	int getCharNum();
	FileDescriptor(char FileName[]); // opens the stdin FileName is Null
	~FileDescriptor();
	FileDescriptor(); //opens the stdin
	void close(); // closes the file descriptor
	char getChar(); // Gets the current character in the file
	//bool open_file_descriptor (char *filename);
	void reportError(char* msg); // reports the error specifying the current line and //character
	void ungetChar(char c); // puts back the current character, modifies char number
};
#endif