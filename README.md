### Custom Linux ls Command Implementation

A lightweight, high-performance custom implementation of the standard Linux command-line utility (ls) written from scratch in C. This project demonstrates low-level **Linux System Programming**, direct file system API integration, and manual system data extraction using POSIX standards. 

### 🚀 Features

* **Directory & File Processing**: Automatically detects whether the input target is a standard file or a directory structure using macro evaluation.
* **Dynamic Flag Parsing**: Supports multiple option parameters passed directly through standard terminal arguments.
* **File Meta Extraction**: Communicates with the OS kernel layer to extract active hardware properties and structure data.
* **Manual Permission Masking**: Extracts exact read, write, and execute permissions natively using precise bitwise operation loops.
* **Color-Coded Terminal Output**: Integrates custom ANSI escape formatting controls to easily differentiate active directories from regular system files.

### 🛠️ Supported Options

You can combine flags just like the native command-line program: 

* -l : Displays extended file metadata including permissions, hard link counts, Owner UID, Group GID, file size in bytes, and modification timestamps.
* -i : Prints the specific system **Inode index tracking number** for the target.
* -s : Displays total file layout tracking allocation sizes scaled into individual memory blocks.

### ⚙️ How it Works under the Hood

1. **Argument Parsing**: Iterates through terminal parameters to separate input command control flags from absolute or relative target directory strings.
2. **Directory Streaming**: Opens and scans structural boundaries using low-level POSIX functions (opendir, readdir).
3. **Kernel Data Extraction**: Leverages the system's stat system call structure to pull underlying storage records directly from the operating system.
4. **Bit-Shift Processing**: Decodes system permission flags using a bit-mask shift loop: 

c

for(int i = 8; i >= 0; i--) {
    if((m >> i) & 1) { /* Extract r, w, x permissions */ }
}

Use code with caution.

### 🛠️ Compilation & Execution

Compile the source engine using any standard C compiler (like gcc): 

bash

# Compilation
gcc ls.c -o my_ls

# Check the contents of the current directory
./my_ls .

# Check file parameters with detailed metadata, blocks, and inode options
./my_ls -lis /usr/bin

Use code with caution.

### 🧰 Tech Stack & Core APIs Used

* **Language**: Pure C
* **System APIs**: sys/stat.h, sys/types.h, dirent.h, unistd.h
* **Concepts**: Bitwise Operations, File System Infrastructure, System Call Processing, Terminal Escape Controls
