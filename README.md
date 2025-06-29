# MBA-generator
Mixed Boolean Arithmetic Obfuscation module that can be added to binary obfuscation toolsets.
# MBA Generator

Program protection is a double-edged sword: while it strengthens the security of legitimate software, it also provides malware authors with techniques to create more resilient and harder-to-analyze code. This project explores **Program Obfuscation Methods** that make the program analysis process more demanding for reverse engineers and analysis tools.

## Overview

This project focuses on implementing binary code obfuscation techniques to increase the complexity of binaries and hinder static analysis tools like **IDA Pro** and **Ghidra**.

Implemented methods include:

- **MBA (Mixed Boolean-Arithmetic)**  
  Generates *alive* code to increase binary complexity, making reverse engineering more challenging. The design of this method is inspired by the approach in [12].
  
- **CFF (Control-Flow Flattening)**  NOT INCLUDED

  Breaks down large code blocks and rearranges them into smaller, less obvious pieces. This disrupts the ability of static analysis tools to generate accurate control flow or call graphs.
  
- **CI (Code Insertion)**  NOT INCLUDED

  Inserts *dead* or *alive* binary code at strategic locations to further confuse disassemblers and analyzers.

## Features

- ✅ Generates complex, obfuscated binary code  
- ✅ Applies mixed boolean-arithmetic transformations

## Why This Project?

This work builds upon my experience with program analysis and aims to provide hands-on tools for:

- Studying the effectiveness of obfuscation against static analysis
- Demonstrating how common obfuscation techniques impact reverse engineering

## Getting Started

### Prerequisites

- A C/C++ compiler (e.g., `gcc`, `clang`)
- (Optional) IDA Pro, Ghidra, or other disassembler tools to observe the obfuscation effects

### Build & Run

```bash
git clone https://github.com/visionius/MBA-generator.git
cd MBA-generator
# Build instructions here (e.g., make, cmake, etc.)
```
Screenshots of Obfuscating Notepad launcher shellcode (Dissassembled by Cutter):
![fcn_00000001](https://github.com/user-attachments/assets/c594e251-4ec9-4107-943b-f0458caecdc9)
![fcn_00000002](https://github.com/user-attachments/assets/fdc1e528-9c3f-4d99-8f89-5794c5423b90)
![fcn_00000000_40](https://github.com/user-attachments/assets/b4130c97-5918-4fed-9315-43c7ce4d2b3c)
