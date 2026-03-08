#pragma once
#include <Windows.h>
#include "Stack.h"
/**
 * @class Handler
 * @brief Provides operations that process and transform data stored in a Stack.
 *
 * The Handler class operates on raw byte data stored inside a Stack object.
 * It provides arithmetic-like operations, byte obfuscation, string processing,
 * and comparison utilities.
 *
 * Most operations read bytes from the stack buffer and transform the results
 * into alphanumeric characters using a Base62-style mapping:
 *
 *  - '0'–'9'
 *  - 'A'–'Z'
 *  - 'a'–'z'
 *
 * The class does not own the stack by default unless it is explicitly created
 * and passed to the constructor.
 */
class Handler {
public:

    /**
     * @brief Constructs a Handler with an existing Stack instance.
     *
     * @param _stack Pointer to the stack that will be used for all operations.
     */
    Handler(Stack* _stack) {
        this->stack = _stack;
    }

    /**
     * @brief Default constructor.
     *
     * Creates a Handler without an assigned stack.
     */
    Handler() = default;

    /**
     * @brief Destructor.
     *
     * Deletes the associated stack if it exists.
     */
    ~Handler() { if (stack) { delete stack; } };

    /**
     * @brief Computes a sum between the first and last byte in the stack.
     *
     * The function retrieves the first and last byte stored in the stack,
     * performs an addition, and maps the resulting value to an alphanumeric
     * character using a Base62 mapping.
     *
     * @return ASCII character representing the mapped result.
     */
    int sum();

    /**
     * @brief Computes a multiplication between the first and last byte in the stack.
     *
     * The resulting value is mapped into an alphanumeric character using
     * a Base62 mapping.
     *
     * @return ASCII character representing the mapped result.
     */
    int mul();

    /**
     * @brief Computes a division between the first and last byte in the stack.
     *
     * If either operand is zero, an alternative transformation is applied
     * before performing the division. The result is mapped to a Base62
     * alphanumeric character.
     *
     * @return ASCII character representing the mapped result.
     */
    int div();

    /**
     * @brief Obfuscates the last byte stored in the stack.
     *
     * The function applies a transformation using a key:
     *
     * 1. XOR with the provided key
     * 2. Arithmetic transformation
     * 3. Base62 character mapping
     *
     * The resulting value replaces the original byte in the stack.
     *
     * @param key Obfuscation key used in the transformation.
     * @return The resulting mapped character.
     */
    uint8_t obfuscate(uint8_t key);

    /**
     * @brief Applies obfuscation to all bytes in the stack.
     *
     * Iterates through the stack buffer and applies the obfuscation
     * algorithm using a fixed key (0x54) to each byte.
     *
     * The stack content is modified in-place.
     */
    void getFinalString();

    /**
     * @brief Compares the stack content with a user-provided string.
     *
     * Each byte in the stack buffer is compared with the corresponding
     * character in the input string.
     *
     * @param user_string Null-terminated string provided by the user.
     * @return 0 if both strings match, 1 otherwise.
     */
    int strcompare(const char* user_string);

protected:

    /**
     * @brief Pointer to the Stack used for storage and processing.
     */
    Stack* stack;
};