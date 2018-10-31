#include "ProcessWindow.h"

struct handle_data
{
    unsigned long procecss_id;
    HWND best_handle;
};

BOOL CALLBACK FindProcessWnd(HWND hWnd, LPARAM lparam)
{
   handle_data& data = *(handle_data*)lparam;
   DWORD procID = 0;
   GetWindowThreadProcessId(hWnd, &procID);
   //procID等于参数ID
   if(procID == data.procecss_id && 0 != data.procecss_id)
   {
       if((HWND)0 == GetWindow(hWnd, GW_OWNER)
               && IsWindowVisible(hWnd))
       {
           data.best_handle = hWnd;
           return FALSE;
       }
   }
   data.best_handle = NULL;
   return TRUE;
}

HWND FindMyWindows(const std::string processName, int& pid)
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    //将从hSnapShot中抽取数据到一个PROCESSENTRY32结构中（存储快照结构体）
    PROCESSENTRY32* processInfo = new PROCESSENTRY32;
    //必须设置dwSize值
    processInfo->dwSize = sizeof(PROCESSENTRY32);
    int index = 0;
    pid = -1;
    while(FALSE != Process32Next(hSnapShot, processInfo))
    {
        index++;
        int size = WideCharToMultiByte(CP_ACP, 0, processInfo->szExeFile, -1,NULL,0,NULL,NULL);
        char*ch = new char[size+1];
        //取进程名然后对比
        if(WideCharToMultiByte(CP_ACP, 0, processInfo->szExeFile, -1,ch,size,NULL,NULL))
        {
            if(strstr(ch, processName.c_str()))
            {
                pid = processInfo->th32ProcessID;
                handle_data data;
                data.procecss_id = pid;
                data.best_handle = 0;
                BOOL bRet = EnumWindows(FindProcessWnd, (LPARAM)&data);
                if(FALSE == bRet)
                    return data.best_handle;
            }
        }
    }
    return NULL;
}
