# 🐍 2D Snake Game

A simple 2D Snake game with a **custom renderer** for smooth graphics and text.

---

## Features

- Classic Snake gameplay with 3 states: **Menu**, **InGame**, and **EndScreen**  
- Custom rendering engine with **sprite and text batching**  
- Smooth movement with support for **rotation, scaling, colors, and textures**  
- Dynamic text rendering (scores, messages) using a font atlas  

---

## Libraries Used

- **GLFW** – Window creation and input handling  
- **GLAD** – OpenGL loader  
- **GLM** – Mathematics (vectors, matrices)  
- **STB** – Image loading  
- **FreeType** – Font rendering  

---

## Rendering

- **SpriteBatch** – Draws multiple sprites in a single call for efficiency  
- **TextBatch** – Draws dynamic text with alignment, rotation, and color  
- Uses dynamical GPU batching for better performance  

---

## Example of working

![Snake Gameplay](clips/gameplay.gif)

> Make sure to clone the repository recursively to include all submodules:  
```bash
git clone --recursive https://github.com/andriishul/Snake2D.git