#pragma once
#include <Windows.h>
#include <memory>
#include "Stack.h"
#include "Handler.h"
#include "CustomOpcodes.h"

struct Context
{
	Stack* stack;
	uint8_t* RIP;
	std::size_t size_of_bytecode;
	~Context()
	{
		if (stack)
		{
			delete stack;
		}
		RIP = 0;
	}
};

class ExecutionFlow : Handler {
public:
	ExecutionFlow(std::vector<UINT8> byte_code, const char* userPassword) : Handler{ new Stack() } {

		ctx = new Context{ this->stack, NULL,byte_code.size() };
		ctx->RIP = (std::uint8_t*)(malloc(byte_code.size()));
		memcpy(ctx->RIP, byte_code.data(), byte_code.size());
		Handler{ ctx->stack };
		user_Password = userPassword;
	};
	ExecutionFlow() = default;
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
				ctx->stack->push(*++ctx->RIP);
				break;
			case SUM:
				result += (char)this->sum();
				ctx->stack->clearStack();
				break;
			case MUL:
				result += (char)this->mul();
				ctx->stack->clearStack();
				break;
			case DIV:
				result += (char)this->div();
				ctx->stack->clearStack();
				break;
			case XOR:
				result += char(this->obfuscate( 0XF2));
				ctx->stack->clearStack();
				break;
			case END:
				ctx->stack->clearStack();
				ctx->stack->push_string(result.c_str());
				this->getFinalString();
				break;
			case CMPSTR:
				if (this->strcompare(user_Password.c_str()) == 0)
				{
					printf("Congratulations you are very good 1337 haxxor\n");
				}
				else {
					printf("Noob try again\n");
				}

			default:
				break;
			}

			ctx->RIP++;
		}

	}

	~ExecutionFlow()
	{
		if(ctx)
		{
			if (ctx->RIP)
			{
				free(ctx->RIP);
			}
			delete ctx;
		}
		
		this->stack = 0;
	}
private:
	Context* ctx;
	std::string user_Password;
};