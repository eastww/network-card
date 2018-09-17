#include <windows.h> 
#include <tchar.h>    
#include <stdio.h> 
#include <iostream>
#include <string.h>
using namespace std;

//#pragma   comment(   linker,   "/subsystem:\ "windows\ "   /entry:\ "mainCRTStartup\ " "   ) 


//�ж�ϵͳ��64λ����32λ��64λ����1��32λ����0 
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

//�ж�windowϵͳ�İ汾��0��window xp��1��window vista��2��window 8�Ժ�ϵͳ��3�������ϰ汾 
int GetSystemName(void)  
{  
    SYSTEM_INFO info;        //��SYSTEM_INFO�ṹ�ж�64λAMD������   
    GetSystemInfo(&info);    //����GetSystemInfo�������ṹ   
    OSVERSIONINFOEX os;   
    os.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);     
  
    if(GetVersionEx((OSVERSIONINFO *)&os))  
    {   
        //������ݰ汾��Ϣ�жϲ���ϵͳ����   
        switch(os.dwMajorVersion)//�ж����汾��  
        {  
        case 5:  
            switch(os.dwMinorVersion)   //�ٱȽ�dwMinorVersion��ֵ  
            {   
            case 1:
				return 0;//ϵͳ��Microsoft Windows XP��2001��8�·���  
                break;  
  
            case 2:  
                if(os.wProductType==VER_NT_WORKSTATION   
                    && info.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)  
                    return 0;//ϵͳ��Microsoft Windows XP Professional x64 Edition
                break;  
            }  
            break;  
  
        case 6:  
            switch(os.dwMinorVersion)  
            {  
            case 1:  
                if(os.wProductType == VER_NT_WORKSTATION)   
                	return 1;//ϵͳ��Microsoft Windows 7  
                break;
			case 2:  
                return 2;//ϵͳ��Microsoft Windows 8֮��汾  
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
    ZeroMemory(&si, sizeof(si)); // ��ʼ�ڴ�
    ZeroMemory(&pi, sizeof(pi)); // ��ʼ�ڴ�
    si.cb = sizeof(si);
	*/
	
	//_tprintf(TEXT("The process is running under.\n")); 
	
	string *error_message = (string *)_T("This driver is only applicable to Window XP, Window 7, Window 8, and Window 10. If you have any problems, please contact to the salesman. "); 
	
	if(os_mark == 0){ //window xp 
		if(GetSystemBits){//64λϵͳ 
			//WinExec(".\\Win_XP_Driver\\Win64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win_XP_Driver\\Win64\\Setup.exe"), NULL, NULL, SW_HIDE);//�������ԱȨ�޴� 	
		} else {
			//WinExec(".\\Win_XP_Driver\\Win32\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win_XP_Driver\\Win32\\Setup.exe"), NULL, NULL, SW_HIDE);
			
		} 
			
	} else if(os_mark == 1){ //window vista 
		if(GetSystemBits){//64λϵͳ 
			//WinExec(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x64\\Setup.exe"), NULL, NULL, SW_HIDE); 	
		} else {
			//WinExec(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x32\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win7_Vista_Driver\\BTW_6.5.1.6930_win7_vista_x32\\Setup.exe"), NULL, NULL, SW_HIDE);
		} 
			
	} else if(os_mark == 2){ //window vista 
		if(GetSystemBits){//64λϵͳ 
			//WinExec(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe",SW_SHOW);
			ShellExecute(NULL, _T("runas"), _T(".\\Win8_Win10_Driver\\BTW_12.0.1.940_win8_10_x64\\Setup.exe"), NULL, NULL, SW_HIDE);//�������ԱȨ�޴�
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
