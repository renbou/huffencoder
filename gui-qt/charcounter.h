#ifndef HUFFMAN_CHARCOUNTER_H
#define HUFFMAN_CHARCOUNTER_H

#include "heap.h"

#ifndef UVARS
#define ush unsigned short int
#define uint unsigned int
#define ull unsigned long long
#define uchar unsigned char
#define null nullptr
#endif

struct charCounter {
	long long table[256];
	ush size = 0;
	charCounter () {
		for (ush i = 0; i < 256; i++)
			table[i] = -1;
	}
	void readChar(uchar chr) {
		if (table[chr] < 0)
			table[chr] = 1, size++;
		else
			table[chr]++;
	}
	void removeEOF() {
		if (table[255] > 1)
			table[255]--;
		else {
			table[255] = -1;
			--size;
		}
	}
	heapNode ** getVals() {
		heapNode ** ret = new heapNode*[size];
		ush pointer = 0;
		for (ush i = 0; i < 256; i++)
			if (table[i] > 0)
				ret[pointer++] = new heapNode(table[i], i);
		return ret;
	}
};

#endif //HUFFMAN_CHARCOUNTER_H
