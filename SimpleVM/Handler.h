#pragma once
#include <Windows.h>
#include "Stack.h"
class Handler {
public:
	Handler(Stack* _stack) {
		this->stack = _stack;
	}
	Handler() = default;
	~Handler() { if (stack) { delete stack; } };
	int sum();
	int mul();
	int div();
	uint8_t obfuscate( uint8_t key);
	void getFinalString();
	int strcompare(const char* user_string);
protected:
	Stack* stack;
};