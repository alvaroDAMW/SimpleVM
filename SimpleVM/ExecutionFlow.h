#pragma once
#include <Windows.h>
#include <memory>
#include "Stack.h"
#include "Handler.h"
#include "CustomOpcodes.h"

/**
 * @struct Context
 * @brief Execution context used by the bytecode interpreter.
 *
 * The Context structure stores the state required to execute the bytecode,
 * including the instruction pointer and the total size of the bytecode buffer.
 *
 * The instruction pointer (RIP) points to the current instruction being
 * interpreted during execution.
 */
struct Context
{
    /**
     * @brief Pointer to the current instruction in the bytecode.
     *
     * This pointer is incremented during execution to move through the
     * bytecode instructions.
     */
    uint8_t* RIP;

    /**
     * @brief Total size of the bytecode in bytes.
     */
    std::size_t size_of_bytecode;

    /**
     * @brief Destructor.
     *
     * Resets the instruction pointer.
     */
    ~Context()
    {
        RIP = 0;
    }
};


/**
 * @class ExecutionFlow
 * @brief Simple bytecode interpreter that executes operations using a stack.
 *
 * ExecutionFlow interprets a sequence of bytecode instructions and executes
 * them sequentially using a stack-based model. The class inherits from
 * Handler and therefore uses its arithmetic, obfuscation, and comparison
 * utilities.
 *
 * The interpreter processes bytecode instructions through an instruction
 * pointer stored in a Context structure.
 *
 * Supported operations include:
 *  - Pushing values onto the stack
 *  - Arithmetic transformations
 *  - Byte obfuscation
 *  - Final string transformation
 *  - Password comparison
 *
 * The execution model resembles a very small virtual machine.
 */
class ExecutionFlow : Handler {
public:

    /**
     * @brief Constructs the execution environment.
     *
     * Allocates a new Stack and initializes the execution context with
     * the provided bytecode.
     *
     * The bytecode is copied into dynamically allocated memory so the
     * interpreter can iterate through it safely.
     *
     * @param byte_code Vector containing the bytecode instructions.
     * @param userPassword User-provided password used for final comparison.
     */
    ExecutionFlow(std::vector<UINT8> byte_code, const char* userPassword)
        : Handler{ new Stack() }
    {
        ctx = new Context{ NULL, byte_code.size() };

        ctx->RIP = (std::uint8_t*)(malloc(byte_code.size()));
        memcpy(ctx->RIP, byte_code.data(), byte_code.size());

        user_Password = userPassword;
    }

    /**
     * @brief Default constructor.
     */
    ExecutionFlow() = default;

    /**
     * @brief Executes the loaded bytecode program.
     *
     * The interpreter iterates through the bytecode instructions until
     * the end of the bytecode buffer is reached.
     *
     * Each opcode triggers a specific operation such as:
     *
     * - Pushing values onto the stack
     * - Performing arithmetic transformations
     * - Obfuscating values
     * - Generating a final string
     * - Comparing the result with the user password
     *
     * The results of arithmetic or transformation instructions are appended
     * to an internal result string.
     */
    void run()
    {
        uint8_t* end = ctx->RIP + ctx->size_of_bytecode;
        std::string result;

        while (ctx->RIP < end)
        {
            uint8_t opcode = *ctx->RIP;

            switch (opcode)
            {
            case PUSH:
                stack->push(*++ctx->RIP);
                break;

            case SUM:
                result += (char)this->sum();
                stack->clearStack();
                break;

            case MUL:
                result += (char)this->mul();
                stack->clearStack();
                break;

            case DIV:
                result += (char)this->div();
                stack->clearStack();
                break;

            case XOR:
                result += char(this->obfuscate(0xF2));
                stack->clearStack();
                break;

            case END:
                stack->clearStack();
                stack->push_string(result.c_str());
                this->getFinalString();
                break;

            case CMPSTR:
                if (this->strcompare(user_Password.c_str()) == 0)
                {
                    printf("Congratulations you are very good 1337 haxxor\n");
                }
                else
                {
                    printf("Noob try again\n");
                }

            default:
                break;
            }

            ctx->RIP++;
        }
    }

    /**
     * @brief Destructor.
     *
     * Releases the execution context and resets pointers.
     */
    ~ExecutionFlow()
    {
        if (ctx)
        {
            if (ctx->RIP)
            {
                ctx->RIP = 0;
            }

            delete ctx;
        }

        this->stack = 0;
    }

private:

    /**
     * @brief Pointer to the execution context.
     */
    Context* ctx;

    /**
     * @brief User-provided password used during comparison.
     */
    std::string user_Password;
};