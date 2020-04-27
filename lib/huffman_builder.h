#ifndef HUFFMAN_BUILDER_H
#define HUFFMAN_BUILDER_H

#include "charcounter.h"
#include "heap.h"
#include "bit_file.h"

struct huffmanBuilder {
	heapNode * huffmanTree;

	huffmanBuilder(const char * filename) {
		FILE * file = fopen(filename, "r");
		if (file == null)
			throw std::runtime_error("No such file exists!");
		else {
			charCounter * cnter = new charCounter;
			while (!feof(file))
				cnter->readChar(fgetc(file));
			cnter->removeEOF();
			heapNode ** resArray = cnter->getVals();
			ush numChars = cnter->size;
			delete cnter;
			heap *huffmanHeap = new heap;
			huffmanHeap->build(resArray, numChars);
			buildHuffmanTree(huffmanHeap);
			huffmanTree = huffmanHeap->arr[0];
			delete huffmanHeap;
			fclose(file);
		}
	}

	void buildHuffmanTree(heap *&huffmanHeap) {
		while (huffmanHeap->size > 1) {
			heapNode *first = huffmanHeap->getMin();
			heapNode *second = huffmanHeap->getMin();
			heapNode *result = new heapNode(first->size + second->size, '\0');
			result->left = first, result->right = second;
			huffmanHeap->insert(result);
		}
	}

	void nodeWrite(bitFile &file, heapNode * node) {
		if (node->left == null && node->right == null) {
			file.writeBitSequence({1,1});
			file.writeBitSequence(node->value);
			return;
		}
		file.writeBitSequence({0,1});
		nodeWrite(file, node->left);
		nodeWrite(file, node->right);
	}

	unsigned int countSize(heapNode * node) {
		if (node == nullptr)
			return 0;
		if (node->left == null && node->right == null)
			return 9;
		return countSize(node->left) + countSize(node->right) + 1;
	}

	void writeHuffmanTree(const char * filename) {
		bitFile file;
		unsigned int size = countSize(huffmanTree)+3;
		file.open(filename, "w");
		size = 8 - size % 8;
		if (size == 8)
			size = 0;
		bitSequence fileSize = {(unsigned char)size, 3};
		file.writeBitSequence(fileSize);
		nodeWrite(file, huffmanTree);
		file.close();
	}
};

#endif //HUFFMAN_BUILDER_H
