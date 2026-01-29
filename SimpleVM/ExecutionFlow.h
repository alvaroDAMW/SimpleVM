#pragma once
#include <Windows.h>
#include <memory>
#include "Stack.h"
#include "Handler.h"
#include "CustomOpcodes.h"

struct Context
{
	uint8_t* RIP;
	std::size_t size_of_bytecode;
	~Context()
	{

		RIP = 0;
	}
};

class ExecutionFlow : Handler {
public:
	ExecutionFlow(std::vector<UINT8> byte_code, const char* userPassword) : Handler{ new Stack() } {

		ctx = new Context{ NULL,byte_code.size() };
		ctx->RIP = (std::uint8_t*)(malloc(byte_code.size()));
		memcpy(ctx->RIP, byte_code.data(), byte_code.size());
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
				result += char(this->obfuscate( 0XF2));
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
				ctx->RIP = 0;
			}
			delete ctx;
		}
		
		this->stack = 0;
	}
private:
	Context* ctx;
	std::string user_Password;
};