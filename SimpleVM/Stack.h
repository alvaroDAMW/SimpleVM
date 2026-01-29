#pragma once
#include <iostream>

class Stack {
public:
    Stack() : stack_pointer(0), used_bytes(0) {}
    template<typename T>
    bool push(const T& value) {

        std::memcpy(&buffer[used_bytes], &value, sizeof(T));
        stack_pointer += sizeof(T);
        used_bytes += sizeof(T);
        last_arg_size = sizeof(T);
        return true;
    }

    bool pop() {
        if (stack_pointer < last_arg_size)
            return false;
        buffer[stack_pointer] = 0;
        stack_pointer -= last_arg_size;
        used_bytes-= last_arg_size;
        return true;
    }
    bool push_string(const char* str)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            push(str[i]);
        }
        return true;
    }

    bool clearStack()
    {
        do {
            pop();
        } while (used_bytes > 0);
        return true;
    }

    uint8_t* getBuffer()
    {
        return buffer;
    }
    uint8_t getUsedBytes()
    {
        return used_bytes;
    }
    uint8_t getStackPointer()
    {
        return stack_pointer;
    }
private:
    static constexpr std::size_t MAX_STACK_CAPACITY = 256;
    uint8_t buffer[MAX_STACK_CAPACITY];
    std::size_t stack_pointer;
    std::size_t used_bytes;
    std::size_t last_arg_size;
};
