#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <string.h>
#include <sstream>
#include <iostream>

using namespace std;

void killProcessById(int id) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    while (hRes) {
        if (pEntry.th32ProcessID == id) {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

void killProcessByName(const char* filename) {
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof(pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);
    size_t cSize = strlen(filename) + 1;
    wchar_t * wc = new wchar_t[cSize];
    mbstowcs(wc, filename, cSize);
    while (hRes) {
        if (wcscmp(pEntry.szExeFile, wc) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                (DWORD)pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}

int main(int argc, char* argv[]) {
    const CHAR* name = "PROC_TO_KILL";
    const DWORD buffSize = 65535;
    char buffer[buffSize];
    cout << "Hello from killer\n";
    GetEnvironmentVariableA(name, buffer, buffSize);
    std::stringstream ss(buffer);
    while (ss.getline(reinterpret_cast<char*>(&buffer), buffSize, ',')) {
        killProcessByName(buffer);
    }

    if (argc < 3) return 0;
    
    if(strcmp(argv[1], "--id") == 0) killProcessById(atoi(argv[2]));
    if (strcmp(argv[1], "--name") == 0) killProcessByName(argv[2]);
    return 0;
}
