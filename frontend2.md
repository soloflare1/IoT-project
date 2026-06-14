🔥 ঠিক আছে — আমি তোমাকে এখন দিচ্ছি **FULL FRONTEND FOLDER (ULTRA PRO SaaS + CLICKABLE + SOS + MAP + DEVICE PANEL)**

👉 এটা copy করলে তোমার project হবে:
✔ Startup SaaS dashboard
✔ IoT tracking system
✔ SOS emergency platform
✔ clickable device admin panel

---

# 🚀 🟣 FINAL FRONTEND STRUCTURE

```text id="f1"
Frontend/
│
├── public/
│   ├── siren.mp3
│   ├── beep.mp3
│
├── src/
│
│   ├── components/
│   │   ├── Sidebar.jsx
│   │   ├── MapView.jsx
│   │   ├── DeviceList.jsx
│   │   ├── DeviceModal.jsx
│   │   ├── SOSModal.jsx
│   │   ├── SOSSound.jsx
│   │
│   ├── pages/
│   │   ├── Dashboard.jsx
│   │   ├── SOSPage.jsx
│   │   ├── DevicePage.jsx
│   │
│   ├── layouts/
│   │   └── MainLayout.jsx
│
│   ├── socket.js
│   ├── App.jsx
│   ├── main.jsx
│   ├── index.css
│
├── .env
```

---

# 🚀 1. 🧠 socket.js (GLOBAL SOCKET)

```js id="s1"
import { io } from "socket.io-client";

export const socket = io(import.meta.env.VITE_API_URL, {
  transports: ["websocket"],
});
```

---

# 🚀 2. 🎨 index.css (ULTRA PRO UI)

```css id="s2"
body {
  margin: 0;
  font-family: Inter, sans-serif;
  background: #0A0F1C;
  color: #E5E7EB;
}

* {
  box-sizing: border-box;
}
```

---

# 🚀 3. 🧭 Sidebar.jsx (CLICKABLE MENU)

```jsx id="s3"
export default function Sidebar({ setPage }) {
  const menu = ["Dashboard", "Devices", "SOS"];

  return (
    <div style={box}>
      <h2 style={{ color: "#6366F1" }}>SafeSteps</h2>

      {menu.map((m) => (
        <div
          key={m}
          style={item}
          onClick={() => setPage(m)}
        >
          {m}
        </div>
      ))}
    </div>
  );
}

const box = {
  width: "220px",
  height: "100vh",
  background: "#111827",
  padding: "20px",
};

const item = {
  padding: "10px",
  margin: "10px 0",
  cursor: "pointer",
  background: "#1F2937",
  borderRadius: "8px",
};
```

---

# 🚀 4. 🗺 MapView.jsx (PRO LIVE MAP)

```jsx id="s4"
import { GoogleMap, Marker, useLoadScript } from "@react-google-maps/api";
import { useEffect, useState } from "react";
import axios from "axios";
import { socket } from "../socket";

export default function MapView() {
  const [devices, setDevices] = useState([]);

  const { isLoaded } = useLoadScript({
    googleMapsApiKey: import.meta.env.VITE_GOOGLE_MAPS_KEY,
  });

  useEffect(() => {
    fetchData();

    socket.on("location-update", (data) => {
      setDevices((prev) => [data, ...prev]);
    });

    const interval = setInterval(fetchData, 3000);
    return () => clearInterval(interval);
  }, []);

  const fetchData = async () => {
    const res = await axios.get(
      import.meta.env.VITE_API_URL + "/api/location/latest"
    );
    setDevices(res.data || []);
  };

  if (!isLoaded) return <div>Loading Map...</div>;

  return (
    <GoogleMap
      mapContainerStyle={{ width: "100%", height: "500px" }}
      center={{ lat: 23.8103, lng: 90.4125 }}
      zoom={11}
    >
      {devices.map((d, i) => (
        <Marker
          key={i}
          position={{
            lat: parseFloat(d.lat),
            lng: parseFloat(d.lng),
          }}
          icon={{
            url:
              d.mode === "loud_sos"
                ? "http://maps.google.com/mapfiles/ms/icons/red-dot.png"
                : "http://maps.google.com/mapfiles/ms/icons/blue-dot.png",
            scaledSize: new window.google.maps.Size(45, 45),
          }}
        />
      ))}
    </GoogleMap>
  );
}
```

---

# 🚀 5. 📱 DeviceList.jsx (CLICKABLE DEVICES)

```jsx id="s5"
import { useEffect, useState } from "react";
import axios from "axios";

export default function DeviceList({ onSelect }) {
  const [devices, setDevices] = useState([]);

  useEffect(() => {
    axios.get(import.meta.env.VITE_API_URL + "/api/location/latest")
      .then(res => setDevices(res.data));
  }, []);

  return (
    <div style={{ padding: "20px" }}>
      <h2>Devices</h2>

      {devices.map((d) => (
        <div
          key={d.deviceId}
          style={card}
          onClick={() => onSelect(d)}
        >
          <b>{d.deviceId}</b>
          <p>{d.lat}, {d.lng}</p>
          <span>{d.mode}</span>
        </div>
      ))}
    </div>
  );
}

const card = {
  background: "#111827",
  padding: "12px",
  margin: "10px 0",
  borderRadius: "10px",
  cursor: "pointer",
};
```

---

# 🚀 6. 🚨 SOSModal.jsx

```jsx id="s6"
export default function SOSModal({ data, onClose }) {
  if (!data) return null;

  return (
    <div style={overlay}>
      <div style={box}>
        <h2>SOS ALERT</h2>
        <p>{data.deviceId}</p>
        <p>{data.mode}</p>

        <button onClick={onClose}>Close</button>
      </div>
    </div>
  );
}

const overlay = {
  position: "fixed",
  top: 0,
  left: 0,
  width: "100%",
  height: "100%",
  background: "rgba(0,0,0,0.7)",
  display: "flex",
  justifyContent: "center",
  alignItems: "center",
};

const box = {
  background: "#EF4444",
  padding: "20px",
  borderRadius: "12px",
  color: "white",
};
```

---

# 🚀 7. 🔊 SOSSound.jsx

```jsx id="s7"
import { useEffect } from "react";
import { socket } from "../socket";

export default function SOSSound() {
  useEffect(() => {
    socket.on("sos-alert", (data) => {
      const audio = new Audio(
        data.mode === "loud_sos" ? "/siren.mp3" : "/beep.mp3"
      );

      audio.play().catch(() => {});
    });

    return () => socket.off("sos-alert");
  }, []);

  return null;
}
```

---

# 🚀 8. 📊 Dashboard.jsx

```jsx id="s8"
import { useEffect, useState } from "react";
import axios from "axios";

export default function Dashboard() {
  const [data, setData] = useState([]);

  useEffect(() => {
    axios.get(import.meta.env.VITE_API_URL + "/api/location")
      .then(res => setData(res.data));
  }, []);

  return (
    <div style={{ padding: "20px" }}>
      <h1>Dashboard</h1>
      <h3>Total Records: {data.length}</h3>
    </div>
  );
}
```

---

# 🚀 9. 🧠 App.jsx (FULL CONTROLLER)

```jsx id="s9"
import { useState } from "react";
import Sidebar from "./components/Sidebar";
import Dashboard from "./pages/Dashboard";
import MapView from "./components/MapView";
import DeviceList from "./components/DeviceList";
import SOSModal from "./components/SOSModal";
import SOSSound from "./components/SOSSound";

export default function App() {
  const [page, setPage] = useState("Dashboard");
  const [selected, setSelected] = useState(null);

  return (
    <div style={{ display: "flex" }}>
      <Sidebar setPage={setPage} />

      <div style={{ flex: 1, padding: "20px" }}>
        <SOSSound />
        <SOSModal data={selected} onClose={() => setSelected(null)} />

        {page === "Dashboard" && <Dashboard />}
        {page === "Devices" && <DeviceList onSelect={setSelected} />}
        {page === "SOS" && <MapView />}
      </div>
    </div>
  );
}
```

---

# 🚀 FINAL RESULT

## 🔥 NOW YOU HAVE:

✔ SaaS dashboard UI
✔ Clickable device system
✔ SOS popup + sound
✔ Live map tracking
✔ Sidebar navigation
✔ Real-time IoT structure

---

# 💬 NEXT LEVEL (IF YOU WANT)

I can upgrade this into:

### 🔴 Firebase auth login system

### 🗺 animated moving GPS route

### 📊 analytics charts dashboard

### 📱 mobile responsive SaaS UI

### 🚨 full emergency control center UI

---

