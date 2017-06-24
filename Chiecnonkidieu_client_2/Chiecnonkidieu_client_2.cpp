// Chiecnonkidieu_client_2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Chiecnonkidieu_client_2.h"
#include <iostream>
#include "stdafx.h"
#include <afxsock.h>
#include <ctime>
#include <string>
#include <string.h>
#include <cstdlib>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
struct OChu
{
	char goiy[30];
	int sokytu;
	int thutudoan;
	int n_thamgia;
	int soluot;
};
struct TTDoan
{
	//int vitri;
	int diem;
	char kq[20];
};


int KiemTraHopLe(char s[]) {
	int nickname_length = strlen(s);

	//48-57 (0-9)
	//65-90 (A-Z)
	//97-122 (a-z)

	for (int i = 0; i < nickname_length; i++)
	{
		if ((s[i] >= 48 && s[i] <= 57) || (s[i] >= 65 && s[i] <= 90) || (s[i] >= 97 && s[i] <= 122))
		{
			continue;
		}
		else
		{
			return 0;
		}

	}
	return 1;
}



// The one and only application object

CWinApp theApp;

using namespace std;

int main()
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(nullptr);

	if (hModule != nullptr)
	{
		// initialize MFC and print and error on failure
		if (!AfxWinInit(hModule, nullptr, ::GetCommandLine(), 0))
		{
			// TODO: change error code to suit your needs
			wprintf(L"Fatal Error: MFC initialization failed\n");
			nRetCode = 1;
		}
		else
		{
			// TODO: code your application's behavior here.
			CSocket client;

			AfxSocketInit();
			client.Create();

			if (client.Connect(_T("192.168.1.81"), 1234))
			{

				// Nhan Ket Noi Tu Server
				cout << "Da ket noi den server!";
				//////////////////////////
				char nickName[100];
				while (1)
				{
					cout << "\nNhap Nickname De Choi Game: ";
					//cin.ignore(1);
					gets_s(nickName);
					if (KiemTraHopLe(nickName))
					{
						client.Send(nickName, strlen(nickName), 0);
						break;
					}
					else
						cout << "Chi Cho phep Nhap ki tu trong khoang [a-z][A-Z][0-9]" << endl;
				}


				/*kiem tra trung*/
				bool is_trung;
				while (1)
				{
					client.Receive(&is_trung, sizeof(bool), 0);
					if (is_trung)
					{
						cout << "Nickname da co nguoi dang ki, Moi nhap lai NickName ! " << endl;
						while (1)
						{
							printf("\nNhap Nickname De Choi Game: ");
							gets_s(nickName);
							if (KiemTraHopLe(nickName))
							{
								client.Send(nickName, strlen(nickName), 0);
								break;
							}
							else
							{
								cout << "Chi Cho phep Nhap ki tu trong khoang [a-z][A-Z][0-9]" << endl;
							}
						}
					}
					else
					{
						cout << "Ban dang ki nickname thanh cong ! " << endl;

						cout << endl;
						break;
					}
				}
				/*Ket thuc kiem tra trung*/
			BD:
				cout << "-----------------------------------------------------------" << endl;
				cout << "*******************DANG CHO SERVER XU LY*******************" << endl;
				cout << "-----------------------------------------------------------" << endl;
				/*Nhan thong tin ve nguoi choi va o chu*/
				OChu ochu;
				client.Receive(&ochu, sizeof(ochu), 0);
				cout << "-----------------------------------------------------------" << endl;
				cout << "So nguoi tham gia: " << ochu.n_thamgia << endl;
				cout << "Thu tu doan cua " << nickName << " la: " << ochu.thutudoan << endl;
				cout << "So ky tu o chu: " << ochu.sokytu << endl;
				cout << "So luot doan toi da cua ban: " << ochu.soluot << endl;
				cout << "Goi Y: " << ochu.goiy << endl;
				cout << "-----------------------------------------------------------" << endl;
				/*****************************************************************************/

				int luotchoi = 1;
				/*Bat dau luot choi game*/
				while (luotchoi <= ochu.soluot)
				{
					char thongbao[100];
					int len = client.Receive(thongbao, 100, 0);

					// O chu da duoc doan 
					if (thongbao[0] == 'E')
					{
						cout << "-----------------------------------------------------------" << endl;
						cout << "\tO CHU DA DUOC GIAI RA !" << endl;
						cout << "-----------------------------------------------------------" << endl;
						break;
					}

					// Co 1 nguoi choi da quay 0 diem
					if (thongbao[0] == 'O')
					{
						for (int k = 1; k < len; k++)
							cout << thongbao[k];
						cout << endl;
						cout << "-----------------------------------------------------------" << endl;
					}

					// Co 1 nguoi choi da doan dung o chu
					else if (thongbao[0] == 'F')
					{
						cout << endl;
						cout << "-----------------------------------------------------------" << endl;
						cout << "DA TIM RA NGUOI DOAN DUNG O CHU" << endl;
						for (int z = 1; z < len; z++)
							cout << thongbao[z];
						cout << endl;
						cout << "-----------------------------------------------------------" << endl;
						break;
					}

					// Den luot doan o chu
					else
					{
						cout << thongbao << endl;
						cout << "chuan bi quay diem..." << endl;
						cout << "-----------------------------------------------------------" << endl;
						cout << "*******************DANG CHO SERVER XU LY*******************" << endl;
						cout << "-----------------------------------------------------------" << endl;
						cout << endl;
						srand(unsigned(time(0)));
						int ran_diem = rand() % 101 + 0;
						TTDoan doan;
						doan.diem = ran_diem;
						//doan.diem = 0;
						if (doan.diem == 0)
							client.Send(&doan, sizeof(TTDoan), 0);
						else
						{
							int lc;
							char kt[20];
							cout << "Ban duoc " << doan.diem << " diem !" << endl;
							cout << "Moi lua chon cach tra loi" << endl;
							cout << "\t1:Doan 1 ky tu" << endl;
							cout << "\t2:Doan ca o chu" << endl;
							cout << "Moi ban chon: ";
							cin >> lc;
							int checkLC = 0;
							do
							{
								if (lc == 1)
								{
									checkLC = 1;
									cout << "Moi ban nhap chu cai: ";
									cin.ignore();
									gets_s(kt);
									kt[1] = '\0';
									strcpy(doan.kq, kt);

								}
								else if (lc == 2)
								{
									checkLC = 1;
									cout << "Moi ban nhap o chu ban doan: ";
									cin.ignore();
									gets_s(kt);
									int len = strlen(kt);
									while (1)
									{
										if (len == 1)
										{
											cout << "KHONG DUOC PHEP NHAP 1 CHU CAI TRONG TRUONG HOP NAY !" << endl;
											cout << "MOI BAN NHAP LAI: "; gets_s(kt);
											len = strlen(kt);
										}
										else
										{
											break;
										}
									}
									kt[ochu.sokytu] = '\0';
									strcpy(doan.kq, kt);
								}
								else
								{
									cout << "Lua chon cua ban khong ton tai !" << endl;
									cout << "Moi Ban Nhap lai: ";
									cin >> lc;
								}
							}
							while (checkLC == 0);


							client.Send(&doan, sizeof(TTDoan), 0);
							cout << "-----------------------------------------------------------" << endl;
							cout << "*******************DANG CHO SERVER XU LY*******************" << endl;
							cout << "-----------------------------------------------------------" << endl;
							cout << endl;
							char NhanKQ[50];
							int len = client.Receive(NhanKQ, 50, 0);
							NhanKQ[len] = '\0';
							cout << NhanKQ << endl;
							cout << "-----------------------------------------------------------" << endl;
							cout << "\tKET THUC LUOT CHOI THU " << luotchoi << endl;
							luotchoi++;
							cout << "-----------------------------------------------------------" << endl;
						}
					}
					// ket thuc 1 luot doan o chu
				}
				if (luotchoi == ochu.soluot + 1)
				{
					cout << endl;
					cout << "-----------------------------------------------------------" << endl;
					cout << "\t\t" << nickName << " Da Het Luot Choi" << endl;
					cout << "-----------------------------------------------------------" << endl;
				}
				cout << "-----------------------------------------------------------" << endl;
				cout << "*******************DANG CHO SERVER XU LY*******************" << endl;
				cout << "-----------------------------------------------------------" << endl;
				cout << endl;
				char DiemF[500];
				int len = client.Receive(DiemF, sizeof(DiemF), 0);
				DiemF[len] = '\0';
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				cout << endl;
				cout << "DANH SACH DIEM NGUOI CHOI !" << endl;
				cout << DiemF << endl;
				cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
				/*Ket thuc luot choi game*/
				char TBChoiLai[60];
				int length = client.Receive(TBChoiLai, sizeof(TBChoiLai), 0);
				TBChoiLai[length] = '\0';
				cout << TBChoiLai << endl;
				goto BD;
				system("pause");

				//client.Close();
			}

			else
			{
				// TODO: change error code to suit your needs
				wprintf(L"Fatal Error: GetModuleHandle failed\n");
				nRetCode = 1;
			}
			return nRetCode;
		}
	}
}