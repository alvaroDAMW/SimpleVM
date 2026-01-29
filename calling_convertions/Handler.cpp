#include "Handler.h"
#include <random>

int Handler::sum()
{
    if (stack->getUsedBytes() < 2)
    {
        return 0;
    }
    int result = 0;
    auto first_argument = stack->getBuffer()[stack->getStackPointer() - stack->getUsedBytes()];
    auto last_argument = stack->getBuffer()[stack->getStackPointer() - sizeof(std::uint8_t)];
    result = first_argument + last_argument;
    uint8_t mapped = result % 62;

    if (mapped < 10)
        result = '0' + mapped;
    else if (mapped < 36)
        result = 'A' + (mapped - 10);
    else
        result = 'a' + (mapped - 36);
    return result;
}

int Handler::mul()
{
    if (stack->getUsedBytes() < 2)
    {
        return 0;
    }
    int result = 0;
    auto first_argument = stack->getBuffer()[stack->getStackPointer() - stack->getUsedBytes()];
    auto last_argument = stack->getBuffer()[stack->getStackPointer() - sizeof(std::uint8_t)];
    result = first_argument * last_argument;
    uint8_t mapped = result % 62;

    if (mapped < 10)
        result = '0' + mapped;
    else if (mapped < 36)
        result = 'A' + (mapped - 10);
    else
        result = 'a' + (mapped - 36);
    return result;
}

int Handler::div()
{
    if (stack->getUsedBytes() < 2)
    {
        return 0;
    }
    int result = 0;
    auto first_argument = stack->getBuffer()[stack->getStackPointer() - stack->getUsedBytes()];
    auto last_argument = stack->getBuffer()[stack->getStackPointer() - sizeof(std::uint8_t)];
    if (last_argument == 0 || first_argument == 0)
    {
        uint8_t a = (first_argument ^ 0xA5) + 17;
        uint8_t b = (last_argument | 1);
        result = a / b;
    }
     result = first_argument / last_argument;
     uint8_t mapped = result % 62;

     if (mapped < 10)
         result = '0' + mapped;
     else if (mapped < 36)
         result = 'A' + (mapped - 10);
     else
         result = 'a' + (mapped - 36);
    

    return result;
}

uint8_t Handler::obfuscate(uint8_t key)
{
    if (stack->getUsedBytes() < 1)
        return 0;

    uint8_t result = stack->getBuffer()[stack->getStackPointer() - 1];
    result ^= key;
    result = (result + 7) * 3;
    result &= 0xFF;
    uint8_t mapped = result % 62;

    if (mapped < 10)
        result = '0' + mapped;
    else if (mapped < 36)
        result = 'A' + (mapped - 10);
    else
        result = 'a' + (mapped - 36);

    stack->getBuffer()[stack->getStackPointer() - 1] = result;
    return result;
}

void Handler::getFinalString()
{
    std::string result;
    for (int i = stack->getUsedBytes() -1 ; i >= 0; i--)
    {
        stack->getBuffer()[i] = (char)obfuscate(0x54);
    }
}

int Handler::strcompare(const char* user_string)
{
    for (int i = stack->getUsedBytes() - 1; i >= 0; i--)
    {
        char current_string = stack->getBuffer()[i];
        if (current_string != user_string[i])
        {
            return 1;
        }


    }
    return 0;
}
