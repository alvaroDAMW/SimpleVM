// calling_convertions.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include "ExecutionFlow.h"
#include <memory>

/**
 * @brief Entry point of the virtual machine application.
 *
 * This function initializes the program, collects user input, injects the
 * provided username into the bytecode program, and executes the virtual
 * machine responsible for validating the password.
 *
 * Program flow:
 *
 * 1. Display a welcome message and request a username from the user.
 * 2. Validate that the username has exactly 10 characters.
 * 3. Inject the username characters into the bytecode using fix_arguments().
 * 4. Request a password from the user.
 * 5. Initialize the ExecutionFlow virtual machine with the prepared bytecode.
 * 6. Execute the bytecode program.
 *
 * The virtual machine will process the username through a series of
 * stack-based operations and transformations. The resulting value will
 * be compared against the user-provided password to determine whether
 * the validation succeeds.
 *
 * @return 0 when the program finishes execution.
 */
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

    /* Inject username characters into the bytecode arguments */
    fix_arguments(username);

    printf("Password: ");

    std::string password;
    std::cin >> password;

    /* Initialize and execute the virtual machine */
    ExecutionFlow execution_flow = ExecutionFlow(bytecode, password.c_str());
    execution_flow.run();

    getchar();
}