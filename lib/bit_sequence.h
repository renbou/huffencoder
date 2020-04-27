#ifndef BIT_SEQUENCE_H
#define BIT_SEQUENCE_H

struct bitSequence {
	unsigned long long bits[4] = {0, 0, 0, 0};
	unsigned short length = 0;
	bitSequence() {}
	bitSequence(bitSequence &other) {
		for (unsigned char i = 0; i < 4; i++)
			bits[i] = other.bits[i];
		length = other.length;
	}
	bitSequence operator+ (bool bit) {
		bitSequence result = *this;
		result.addBit(bit);
		return result;
	}
	bitSequence operator- () {
		bitSequence result = *this;
		result.remBit();
		return result;
	}
	bitSequence& operator=(bitSequence &other) {
		for (unsigned char i = 0; i < 4; i++)
			bits[i] = other.bits[i];
		length = other.length;
		return *this;
	}
	bitSequence& operator<<= (unsigned short amount) {
		bits[0] <<= amount;
		bits[0] |= (bits[1] >> (64 - amount));
		bits[1] <<= amount;
		bits[1] |= (bits[2] >> (64 - amount));
		bits[2] <<= amount;
		bits[2] |= (bits[3] >> (64 - amount));
		bits[3] <<= amount;
		return *this;
	}
	bitSequence(unsigned char t_char, unsigned char t_length) {
		length = t_length;
		bits[0] |= ((unsigned long long)t_char << (64 - length));
	}
	bitSequence(unsigned char t_char) {
		length = 8;
		bits[0] |= ((unsigned long long)t_char << 56);
	}
	inline void addBit(bool bit) {
		bits[(length >> 6)] |= ((unsigned long long)bit << (63 - (length & 63)));
		++length;
	}
	inline void remBit() {
		--length;
	}
};

#endif //BIT_SEQUENCE_H
