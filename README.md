# 🐚 Minishell

Minishell is a small UNIX shell written in C, developed as part of the 42 school curriculum. It reproduces the core behavior of bash, exploring process management, I/O redirections, and signal handling in a UNIX environment.

https://github.com/user-attachments/assets/2405426b-bebb-44b6-8c89-79e7ff6d0ae4

---

## 🏗️ Architecture

### Overview

<img width="800" height="400" alt="Global Architecture" src="https://github.com/user-attachments/assets/137a3ee0-c0ae-4bc6-9429-933c4a9fd3af" />

The shell is organized around three components:

- **Orchestrator** — drives the main loop, manages shell state (menu, heredoc, executing) and centralizes signal transitions
- **Parsing** — tokenizes input, groups commands, builds an AST using the shunting-yard algorithm
- **Execution** — traverses the AST, forks processes, wires pipes, handles redirections and builtins

### Parsing example

<img width="500" height="450" alt="Parsing example" src="https://github.com/user-attachments/assets/1460043a-1cd5-46c3-b3b2-4cfc3c986787" />

### Execution example

<img width="800" height="500" alt="Execution example" src="https://github.com/user-attachments/assets/03dbd30e-1751-435c-9598-0f8bf9462c75" />

---

## 🚀 Features

- Command parsing and execution
- Built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- Pipes (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- Environment variable expansion (`$VAR`, `$?`)
- Quote handling following bash rules (`'`, `"`)
- Wildcard expansion (`*`)
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)
- Error handling and exit status propagation

---

## 🧰 Requirements

- GCC or Clang
- Make
- libreadline (`sudo apt-get install libreadline-dev`) (automatic)
- expect tmux for test (automatic with make test)
- Linux or macOS

---

## ⚙️ Build & Run

```bash
make
./minishell
```

---

## 🧪 Tests

```bash
make signals   # signal & heredoc tests
make tester    # functional test suite
```

---

## 👥 Authors

- [docteurbadluck](https://github.com/docteurbadluck)
- [jholterh](https://github.com/jholterh)
