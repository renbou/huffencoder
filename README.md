# huffencoder  
Huffman-encoding based compression as a project and library  
The library files are in the lib directory  
Qt project with GUI-ready encoder/decoder is inside gui directory  

## Library usage:  
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
### Extra stuff:  
This also contains some extra files such as **bit_sequence.h** which has a class for working with 256-bit sequences and **bit_file.h** for working with files you need to read bit-by-bit ;)  
