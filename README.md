# Blackjack Simulator
![License](https://img.shields.io/badge/license-MIT-green.svg)
![Language](https://img.shields.io/badge/language-C++17-blue.svg)
![Status](https://img.shields.io/badge/status-Completed-brightgreen.svg)
![Platform](https://img.shields.io/badge/platform-Terminal-lightgrey.svg)
![Build](https://img.shields.io/badge/build-passing-brightgreen)

A terminal-based Blackjack game built in modern C++, with a clean, modular design, random number generation, function overloading, and game logic implementation.

## Features
- Standard Blackjack rules: Hit, Stand, Double Down, Blackjack detection
- Dynamic starting balance: Randomized between `$10.10` and `$1000.10`
- Wildcard mechanics: Affect gameplay based on suit (Hearts, Diamonds, Clubs, Spades)
- Dealer logic: Hits ≤ 16, stands on 17+
- Round-by-round gameplay with balance tracking and smart prompts
- Game session summary with win/loss/tie stats and net gain/loss
- Robust input validation and real-time player feedback

## Demo
> Below is a walkthrough video showing gameplay: including betting, card drawing, wildcards, and win/loss evaluation.

[Click to watch video](https://github.com/user-attachments/assets/29269b00-75e5-4d24-8afd-644d6e0e6b8d)

## Tech Stack
| Tool | Badge |
|------|-------|
| Language | ![C++](https://img.shields.io/badge/C++-17-blue.svg) |
| Compiler | ![g++](https://img.shields.io/badge/g++-MinGW--w64-red) |
| Editor | ![VS Code](https://img.shields.io/badge/Editor-VS%20Code-blue?logo=visualstudiocode) |
| Platform | ![Windows Terminal](https://img.shields.io/badge/Platform-Windows%20Terminal-lightgrey?logo=windows) |

## Getting Started
To build and run the project locally:

```bash
g++ main.cpp blackjack.cpp -o blackjack
./blackjack
```
*Requires a C++17-compliant compiler (e.g., g++ via MinGW or WSL)*

## License

This project is licensed under the [MIT License](LICENSE).
