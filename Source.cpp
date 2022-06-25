#include <iostream>
#include <Windows.h>

int Wait()
{
	char a;
	printf("Any: ");
	std::cin >> a;
	return 0;
}


int main() {

	DWORD ProcId = 55;
	std::string dllName = "Ñ:";

	std::cout << "id: " << std::endl;
	std::cin >> ProcId;

	HANDLE OpendProcces = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcId);
	if (OpendProcces == NULL) {
		 return Wait();
	}

	HMODULE KernelModule = GetModuleHandleW(L"Kernel32.dll");
	if (KernelModule == NULL) {
		return Wait();
	}

	LPVOID loadLib = GetProcAddress(KernelModule, "Load lib");
	if (loadLib == NULL) {
		return Wait();
	}

	LPVOID ArgLoadLib = (LPVOID)VirtualAllocEx(OpendProcces, NULL, dllName.size(), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	const char* dl = dllName.c_str();

	int CountWrite = WriteProcessMemory(OpendProcces, ArgLoadLib, dl, dllName.size(), NULL);
	if (CountWrite == NULL) {
		return Wait();
	}

	HANDLE ThreadId = CreateRemoteThread(OpendProcces, NULL, 0, (LPTHREAD_START_ROUTINE)loadLib, ArgLoadLib, NULL, NULL);
	if (ThreadId == NULL) {
		return Wait();
	}
	else {
		std::cout << "DLL INJECTED" << std::endl;
	}

	CloseHandle(OpendProcces);
	

}

