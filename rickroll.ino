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
