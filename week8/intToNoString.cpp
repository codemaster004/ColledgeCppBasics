//
// Created by Filip Dabkowski on 29/11/2023.
//
#include "iostream"

using namespace std;

void print(const char*str){

}

uint nDigits(int n, int base) {
	uint count = 1;
	uint i = 1;
	while (n / count) {
		count *= base;
		i++;
	}
	return --i;
}

char* toNotString(int number) {
	if (number == 0) {
		char* res = new char[2];
		res[0] = '0';
		res[1] = '\0';
		return res;
	}

	int len = nDigits(number, 10);
	char *res = new char[len + 1]; // +1 for null terminator
	int index = 0;

	// If number is negative, start with a negative sign
	if (number < 0) {
		res[index++] = '-';
		number = -number;
	}

	for (int i = len - 1; i >= 0; --i) {
		res[i] = (number % 10) + '0';
		number /= 10;
	}
	res[len] = '\0'; // null terminator

	// If number was negative, reverse the string except the negative sign
	if (index == 1) {
		std::reverse(res + 1, res + len);
	} else {
		std::reverse(res, res + len);
	}

	return res;
}

int main() {

	return 0;
}