#include <Windows.h> // For handles and other stuffs
#include <TlHelp32.h> // Required for PROCESSENTRY32
#include <stdio.h> // For printf function

int FindProcessAndKill(char* processName) { // Function
	HANDLE hSnapShot;
	PROCESSENTRY32 pe32;

	hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); // Snap all current process list

	if (hSnapShot == INVALID_HANDLE_VALUE) {
		printf("process snapshot failed with error code: %d", GetLastError());
		CloseHandle(hSnapShot);
		return 0;
	}

	while (Process32Next(hSnapShot, &pe32)) {
		if (strcmp(pe32.szExeFile, processName) == 0) {
			printf("process found: %s\n", pe32.szExeFile);

			HANDLE hOpen = OpenProcess(PROCESS_TERMINATE, FALSE, pe32.th32ProcessID); // For only terminate purpose I've picked up PROCESS_TERMINATE op
			if (hOpen == NULL) {
				// If there's no process found
				printf("there's no process found, error code: %d", GetLastError());
				CloseHandle(hSnapShot);
				CloseHandle(hOpen);
				return 0;
			}

			if (TerminateProcess(hOpen, 0) != 0) {
				printf("process was been terminated with pid: %d", pe32.th32ProcessID);
				CloseHandle(hOpen);
				CloseHandle(hSnapShot);
				return 0;
			}
			else {
				printf("can't terminate that process, error code: %d", GetLastError());
				CloseHandle(hOpen);
				CloseHandle(hSnapShot);
				return 0;
			}
		}
	}
	return 0;
}


int main(int argc, char** argv) {
	if (argv[1] == NULL) {
		printf("where is process name?");
		return 0;
	}
	FindProcessAndKill(argv[1]);
	return 0;
}