# Hitman Blood Money Trainer
### Timeline
- Project started:      08/29/2021
- Project completed:    09/01/2021
- Project revisited:    12/29/2021
  
## Overview:
This is a repository for a Hitman Blood Money Trainer that I built with C++.

The main purpose of this project was to get familiar with programming internal GUIs from scratch and  
familiarize myself with process hooking techniques.

[Demonstration](https://www.youtube.com/watch?v=0btTuzX9aQU)
of God Mode and Teleport hacks.  

## Table of Contents
- [What I Learned](#what-i-learned)
- [How it Works](#how-it-works)
- [Build Instructions](#build-instructions)
- [Known Issues](#known-issues)
- [Goals](#Goals)
  
### What I Learned
[ What the fuck did I actually learn ]

### How it works
The DLL must be injected WHILE the game is running in the foreground.  
It is very finicky and will crash/hang otherwise.

The hacks written are:
- Press <code>END</code> to eject.
- Press <code>TAB</code> to toggle God mode.
- Press <code>[</code> previous entity.
- Press <code>]</code> next entity.
- Press <code>T</code> to teleport to current entity.
- Press <code>Shift + T</code> to teleport to current camera coordinates.

### Known issues
One shot kill currently prevents "Accidental deaths" from counting as killed targets.  
The player has to manually kill them in order for their death to register. This may be  
solvable by changing the one shot op code from <code>mov</code> to <code>xor</code>

There are currently game states that may trigger a crash if cheats are enabled.

These game states include:
- Restarting a mission with cheats enabled (sometimes)

### Build Instructions
- WSL (Preferred)
	1. install Visual Studio with CMake support
	2. cd into project root
    ```
    $ make
    ```
- Windows
	1. install Visual Studio with CMake support
    - Visual Studio 2019
        1. open the project folder in Visual Studio 2019
        2. ctrl + shift + b
    - Powershell
        1. open Powershell in project directory
        ```
        $ cmake -G "Visual Studio 2019" -A Win32 -B "build"
        $ cmake --build "build" --config "Release"
        ```

### Goals
 - [x] Find reliable weapon pointer.
 - [x] Find reliable entity_list pointer.
 - [x] Find reliable player_health pointer.
 - [x] Find a way to prevent teleports from crashing the game.
 - [x] Find reliable 'in game' boolean (or other explicit distinction).
 - [ ] Include entity type in GUI main window, just below the entity number.