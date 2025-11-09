# 🌲 Little Red Riding Hood

*A text-based survival and exploration game reimagining the classic fairy tale.*

Step into the boots of **Little Red Riding Hood (LRRH)** as she ventures through a dark, unpredictable forest on her way to Granny’s house. Along the way, she must collect **bread** and **flowers**, seek help from the **Woodsman**, and avoid the **Big Bad Wolf** and the **deadly pits** lurking beneath the trees.

---

## 🧠 Project Information

This project was developed for **CBPROG1 – Machine Project** under the **CCS Bachelor of Science in Computer Science (CBL)**,  
**De La Salle University**.

---

## 🚀 Clone and Run
1. **Clone the repository**:

```bash
git clone https://github.com/andeng07/cbprog1-lrrh.git
cd cbprog1-lrrh
```

2. **Compile the source code**:
```bash
gcc -Iinclude -Wall -std=c99 src/*.c -o bin/out
```

3. **Run the game**:

Windows:
```bash
bin\out.exe
```
Linux/macOS:
```bash
./bin/out
```

---

## 🧩 Programming Concepts Demonstrated

| Concept | Description |
|:---------|:-------------|
| **Arithmetic Operations** | Handle movement and counters |
| **Conditional Statements** | Control game logic and validate user input |
| **Iterative Constructs** | Traverse the grid and simulate movement |
| **Arrays** | Represent the game board and its objects |
| **Structs** | Group related data for game entities |
| **Enums** | Define object types and directions |
| **Pointers** | Reference and modify entities efficiently |
| **Dynamic Memory Allocation** | Support flexible, user-defined grid sizes |

---

## 🎮 Gameplay Overview

The game unfolds on an `n×n` forest grid (8–15 tiles).  
You control **LRRH** using movement and rotation commands, exploring the forest one step at a time.

She can:
- **Move forward** to traverse the grid  
- **Rotate clockwise** to change direction  
- **Sense** what lies ahead — *a breeze (pit), a howl (wolf), a scent (flower), heat (bakeshop), sound (woodsman), or light (Granny’s house)*  

**Objective:**  
Reach Granny’s house safely **with both bread and flowers**, and **with the Woodsman’s help**.

---

## 🏗️ Development Progress

| Milestone | Description | Status |
|:-----------|:-------------|:--------|
| **Milestone 1** | Grid setup, movement, sensing, and counters | ✅ Completed |
| **Milestone 2 (Final)** | Full gameplay: interactions, win/lose conditions, Woodsman integration | 🚧 In Progress |

---

## ⚙️ Built With

- **C Programming Language**

---

## 👤 Author

**Andrei John Sumilang**  
Bachelor of Science in Computer Science (CBL)  
De La Salle University  