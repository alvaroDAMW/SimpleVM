# VM-Based CTF Challenge

## Overview

This repository contains a **Capture The Flag (CTF) challenge based on a custom virtual machine (VM)** implemented in C++.

Instead of performing password validation directly in native code, the logic is executed through a **custom bytecode interpreter**. The VM processes user input through a series of stack-based operations, transformations, and obfuscation steps before validating the final result.

This design intentionally increases the **difficulty of reverse engineering**, forcing the solver to understand the behavior of the virtual machine before being able to recover the correct password.

---

# Why a Virtual Machine?

Virtual machines are commonly used in:

- **software protection**
- **malware obfuscation**
- **packers**
- **reverse engineering challenges**
- **CTF crackmes**

By moving program logic into **custom bytecode**, the original algorithm becomes harder to analyze.

Instead of reversing straightforward compiled code, an attacker must:

1. Understand the **VM architecture**
2. Reconstruct the **instruction set**
3. Analyze the **bytecode program**
4. Emulate or reverse the algorithm

This significantly increases the **complexity of the reversing process**.

---

# VM Architecture

The project implements a **simple stack-based virtual machine**.

Execution model:

User Input

Bytecode Argument Injection 

Virtual Machine Execution

Stack Operations

Result String Generation

Password Comparison


The VM interprets a sequence of **custom opcodes** stored in a bytecode program.

---

# Components

## Stack

The `Stack` class provides a **byte-based stack implementation** used by the VM.

Responsibilities:

- Store raw byte values
- Push values onto the stack
- Remove values
- Push strings
- Clear stack memory

Maximum capacity: **256 bytes**

---

## Handler

`Handler` implements the **operations executed by the VM**.

These operations manipulate the stack and perform transformations on its contents.

### Supported operations

| Function | Description |
|--------|--------|
| `sum()` | Adds values and maps result to Base62 |
| `mul()` | Multiplies values |
| `div()` | Divides values |
| `obfuscate()` | XOR-based transformation |
| `getFinalString()` | Obfuscates entire stack |
| `strcompare()` | Compares stack with password |

Arithmetic results are mapped to **Base62 characters**:


0-9
A-Z
a-z


---

## ExecutionFlow (VM Interpreter)

`ExecutionFlow` is the **core of the virtual machine**.

Responsibilities:

- Load the bytecode program
- Maintain execution state
- Interpret opcodes
- Execute stack operations
- Produce a result string
- Validate the password

The interpreter walks through the bytecode using an **instruction pointer (RIP)**.

---

## Context

`Context` stores the execution state:

- instruction pointer
- bytecode size

This allows the VM to track the current instruction during execution.

---

# Instruction Set

The VM uses a small custom **opcode set**.

| Opcode | Instruction | Description |
|------|------|------|
| `0x01` | PUSH | Push next byte to stack |
| `0xC3` | SUM | Add values |
| `0x99` | MUL | Multiply values |
| `0x62` | DIV | Divide values |
| `0x98` | XOR | Apply obfuscation |
| `0x00` | ARG | Placeholder argument |
| `0xFF` | END | Final transformation stage |
| `0x76` | CMPSTR | Compare with password |

---

# Bytecode Program

The bytecode program defines the algorithm executed by the VM.

Example snippet:


PUSH ARG
PUSH KEY
SUM

PUSH ARG
PUSH KEY
MUL


The operations combine:

- arithmetic transformations
- XOR obfuscation
- stack-based manipulation

The resulting characters are appended into a **result string**.

---

# Argument Injection

The bytecode contains placeholder values (`ARG`) which are replaced at runtime.

Before execution:


fix_arguments(username)


injects characters from the user-provided username into the bytecode.

This allows the VM program to process dynamic input.

---

# Challenge Flow

1. User enters a **username (10 characters)**.
2. Username characters replace `ARG` placeholders inside the bytecode.
3. User enters a **password**.
4. The VM executes the bytecode program.
5. The result string is generated.
6. The result is compared with the password.

If the password matches the computed result:


Congratulations you are very good 1337 haxxor


Otherwise:


Noob try again


---

# Why This Makes Reversing Harder

Without the VM:


native code → algorithm → password


With the VM:


native code
↓
virtual machine
↓
custom instruction set
↓
bytecode program
↓
algorithm
↓
password


The solver must reverse **multiple abstraction layers**.

Typical reversing steps:

1. Identify the VM interpreter
2. Recover the instruction set
3. Analyze bytecode
4. Reconstruct the algorithm
5. Generate valid input

---

# Performance Cost of VM-Based Protection

While virtual machines increase **reverse engineering difficulty**, they introduce **performance overhead**.

### Reasons

1. **Instruction interpretation**
   - Each VM instruction requires multiple native instructions.

2. **Indirect control flow**
   - Switch-based dispatch slows execution.

3. **Memory indirection**
   - Stack operations require additional memory access.

4. **Reduced compiler optimizations**
   - The algorithm is no longer visible to the compiler.

### Tradeoff

| Advantage | Disadvantage |
|--------|--------|
| Harder to reverse | Slower execution |
| Custom instruction set | Increased complexity |
| Obfuscated logic | Harder debugging |

In security-sensitive applications (protectors, DRM, malware, CTF challenges), this tradeoff is often acceptable.

---

# Purpose of the Challenge

This project is designed for:

- **reverse engineering practice**
- **CTF challenges**
- **learning VM-based obfuscation**
- **understanding interpreter design**

Participants are expected to analyze the virtual machine and recover the correct password.

---

# Educational Disclaimer

This project is intended for **educational purposes**, including:

- reverse engineering training
- CTF practice
- VM design experimentation
