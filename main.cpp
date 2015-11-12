#include "main.h"
#include <cmath>
#include "rc.h"

int NumDialog::IDD(){
	return IDD_NUMBER; 
}

bool NumDialog::OnInitDialog(){
	return true;
}

bool NumDialog::OnOK(){
	return true;
}

void MainWindow::OnPaint(HDC hdc){
}

void MainWindow::OnCommand(int id){
	switch(id){
		case ID_COLOR: 
			break;
		case ID_NUMBER: 
			break;
		case ID_EXIT: 
			DestroyWindow(*this); 
			break;
	}
}

void MainWindow::OnDestroy(){
	::PostQuitMessage(0);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hp, LPSTR cmdLine, int nShow)
{
	Application app;
	MainWindow wnd;	
	wnd.Create(NULL, WS_OVERLAPPEDWINDOW | WS_VISIBLE, "NWP", 
		(int)LoadMenu(hInstance, MAKEINTRESOURCE(IDM_MAIN)));	
	return app.Run();
}

