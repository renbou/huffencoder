#ifndef BIT_FILE_H
#define BIT_FILE_H

#include "bit_sequence.h"
#include <cstdio>
#include <stdexcept>
#include <algorithm>

class bitFile {
	FILE * file = nullptr;
	unsigned char bitpos = 8;
	unsigned char curChar = 0;
	unsigned long long fileSize = 0;
	enum filemode {read, write, append, readedit, writeedit, appendedit};
	filemode mode;
public:
	const unsigned long long &size = fileSize;
	bitFile() {}
	~bitFile() {
		close();
	}
	void open(const char * filename, const char * fmode) {
		if (fmode[0] == 'a') {
			if (fmode[1] == '\0') {
				mode = append;
				file = fopen(filename, "ab");
			}
			else if (fmode[1] == '+' && fmode[2] == '\0') {
				mode = appendedit;
				file = fopen(filename, "ab+");
			}
			else
				throw std::runtime_error("Invalid file open mode.");
		} else if (fmode[0] == 'r') {
			if (fmode[1] == '\0') {
				mode = read;
				file = fopen(filename, "rb");
			}
			else if (fmode[1] == '+' && fmode[2] == '\0') {
				mode = readedit;
				file = fopen(filename, "rb+");
			}
			else
				throw std::runtime_error("Invalid file open mode.");
		} else if (fmode[0] == 'w') {
			if (fmode[1] == '\0') {
				mode = write;
				file = fopen(filename, "wb");
			}
			else if (fmode[1] == '+' && fmode[2] == '\0') {
				mode = writeedit;
				file = fopen(filename, "wb+");
			}
			else
				throw std::runtime_error("Invalid file open mode.");
		} else
			throw std::runtime_error("Invalid file open mode.");
		if (file == nullptr)
			throw std::runtime_error("Couldn't open file.");
		fseek(file, 0, SEEK_END);
		fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);
	}
	bool readBit() {
		if (mode == append)
			throw std::runtime_error("Can't read from file opened in 'append' mode.");
		else if (mode == write)
			throw std::runtime_error("Can't read from file opened in 'write' mode.");
		if (bitpos >> 3) {
			if (!fileSize)
				throw std::runtime_error("Trying to read from file when end of file reached.");
			curChar = fgetc(file);
			fileSize--;
			bitpos = 0;
		}
		bool retVal = curChar & (1 << (7 - bitpos++));
		return retVal;
	}
	unsigned char readByte() {
		if (mode == append)
			throw std::runtime_error("Can't read from file opened in 'append' mode.");
		else if (mode == write)
			throw std::runtime_error("Can't read from file opened in 'write' mode.");
		if (!fileSize)
			throw std::runtime_error("Trying to read from file when end of file reached.");
		unsigned char byte = 0;
		bool bit;
		for (char i = 0; i < 8; i++) {
			bit = readBit();
			byte |= bit;
			if (i < 7)
				byte <<= 1;
		}
		return byte;
	}
	void writeBitSequence(bitSequence value) {
		if (bitpos >> 3)
			bitpos = 0;
		if (mode == read)
			throw std::runtime_error("Can't write to file opened in 'read' mode.");
		bitSequence towrite = value;
		unsigned short &leftover = towrite.length;
		unsigned long long *writeVal = towrite.bits;
		while (leftover > 0) {
			unsigned char numToWrite = std::min(leftover, (unsigned short)(8 - bitpos));
			unsigned char writeBits = (writeVal[0] >> (64 - numToWrite)) << (7 - bitpos - numToWrite + 1);
			curChar |= writeBits;
			bitpos += numToWrite;
			if (bitpos >> 3) {
				bitpos = 0;
				fputc(curChar, file);
				curChar = 0;
			}
			leftover -= numToWrite;
			towrite <<= numToWrite;
		}
	}
	void fseekEnd() {
		fseek(file, 0, SEEK_END);
		bitpos = 8;
	}
	void fseekStart() {
		fseek(file, 0, SEEK_SET);
		bitpos = 8;
	}
	void close() {
		if (bitpos != 0 && (mode != read))
			fputc(curChar, file);
		fclose(file);
		bitpos = 0;
	}
};

#endif //BIT_FILE_H
