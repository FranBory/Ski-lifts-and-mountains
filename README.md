# 🏔️ Ski Lifts and Mountains (C + Visual Studio)

This project is a **C language implementation** of a pathfinding algorithm over terrain with **elevation changes and ski lifts**. It is developed using **Microsoft Visual Studio**.

## 📋 Problem Summary

- You are given a 2D map with elevations and ski lifts.
- You can move to adjacent tiles (up, down, left, right).
- Moving rules:
  - Takes **1 minute** if moving to a lower or same elevation
  - Takes **A - B + 1 minutes** if moving uphill (from B to A)
- Ski lifts:
  - Work in one direction
  - Have fixed travel time
  - Depart every N minutes
- The goal is to reach the destination in the **shortest time** possible.

## 🛠 How to Run (Visual Studio)

1. Open the `.sln` or `.vcxproj` file in **Microsoft Visual Studio**.
2. Ensure the active configuration is **Release** or **Debug**.
3. Build the project (`Ctrl + Shift + B`).
4. Prepare an input file (e.g. `input.txt`) with map and lift data.
5. Run the executable with input redirection:
   - Press `Ctrl + F5` to run
   - Or run in Terminal:  
     ```
     SkiLifts.exe < input.txt
     ```

## 🧪 Input Format

