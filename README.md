# **HiLetGo BadUSB Beetle - Keystroke Injection - Multi-OS Support**

## **Overview**
This project turns the **HiLetgo BadUSB Beetle (ATMEGA32U4)** into a **multi-OS keystroke injection tool** that can automate commands across **Windows, Linux, and macOS**. The included **Rickroll payload** is just an example of what’s possible. Additional payloads will be added to support various automation and security research tasks.

## **⚠️ Disclaimer**
This tool is for **educational and ethical hacking purposes only**. Do not use this on systems you do not own or have explicit permission to test. The misuse of this tool may result in legal consequences.

---

## **🔧 Requirements**
- **HiLetgo BadUSB Beetle (ATMEGA32U4)** or any ATMEGA32U4-based board
- **Arduino-CLI installed**
- **Arduino Keyboard Library installed**
- **A computer running Windows, Linux, or macOS**
- **USB cable for flashing the board**

---

## **🛠️ Installation & Setup**
### **Step 1: Install Arduino-CLI**
Arduino-CLI is required to compile and upload scripts to the BadUSB device.

Run the following command to install Arduino-CLI:
```bash
curl -fsSL https://raw.githubusercontent.com/arduino/arduino-cli/master/install.sh | sh
```
Verify the installation:
```bash
arduino-cli version
```

### **Step 2: Configure Arduino-CLI**
Initialize the configuration file:
```bash
arduino-cli config init
```
Update the core index and install support for ATMEGA32U4 boards:
```bash
arduino-cli core update-index
arduino-cli core install arduino:avr
```

### **Step 3: Install the Keyboard Library**
The Keyboard library is required to simulate keystrokes. Install it using:
```bash
arduino-cli lib install "Keyboard"
```

### **Step 4: Check If Your Board is Detected**
Plug in your HiLetgo BadUSB Beetle and run:
```bash
arduino-cli board list
```
If detected, you should see an output like:
```
Port         Type              Board Name  
/dev/ttyACM0 Serial Port      Arduino Micro
```

---

## **📜 Writing a Keystroke Injection Script**
The following is an **example Rickroll payload for Windows**. Additional payloads will be added to support different automation use cases.

### ** Create a New Sketch**
Create a new file called `payload.ino` and paste the following script:

```cpp
#include "Keyboard.h"

void setup() {
    delay(3000); // Wait for system to be ready
    Keyboard.begin();

    // Open Run Dialog (Win + R)
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.press('r');
    Keyboard.releaseAll();
    delay(500);

    // Open PowerShell
    Keyboard.print("powershell");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(1500);

    // Command to play video in Microsoft Edge Kiosk Mode
    Keyboard.print("Start-Process msedge.exe -ArgumentList \"--kiosk https://shattereddisk.github.io/rickroll/rickroll.mp4 --edge-kiosk-type=fullscreen\"");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(1000);

    // If Edge is unavailable, use Windows Media Player
    Keyboard.print("$wmp = New-Object -ComObject WMPlayer.OCX; $wmp.URL = 'https://shattereddisk.github.io/rickroll/rickroll.mp4'; $wmp.controls.play();");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
    delay(1000);

    // Exit PowerShell
    Keyboard.print("exit");
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();

    Keyboard.end();
}

void loop() {}
```

---

## **🛠️ Compiling & Uploading the Script**
### **Step 1: Compile the Script**
Run the following command to compile the script for the **ATMEGA32U4**:
```bash
arduino-cli compile --fqbn arduino:avr:micro payload.ino
```
If your board uses the **Leonardo bootloader**, use:
```bash
arduino-cli compile --fqbn arduino:avr:leonardo payload.ino
```

### **Step 2: Upload the Script to the BadUSB Device**
```bash
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro payload.ino
```
Replace `/dev/ttyACM0` with the correct port detected earlier.

---

## **🚀 Executing the Payload**
1. **Plug the BadUSB into a computer** running Windows, Linux, or macOS.
2. The script will automatically execute after a **3-second delay**.
3. The behavior depends on the payload:
   - The **Rickroll example** will launch and play the video.
   - Future payloads will support **automated commands, network scripts, or penetration testing tools**.

---

## **🎯 Troubleshooting**
### **1. The Payload Doesn't Execute**
- Ensure the script is **compiled and uploaded correctly**.
- Verify that **Arduino-CLI detects the board** with `arduino-cli board list`.
- Try increasing the delay (`delay(3000);` to `delay(5000);`) in `setup()`.

### **2. Edge Doesn’t Open in Kiosk Mode (Windows Example)**
- Ensure **Microsoft Edge is installed** by running:
  ```powershell
  Start-Process msedge.exe
  ```
- If Edge isn’t installed, the script will automatically fall back to **Windows Media Player**.

### **3. Expanding Beyond the Rickroll Payload**
- New payloads will be added to support **Linux terminal automation**, **macOS scripting**, and **advanced penetration testing workflows**.
- Stay updated by checking the repository for new releases!

---

## **📌 Additional Enhancements**
- **Make it more stealthy**: Modify commands to **hide execution windows**.
- **Expand payload library**: Add **multi-OS automation scripts**.
- **User interaction bypass**: Implement logic to detect and manipulate UI elements.

---

## **📢 Final Notes**
This repository is designed for **educational purposes**, helping users understand how keystroke injection can be used for **automation and security research**.

For any issues or improvements, feel free to **submit a pull request** or **open an issue** on GitHub.

**More payloads coming soon!** 🚀

