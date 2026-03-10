<div align="center">

# 🐚 Minishell

### _As beautiful as a shell_

<img src="https://img.shields.io/badge/Shell-Bash-4EAA25?style=for-the-badge&logo=gnu-bash&logoColor=white" alt="Bash">
<img src="https://img.shields.io/badge/Language-C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="C">
<img src="https://img.shields.io/badge/Grade-100%2F100-success?style=for-the-badge" alt="Grade">
<img src="https://img.shields.io/badge/School-42-000000?style=for-the-badge" alt="42">

**A minimal yet powerful shell implementation in C**

[Features](#-features) • [Installation](#-installation) • [Usage](#-usage) • [Architecture](#-architecture) • [Built-ins](#%EF%B8%8F-built-in-commands)

---

</div>

## 📖 About

**Minishell** is a lightweight Unix shell implementation that recreates the behavior of bash. This project explores the fundamentals of process management, file descriptors, signal handling, and parsing in C. Built as part of the 42 curriculum, it demonstrates low-level systems programming and attention to detail.

> _"The shell is the command interpreter. It is the program that interacts with the user and runs commands."_

<br>

## ✨ Features

<table>
<tr>
<td width="50%">

### 🎯 Core Functionality
- **Command Execution** with absolute/relative paths and PATH resolution
- **Signal Handling** (Ctrl-C, Ctrl-D, Ctrl-\\)
- **Environment Variables** management
- **Exit Status** tracking (`$?`)
- **Pipe Support** (`|`) for command chaining
- **Quote Handling** (single `'` and double `"`)

</td>
<td width="50%">

### 🔧 Advanced Features
- **Redirections**:
  - Input: `<`
  - Output: `>`
  - Append: `>>`
  - Here-doc: `<<`
- **Variable Expansion** (`$VAR`)

</td>
</tr>
</table>

<br>

## 🛠️ Built-in Commands

Minishell implements the following built-in commands:

| Command | Description |
|---------|-------------|
| `echo` | Display a line of text (with `-n` option) |
| `cd` | Change the current directory |
| `pwd` | Print the current working directory |
| `export` | Set environment variables |
| `unset` | Unset environment variables |
| `env` | Display environment variables |
| `exit` | Exit the shell |

<br>

## 🚀 Installation

### Prerequisites

```bash
# Required libraries
- gcc or clang compiler
- GNU readline library
- make
```

### Build

```bash
# Clone the repository
git clone https://github.com/Kaiolinoan/Minishell.git
cd Minishell

# Compile the project
make

# Run minishell
./minishell
```

### Additional Commands

```bash
make clean      # Remove object files
make fclean     # Remove object files and executable
make re         # Recompile everything
make reclear	# make re + clear
make r			# reclear + ./minishell
make v			# make reclear + valgrind --leak-check=full  --track-origins=yes --show-leak-kinds=all --track-fds=yes --suppressions=readline.supp ./minishell
```

<br>

## 💻 Usage

### Basic Commands

```bash
minishell> echo "Hello, World!"
Hello, World!

minishell> pwd
/home/user/Minishell

minishell> export MY_VAR="42"
minishell> echo $MY_VAR
42
```

### Pipes and Redirections

```bash
# Piping commands
minishell> ls -la | grep minishell | wc -l

# Output redirection
minishell> echo "Save this" > output.txt

# Input redirection
minishell> cat < input.txt

# Here-doc
minishell> cat << EOF
> Line 1
> Line 2
> EOF
```

### Advanced Usage

```bash
# Multiple pipes
minishell> cat file.txt | grep "pattern" | sort | uniq

# Combining redirections
minishell> < input.txt grep "search" > output.txt

# Exit status
minishell> ls /nonexistent
minishell> echo $?
2
```

<br>

## 🏗️ Architecture

```
minishell/
│
├── includes/
│   └── minishell.h           # Main header file
│
├── srcs/
│   ├── main.c                # Entry point
│   │
│   ├── parsing/              # Input parsing & tokenization
│   │   ├── parse_main.c      # Main parsing logic
│   │   ├── parse_input.c     # Input validation
│   │   ├── parse_expansion.c # Variable expansion
│   │   └── ...
│   │
│   ├── execution/            # Command execution
│   │   ├── exc_start.c       # Execution initialization
│   │   ├── exc_command.c     # Command runner
│   │   ├── exc_heredoc.c     # Here-doc handling
│   │   ├── exc_redir.c       # Redirection handling
│   │   └── exc_signals.c     # Signal management
│   │
│   ├── built-in/             # Built-in commands
│   │   ├── exc_ft_echo.c
│   │   ├── exc_ft_cd.c
│   │   ├── exc_ft_pwd.c
│   │   ├── exc_ft_export.c
│   │   └── ...
│   │
│   ├── env/                  # Environment management
│   │   ├── exc_env_create.c
│   │   ├── exc_env_functions.c
│   │   └── exc_env_path.c
│   │
│   └── utils/                # Utility functions
│       └── ...
│
└── Libft/                    # Custom C library
    ├── Libfunctions/         # Standard library reimplementations
    ├── GNL/                  # Get Next Line
    └── Ft_printf/            # Printf implementation
```

<br>

## 🧠 How It Works

### 1. **Lexical Analysis & Parsing**
The input string is tokenized and parsed into a command structure, handling quotes, operators, and special characters.

### 2. **Expansion**
Environment variables (`$VAR`) and special parameters (`$?`) are expanded before execution.

### 3. **Command Resolution**
Commands are resolved by checking:
- Built-in commands first
- Absolute/relative paths
- PATH environment variable

### 4. **Execution**
Commands are executed with proper:
- Process forking and waiting
- File descriptor management
- Pipe creation and linking
- Redirection handling

### 5. **Signal Handling**
Appropriate signals are caught and handled:
- `Ctrl-C` (SIGINT): Interrupt current command
- `Ctrl-D` (EOF): Exit shell
- `Ctrl-\` (SIGQUIT): Ignored in interactive mode

<br>

## 🎓 Technical Highlights

### Memory Management
- **Zero memory leaks** verified with Valgrind
- Custom allocators for efficient node management
- Proper cleanup on exit and error conditions

### Error Handling
- Comprehensive error messages matching bash behavior
- Proper exit status codes
- Syntax error detection

### Signal Safety
- Non-blocking signal handling
- Global signal variable for asynchronous events
- Proper signal restoration after command execution

<br>

## 🧪 Testing

```bash
# Test with simple commands
minishell> ls
minishell> pwd
minishell> echo test

# Test pipes
minishell> ls | grep .c | wc -l

# Test redirections
minishell> echo "test" > file.txt
minishell> cat < file.txt

# Test environment variables
minishell> export TEST="value"
minishell> echo $TEST

# Test edge cases
minishell> echo "$USER is in $PWD"
minishell> cat << EOF | grep pattern
```

<br>

## 🤝 Contributing

This is an educational project from 42 School. While pull requests are welcome for bug fixes and improvements, please note that the core functionality is designed to meet specific project requirements.

<br>

## 👥 Authors

- **[@Kaiolinoan](https://github.com/Kaiolinoan)** - *Development & Implementation*
- **[@ArTY](https://github.com/ArTYYwasTaken)** - *Development & Implementation*

<br>

## 📄 License

This project is part of the 42 School curriculum. Feel free to use it for educational purposes.

<br>

<div align="center">

### ⭐ If you found this project helpful, consider giving it a star!

---

**Made with ❤️ at [42 School](https://www.42.fr/)**

</div>
