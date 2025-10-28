#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1 = enabled (unmasked), 0 = disabled (masked)
int keyboard_enabled = 1;
int mouse_enabled = 0;   // Masked as per requirement
int printer_enabled = 1;

// Mutex for synchronization
HANDLE lock;

// Function to log interrupt activity with timestamps
void log_event(const char *device, const char *status) {
    FILE *file = fopen("interrupt_log.txt", "a");
    if (file == NULL) return;

    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    fprintf(file, "[%02d-%02d-%04d %02d:%02d:%02d] %s Interrupt %s\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min, t->tm_sec,
            device, status);

    fclose(file);
}

// ISR (Interrupt Service Routine) for Keyboard
DWORD WINAPI keyboard_isr(LPVOID arg) {
    while (1) {
        Sleep((rand() % 3 + 1) * 1000);
        WaitForSingleObject(lock, INFINITE);
        if (keyboard_enabled) {
            printf("Keyboard Interrupt Triggered -> Handling ISR -> Completed\n");
            log_event("Keyboard", "Handled -> Completed");
        } else {
            printf("Keyboard Interrupt Ignored (Masked)\n");
            log_event("Keyboard", "Ignored (Masked)");
        }
        ReleaseMutex(lock);
    }
    return 0;
}

// ISR for Mouse (Masked)
DWORD WINAPI mouse_isr(LPVOID arg) {
    while (1) {
        Sleep((rand() % 3 + 1) * 1000);
        WaitForSingleObject(lock, INFINITE);
        if (mouse_enabled) {
            printf("Mouse Interrupt Triggered -> Handling ISR -> Completed\n");
            log_event("Mouse", "Handled -> Completed");
        } else {
            printf("Mouse Interrupt Ignored (Masked)\n");
            log_event("Mouse", "Ignored (Masked)");
        }
        ReleaseMutex(lock);
    }
    return 0;
}

// ISR for Printer
DWORD WINAPI printer_isr(LPVOID arg) {
    while (1) {
        Sleep((rand() % 4 + 1) * 1000);
        WaitForSingleObject(lock, INFINITE);
        if (printer_enabled) {
            printf("Printer Interrupt Triggered -> Handling ISR -> Completed\n");
            log_event("Printer", "Handled -> Completed");
        } else {
            printf("Printer Interrupt Ignored (Masked)\n");
            log_event("Printer", "Ignored (Masked)");
        }
        ReleaseMutex(lock);
    }
    return 0;
}

int main() {
    srand((unsigned int)time(0));

    // Clear the previous log file contents
    FILE *clear = fopen("interrupt_log.txt", "w");
    if (clear != NULL) {
        fprintf(clear, "==== Interrupt Controller Simulation Log ====\n");
        fclose(clear);
    }

    printf("Interrupt Controller Simulation Started\n");
    printf("Keyboard = Enabled | Mouse = Masked | Printer = Enabled\n\n");

    // Initialize mutex
    lock = CreateMutex(NULL, FALSE, NULL);

    // Create threads
    HANDLE t1 = CreateThread(NULL, 0, keyboard_isr, NULL, 0, NULL);
    HANDLE t2 = CreateThread(NULL, 0, mouse_isr, NULL, 0, NULL);
    HANDLE t3 = CreateThread(NULL, 0, printer_isr, NULL, 0, NULL);

    // Run for 20 seconds before stopping
    Sleep(20000);

    printf("\nSimulation Completed. Check 'interrupt_log.txt' for details.\n");

    // Clean up
    TerminateThread(t1, 0);
    TerminateThread(t2, 0);
    TerminateThread(t3, 0);
    CloseHandle(lock);
    return 0;
}
