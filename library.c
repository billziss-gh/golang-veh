#include <windows.h>

__declspec(dllexport)
VOID RaiseExcept(VOID)
{
    __try
    {
        RaiseException(42, 0, 0, 0);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
}

__declspec(dllexport)
VOID RaiseNoExcept(VOID)
{
    RaiseException(42, 0, 0, 0);
}

static DWORD WINAPI ThreadRaiser(PVOID Context)
{
    if (Context)
        RaiseExcept();
    else
        RaiseNoExcept();
    return 0;
}

static VOID ThreadRaiseXxx(BOOL Except)
{
    static int Dummy;
    HANDLE Thread = CreateThread(0, 0, ThreadRaiser, Except ? &Dummy : 0, 0, 0);
    if (0 != Thread)
    {
        WaitForSingleObject(Thread, INFINITE);
        CloseHandle(Thread);
    }
}

__declspec(dllexport)
VOID ThreadRaiseExcept(VOID)
{
    ThreadRaiseXxx(TRUE);
}

__declspec(dllexport)
VOID ThreadRaiseNoExcept(VOID)
{
    ThreadRaiseXxx(FALSE);
}

BOOL WINAPI DllMain(HINSTANCE Instance, DWORD Reason, PVOID Reserved)
{
    return TRUE;
}
