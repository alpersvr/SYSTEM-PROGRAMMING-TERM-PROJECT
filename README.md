# Terminal-Based File Manager

This project is a terminal-based file manager written in C. It provides basic file and directory management operations using Linux/Unix system calls. The application includes a command-line interface for user-friendly interaction and logs all operations performed.

## Features

1. **File Operations**:
   - Create a file (`screatefile <file_path>`)
   - Delete a file (`sremove <file_path>`)
   - Copy a file (`scopy <source_path> <destination_path>`)
   - Move a file (`smove <source_path> <destination_path>`)
   - Display a file's content (`sdisplay <file_path>`)

2. **Directory Operations**:
   - Create a directory (`screatedir <directory_path>`)
   - Delete a directory (`srmdir <directory_path>`)
   - List directory contents (`slist <directory_path>`)
   - Search for a file in a directory (`ssearch <directory_path> <filename>`)
   - Copy a directory (`scopy <source_path> <destination_path>`)
   - Move a directory (`smove <source_path> <destination_path>`)

3. **Permission Management**:
   - Change file or directory permissions (`schmod <file_path> <mode>`)

4. **Logging**:
   - All operations are logged in a `operations.log` file stored in the `log/` directory.

## Makefile to build the project

### Installation and Usage

### Prerequisites

- GCC Compiler
- Linux/Unix operating system

### Build the Project

1. **Clone the repository**:
    ```bash
    git clone https://github.com/alpersvr/SYSTEM-PROGRAMMING-TERM-PROJECT.git
    cd SYSTEM-PROGRAMMING-TERM-PROJECT
2. **Build the project using make**:
    ```bash
    make
3. **The executable will be created in the bin/ directory as program.exe.**
### Run the Program
  ```bash
 ./bin/program.exe
 


