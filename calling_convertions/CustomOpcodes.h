#pragma once
#include <iostream>
#include <vector>
#define DECRIPTKEY 0xEE

enum Opcodes
{
    PUSH = 0x01,
    SUM = 0xC3,
    MUL = 0x99,
    DIV = 0x62,
    XOR = 0x98,
    ARG = 0x0,
    END = 0xFF,
    CMPSTR = 0x76
};
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
    END,CMPSTR
};


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
