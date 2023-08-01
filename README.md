# RY Game Engine
Graphic video game engine created using C++ and SDL2

### Description

This is a 2D graphics framework with built in game engine mechanics such as perishable sprite entity generation, collision detection, camera scrolling level navigation, etc.

### Framework Functionality

Operating System Handling:
- cross-platform OS API handling
- system window manipulation
- system independent event loop handling (time based iteration)

Input:
- clickable buttons supporting multiple click-states, including click, hover, release.
- direct text input
- keyboard input

Media:
- Multi-Format Graphics, including PNG, BMP
- Audio, supports WAV format for effects and music 

Rendering:
- hardware accelerated media rendering using texture
- hardware accelerated geometry rendering for basic shapes
- animation rendering 
- built in direct text rendering

File Handling:
- binary file creation, read, and write. 

Scalability:
- comprehensive encapsulation for streamlined object generation.
- centralized dimensional data handling for one-stop global-scale manipulation across all objects.

### Game Engine Functionality

Entity Generation:
- built-in entity type hierarchy, type separation to eliminate non-essential functions for specific entities
- built-in perishable entity type with life functions such as health and death

Game Play:
- projectile generation, natively supports shooter-style game play
- melee attack 

Game Loop Handling:
- frame-rate independent, time-based entity movement handling

Collision:
- built-in collision box generation for entities, including collision box rendering for testing purposes

Save Game:
- framework supports efficient binary file manipulation

### Back-End Information

Created with C++ utilizing the SDL2 library.

Copyright 2023 Ruoxing (David) Yang.
