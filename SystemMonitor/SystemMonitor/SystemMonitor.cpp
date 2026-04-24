#include <iostream>
#include <Windows.h>
#include <filesystem>
#include <thread>
#include <chrono>

namespace fs = std::filesystem;
using namespace std;

void printMemoryStats() {
	MEMORYSTATUSEX memInfo;
	memInfo.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&memInfo);

	long long totalPhysMem = memInfo.ullTotalPhys / 1024 / 1024 / 1024;
	long long physMemUsed = (memInfo.ullTotalPhys - memInfo.ullAvailPhys) / 1024 / 1024 / 1024;
	int memPercent = memInfo.dwMemoryLoad;

	fs::space_info cd = fs::space("C:\\");
	long long totalDisk = cd.capacity / 1024 / 1024 / 1024;
	long long freeDisk = cd.available / 1024 / 1024 / 1024;

	cout << "\033[H";
	cout << "loading memory: " << memPercent << "%\n";
	cout << "used: " << physMemUsed << "GB from " << totalPhysMem << "GB\n";
	cout << "disk " << totalDisk - freeDisk << "GB from " << totalDisk << "GB\n";
}

int main() {
	while (true) {
		printMemoryStats();
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}