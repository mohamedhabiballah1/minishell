# Minishell 42 Project

![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)

## Overview

Minishell is a simplified shell implementation as part of the 42 school curriculum. This project aims to replicate basic shell functionality, allowing users to execute commands, navigate directories, and manage processes. It serves as an introduction to system calls, process management, and parsing in the Unix environment.

## Features

- **Command Execution:** Execute shell commands and external programs.
- **Built-in Commands:** Supports essential built-in commands like `echo`, `cd`, `pwd`, and `env`.
- **Piping and Redirection:** Allows piping and redirection of input/output.
- **Signal Handling:** Handles signals such as Ctrl+C (SIGINT) and Ctrl+\ (SIGQUIT).
- **Command Line Editing:** Provides line editing capabilities using the GNU Readline library.
- **Error Handling:** Gracefully handles errors and provides informative error messages.

## Getting Started

Follow these instructions to get a copy of the Minishell project up and running on your local machine.

### Prerequisites

- C compiler (e.g., GCC)
- GNU Make
- Readline library (for command line editing)

### Building

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/minishell.git
   cd minishell
