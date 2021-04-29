#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

int main() {
    const CHAR* name = "PROC_TO_KILL";
    const CHAR* value = "notepad.exe,mspaint.exe";
    const DWORD buffSize = 65535;
    char buffer[buffSize];
    SetEnvironmentVariableA(name, value);
    GetEnvironmentVariableA(name, buffer, buffSize);

    STARTUPINFO si = { 0 };
    PROCESS_INFORMATION pi = { 0 };
    std::cout << name << " { " << buffer << "};" << '\n';
    std::cout << "Create processes mspaint and notepad. It's important code have absolut path for this processes." <<
        "C:\\WINDOWS\\system32..." << "\n";
    CreateProcessW(L"C:\\WINDOWS\\system32\\mspaint.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    CreateProcess(L"C:\\WINDOWS\\system32\\notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    std::cout << "delete notepad throw id " << pi.dwProcessId << '\n';
    std::string text = "C:\\Users\\illia\\source\\repos\\os\\process\\Debug\\killer.exe --id " + pi.dwProcessId;
    wchar_t tmp[200];
    mbstowcs(tmp, text.c_str(), text.length());
    
    CreateProcess(NULL, tmp, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);

    std::cout << "round 2" << '\n';
    std::cout << "Create processes mspaint and notepad " << "\n";
    CreateProcess(L"C:\\WINDOWS\\system32\\mspaint.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    CreateProcess(L"C:\\WINDOWS\\system32\\notepad.exe", NULL, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    std::cout << "delete explorer.exe throw name" << '\n';

    text = "C:\\Users\\illia\\source\\repos\\os\\process\\Debug\\killer.exe --name explorer.exe";
    mbstowcs(tmp, text.c_str(), text.length());

    CreateProcess(NULL, tmp, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    std::cout << "it's normal explorer.exe just reload. Explorer.exe win" << '\n';

    SetEnvironmentVariableA(name, NULL);
    buffer[0] = '\0';
    GetEnvironmentVariableA(name, buffer, buffSize);
    std::cout << name << " { " << buffer << "};" << '\n';
    system("pause");
}
