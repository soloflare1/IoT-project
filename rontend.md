🔥 Great — you chose **B: Frontend Live Map (SafeSteps Dashboard)**

Now I’ll guide you step-by-step to build a **REAL production-style tracking dashboard**.

---

# 🗺️ SAFE STEPS FRONTEND — LIVE MAP SYSTEM

---

# 🚀 STEP 1 — INSTALL GOOGLE MAPS PACKAGE

Go to your frontend folder:

```bash id="f1"
cd Frontend
npm install @react-google-maps/api axios socket.io-client
```

---

# 🚀 STEP 2 — ADD ENV FILE

Create `.env` in Frontend:

```env id="f2"
VITE_API_URL=https://safesteps-1.onrender.com
VITE_SOCKET_URL=https://safesteps-1.onrender.com
VITE_GOOGLE_MAPS_KEY=YOUR_GOOGLE_MAPS_KEY
```

---

# 🗺️ STEP 3 — CREATE MAP COMPONENT

Create file:

```text id="f3"
src/components/MapView.jsx
```

---

## ✨ CODE (LIVE MAP)

```jsx id="map1"
import { GoogleMap, Marker, useLoadScript } from "@react-google-maps/api";
import { useEffect, useState } from "react";
import axios from "axios";

const containerStyle = {
  width: "100%",
  height: "500px",
};

const center = {
  lat: 23.8103,
  lng: 90.4125,
};

export default function MapView() {
  const [locations, setLocations] = useState([]);

  const { isLoaded } = useLoadScript({
    googleMapsApiKey: import.meta.env.VITE_GOOGLE_MAPS_KEY,
  });

  useEffect(() => {
    const fetchData = async () => {
      const res = await axios.get(
        import.meta.env.VITE_API_URL + "/api/location"
      );
      setLocations(res.data);
    };

    fetchData();
    const interval = setInterval(fetchData, 3000);
    return () => clearInterval(interval);
  }, []);

  if (!isLoaded) return <div>Loading Map...</div>;

  return (
    <GoogleMap mapContainerStyle={containerStyle} center={center} zoom={7}>
      {locations.map((loc, i) => (
        <Marker
          key={i}
          position={{ lat: loc.lat, lng: loc.lng }}
        />
      ))}
    </GoogleMap>
  );
}
```

---

# 🚀 STEP 4 — USE MAP IN APP

Edit:

```text id="f4"
src/App.jsx
```

```jsx id="app1"
import MapView from "./components/MapView";

export default function App() {
  return (
    <div style={{ padding: "20px" }}>
      <h1>SafeSteps Live Tracking</h1>
      <MapView />
    </div>
  );
}
```

---

# 🚀 STEP 5 — GOOGLE MAPS KEY (IMPORTANT)

Go here:

👉 [https://console.cloud.google.com](https://console.cloud.google.com)

Enable:

✔ Maps JavaScript API

Then create API key

---

# 🚀 STEP 6 — RUN FRONTEND

```bash id="f5"
npm run dev
```

Open:

```text id="f6"
http://localhost:5173
```

---

# 🧠 WHAT YOU WILL SEE

✔ Map of Bangladesh
✔ Markers from MongoDB
✔ Live updates every 3 sec
✔ Multiple device tracking ready

---

# 🔥 SYSTEM FLOW NOW

```text id="flow1"
Thunder Client / ESP32 → Render API → MongoDB → Frontend Map ✔
```

---

# 🚀 NEXT LEVEL (OPTIONAL UPGRADE)

After this, I can help you:

## 🔴 SOS ALERT POPUP SYSTEM

## 🔵 LIVE MOVING MARKERS (animation)

## 📡 SOCKET.IO REAL-TIME MAP (no refresh)

## 👮 ADMIN DASHBOARD

---


