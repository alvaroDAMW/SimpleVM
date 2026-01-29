// calling_convertions.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "ExecutionFlow.h"
#include <memory>



int main()
{

	printf("Welcome to a VM\nEnter a username with length of 10 characters\n");
	std::string username;
	std::cin >> username;
	if (username.length() != 10) {
		printf("Not enought length\n");
		getchar();
		return 0;
	}
	fix_arguments(username);
	printf("Password: ");
	std::string password;
	std::cin >> password;
	ExecutionFlow execution_flow = ExecutionFlow(bytecode, password.c_str());
	execution_flow.run();
	getchar();

}
