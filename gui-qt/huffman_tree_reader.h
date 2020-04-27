#ifndef HUFFMAN_TREE_READER_HPP
#define HUFFMAN_TREE_READER_HPP

#include "heap.h"
#include "bit_file.h"

class huffmanTreeReader {
	void readNode(bitFile &file, heapNode *& node) {
		if (node == nullptr)
			node = new heapNode;
		bool bit;
		try {
			bit = file.readBit();
		} catch (std::runtime_error &e) {
			throw std::runtime_error("Couldn't read huffman tree from file.");
		}
		if (bit == 1) {
			unsigned char byte = 0;
			try {
				byte = file.readByte();
			} catch (std::runtime_error &e) {
				throw std::runtime_error("Couldn't read huffman tree from file.");
			}
			node->value = byte;
			return;
		}
		node->left = new heapNode;
		node->right = new heapNode;
		readNode(file, node->left);
		readNode(file, node->right);
	}
public:
	huffmanTreeReader () {};
	heapNode * readHuffmanTree(const char * filename) {
		bitFile file;
		file.open(filename, "r");
		heapNode * huffmanTree = nullptr;
		readNode(file, huffmanTree);
		file.close();
		return huffmanTree;
	}
};

#endif //HUFFMAN_TREE_READER_HPP
