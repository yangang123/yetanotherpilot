#include "wnd_install.h"
#include "resource.h"
#include "comm.h"

extern Comm test;

float matrix;
float throttle_idle;

HWND wnd;

int read_install()
{
	test.read_float("mat", &matrix);
	test.read_float("idle", &throttle_idle);

	// update UI
	// matrix
	HBITMAP bm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1));
	DWORD matrix_table[] = {IDC_RADIO_MATRIX0, IDC_RADIO_MATRIX1};
	CheckRadioButton(wnd, IDC_RADIO_MATRIX0, IDC_RADIO_MATRIX1, matrix_table[int(matrix)]);
	DWORD button_table[] = {IDC_MATRIX_0, IDC_MATRIX_1};
	for(int i=0; i<sizeof(button_table)/sizeof(button_table[0]); i++)
	{
		SendMessage(GetDlgItem(wnd, button_table[i]), BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)(i == int(matrix) ? bm : NULL));
	}


	// idle throtte
	DWORD matrix_table2[] = {IDC_IDLE_0, IDC_IDLE_1, IDC_IDLE_2, IDC_IDLE_3, IDC_IDLE_4};
	CheckRadioButton(wnd, IDC_IDLE_0, IDC_IDLE_4, matrix_table2[int(throttle_idle - 1144)/16]);



	return 0;
}


int write_install()
{
	test.write_float("mat", matrix);
	test.write_float("idle", throttle_idle);
	return read_install();
}

int install_OnEvent(int code, void *extra_data)
{
	if (code == WM_CONNECT)
		read_install();

	return 0;
}

INT_PTR CALLBACK WndProcInstall(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		wnd = hWnd;
		test.add_callback(install_OnEvent);
		break;

	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;

	case WM_COMMAND:
		{
			int id = LOWORD(wParam);
			bool down = false;
			if (id == IDC_MATRIX_0 || id == IDC_RADIO_MATRIX0)
			{
				matrix = 0;
				write_install();
			}
			else if (id == IDC_MATRIX_1 || id == IDC_RADIO_MATRIX1)
			{
				matrix = 1;
				write_install();
			}
			else if (id == IDC_IDLE_0)
			{
				throttle_idle = 1144;
				write_install();
			}
			else if (id == IDC_IDLE_1)
			{
				throttle_idle = 1160;
				write_install();
			}
			else if (id == IDC_IDLE_2)
			{
				throttle_idle = 1176;
				write_install();
			}
			else if (id == IDC_IDLE_3)
			{
				throttle_idle = 1192;
				write_install();
			}
			else if (id == IDC_IDLE_4)
			{
				throttle_idle = 1208;
				write_install();
			}
		}
		break;

	default:
		return FALSE;
	}
	return TRUE;
}