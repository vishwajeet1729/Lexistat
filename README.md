# 🧠 LexiStat: Lexical Analyzer and Symbol Table Generator

---

## 📌 Overview

**LexiStat** is a C++-based compiler front-end tool that performs **lexical analysis**, builds a **symbol table**, and detects **lexical errors**. It simulates part of the compiler's scanning and symbol handling phase by reading from a source file (`input.cpp`) and breaking it into meaningful tokens.

---

## 🎯 Features

| Feature              | Description                                                                 |
|----------------------|-----------------------------------------------------------------------------|
| Tokenization         | Extracts keywords, identifiers, constants, operators, and separators        |
| Symbol Table         | Captures identifier metadata: type, scope, declaration line, references     |
| Error Detection      | Logs lexical errors like invalid tokens and undeclared identifiers          |
| Scope Tracking       | Tracks nested `{}` to identify variable scoping                             |
| Comment Removal      | Handles both single-line `//` and multi-line `/* */` comment removal        |

---

## 🛠️ Tech Stack

- **C++** — Core language
- **STL** — `unordered_map`, `set`, `vector`, `regex` for parsing and tracking
- **File I/O** — To read source file and display output

---

## 📁 Project Structure

```bash
.
├── LexiStat.cpp       # Main source code
├── input.cpp          # Sample source code input
└── README.md          # Project documentation
