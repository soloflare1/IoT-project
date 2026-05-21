# 🟦 ESP32 + OLED + BUTTON + BUZZER + GPS + GSM

step-by-step:

✅ Wiring
✅ Breadboard usage
✅ Library installation
✅ Arduino IDE setup
✅ Code upload
✅ Serial Monitor
✅ Testing each module
✅ Common mistakes

---

# 🟦 STEP 0 — Understand  ESP32

![Image](https://images.openai.com/static-rsc-4/Ixz8YszvNrLnu5L4wskOgkdZQ9tiDe1RjWYcOwb1OQS--jzAHlxwYIByxbA5Jj5nqgTPe6Eyg4vYW5uSbDSqo5NwAWPn6rqKkbybhrr4DJ0FMzPuA0L06IQB8elYO2KdKgYzLPmgcSpyb7k-d1Zxb1op6XurOjIyWk_CzF6hiwJrItDjtN4yZyX_BtF-Reqr?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/8i85LVZ9PAPmWSGeCqvIwxkt2EM3szjIkBSHznTwZvOPp47pLX0ieAMmR7S4840hpmq6OjjzQzQ5JKC-JUSADzwIZZsx2o18-E6cjJcusr6rvTkE6MXjM7SbVyAhHotxapRhjpuNZmBFvldz9PN6w3FynczO2an9oQMc1KCjIN8bgjw5Bvy-IVtY0CdIBn75?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/doZVDcGrJs5LU2T9XEG-Z5Z358RWBpEZGBLeID8cXFFubP4ioa8ks47A-BTWi0OZeoOM0RmwlhBdec-Wis00HsINqfjeUVjA8OthgbQIsj4o4oaEZOMr7OfVkinO8YTsCx5Y35jnPEBLP_GWtQd5X9UIwL8p65tK0iS50Wb0Gsp_Su56UvWwpPrweURzLwks?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/S7ZgvaDwZuT1zRzVvaHVjuHpWZMhra-kUhXM1PoSFpEqAln1NU9TIoOPFR1wN-KIKbCIbjtoSO9iQ3nCgPqIoV5sKjeajVwAtXtQVJn86sX55veNM8H926iA8pcwt4xWEYLmly05zUSM3toZaTk-SmoPlOkkuM5C68qH4QTz_QA2SVhwv-F00iwrDgztiWXI?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/LZLX8oN3qxKx6XFqu4Hd4wDUulQzSNlUB7wcQq7ghyDFLTVeXMkIFaIDsasRFEo25HsSp8DHGp6e1kJ4mf2r1I5GzhiE0Ycv6bQOhJzTky-qrq8BKQNdzDxpEThU0M1R2NAEGknK-Hyt5XSfPcI8SFuDebc_B26ogthQIfl-Y_UcTyQECu86X6Q82PmkHHv0?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/pKpWKOF9frUBjkQ0JhFIPNWoQ58H7TxomrShsLG9cW3Adb1j4qMtpeVQbFkL_VHX6iUc0XcIWw8CdtatkXr3am6AMH87PmyoXW0sHD99PIu5Lqut1Qoq3bj6KVomowTYm4D_PUSebcv_dVuQy73jUgs6KZgOaIj7uprYMXdL06m7q8XUrdzWKy_YP1PJ7z-J?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/XcyGE6vnGRshIrb7UOTve8H0l1eImhLlgcG0-KagGf5Pp2ZKZXbKy2g5LaqPt0OEIu73bM4xZ_vZADKLutjZQ-w-RIh2BnV7bmYIhPXDqLZOjKSk9u5QyQ71QLjV6Q-Ki0sug96CyGySWLjTOLZe5EEFKrXfg37IruLk8Dp4q90CFCmWLD_Mek8_USk1MavW?purpose=fullsize)

Important pins you will use:

| Function  | GPIO  |
| --------- | ----- |
| OLED SDA  | 21    |
| OLED SCL  | 22    |
| Button    | 4     |
| Buzzer    | 5     |
| GPS RX/TX | 16,17 |
| GSM RX/TX | 26,27 |

---

# 🟦 STEP 1 — Install Arduino IDE

## Download Arduino IDE

[Arduino IDE Download](https://www.arduino.cc/en/software?utm_source=chatgpt.com)

Install normally.

---

# 🟦 STEP 2 — Install ESP32 Board Package

## Open Arduino IDE

Go to:

```text id="u2v4m8"
File → Preferences
```

Find:

```text id="e6w2pk"
Additional Board Manager URLs
```

Paste:

```text id="p1m5rx"
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Click OK.

---

# 🟦 STEP 3 — Install ESP32 Board

Go to:

```text id="r9k3wc"
Tools → Board → Boards Manager
```

Search:

```text id="h7v1yt"
ESP32
```

Install:

```text id="z8d4qn"
esp32 by Espressif Systems
```

---

# 🟦 STEP 4 — Connect ESP32 to PC

Use USB cable.

Then go to:

```text id="f3k8nd"
Tools → Port
```

Select available COM port.

Example:

```text id="w2r7pq"
COM5
```

---

# 🟦 STEP 5 — Select Board

Go to:

```text id="t5m9xv"
Tools → Board
```

Select:

```text id="a1u7cy"
ESP32 Dev Module
```

---

# 🟦 STEP 6 — Breadboard Setup

![Image](https://images.openai.com/static-rsc-4/cdaaAyRtW1aINX5vKNAPKvyw56AkMZWEhw6AJAtv2d49byy5hSKIXRbktUIxpsaBgGbF4ngrcIgFryFhkEH6H-wx3PW25OStgpL6mZ9e0Ay3EP5L1obrBVcbd1jlW6ruQOuBKFOIcq4Wb1n3LpASO1HUHav0RjBTv_d2UGTKC8KxV3INu6dc-DAZCTOnarbX?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/Xr4tHOGTg2Xkfv6NgPgQ_w-6cSp1Ch4x7PBOF9DK5Z1gF4ZnGs4O0rKZWSp7PtKqv7xuBJ6wnSX7ovCI4cPOMfZQPDGEHsBg_bcu2gV15a7Hz00oa529Oj5agXRqKs0zfcjcAuGy006UzRtZ8LSMgYMsI9rJCoNT-Fw1WrLGTuhZ1Y1_woTpZOZQfvO8wU5e?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/ESwdCG_tbUD7ira4EQamFIfVBMeV5DRpK4SbmbJQN-yducRMZHz_fnRIeN3nQ4v4rfChDIzA1ry60yp0fTxEdl24xJnFbgAtREa2Odppsq1RxYmnniWsAQaoEOB133pRYZOEcurVDYGQgdPBmOQtXAmty0W7YfjOJagbsHwGJduQnwGK78w5gwxcXsKrHVkN?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/W_2RKhuZl2lWrgazbeJGOGXz8er6Tnd01xwRG_sEqwh40Sq4kWh_HR_X8jDFIE5TnHeN5Qq-n2kORdMw3kL3ei6awy1q6M-MyEB8jNqmX7osDkXuslr6zZ0f86Wy0FpJbgIU0OFnRUx4Z0RqXWMtdnZu-OrOoQjfDZtZtw4yZOz9smQrwSR5HglQLYrJhc3I?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/YkAbNueQXqba4WRfZJCXFTbpZ-dOErO8K6EwdsrnlDBnuL3RdRcWB8XMzVoJdN6yJN9ixLDe4AUAW2IjxIy_zp-TuP8DLIV8lre-Qatt3K0bQL7hwqFyhpmCbqNCEy7d5OvPWYyg91csL8sM0T1BcXdVzQwLd3usKT6ATNM-wCfh7UUGFCzNWNRbaRwwJymP?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/aVfsuvojSV87mWb_ycWnDNbKtw1UkM4RI0xQlu96WL0pwUOadFs6onGI_ma3BjJGo_dGXIio6jgPbKa2eRmzZw-IovyysDU-Sf_oQV7MQRdeZUQS2Rwfcy7YzGIjTvWlVHLqbPg1X98WPouebb4rCHkZAhXmj6_sdmj7s78mJlaioihyN3Rk7ixIUy696h6o?purpose=fullsize)

## Important

* Same row = connected
* Red line = positive power
* Blue line = ground
* Place ESP32 in middle

---

# 🟦 STEP 7 — OLED DISPLAY TEST

---

# 🔌 OLED Wiring

![Image](https://images.openai.com/static-rsc-4/X0j0MCj8rnuMkazZWVcC6Wyke5VdESm769tSe1DQuiKnkVGZJQbsBIM9IhKi2Piexrv1qieZpTMMObDgyiSNBE_iH7XMsO_kuv7wBmzPPYi3o9Iu2gvGTd8FuSS8osXl1q3OrwfIZo2vhVfhEdMQzSAM8_cN7OoBUkDTi32Hu5RMzedcpUTUequfwRZCsZ0A?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/HKjrRuPz2HoSHkqSHEblUvVNp3yyYYkVu9XHm3Ks7FRvSf4yjrl7jVJdZlYkcsC4J2V6JqkRIeXoY2JVwfAnMeUF6WD6ijPq8QeGzyahkBXUDc_0g2Lz7wVuN6kpPlOX0o1NpibD886OZp5nB9N--w130vx7rhGV4i1dxDC1VTkqdUESjasxJmpzlBVm16pm?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/_3XqqJKSKWH4XbJHebzRDZo2swkk3rz1TotW8_Qoufd9UWiwbNig07cMmi3Ob8zO24gRv3pccjySb_SrKPnmq7pX8hkK-vg05tEbYdEuEgbmL5nQh-geSvj3yX3K5LuTGhQNoMsKVtPPK8NXu9tmNSXcqx-YlsF-1AWJdQfncRMIFrBLTEGwxOWzZpdGlinc?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/GnOu6Lgqo2JxlQZ6Y7nC8thp4haQsW8H0ApgsXaNJjoSpFdZ5dn4mWsFq-E8XFwH8L_ATW7Unc2hHXb_iM--0We9FD8IhKRyMWNBm6XxJwqfOy7puNctTHnSzunBBftcYwsrIHxQEgrzTqdFDfjQh7hwGSNilJk4RtlZKY7u7tPCK19e-H3PyeGnPH6FDOHE?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/Pmo4gKzyfMJ-2hO3g7lCMfsni3pTFpanRr9n2ptoJqEk67m1WSMvwzsTcATojIMhc_YcmwPDunEpuKokDoag5GWb6pgTowmi7qZh1WFIKMwc9fWrQALSSUHr0OoXK0ZE6JodfRLCgvO5Jvbf0IL1XJIikl4-4fXaODfOfq4be7cPQh2RWAAWZ3PrlJV9O7Ps?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/8JoS_7WNHfGqn1bVFboU3FV3c6WXD-LhjF0zXV9jp7ZbDpS902KlbmcWpSj6nkaHmuh9fFBz5Je2Tlha857tvdv3UWclLFuhIXCQ7UX0iQ4NqbwBn_oWK1cN-nVdwfl913a58E3Hrej6fvnNVFZIHOkkRUQgzkZ2AVMBvE9emqE4w5PjQ1OeoDUC9-7B1q5H?purpose=fullsize)

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| VCC      | 3.3V      |
| GND      | GND       |
| SCL      | GPIO 22   |
| SDA      | GPIO 21   |

---

# 🟦 STEP 7.1 — Install OLED Libraries

Go to:

```text id="m4v7kc"
Sketch → Include Library → Manage Libraries
```

Search and install:

```text id="x8b2pq"
Adafruit GFX
```

Then install:

```text id="n1w5ur"
Adafruit SSD1306
```

---

# 🟦 STEP 7.2 — OLED Code

Create new sketch and paste:

```cpp id="v6r9ht"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(
  SCREEN_WIDTH,
  SCREEN_HEIGHT,
  &Wire,
  -1
);

void setup() {

  Serial.begin(115200);

  if(!display.begin(
      SSD1306_SWITCHCAPVCC,
      0x3C)) {

    Serial.println("OLED Failed");

    while(true);
  }

  display.clearDisplay();

  display.setTextSize(2);

  display.setTextColor(WHITE);

  display.setCursor(5,20);

  display.println("SHUROKKHA");

  display.display();
}

void loop() {

}
```

---

# 🟦 STEP 7.3 — Upload Code

## Click:

✅ Verify
⬆️ Upload

---

# 🟦 If Upload Fails

Hold BOOT button while uploading.

---

# 🟦 Expected OLED Output

```text id="g9p2xf"
SHUROKKHA
```

---

# 🟦 STEP 8 — BUTTON TEST

---

# 🔌 Button Wiring

![Image](https://images.openai.com/static-rsc-4/IIBccak6Lx55iPl2zPfW0PG5mCk-3Fb4k9_xR9BYcNnDySGWHn63Cm64GIBQVeeb9muZ5tcQGKHChsVSW4BUR92vLDhlr09whZkro4I-skBX4necqdqzoXItTcfqhrqjuXi-RNHWqBCiVW41hyR25VZNKZZuIkysy9--4NCrB7PnbtMNgL0V3Hw8FKfjwi6-?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/opVEt6W2E50T_P9qxK2MiLRDVsTxFcji7FxautVHP7de7L8Egb9obSgvj5GlDeSMxj6ENOkXcbTSa6f6caXBOfBvMUXzAqm30spVnR9FcRQV-00MzgL6TDsEp9mVSwC6uWtLuGPiDWsuh82JGhD2K53IlUDRkpXz0_WKkOjAAwCxdGAauPTcRBku1qlJycim?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/xCb1kVKwTM23d-aqVGqE2sFY85wYtndQ7jcT4SR5hJleb70S5FpnxD57fvOQfoyXVfxYkwLyeoCIm-GcctCB0BYFLAf_LtNFq3cZUL011uNaysX1jh3gKwhxK3nmJ4xJv9QvKW9a7k73KTGHfKOo204wccacnkmitAYqCLjhMPsPihKbo5684rBAP3rs5LYb?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/iU-r3oea6OIrhzlthmARKwhMZI5TSGadaaZ79yi_rst7fxi8QKPPCvr2XE4YFDNOmW5CggCWTf7l1v4TKozkAHsyZBfyzsk-ujco8abqfZzD3sIT_zi3qhxyYFWE5a4DEPDYp4cQLxYnn5z9S07aD8Mc4gAsOanfdq-ov7aQAOLBNEVlzHXoA2P1ZmhhnFxW?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/vZyiiraH8yRGCZvSvO3W-GjxB8MEvJp9OJ6EAttaeD-eqlo-l08yIk3AOL1boBSO7MU--2Y5Y03l-1TRZ97ilLG0HArDKgv8OG8pHwxrbv1luYTcpNvve0SGJyixvLzN5KCAqaoUSNTcZqUjz4qTKtbXC5Ks46JBd-xB1KRqA6S1_hQVfqy0UtJA1MQMCa1I?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/ChoAQAM36W9ObcIVf75ZTFwor3Q7iNo9BNHMPxMO9g0coVOWjwbNNX-aRDQ2gOpsj-Q2uJd8ciDhn4P_QVKbc9yTVyBdvNE2lVNpG_NR_bnEdLnQPuG2uUsWZP4B43_GgRmLb-4I0lcRYyhe8NgAK6tk3HtjrvXYmVdximm0M0i4dRkZYNW4HD4RIUzQmtI1?purpose=fullsize)

| Button    | ESP32  |
| --------- | ------ |
| One Pin   | GPIO 4 |
| Other Pin | GND    |

---

# 🟦 STEP 8.1 — Button Code

```cpp id="j5n8wu"
#define SOS_BUTTON 4

void setup() {

  Serial.begin(115200);

  pinMode(SOS_BUTTON, INPUT_PULLUP);
}

void loop() {

  if(digitalRead(SOS_BUTTON) == LOW) {

    Serial.println("BUTTON PRESSED");

    delay(300);
  }
}
```

---

# 🟦 STEP 8.2 — Open Serial Monitor

Go to:

```text id="y4m7rs"
Tools → Serial Monitor
```

Set baud rate:

```text id="b8n3qx"
115200
```

---

# 🟦 Expected Output

When button pressed:

```text id="d2w5fh"
BUTTON PRESSED
```

---

# 🟦 STEP 9 — BUZZER TEST

---

# 🔌 Buzzer Wiring

![Image](https://images.openai.com/static-rsc-4/dtTUNR5eth0SK0Tp0vrxJE3iitIu_35y63kMTJK9gyCyAcR10T1fUjApmzVtEnrzulBaqci-v0ojeG4Fg4Bw2aLr7P2GFHlDDypA7w3dJvUJZgvyPpXL6TV5m7n71l56B5U6lLQ0QoBS6ywHjB6tC_VJ9xj4iguQaLEjp7nvkwlikS5W6t5oIyPZFPO0sjtI?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/nVaXqtT2F8bwlgR1MldxTjMnTKPSRg7h93ULvnGO_mFlxZ4ABLkTYJIx27dELC8dPnoJWkdim3Euo_mOriiQyebZp8bwkBfrzv4X8dLAak2Aquf-tgBiRWlpPTOSzBmhGtaBKtB-eADWHKW7feTKcFQoTBtYE92A7-bJbby09j80tAwEfS4Ox1yvlS4Ti3_S?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/XzqJpqeeOk6jlpY2d7uagbNsB9sGRc5j5HgSrtPvrHSfyxkXOzi01fsn_iHJ-4e5ZcExc4zoWbAiHFNOPj3FgFVXH6HABIqCnnqTjasv2-VuDFj1-yi3s1f1BNgfd7Ye_rs5ZzlTef1qLHCEeQ-pmsrEPi0d7GvFpAUnlWKwCCqyZhq-g7Xom-cZj0i4jyl8?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/Wlqi9Lu-q0yaVnTWEXfEe8yxn2R3Ic4h_pO6JeoXEEkFPXLdSHb0fTXBC6RVbuykSy4avzSY99_vdCUOifcndMGm-jnagXd4l9Q-xxnBd1VXLP9KJ1xA0h7MZt6dU4usuboRTPEWZIvHePSZWTru96454NvEg7pSZxN1a8w9brNkRurwuTXujRUdxsk2vuaS?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/RlAs6UcMeFhYRp0DZkdrwR9oTIEah1nDU0I0Xt6OaHe0Np1bnNW89rcscT5z4bG1V2G0KIN5-kjyP35ZYqgEYSN5KGKhC--mcKdOzgfLnAM0o1RzkloEofQGfovD5SNvoBrN_V-W99DhEMl8ggYIim4ullrxnlaaeeqBSpXdMVCI5QC_sSRDkDQiWftK2wb-?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/ECjJ8f6rr7r-RQSn0gX45AuMKVVHCgb1G7Fz_s6EWD-NdC0RAF1wKq9VUewqYnDzHMFGzSWdpZ7oDDdlMpoK_vjE58FVmrMEJuaqP9pDPpBvFMrPa8NMdP6dE90-vedwjcbry6ypMJQGc6oPcgFPYmKCkBEfzMlFYPjJESnF6hDe2hMmEH6Qq5Y6H11LaPdm?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/xt5MHYPX4FmfvA2p8rSSC0eEg2MWCElvxqiREt9F8Zr_tOXOw_bIohVbw58_V72pZHTyUB0P_xTbTCo9X7ZaMDwZM41EH-djP_yLZjRoJXjeCOzSZeUOFZ8AmxZOUjrJW4msLSdR3GWSK2lw4_jQZy1aSU7RMq44SQTqllSvYmJbSCiGHFg00CSKwZ6a79CG?purpose=fullsize)

| Buzzer | ESP32  |
| ------ | ------ |
| +      | GPIO 5 |
| -      | GND    |

---

# 🟦 STEP 9.1 — Buzzer Code

```cpp id="s4u8vn"
#define BUZZER 5

void setup() {

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  digitalWrite(BUZZER, HIGH);

  delay(1000);

  digitalWrite(BUZZER, LOW);

  delay(1000);
}
```

---

# 🟦 Expected Result

Buzzer ON/OFF every second.

---

# 🟦 STEP 10 — GPS TEST

---

# 🔌 GPS Wiring

![Image](https://images.openai.com/static-rsc-4/DX1GAUXFXBPjAaTtzMWBMOka8A2mqK8h2Ly8ykUw_8gv7w7RyemyaQz3EamlKMMulVgwNhvfGiRLDggXWIlF4-BGHIiMnHk-fytE6dqad0dkW_DFAxA37ivN-B8Nm3nNAwkRQ1qvPTNOTm__KK7qVIOWj6wMWySLvEyM_b14mD7U-gEXgtx7JiU4xqK9fun6?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/qn8u8KOZ9YnPhTa3Ws-vfcfzDR0R0DefbRQx17tayoolXS1pTKj-h4sFepLN9PLC3jukoUUWm4TCq6818BpClmdIX-W6lYJedaiGzU4tcA4YXyVyOa1asCrursaRVXkFjJybuE0JxzWtAmydKUULtbfBEyVZtZawmsUGnr9KF9WldSOvWp-ZyJLsmXtpTKF0?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/KuZIjCuw-yq9NA8MXQaOGOxuNM2JAIb8jOImD2qjS7BcoYn46TMrhMMWYXpZBA8ODZbVblpw26HnVkfINX_PiTNbYgga6bqcy3bFrnb5VUCbEajOhxLREeUS9d8W3KSqLPDtePAhNxnAgDe9eRRvaUJFF2mpYLPCJsnfkMsrqdiGVNqVML-LIMcYUCWxZW6F?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/CKWFFYRw7VINuLgI6kk11ct-wIbmSUVKZUpieganlWznFEgJcjvtuq5iXy6lDJm1EkXlqyHFmsodlfrhBrGdCdOm1FErBO19GFZPaB8jmOmffFBmFLYa2-csJ6XP2Nwmv_82hzF8obnlG8oWRzQhNRM4_WWnTjH2PHRHzEHMR7RxWJlxYDBXwOnENyzhjeaK?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/ap_OAA73MTe1xeedt-V3Btf9Q7j_vuRADmu429YUnP7_Z6eW9R3FxXQtwpD17dZX7hCTz8aer-hgda3vCn1GAF_8r0Jk23lmaoo-Qj6iuki1DszvbMChY3-UAlLq4dUvIJV5suyVG4WaoQqDCToRABKv2mnq3Ki4rfdUe0s0YlDVz5F-vmL1hh1_XkaowpQI?purpose=fullsize)

| GPS | ESP32   |
| --- | ------- |
| VCC | 3.3V    |
| GND | GND     |
| TX  | GPIO 16 |
| RX  | GPIO 17 |

---

# 🟦 IMPORTANT

Cross connection:

* GPS TX → ESP32 RX
* GPS RX → ESP32 TX

---

# 🟦 STEP 10.1 — Install GPS Library

Install:

```text id="x5f9pq"
TinyGPSPlus
```

---

# 🟦 STEP 10.2 — GPS Code

```cpp id="c8r4wv"
#include <TinyGPS++.h>
#include <HardwareSerial.h>

TinyGPSPlus gps;

HardwareSerial gpsSerial(1);

void setup() {

  Serial.begin(115200);

  gpsSerial.begin(
    9600,
    SERIAL_8N1,
    16,
    17
  );
}

void loop() {

  while(gpsSerial.available()) {

    gps.encode(gpsSerial.read());

    if(gps.location.isUpdated()) {

      Serial.print("Latitude: ");

      Serial.println(
        gps.location.lat(),
        6
      );

      Serial.print("Longitude: ");

      Serial.println(
        gps.location.lng(),
        6
      );

      Serial.println();
    }
  }
}
```

---

# 🟦 Expected GPS Output

```text id="k7u3xn"
Latitude: 23.xxxxxx
Longitude: 90.xxxxxx
```

---

# 🟦 GPS NOT WORKING?

## Fix

* Go near window
* Go outside
* Wait 2–5 minutes
* Check TX/RX wiring

---

# 🟦 STEP 11 — GSM TEST

---

# ⚠️ VERY IMPORTANT

SIM800L should use external battery.

Do NOT use ESP32 3.3V pin.

---

# 🔌 GSM Wiring

![Image](https://images.openai.com/static-rsc-4/zFDt6IlMYhx1rU_S80-a5_6JuSU_jslz4RMMH_LmgV2o2bfg-fNR5L_YRM2lxDI3sQ75PU7r5SYR6v52HiINeYDP2zhd1OUp45hEA4mk_CxON4ohwDWLoPZN6flnGb025E-LaF9PYq0hhr8804qxRRLnpDgUX6paHgG1CWqBbWumtEMp8sedGHk1hsfbElIi?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/YFVQn9rBkHDunY9mE507YQQySIGFIC2yZCm8XM8XQaI2r-F1UoBKzk49yMd6h2UVGnP6zsHd6b9cwWLVxsI1QdzSNFql2XR-2W69f7VkU1XYdokOVhkWwIcxhzk3nKS2_EckUUjDt2Pwmg1EeHjFhD_J3ogWE8QZlHJabwG2k4tMB7vf_fHNDK95nyXVcPTl?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/f7c8DLz2rPqx-sM5fGYXy1R96j01PULdJ14FCmEvjzHYnrUxkqUWs4eYugGz8dn-JmWTKdWmlQT5XltB8CZ1P8i2A0TKOmHMC9Y6p6itE04UARPW_-YOAeNJdQ6hDHd3tWZvF11a6YsGU4Q8Kp_qo9sflfYIuJ_QZrzlB8WAIEXso-wPNtooPC4dJMQEiHYQ?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/OFgchPAozFsFxyGSIjREw7HDEZrj71E0Y53Z317hLV8-rJVvOdzsVvGmTdapkQmEhxP50awrGIp2yx32nW73Xpj8lfxcMfK-T1oDRMjEeLZBuNtGI5sMi6eQRO7a1p9pb4LrsPMoLlyjgwAOhd4HOhHOf2HFUdrRQ8DLig8B3pXNFkmxj9UdUGzdCfgLb5vc?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/3QU6198M1ZQCANzYxAeUcQ_4FiN1zkbGCy2bE2Ys6AVZDey6hilm5YAMyuNEUMM0KHQK5MEPGEesEwno-OJhqpxbQCMbIjEADwnEkovK3MeDJExdeJ-8mk4qJNmxVoUAHPFiOfdFuQCyCg3C6kng1TDdHNGGBFz38Y6lJJHsBODi_jYfA3JNqpOFkoAv8kUa?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/vVhhr3kjpwOU806vK3oeW7ZAs586yOuzhe6uy35L7hHm6dDTuQCm7ZgaG1HYBDi5m35Rw-0AbVonC9LsMYiiOMAsvTAK6fLMvAuVYEUm60QWCupUzKR0N8q1K2UxewIuuPYDfmpNBwU79LpZsGDjJnsLfvS32rqoI7r_VhsK13YwmBMcl9DYZ4obU4o8l95K?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/blnSPMIDxAelgTgKC6KgUq1MnblPepjW_qJoz1cdjyjIL6pS1zuFcygeq3usdzQKjoP3jKnX_vHZZYxMddN3OAqvPMLy8nwjYg8FdP1VvG9abC1nYKUyCg_mKugAKg8ZSFgCSCMhsw1jrFHrEywPwubHjYcQZSz8HCu05DdwZjZZIAsE8ssdv1zSoq32j7-k?purpose=fullsize)

![Image](https://images.openai.com/static-rsc-4/KktjxVgX0jXXhbAvqT8yA_Wf5AW1qoQ80rQJMvK7n3GhwAjaFbPU9TUfLHFDNv2mDkb_oCPRwn5iBQhihTRC1qFMpjxYnQkQ2N_aw8rHQ7ovGjTgQjtkW1uyCYvQWfqq2REMPJRmxVFweA0wYf3hwiVEiTIkcpbHMFHyx65eJhj-7QtqfHDR_p-tIuTK5aTb?purpose=fullsize)

| SIM800L | ESP32   |
| ------- | ------- |
| TXD     | GPIO 26 |
| RXD     | GPIO 27 |
| GND     | GND     |

---

# 🟦 STEP 11.1 — GSM Test Code

```cpp id="f1m7qt"
#include <HardwareSerial.h>

HardwareSerial gsmSerial(2);

void setup() {

  Serial.begin(115200);

  gsmSerial.begin(
    9600,
    SERIAL_8N1,
    26,
    27
  );

  delay(3000);

  gsmSerial.println("AT");
}

void loop() {

  while(gsmSerial.available()) {

    Serial.write(
      gsmSerial.read()
    );
  }
}
```

---

# 🟦 Expected Output

```text id="r9v2cx"
OK
```

---

# 🟦 STEP 12 — SMS TEST

---

# 🟦 SMS Code

```cpp id="z5m1pk"
#include <HardwareSerial.h>

HardwareSerial gsmSerial(2);

String phoneNumber =
"+8801XXXXXXXXX";

void setup() {

  gsmSerial.begin(
    9600,
    SERIAL_8N1,
    26,
    27
  );

  delay(3000);

  gsmSerial.println("AT+CMGF=1");

  delay(1000);

  gsmSerial.print("AT+CMGS=\"");

  gsmSerial.print(phoneNumber);

  gsmSerial.println("\"");

  delay(1000);

  gsmSerial.print(
    "SHUROKKHA TEST"
  );

  delay(1000);

  gsmSerial.write(26);
}

void loop() {

}
```

---

# 🟦 Expected Result

Phone receives SMS.

---

# 🟦 STEP 13 — 2 PRESS / 3 PRESS SYSTEM

---

# 🟦 Logic

| Press Count | Mode    |
| ----------- | ------- |
| 2 Press     | Silent  |
| 3 Press     | Audible |

---

# 🟦 Code

```cpp id="g8n2ws"
#define BUTTON 4
#define BUZZER 5

int pressCount = 0;

unsigned long lastPress = 0;

void setup() {

  Serial.begin(115200);

  pinMode(BUTTON, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
}

void loop() {

  if(digitalRead(BUTTON) == LOW) {

    pressCount++;

    lastPress = millis();

    Serial.print("Count: ");

    Serial.println(pressCount);

    delay(300);
  }

  if(pressCount > 0 &&
     millis() - lastPress > 2000) {

    if(pressCount == 2) {

      Serial.println(
        "SILENT MODE"
      );
    }

    else if(pressCount == 3) {

      Serial.println(
        "AUDIBLE MODE"
      );

      digitalWrite(BUZZER, HIGH);

      delay(3000);

      digitalWrite(BUZZER, LOW);
    }

    pressCount = 0;
  }
}
```

---

# 🟦 FINAL TESTING ORDER

| Step | Test              |
| ---- | ----------------- |
| 1    | OLED              |
| 2    | Button            |
| 3    | Buzzer            |
| 4    | GPS               |
| 5    | GSM               |
| 6    | SMS               |
| 7    | Dual Press Logic  |
| 8    | Final Full System |

---

# 🟦 Common Problems

| Problem         | Solution             |
| --------------- | -------------------- |
| OLED blank      | Check SDA/SCL        |
| GPS no data     | Go outside           |
| GSM no response | Use external battery |
| Upload failed   | Hold BOOT            |
| No COM port     | Install drivers      |
| Random restart  | Weak power supply    |
