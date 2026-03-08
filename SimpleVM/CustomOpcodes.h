#pragma once
#include <iostream>
#include <vector>
/**
 * @def DECRIPTKEY
 * @brief Constant key used during bytecode execution for obfuscation operations.
 *
 * This value is used by several instructions in the bytecode program to
 * transform stack values through arithmetic and XOR operations.
 */
#define DECRIPTKEY 0xEE


 /**
  * @enum Opcodes
  * @brief Instruction set used by the bytecode interpreter.
  *
  * Each opcode represents a specific instruction that will be executed
  * by the ExecutionFlow virtual machine. Instructions operate primarily
  * on a stack-based model.
  */
enum Opcodes
{
    /**
     * @brief Pushes the next byte value onto the stack.
     *
     * The interpreter reads the following byte and stores it in the stack.
     */
    PUSH = 0x01,

    /**
     * @brief Performs an addition between the first and last stack values.
     *
     * The result is transformed into a Base62 character and appended to
     * the intermediate result string.
     */
    SUM = 0xC3,

    /**
     * @brief Performs a multiplication between the first and last stack values.
     *
     * The result is mapped to an alphanumeric character.
     */
    MUL = 0x99,

    /**
     * @brief Performs a division between the first and last stack values.
     *
     * Special handling is applied if one of the operands is zero.
     */
    DIV = 0x62,

    /**
     * @brief Applies an XOR-based obfuscation to the current stack value.
     */
    XOR = 0x98,

    /**
     * @brief Placeholder argument used in the bytecode.
     *
     * This value is replaced at runtime with characters from the user input
     * using the fix_arguments function.
     */
    ARG = 0x0,

    /**
     * @brief Signals the end of the bytecode computation stage.
     *
     * At this point the accumulated result string is pushed into the stack
     * and transformed using the final obfuscation routine.
     */
    END = 0xFF,

    /**
     * @brief Compares the computed string with the user-provided password.
     *
     * The comparison determines whether the validation succeeds.
     */
    CMPSTR = 0x76
};


/**
 * @brief Bytecode program executed by the virtual machine.
 *
 * This vector represents the instruction sequence interpreted by the
 * ExecutionFlow class. The program performs a series of stack-based
 * arithmetic and obfuscation operations on user-provided input data.
 *
 * Some instructions contain the placeholder opcode ARG, which will
 * be replaced at runtime with characters from the user input.
 */
std::vector<uint8_t> bytecode = {
    PUSH, ARG,
    PUSH, DECRIPTKEY,
    SUM,

    PUSH, ARG,
    PUSH, DECRIPTKEY,
    MUL,

    PUSH, ARG,
    PUSH, DECRIPTKEY,
    DIV,

    PUSH, ARG,
    XOR,

    PUSH, ARG,
    XOR,

    PUSH, DECRIPTKEY,
    XOR,

    PUSH, DECRIPTKEY,
    PUSH, 0x04,
    DIV,

    PUSH, ARG,
    XOR,

    PUSH, ARG,
    PUSH, ARG,
    MUL,

    PUSH, ARG,
    PUSH, ARG,
    SUM,

    END, CMPSTR
};


/**
 * @brief Replaces placeholder arguments in the bytecode with user input.
 *
 * The function scans the bytecode program for the ARG opcode (0x00) and
 * replaces each occurrence with characters from the provided user input.
 *
 * The replacement occurs sequentially: the first ARG is replaced with
 * the first character of the input, the second ARG with the next character,
 * and so on.
 *
 * @param user_input String provided by the user that will be injected
 *                   into the bytecode program as runtime arguments.
 */
void fix_arguments(std::string user_input)
{
    for (int i = 0; i < user_input.size(); i++)
    {
        for (int j = 0; j < bytecode.size(); j++)
        {
            if (bytecode.at(j) == 0x0)
            {
                bytecode.at(j) = user_input.at(i);
                break;
            }
        }
    }
}