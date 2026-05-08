## Note: Arduino + Git & GitHub Connection (Version Control)

Arduino IDE does not directly integrate with GitHub. Instead, version control is done externally using Git through Command Prompt (CMD) or Terminal. The Arduino project files (.ino) are tracked as normal text files using Git.

---

## Connection Workflow (Step-by-step)

### 1. Create Arduino Project

* Write code in Arduino IDE
* Save project in a folder (e.g., Shurokkha)

---

### 2. Initialize Git Repository

```bash
git init
```

This creates a local Git repository inside the project folder.

---

### 3. Add Project Files to Git

```bash
git add .
```

or specific file:

```bash
git add filename.ino
```

---

### 4. Commit Changes

```bash
git commit -m "initial commit"
```

This saves a snapshot of the Arduino code.

---

### 5. Connect to GitHub Repository

```bash
git remote add origin https://github.com/username/repo.git
```

---

### 6. Push Code to GitHub

```bash
git push -u origin main
```

---

## How It Works in Arduino Projects

* Arduino IDE is used only for coding and uploading to ESP32/Arduino board
* Git tracks changes in `.ino` files
* GitHub stores project online for backup and sharing
* Each update in code can be saved as a new version using commit

---

## Important Points

* Arduino IDE has no built-in Git integration
* Git works on project folder level, not inside Arduino IDE
* `.ino` files behave like normal source code files
* Every change should be committed for proper version history

---

## Report Writing Line 

> Version control for the Arduino-based firmware is maintained using Git and GitHub through Command Line Interface. The Arduino IDE is used for code development and uploading, while Git is used for tracking changes and maintaining version history of the embedded system.

---


> “Arduino code is managed using Git via CMD, and GitHub is used for remote backup and version control of ESP32 firmware.”

---
