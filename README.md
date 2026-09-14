# Modular Text Adventure Game Engine in C++

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-00599C?logo=c%2B%2B&logoColor=white)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Architecture](https://img.shields.io/badge/Architecture-Object--Oriented-blue.svg)](include/)
[![Build](https://img.shields.io/badge/Build-Makefile-orange.svg)](Makefile)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

A data-driven interactive fiction and text adventure engine written in modern C++17. Features decoupled world loading from configuration files, inventory management, NPC dialogue trees, triggered narrative events, and save/load serialization.

## Overview

Text adventure engines require extensible state management to handle player navigation, item interactions, and non-linear storylines without hardcoding game logic into the source code. This engine separates game data (`data/world.txt`, `data/dialogues/`) from core game loop systems, allowing developers to design complex narrative worlds through plain text configuration files.

## Architecture

```
Text Adventure (C++)/
├── data/
│   ├── world.txt           # Room definitions, connections, and initial item spawns
│   ├── save.txt            # Serialized player state and inventory records
│   └── dialogues/
│       ├── guard.txt       # Branching dialogue script for guard NPC
│       └── merchant.txt    # Branching dialogue script for merchant NPC
├── include/
│   ├── Command.h           # Command pattern dispatch interface
│   ├── Event.h             # Triggered environmental and narrative events
│   ├── Game.h              # Main game loop coordinator and state holder
│   ├── Item.h              # Item entity definition and properties
│   ├── NPC.h               # Non-player character state and dialogue hooks
│   ├── Parser.h            # Natural language command tokenizer
│   ├── Player.h            # Player stats, location pointer, and inventory
│   ├── Room.h              # Graph node representing locations and exits
│   ├── SaveSystem.h        # File persistence and deserialization
│   └── WorldLoader.h       # World graph parser reading from data files
├── src/                    # C++ source implementations for all headers
├── Makefile                # Build targets and compiler options
└── README.md               # Engine documentation
```

## Key Engine Features

* **Data-Driven World Graph**: World topology is parsed dynamically from `data/world.txt`. Rooms are connected as a directional graph supporting cardinal directions (`north`, `south`, `east`, `west`, `up`, `down`).
* **Command Interpreter**: Natural language tokenizer parses verb-noun patterns (`look`, `go <direction>`, `take <item>`, `drop <item>`, `inventory`, `talk <npc>`, `use <item>`).
* **NPC Dialogue Trees**: Scripted conversation trees with conditional responses and inventory trade mechanics.
* **Event Dispatch System**: Dispatches room entry and item usage triggers (unlocking gates, puzzle solutions, traps).
* **Save / Load Serialization**: Serializes player position, current room states, and backpack contents to `data/save.txt`.

## Requirements

* C++17 compliant compiler (GCC 9+, Clang 10+, Apple Clang)
* Make

## Compilation

Build the game binary:

```bash
make
```

To clean object files and executables:

```bash
make clean
```

## Usage

Start the game from the project root:

```bash
./textadventure
```

### Supported In-Game Commands

* `go <direction>`: Move between connected rooms (e.g. `go north`, `go east`).
* `look` / `examine <item>`: Inspect current room surroundings or items.
* `take <item>` / `drop <item>`: Pick up or discard inventory items.
* `inventory`: List all items currently carried.
* `talk <npc>`: Initiate interactive conversation with an NPC.
* `save`: Save current game progress to disk.
* `load`: Restore saved game state from `data/save.txt`.
* `quit`: Exit the game session.

## Project Status

Core engine architecture complete and functional with included demonstration campaign.

## Authors and Acknowledgment

Developed by Adam Anwar. Designed to demonstrate object-oriented software patterns, decoupled file parsing, and state machine design in modern C++.

## License

MIT License.


## Roadmap
* [x] Core architecture and baseline implementation.
* [x] Functional verification and test coverage.
* [ ] Add JSON-based room and quest script parser
* [ ] Support player save-state persistence


## Contributing
Contributions are welcome.
1. Fork the repository.
2. Create a feature branch: `git checkout -b feature/improvement`.
3. Commit your changes: `git commit -m "feat: enhance functionality"`.
4. Push to the branch: `git push origin feature/improvement`.
5. Open a Pull Request.
