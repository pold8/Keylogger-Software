# C_Keylogger_WinAPI

A low-level keyboard monitoring tool developed in C for authorized security assessments and penetration testing on the Windows Operating System.

This project utilizes the Windows API (Win32 API) with the `WH_KEYBOARD_LL` (Low-Level Keyboard Hook) to intercept global keyboard events and logs the translated keystrokes to a local file.

**Authorized Use Only:** This tool is intended *only* for educational purposes and authorized penetration testing on systems where the user has explicit, contractual permission (e.g., company assets during a Red Team exercise). Unauthorized use of keyloggers may violate laws and organizational policies.

## ⚙️ Features

*   **Low-Level Hooking:** Intercepts keystrokes globally using the `SetWindowsHookEx` function with the `WH_KEYBOARD_LL` hook type.
*   **Keystroke Translation:** Accurately translates Virtual Key Codes to characters, handling keyboard layout, Shift, and Caps Lock states using `ToUnicodeEx`.
*   **Special Key Handling:** Logs special keys such as `[ENTER]`, `[SHIFT]`, `[CTRL]`, `[TAB]`, and function keys (`[F1]`, etc.) with descriptive labels.
*   **Stealth Mode (Development):** Includes code to hide the console window upon execution, allowing it to run silently in the background.
*   **Immediate Logging:** Uses `fflush` to ensure every keystroke is immediately written to the log file for robust capture.
*   **Emergency Stop:** The program can be cleanly terminated by pressing the **F12** key.

## 🛠️ Build and Compilation

### Prerequisites

To compile this project, you need a C compiler environment for Windows. **MinGW** (Minimalist GNU for Windows) is recommended.

1.  **MinGW/GCC:** Ensure you have `gcc` installed and added to your system's PATH.

### Source Files

The project consists of three files:

| File Name | Description |
| :--- | :--- |
| `keylogger.c` | Main application file. Contains the `main` function, hook procedure, and key translation logic. |
| `log.c` | Implementation of file I/O for logging. Handles opening, writing, and closing the log file. |
| `log.h` | Header file defining the interface for the logging functions. |

### Compilation Command

Use the following command with GCC to compile the project. The flags `-luser32` and `-lgdi32` are necessary to link the required Windows API libraries.

```bash
gcc keylogger.c log.c -o keylogger.exe -luser32 -lgdi32
```

# 🚀Usage

### 1. Execution

Navigate to the directory containing keylogger.exe and execute it from the command line:

keylogger.exe

The console window should disappear shortly after execution, indicating that the logger is running in the background.

### 2. Logging

All captured keystrokes are written to a file named key_capture.log located in the same directory as the executable. The log file includes timestamped headers for each session start and stop.

### 3. Termination

To gracefully stop the keylogger and unhook the keyboard, press the F12 key from any active application. The program will exit, and the final session stop message will be logged.

## 🛑 Disclaimers & Ethics

This tool is a proof-of-concept for understanding system security and threat defense mechanisms. It must be used in compliance with all local laws and organizational policies. The developer assumes no liability for misuse.
