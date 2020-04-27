#ifndef HUFFMAN_DECODER_H
#define HUFFMAN_DECODER_H

#include "heap.h"
#include "huffman_tree_reader.h"
#include "bit_file.h"

class huffmanDecoder {
	heapNode * huffmanTree;
public:
	huffmanDecoder(const char * filename) {
		huffmanTree = huffmanTreeReader().readHuffmanTree(filename);
	}

	ull readSize(bitFile &file) {
		ull size = 0;
		uchar byte = file.readByte();
		size |= (byte >> 1);
		while (byte & 1) {
			byte = file.readByte();
			size <<= 7;
			size |= (byte >> 1);
		}
		return size;
	}

	void decode(const char * inputFilename, const char * outputFilename) {
		FILE * output = fopen(outputFilename, "wb");
		FILE * tmpinput = fopen(inputFilename, "rb");
		fseek(tmpinput, 0, SEEK_END);
		ull size = ftell(tmpinput);
		fseek(tmpinput, 0, SEEK_SET);
		fclose(tmpinput);
		bitFile input;
		input.open(inputFilename, "r");
		uchar bits = (((uchar)input.readBit()) << 2) | (((uchar)input.readBit()) << 1) | ((uchar)input.readBit());
		size <<= 3;
		size -= bits + 3;

		heapNode *curNode = huffmanTree;
		bool bit;
		int count = 0;
		for (ull i = 0; i < size; i++) {
			if (count == 25) {

			}
			bit = input.readBit();
			if (bit&1)
				curNode = curNode->right;
			else
				curNode = curNode->left;
			if (curNode->left == null && curNode->right == null)
				fputc(curNode->value, output), curNode = huffmanTree, count++;
		}

		input.close();
		fclose(output);
	}
};

#endif //HUFFMAN_DECODER_H
