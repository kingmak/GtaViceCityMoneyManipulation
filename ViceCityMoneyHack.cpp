#include <iostream>
#include <windows.h>

using namespace std;

void readFromMem(DWORD address, LPCSTR windowName);
void writeToMem(DWORD address, LPCSTR windowName, long int newValue);

int main()
{
	system("color 0a");
	system("title Vice City Money Hack by KingMak");
	cout << "Vice City Money Hack by KingMak" << endl << endl;
	
	DWORD address = 0x94ADC8;
	LPCSTR windowName = "GTA: Vice City";
	
	cout << "current money amount = $";
	readFromMem(address, windowName);
	
	char result;
	cout << "change money amount? [y/n] = ";
	cin >> result;
	
	long int newMoney;
	if (result == 'y' || result == 'Y')
	{
		cout << endl << "Enter new money amount = ";
		cin >> newMoney;
		
		writeToMem(address, windowName, newMoney);
	}
	
	cout << endl;
	system("pause");
	return 0;
}

void readFromMem(DWORD address, LPCSTR windowName)
{
	long int value;
	HWND windowHandle = FindWindow(0, windowName);
	 
	if (! windowHandle)
	{
		cout << "error, can't find window" << endl;
	}
	
	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_VM_READ, FALSE, processId);
		
		if (! processHandle)
		{
			cout << "error, can't find process" << endl;
		}
		 
		else
		{
			int status = ReadProcessMemory(processHandle, (LPVOID) address, &value, sizeof(value), 0); //LPVOID = void *
			if (status > 0)
			{
				cout << value << endl;
			}
			
			else 
			{
				cout << "failure" << endl;
			}	
			
			CloseHandle(processHandle);	
			return;
								
		}
	}
}

void writeToMem(DWORD address, LPCSTR windowName, long int newValue)
{		
	HWND windowHandle = FindWindow(0, windowName);
	
	if (! windowHandle)
	{
		cout << "error, can't find window" << endl;
	}
	
	else
	{
		DWORD processId;
		GetWindowThreadProcessId(windowHandle, &processId);
		HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, processId);
		
		if (! processHandle)
		{
			cout << "error, can't find process" << endl;
		}
		
		else
		{
			int status = WriteProcessMemory(processHandle, (LPVOID) address, &newValue, (DWORD) sizeof(newValue), NULL);
			if (status > 0)
			{
				cout << "Success" << endl;
			}
			
			else 
			{
				cout << "Failure" << endl;
			}
		}
		
		CloseHandle(processHandle);
		return;
	}
}
