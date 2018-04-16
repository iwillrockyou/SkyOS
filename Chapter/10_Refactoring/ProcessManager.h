#pragma once
#include "VirtualMemoryManager.h"
#include "SkyStruct.h"
#include "ProcessUtil.h"
#include "List.h"
#include "PEImage.h"
#include "Process.h"
#include "Thread.h"
#include "fileio.h"

class Process;
class Thread;

#define PROC_INVALID_ID -1

class ProcessManager
{

public:
	ProcessManager();
	virtual ~ProcessManager();

	typedef std::map<int, Process*> ProcessList;
	typedef std::list<Thread*> TaskList;
		
	Process* GetCurrentProcess();	

	ProcessList* GetProcessList() { return &m_processList;}
	int GetNextProcessId() { return m_nextProcessId++; }

	static ProcessManager* GetInstance()
	{		
		if (m_processManager == nullptr)
			m_processManager = new ProcessManager();

		return m_processManager;
	}
		
	Process* CreateKernelProcessFromMemory(const char* appName, LPTHREAD_START_ROUTINE lpStartAddress, void* param);
	Process* CreateProcessFromMemory(const char* appName, LPTHREAD_START_ROUTINE lpStartAddress, void* param);
	
	Process* CreateProcessFromFile(char* appName, UINT32 processType);	
	Thread* CreateThread(Process* pProcess, FILE* pFile, LPVOID param);
	Thread* CreateThread(Process* pProcess, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID param);

	bool AddProcess(Process* pProcess);
	Process* FindProcess(int processId);

	bool RemoveTerminatedProcess();
	bool RemoveFromTaskList(Process* pProcess);
	bool DestroyProcess(Process* pProcess);
	bool DestroyKernelProcess(Process* pProcess);
	bool ReleaseThreadContext(Process* pProcess);

	TaskList* GetTaskList() { return &m_taskList; }

//Page Directory Mapping
	PageDirectory* MapKernelSpace();
	//void MapSysAPIAddress(PageDirectory* dir);

private:	

private:
	static ProcessManager* m_processManager;

	int m_nextProcessId;
	int m_nextThreadId;

	ProcessList m_processList;
	TaskList m_taskList;
	TaskList m_terminatedTaskList;
};