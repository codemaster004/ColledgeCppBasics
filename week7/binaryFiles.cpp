//
// Created by Filip Dabkowski on 22/11/2023.
//
#include <iostream>
#include <cstdio>

const int SIZE = 6;


const uint32_t BMP_HEADER_SIZE = 14;
const uint32_t DIB_HEADER_SIZE = 12;
const uint32_t PIX_ARRAY_OFFSET = BMP_HEADER_SIZE + DIB_HEADER_SIZE;
const uint16_t BPP = 24;
const uint16_t BPB = 8;

const uint8_t orange[3] = {0, 127, 255};
const uint8_t blue[3] = {255, 200, 200};
const uint8_t padding[3] = {0, 0, 0};

uint32_t sizeOfRawData(uint16_t nColumns) {
	return nColumns * BPP / BPB;
}

uint32_t numberOfPaddingBytes(uint16_t nColumns) {
	uint32_t nBytesAboveMultipleOf4 = sizeOfRawData(nColumns) % 4;
	return (4 - nBytesAboveMultipleOf4) % 4;
}

uint32_t sizeOfRow(uint16_t nColumns) {
	return sizeOfRawData(nColumns) + numberOfPaddingBytes(nColumns);
}

uint32_t sizeOfPixelArray(uint16_t nRows, uint16_t nColumns) {
	return nRows * sizeOfRow(nColumns);
}

uint32_t sizeOfBMP(uint16_t nRows, uint16_t nColumns) {
	return BMP_HEADER_SIZE + DIB_HEADER_SIZE + sizeOfPixelArray(nRows, nColumns);
}

void writeBMPHeader(FILE *f, uint16_t nRows, uint16_t nColumns) {
	char BM[2] = {0x42, 0x4D};
	fwrite(&BM, 1, 2, f);
	uint32_t size = sizeOfBMP(nRows, nColumns);
	fwrite(&size, 4, 1, f);
	uint16_t reserved[2] = {0, 0};
	fwrite(&reserved, 2, 2, f);
	fwrite(&PIX_ARRAY_OFFSET, 4, 1, f);
}

void writeDIBHeader(FILE *f, uint16_t nRows, uint16_t nColumns) {
	fwrite(&DIB_HEADER_SIZE, 4, 1, f);
	fwrite(&nColumns, 2, 1, f);
	fwrite(&nRows, 2, 1, f);
	uint16_t nColorPlanes = 1;
	fwrite(&nColorPlanes, 2, 1, f);
	fwrite(&BPP, 2, 1, f);
}

void writePixelArray(FILE *f, uint16_t nRows, uint16_t nColumns, char src[SIZE][SIZE]) {
	for (uint16_t row = nRows - 1;; row--) {
		for (uint16_t col = 0; col < nColumns; col++) {
			if (src[row][col] == 1) {
				fwrite(&orange, 1, 3, f);
			} else {
				fwrite(&blue, 1, 3, f);
			}
		}
		fwrite(&padding, 1, numberOfPaddingBytes(nColumns), f);
		if (row == 0) {
			break;
		}
	}
}

void readInputFromFile(const char *filename) {

}

int main(int argc, char **argv) {
	if (argc <= 1) {
		std::cout << "Incorrect number of arguments";
		return 0;
	}
	char data[SIZE][SIZE] = {
		1, 1, 1, 1, 1, 0,
		1, 0, 0, 0, 0, 0,
		1, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0,
		1, 0, 0, 0, 0, 0,
	};

	FILE *f = fopen(argv[1], "wb");
	writeBMPHeader(f, SIZE, SIZE);
	writeDIBHeader(f, SIZE, SIZE);
	writePixelArray(f, SIZE, SIZE, data);
	fclose(f);

}