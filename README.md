
🐚 Minishell

Minishell is a small UNIX shell written in C, developed as part of the 42 school curriculum.
It aims to reproduce the behavior of bash for fundamental shell features, while exploring process management, I/O redirections, and signal handling in a UNIX environment.

https://github.com/user-attachments/assets/2405426b-bebb-44b6-8c89-79e7ff6d0ae4

Global Architecture :

<img width="800" height="400" alt="Screenshot from 2026-05-20 12-25-32" src="https://github.com/user-attachments/assets/137a3ee0-c0ae-4bc6-9429-933c4a9fd3af" />



Parsing example :

<img width="500" height="450" alt="Screenshot from 2026-05-20 12-36-05" src="https://github.com/user-attachments/assets/1460043a-1cd5-46c3-b3b2-4cfc3c986787" />

Execution example

<img width="800" height="500" alt="exec" src="https://github.com/user-attachments/assets/03dbd30e-1751-435c-9598-0f8bf9462c75" />

🚀 Features

Command parsing and execution

Built-in commands: echo, cd, pwd, export, unset, env, exit

Pipes (|) and redirections (>, >>, <, <<)

Environment variable expansion ($VAR)

Proper quote and backslash handling, following Bash rules

Signal handling (Ctrl+C, Ctrl+D, Ctrl+\)

Error handling and exit status management

🧰 Requirements

GCC or Clang

Make

Linux or macOS

⚙️ Build & Run
make
./minishell

👥 Authors

- docteurbadluck

- jholterh
