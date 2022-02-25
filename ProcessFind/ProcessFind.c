#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

int FindProcessAndKill(char* processName) {
	HANDLE hSnapShot;
	PROCESSENTRY32 pe32;

	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (hSnapShot == INVALID_HANDLE_VALUE) {
		printf("process snapshot failed with error code: %d", GetLastError());
		CloseHandle(hSnapShot);
		return 0;
	}

	while (Process32Next(hSnapShot, &pe32)) {
		if (strcmp(pe32.szExeFile, processName) == 0) {
			return pe32.th32ProcessID;
		}
	}
	return 0;
}


int main(int argc, char** argv) {
	if (argv[1] == NULL) {
		return 0;
	}
	printf("Process PID is: %d", FindProcessAndKill(argv[1]));
	// You better get PID and terminate that PID instead using terminate on function
	return 0;
}