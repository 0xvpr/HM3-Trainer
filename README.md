# Hitman Blood Money Trainer
  
## Overview:
This is a repository for a Hitman Blood Money DLL that I built with C, C++, ImGui and Kiero.

The main purpose of this project was to get familiar with programming internal GUIs and  
familiarize myself with process hooking techniques.

## Table of Contents
  - [Demonstration](#demonstration)
  - [What I Learned](#what-i-learned)
  - [How it works](#how-it-works)
  - [Known issues](#known-issues)
  - [Goals](#Goals)
  
### Demonstration
embed YouTube or place gif.

### What I Learned
This project helped me understand the importance of code organization and structure. (in a negative context)  
Windows applications blah blah blah DLL stuff  

### How it works
1. Open sln
2. Build
3. Inject
4. ??
5. Profit.

The hacks written are:
- Press <code>]</code> next entity.
- Press <code>[</code> previous entity.
- Press <code>F2</code> to toggle GUI menu.
- Press <code>TAB</code> to toggle God mode.
- Press <code>T</code> to teleport to any given entity.
- Press <code>Shift + T</code> to teleport to current camera target.

### Known issues
I could not find a reliable method to teleport the player to a given location. Sometimes a value  
would flicker as NAN and simply crash the game if the player tried to teleport with the NAN value  
present.

One shot kill currently prevents "Accidental deaths" from counting as killed targets.  
The player has to manually kill them in order for their death to register. This might be  
solvable by changing the one shot op code from <code>mov</code> to <code>xor</code>

There are currently game states that will trigger a crash if cheats are enabled.

These game states include:
- In game escape menu
- Profile loading
- All cinematics
- Mission loading screen

### Goals
 - [x] Find reliable weapon pointer.
 - [x] Find reliable entity_list pointer.
 - [x] Find reliable player_health pointer.
 - [ ] Find a way to prevent teleports from crashing the game.
 - [x] Find reliable 'in game' boolean (or other explicit distinction).
 - [ ] Include entity type in GUI main window, just below the  entity number.
