#pragma once
#include <iostream>

/**
 * @class Stack
 * @brief A simple byte-based stack implementation with fixed capacity.
 *
 * This class provides a lightweight stack that stores raw bytes in an internal
 * buffer. It supports pushing values of arbitrary types using a template
 * function, as well as pushing strings byte-by-byte.
 *
 * The stack stores data sequentially inside a fixed-size buffer with a maximum
 * capacity of 256 bytes.
 */
class Stack {
public:

    /**
     * @brief Constructs an empty Stack.
     *
     * Initializes the stack pointer and used byte counter to zero.
     */
    Stack() : stack_pointer(0), used_bytes(0) {}

    /**
     * @brief Pushes a value of any type onto the stack.
     *
     * The value is copied byte-by-byte into the internal buffer using memcpy.
     * The size of the pushed value is stored to allow correct removal later.
     *
     * @tparam T Type of the value to push.
     * @param value The value to be pushed onto the stack.
     * @return true if the value was successfully pushed.
     */
    template<typename T>
    bool push(const T& value) {

        std::memcpy(&buffer[used_bytes], &value, sizeof(T));
        stack_pointer += sizeof(T);
        used_bytes += sizeof(T);
        last_arg_size = sizeof(T);
        return true;
    }

    /**
     * @brief Removes the last pushed value from the stack.
     *
     * The function removes the last inserted element based on the stored
     * size of the most recent push operation.
     *
     * @return true if the pop operation succeeded.
     * @return false if there is not enough data to pop.
     */
    bool pop() {
        if (stack_pointer < last_arg_size)
            return false;

        buffer[stack_pointer] = 0;
        stack_pointer -= last_arg_size;
        used_bytes -= last_arg_size;

        return true;
    }

    /**
     * @brief Pushes a null-terminated string onto the stack.
     *
     * Each character of the string is pushed individually as a byte.
     *
     * @param str Pointer to the null-terminated string.
     * @return true when the entire string has been pushed.
     */
    bool push_string(const char* str)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            push(str[i]);
        }
        return true;
    }

    /**
     * @brief Clears the entire stack.
     *
     * Repeatedly pops elements until the stack becomes empty.
     *
     * @return true when the stack has been fully cleared.
     */
    bool clearStack()
    {
        do {
            pop();
        } while (used_bytes > 0);

        return true;
    }

    /**
     * @brief Returns a pointer to the internal buffer.
     *
     * @return Pointer to the stack's raw byte buffer.
     */
    uint8_t* getBuffer()
    {
        return buffer;
    }

    /**
     * @brief Returns the number of bytes currently used in the stack.
     *
     * @return Number of used bytes.
     */
    uint8_t getUsedBytes()
    {
        return used_bytes;
    }

    /**
     * @brief Returns the current stack pointer position.
     *
     * @return Current stack pointer.
     */
    uint8_t getStackPointer()
    {
        return stack_pointer;
    }

private:
    /// Maximum capacity of the stack buffer in bytes.
    static constexpr std::size_t MAX_STACK_CAPACITY = 256;

    /// Internal buffer that stores stack data.
    uint8_t buffer[MAX_STACK_CAPACITY];

    /// Current position of the stack pointer.
    std::size_t stack_pointer;

    /// Total number of bytes currently used.
    std::size_t used_bytes;

    /// Size of the most recently pushed argument.
    std::size_t last_arg_size;
};