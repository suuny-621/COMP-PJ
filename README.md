# DUNGEON QUEST
Yang Sijun 3036669424 

A terminal-based dungeon crawler RPG written in C++.

(1) How to Build

```bash
make
```

(2) How to Play

```bash
./dungeon_quest
```

(3) Features

- 3 difficulty modes: Easy / Normal / Hard
- Turn-based combat system with critical hits
- Random events: monsters, traps, treasure, merchant shop
- Gold system — earn gold from kills, spend at the shop to upgrade stats
- Save / load system
- Floor progression with scaling enemy difficulty

(4) Game Controls

All input is number-based. Follow the on-screen prompts.

| Main Menu | 1: New Game, 2: Load Game, 3: Exit |
| In-Game | 1: Move Forward, 2: Check Status, 3: Save & Quit |
| Battle | 1: Attack, 2: Run (not available in Hard mode) |

(5) Difficulty

| Mode.  |  HP  |  ATK  |  DEF  |
|--------|------|-------|-------|
| Easy   |  130 |   18  |   4   |
| Normal | 100  |   15  |   3   |
| Hard   |  75  |   13  |   1   |

Hard mode: cannot run from battles.

(5) File Structure

```
main.cpp      — entry point, main menu
player.cpp/h  — player struct and initialization
game.cpp/h    — combat, events, game loop
file.cpp/h    — save and load system
Makefile      — build config
```

Requirements

- g++ with C++11 support
- Make