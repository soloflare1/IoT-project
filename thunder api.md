Perfect 👍 I’ll guide you **step-by-step how to use Thunder Client in VS Code** for your SafeSteps backend test.

---

# 🟦 OPTION 2 — THUNDER CLIENT (VS CODE) SETUP

## 🚀 STEP 1 — Install Extension

1. Open **VS Code**
2. Go to **Extensions** (left side panel)
3. Search:

```text id="tc1"
Thunder Client
```

4. Click **Install**

---

# 🚀 STEP 2 — Open Thunder Client

After install:

👉 Left sidebar → Thunder icon (⚡)

Click it

---

# 🚀 STEP 3 — Create NEW REQUEST

Click:

```text id="tc2"
New Request
```

---

# 🚀 STEP 4 — SET METHOD

Select:

```text id="tc3"
POST
```

---

# 🚀 STEP 5 — ENTER URL

Put this:

```text id="tc4"
http://localhost:3000/api/location
```

---

# 🚀 STEP 6 — SET BODY

Click:

👉 Body → JSON

Paste this:

```json id="tc5"
{
  "deviceId": "ESP32_01",
  "lat": 23.8103,
  "lng": 90.4125,
  "mode": "tracking"
}
```

---

# 🚀 STEP 7 — SEND REQUEST

Click:

👉 **Send**

---

# 🟢 STEP 8 — SUCCESS RESULT

If everything is OK, you will see:

```json id="tc6"
{
  "success": true
}
```

---

# 🧠 STEP 9 — VERIFY DATA

Now open browser:

```text id="tc7"
http://localhost:3000/api/location
```

You should see:

```json id="tc8"
[
  {
    "deviceId": "ESP32_01",
    "lat": 23.8103,
    "lng": 90.4125
  }
]
```

---

# 🚨 IF IT DOES NOT WORK

Check these:

## ❌ Backend not running

```bash id="tc9"
node server.js
```

## ❌ Wrong URL

Must be:

```text id="tc10"
http://localhost:3000/api/location
```

---

# 🔥 SIMPLE FLOW

```text id="flow1"
Thunder Client → Backend → MongoDB → Response
```

---

# 💬 NEXT STEP (IMPORTANT)

After this works, we move to:

### 🚀 ESP32 real GPS sending to backend

### 🗺️ Frontend live map dashboard

### 🔴 SOS real-time alert system

Just tell me 👍
