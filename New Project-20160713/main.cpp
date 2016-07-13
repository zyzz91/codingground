#include <Windows.h>
#include <iostream>

void pauseConsole(int sleepTime);	// prototype
void sleepAlert(void);

int main(int argc, char* argv[])
{
    SetConsoleTitleA(TEXT("Call of Duty 4 - No Recoil / No Spread"));

    byte NoSpread[] = {
        0x74,
        0x15
    };

    byte NoRecoil[] = {
        0x75,
        0x08
    };

	HWND hWnd = FindWindow(NULL, TEXT("Call of Duty 4"));

	if(hWnd == NULL)
	{
		std::cerr << "ERROR :: Cannot find window\n" << std::endl;
	}

	else
	{
		DWORD pId;
		GetWindowThreadProcessId(hWnd, &pId);
		HANDLE hProc = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, pId);

		if(!hProc)
		{
			std::cerr << "ERROR :: Cannot open process\n" << std::endl;
		}

		else
		{
            WriteProcessMemory(hProc, (void*)0x00416C7B, &NoSpread, 2, 0);
            WriteProcessMemory(hProc, (void*)0x0041A7BD, &NoRecoil, 2, 0);

            VirtualProtectEx(hProc, (void*)0x00416C7B, 2, 0x02, (DWORD*)&NoSpread);
            VirtualProtectEx(hProc, (void*)0x0041A7BD, 2, 0x02, (DWORD*)&NoRecoil);
		}
		CloseHandle(hProc);
	}
	pauseConsole(0);
	return 0;
}

void pauseConsole(int sleepTime)
{
    if(sleepTime == 0)
    {
        std::clog << "\nPress <Enter> to continue...";
        std::cin.clear();
        std::cin.ignore();
    }

	else
	{
	    Sleep(sleepTime);
	    std::clog << "\nPress <Enter> to continue...";
        std::cin.clear();
        std::cin.ignore();
	}
}

void sleepAlert(void)
{
    std::clog << "SUCCESS :: Process memory written\n\n" << std::endl;
    Sleep(60000);
}