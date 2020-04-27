#ifndef HUFFMAN_ENCODER_H
#define HUFFMAN_ENCODER_H

#include "huffman_tree_reader.h"
#include "bit_file.h"

#ifndef UVARS
#define ush unsigned short int
#define uint unsigned int
#define ull unsigned long long
#define uchar unsigned char
#define null nullptr
#endif

class huffmanEncoder {
	bitSequence *huffmanTable[256];

	void writeHuffmanTable(heapNode * node, bitSequence curCode = {}) {
		if (node->left == null && node->right == null) {
			huffmanTable[node->value] = new bitSequence(curCode);
			return;
		}
		curCode.addBit(0);
		writeHuffmanTable(node->left, curCode);
		curCode.remBit();
		curCode.addBit(1);
		writeHuffmanTable(node->right, curCode);
	}

	void writeSize(ull size, bitFile &file) {
		if (size == 0) {
			file.writeBitSequence({0});
			return;
		}
		ull mask = 0x7f;
		ush count = 0;
		while (size & mask)
			mask <<= 7, count++;
		if (mask == 0) {
			file.writeBitSequence({3});
			mask = ((ull)127 << 56), count = 8;
		} else if (mask == 1)
			mask = ((ull)127 << 56), count = 8;
		else
			mask >>= 7, count--;
		while (mask) {
			if (mask == 127)
				file.writeBitSequence({(uchar)((size & mask) << 1)});
			else
				file.writeBitSequence({(uchar)(((size & mask) >> (7*count-1)) | 1)});
			count--, mask >>= 7;
		}
	}
public:
	huffmanEncoder (const char * filename) {
		for (ush i = 0; i < 256; i++)
			huffmanTable[i] = nullptr;
		heapNode * huffmanTree = huffmanTreeReader().readHuffmanTree(filename);
		if (huffmanTree->left == null && huffmanTree->right == null)
			huffmanTable[huffmanTree->value] = new bitSequence(0);
		writeHuffmanTable(huffmanTree);
	}

	void encode(const char * inputFilename, const char * outputFilename) {
		FILE * input = fopen(inputFilename, "rb");
		bitFile output;
		output.open(outputFilename, "w");
		fseek(input, 0, SEEK_END);
		ull sz = ftell(input);
		fseek(input, 0, SEEK_SET);
		ull resSize = 0;
		for (ull i = 0; i < sz; i++)
			resSize += huffmanTable[fgetc(input)]->length;
		fseek(input, 0, SEEK_SET);
		writeSize(resSize >> 3, output);
		output.writeBitSequence({(uchar)(resSize & 7), 3});
		for (ull i = 0; i < sz; i++) {
			uchar byte = fgetc(input);
			output.writeBitSequence(*huffmanTable[byte]);
		}
		fclose(input);
		output.close();
	}
};

#endif //HUFFMAN_ENCODER_H
