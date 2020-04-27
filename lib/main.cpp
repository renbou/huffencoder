#include "huffman_builder.h"
#include "huffman_encoder.h"
#include "huffman_decoder.h"

int main() {
	huffmanBuilder huffbuild("inputfile.txt");
	huffbuild.writeHuffmanTree("inputfile.txt.hufftree");
	huffmanEncoder enc("inputfile.txt.hufftree");
	enc.encode("inputfile.txt", "inputfile.txt.huff");
	huffmanDecoder dec("inputfile.txt.hufftree");
	dec.decode("inputfile.txt.huff","outfile.txt");
	return 0;
}