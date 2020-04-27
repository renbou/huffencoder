#ifndef HEAP_H
#define HEAP_H

#ifndef UVARS
#define ush unsigned short int
#define uint unsigned int
#define ull unsigned long long
#define uchar unsigned char
#define null nullptr
#endif

struct heapNode {
	ull size: 56;
	uchar value;
	heapNode * left = null, * right = null;
	heapNode() {}
	heapNode(ull t_s, uchar t_val)
	: size(t_s),
	  value(t_val) {}
	void deleteNodes(heapNode * c) {
		deleteNodes(c->left);
		deleteNodes(c->right);
		delete this;
	};
};

inline void swapNodes(heapNode * &a, heapNode * &b) {
	heapNode * tmp = a;
	a = b;
	b = tmp;
}

struct heap {
	heapNode** arr;

	ush size = 0;

	heap() {}

	void siftDown(ush index) {
		ush left = (index << 1) + 1;
		ush right = (index << 1) + 2;
		ush smallest = index;
		while (left < size) {
			if (left < size && arr[left]->size < arr[smallest]->size)
				smallest = left;
			if (right < size && arr[right]->size < arr[smallest]->size)
				smallest = right;
			if (smallest ^ index) {
				swapNodes(arr[index], arr[smallest]);
				index = smallest;
				left = (index << 1) + 1;
				right = (index << 1) + 2;
			} else
				break;
		}
	}

	void siftUp(ush index) {
		while (index) {
			ush parent = ((index - 1) >> 1);
			if (arr[parent]->size > arr[index]->size) {
				swapNodes(arr[index], arr[parent]);
				index = parent;
			} else index = 0;
		}
	}

	heapNode * getMin() {
		--size;
		swapNodes(arr[0], arr[size]);
		siftDown(0);
		return arr[size];
	}

	void insert(heapNode * t_node) {
		arr[size++] = t_node;
		siftUp(size-1);
	}

	void build(heapNode **t_arr, ush t_size) {
		arr = t_arr;
		size = t_size;
		for (int i = ((size - 1) >> 1) - (size&1); i >= 0; --i)
			siftDown(i);
	}
};

#endif //HEAP_H
