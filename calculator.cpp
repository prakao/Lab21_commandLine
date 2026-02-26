#include <windows.h>
#include<cstdlib>
#include<stdio.h>

HWND textfield,TxBox1,TxBox2,but1,but2,but3,but4;
char text1[30];
char text2[30];
/* This is where all the input to the window goes to */
LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	switch(Message) {
		
		/* Upon destruction, tell the main thread to stop */
		case WM_CREATE:
			textfield=CreateWindow(TEXT("STATIC"),TEXT("Please input two numbers"),WS_VISIBLE|WS_CHILD|WS_BORDER,20,20,200,25,hwnd,NULL,NULL,NULL);
			
			TxBox1=CreateWindow(TEXT("EDIT"),
								TEXT(""),
								WS_VISIBLE|WS_CHILD|WS_BORDER,
								35,55,160,25,
								hwnd,NULL,NULL,NULL);

			TxBox2=CreateWindow(TEXT("EDIT"),
								TEXT(""),
								WS_VISIBLE|WS_CHILD|WS_BORDER,
								35,90,160,25,
								hwnd,NULL,NULL,NULL);

			but1=CreateWindow(TEXT("BUTTON"),
							  TEXT("+"),
							  WS_VISIBLE|WS_CHILD|WS_BORDER,
							  35,130,25,25,
							  hwnd,(HMENU)1,NULL,NULL);

			but2=CreateWindow(TEXT("BUTTON"),
							  TEXT("-"),
							  WS_VISIBLE|WS_CHILD|WS_BORDER,
							  80,130,25,25,
							  hwnd,(HMENU)2,NULL,NULL);
							  
			but3=CreateWindow(TEXT("BUTTON"),
							  TEXT("*"),
							  WS_VISIBLE|WS_CHILD|WS_BORDER,
							  125,130,25,25,
							  hwnd,(HMENU)3,NULL,NULL);	
							  
			but4=CreateWindow(TEXT("BUTTON"),
							  TEXT("/"),
							  WS_VISIBLE|WS_CHILD|WS_BORDER,
							  170,130,25,25,
							  hwnd,(HMENU)4,NULL,NULL);				  
			
			break;

		case WM_COMMAND:

			double num1,num2,result;
			char tempo[100];

			GetWindowTextA(TxBox1,text1,30); //ดึงข้อความจาก TextBox ใช้กับstring แบบansi
			GetWindowTextA(TxBox2,text2,30); //GetWindowText จะเป็นตัวเลือกให้ว่าจะใช้แบบansiหรือunicodeจะดูจากการตั้งค่าprojectตอนcompile

			num1=atof(text1);
			num2=atof(text2);

			switch (LOWORD(wParam))
			{
				case 1:
					result=num1+num2;
					sprintf(tempo,"%f",result); //แปลงค่าที่คำนวณได้ ให้เป็นข้อความ แปลงresultที่ให้เป็นข้อมูลทศนิยม(%f)ละเก็บไว้ในtempo
					MessageBoxA(hwnd,tempo,"Result",MB_OK);//แสดงกล่องข้อความ hwnd=บอกว่ากล่องนี้เป็นของหน้าต่างหลัก 
					break;									//tempo=ข้อความที่จะแสดง ชื่อหน้าต่าง=Result MB_OK=มีปุ่มok

				case 2:
					result=num1-num2;
					sprintf(tempo,"%f",result);
					MessageBoxA(hwnd,tempo,"Result",MB_OK);
					break;	
				
				case 3:
					result=num1*num2;
					sprintf(tempo,"%f",result);
					MessageBoxA(hwnd,tempo,"Result",MB_OK);
					break;	

				case 4:
					if(num2==0){
						MessageBoxA(hwnd,"CANNOT DIVIDE BY ZERO","ERROR",MB_OK);
					}else{
						result=num1/num2;
						sprintf(tempo,"%f",result);
						MessageBoxA(hwnd,tempo,"Result",MB_OK);
					}
					break;		
			}
			break;
		
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

/* The 'main' function of Win32 GUI programs: this is where execution starts */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize	 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor	 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = CreateSolidBrush(RGB(255,62,155));
	wc.lpszClassName = TEXT("WindowClass");
	wc.hIcon	 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
	wc.hIconSm	 = LoadIcon(NULL, IDI_APPLICATION); /* use the name "A" to use the project icon */

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL,TEXT("Window Registration Failed!"),TEXT("Error!"),MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,TEXT("WindowClass"),TEXT("My Calculator"),WS_SYSMENU|WS_VISIBLE,//ฟิคขขนาดหน้าจอ
		CW_USEDEFAULT, /* x */ 
		CW_USEDEFAULT, /* y */
		250, /* width */
		200, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, TEXT("Window Creation Failed!"),TEXT("Error!"),MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}

	ShowWindow(hwnd,nCmdShow); //showหน้าต่างที่สร้าง nCmdShow=รูปแบบการแสดงหน้าต่าง
	UpdateWindow(hwnd); //สั่งให้windowวาดgui ex.ปุ่ม background
	/*
		This is the heart of our program where all input is processed and 
		sent to WndProc. Note that GetMessage blocks code flow until it receives something, so
		this loop will not produce unreasonably high CPU usage
	*/
	while(GetMessage(&msg, NULL, 0, 0) > 0) { /* If no error is received... */ //ถ้าuserไม่ได้กดปุ่มหรือออกโปรแกรมจะเข้าไปทำตามคำสั่งด้านล่าง
		TranslateMessage(&msg); /* Translate key codes to chars if present */
		DispatchMessage(&msg); /* Send it to WndProc */
	}
	return msg.wParam;
}
