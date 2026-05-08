
# 1. Project Setup (First Step)

## Create folder

Make a main project folder:

```
D:\Shurokkha\
```

Inside it create:

```
Shurokkha/
 ├── Shurokkha.ino
 ├── README.md
```

---

# 2. Arduino IDE Setup

## Step 1: Install Arduino IDE

* Install Arduino IDE
* Open it once

---

## Step 2: Install ESP32 Board

In Arduino IDE:

```
File → Preferences → Additional Boards URL
```

Paste:

```
https://dl.espressif.com/dl/package_esp32_index.json
```

Then:

```
Tools → Board → Board Manager → Install ESP32
```

---

## Step 3: Select Board

```
Tools → Board → ESP32 Dev Module
Tools → Port → Select COM port
```

---

# 3. Write Full Code (Arduino IDE)

* Open `Shurokkha.ino`
* Write your ESP32 + GPS + GSM code
* Save it inside project folder

---

# 4. Git Setup (Local Version Control)

Open CMD inside project folder:

```bash id="c9p7l3"
cd D:\Shurokkha
git init
```

---

# 5. Add Arduino Project to Git

```bash id="8y3r9m"
git add .
```

Check status:

```bash id="0kq3xw"
git status
```

---

# 6. First Commit

```bash id="p6s1v8"
git commit -m "Initial Shurokkha ESP32 safety system code"
```

---

# 7. Connect GitHub

Go to GitHub and create repo:

```
Shurokkha
```

Then connect:

```bash id="m2xq9a"
git remote add origin https://github.com/yourusername/Shurokkha.git
```

---

# 8. Push Code to GitHub

```bash id="v7n0pd"
git branch -M main
git push -u origin main
```

---

# 9. Daily Update Workflow (Very Important)

Whenever you change Arduino code:

### Step 1: Save in Arduino IDE

### Step 2: Run Git commands

```bash id="k1w8fz"
git add .
git commit -m "Updated GPS logic"
git push
```

---

# 10. How Full System Works (Project Flow)

```
ESP32 starts
   ↓
GPS continuously reads location
   ↓
User presses SOS button
   ↓
ESP32 processes data
   ↓
GSM sends SMS with Google Maps link
   ↓
OLED shows status
   ↓
Buzzer activates (optional)
```

---

# 11. How Arduino + Git + GitHub works together

| Tool        | Role                |
| ----------- | ------------------- |
| Arduino IDE | Write + upload code |
| Git         | Track code versions |
| GitHub      | Store code online   |

---

# 12. Important Notes (Exam/Viva)

* Arduino IDE does NOT support Git directly
* Git works on project folder level
* `.ino` file is treated like normal text code
* Every change must be committed manually

---

# 13. Report Line (Very Important)

You can write:

> “The firmware development is performed using Arduino IDE for ESP32 programming, while Git and GitHub are used for version control, allowing proper tracking, backup, and management of the IoT-based system codebase.”

---



> “Arduino IDE is used for coding ESP32, and Git with GitHub is used externally for version control and backup of the project.”

