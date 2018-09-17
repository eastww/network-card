#include <windows.h> 
#include <tchar.h>    
#include <stdio.h> 
#include <iostream>
#include <string.h>
using namespace std;

//#pragma   comment(   linker,   "/subsystem:\ "windows\ "   /entry:\ "mainCRTStartup\ " "   ) 


//判断系统是64位还是32位？64位返回1，32位返回0 
int GetSystemBits(void)    
{       
	SYSTEM_INFO si;  
    // Copy the hardware information to the SYSTEM_INFO structure.  
    GetNativeSystemInfo(&si);  
    // Display the contents of the SYSTEM_INFO structure.  
    if (si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 || si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64)  
    {  
        return 1;  
    } else {  
        return 0;  
    }   
} 

//判断window系统的版本？0是window xp，1是window vista，2是window 8以后系统，3不是以上版本 
int GetSystemName(void)  
{  
    SYSTEM_INFO info;        //用SYSTEM_INFO结构判断64位AMD处理器   
    GetSystemInfo(&info);    //调用GetSystemInfo函数填充结构   
    OSVERSIONINFOEX os;   
    os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);     
  
    if(GetVersionEx((OSVERSIONINFO *)&os))  
    {   
        //下面根据版本信息判断操作系统名称   
        switch(os.dwMajorVersion)//判断主版本号  
        {  
        case 5:  
            switch(os.dwMinorVersion)   //再比较dwMinorVersion的值  
            {   
            case 1:
				return 0;//系统是Microsoft Windows XP，2001年8月发布  
                break;  
  
            case 2:  
                if(os.wProductType==VER_NT_WORKSTATION   
                    && info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)  
                    return 0;//系统是Microsoft Windows XP Professional x64 Edition
                break;  
            }  
            break;  
  
        case 6:  
            switch(os.dwMinorVersion)  
            {  
            case 1:  
                if(os.wProductType == VER_NT_WORKSTATION)   
                	return 1;//系统是Microsoft Windows 7  
                break;
			case 2:  
                return 2;//系统是Microsoft Windows 8之后版本  
                break;
            }  
            break;
		
		return 3;  
        }  
    }//if(GetVersionEx((OSVERSIONINFO *)&os))  
  
}        

    

int main( void )    
{
	int os_mark = GetSystemName();
	
	/*PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si)); // 初始内存
    ZeroMemory(&pi, sizeof(pi)); // 初始内存
    si.cb = sizeof(si);
	*/
	
	//_tprintf(TEXT("The process is running under.\n")); 
	
	string *error_message = (string *)_T("This driver is only applicable to Window XP, Window 7, Window 8, and Window 10. If you have any problems, please contact to the salesman. "); 
	
	if(os_mark == 0){ //window xp 
		if(GetSystemBits){//64位系统 
			//WinExec(".\\Win_XP_Driver\\Win64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win_XP_Driver\\Win64\\Setup.exe"), NULL, NULL, SW_HIDE);//请求管理员权限打开 	
		} else {
			//WinExec(".\\Win_XP_Driver\\Win32\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win_XP_Driver\\Win32\\Setup.exe"), NULL, NULL, SW_HIDE);
			
		} 
			
	} else if(os_mark == 1){ //window vista 
		if(GetSystemBits){//64位系统 
			//WinExec(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x64\\Setup.exe"), NULL, NULL, SW_HIDE); 	
		} else {
			//WinExec(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x32\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x32\\Setup.exe"), NULL, NULL, SW_HIDE);
		} 
			
	} else if(os_mark == 2){ //window vista 
		if(GetSystemBits){//64位系统 
			//WinExec(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe"), NULL, NULL, SW_HIDE);//请求管理员权限打开
			//_tprintf(TEXT("The process is running under 64.\n")); 
			//MessagBox(NULL,"Press OK to continue","Progrm Launched",MB_OK);
			//MessageBox( NULL , _T((const char*)error_message ), _T("error!") , MB_ICONINFORMATION|MB_YESNO);
			/*CreateProcess(_T(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe"), NULL,NULL, NULL, FALSE, 0, NULL,NULL, &si, &pi);
			CloseHandle(pi.hThread);
        	CloseHandle(pi.hProcess);
        	*/
		} else {
			//WinExec(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x32\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x32\\Setup.exe"), NULL, NULL, SW_HIDE); 
			//_tprintf(TEXT("The process is running under 32.\n")); 
		}
			
	} else if(os_mark == 3){
		MessageBox( NULL , _T((const char*)error_message ), _T("error!") , MB_ICONINFORMATION|MB_YESNO);
	}
/*	string *osname = (string *)_T("unknown OperatingSystem.");      
    if(IsWow64()){
		_tprintf(TEXT("The process is running under WOW64.\n"));
		
	}    
    else{
	_tprintf(TEXT("The process is not running under WOW64.\n")); 
	_tprintf(TEXT((const char*)osname));
	
	//WinExec("C:\\Program Files\\Keysight\\ADS2016_01\\bin\\ads.exe",SW_SHOW);
	//WinExec(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe",SW_SHOW); 
	}
*/	
    return 0;  
}  
