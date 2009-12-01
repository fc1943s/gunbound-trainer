#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UFormMain.h"
#include "Stew.cpp"
#pragma package(smart_init)
#pragma resource "*.dfm"

TFormMain* FormMain;

UnicodeString GBPath;

bool Deploy = false;

const UnicodeString Title = "Hot Gunbound Tools", Version = "1.0", ForumLink = "http://hotcheats.org/", RegKey = "software\\Hot Cheats\\" + Title + "\\" + Version;

const int GodModeOpcodes = 0x0090E244, DeathShotOpcodes = 0x0090E23C, PowerUserOpcodes[60] =
{
	0x00636D30, 0x00636D31, 0x00636D32, 0x00636D33, 0x00636D34, 0x00636D35, 0x00636D36, 0x00636D37, 0x00636D38, 0x00636D39, 0x00636D3A, 0x00636D3B, 0x00636D3C,
	0x00636D3D, 0x00636D3E, 0x00636D3F, 0x0090DFE0, 0x0090DFF0, 0x0090E000, 0x0090E010, 0x0090DFE1, 0x0090DFE2, 0x0090DFE3, 0x0090DFE4, 0x0090DFE5, 0x0090DFE6,
	0x0090DFE7, 0x0090DF70, 0x0090DF80, 0x0090DF90, 0x0090DFA0, 0x0090DF71, 0x0090DF72, 0x0090DF73, 0x0090DF74, 0x0090DF75, 0x0090DF76, 0x0090DF77, 0x0090DFE8,
	0x0090DFF8, 0x0090E008, 0x0090E018, 0x0090DFE9, 0x0090DFEA, 0x0090DFEB, 0x0090DFEC, 0x0090DFED, 0x0090DFEE, 0x0090DFEF, 0x0090DF78, 0x0090DF88, 0x0090DF98,
	0x0090DFA8, 0x0090DF79, 0x0090DF7A, 0x0090DF7B, 0x0090DF7C, 0x0090DF7D, 0x0090DF7E, 0x0090DF7F
}, InstantVictoryOpcodes[16] =
{
	0x0090ECAC, 0x0090ECBC, 0x0090ECCC, 0x0090ECDC, 0x0090ECB4, 0x0090ECC4, 0x0090ECD4, 0x0090ECE4, 0x0090ED1C, 0x0090ED2C, 0x0090ED3C, 0x0090ED4C, 0x0090ED24,
	0x0090ED34, 0x0090ED44, 0x0090ED54
}, GoldOpcodes[32] =
{
	0x0090EBA0, 0x0090EBA1, 0x0090EBA2, 0x0090EBA3, 0x0090EBA4, 0x0090EBA5, 0x0090EBA6, 0x0090EBA7, 0x0090EBA8, 0x0090EBA9, 0x0090EBAA, 0x0090EBAB, 0x0090EBAC,
	0x0090EBAD, 0x0090EBAE, 0x0090EBAF, 0x0090EC20, 0x0090EC21, 0x0090EC22, 0x0090EC23, 0x0090EC24, 0x0090EC25, 0x0090EC26, 0x0090EC27, 0x0090EC28, 0x0090EC29,
	0x0090EC2A, 0x0090EC2B, 0x0090EC2C, 0x0090EC2D, 0x0090EC2E, 0x0090EC2F
}, CopyGPOpcodes[64] =
{
	0x0090EBD0, 0x0090EBD1, 0x0090EBD2, 0x0090EBD3, 0x0090EBD4, 0x0090EBD5, 0x0090EBD6, 0x0090EBD7, 0x0090EBD8, 0x0090EBD9, 0x0090EBDA, 0x0090EBDB, 0x0090EBDC,
	0x0090EBDD, 0x0090EBDE, 0x0090EBDF, 0x0090EBE0, 0x0090EBE1, 0x0090EBE2, 0x0090EBE3, 0x0090EBE4, 0x0090EBE5, 0x0090EBE6, 0x0090EBE7, 0x0090EBE8, 0x0090EBE9,
	0x0090EBEA, 0x0090EBEB, 0x0090EBEC, 0x0090EBED, 0x0090EBEE, 0x0090EBEF, 0x0090EBF0, 0x0090EBF1, 0x0090EBF2, 0x0090EBF3, 0x0090EBF4, 0x0090EBF5, 0x0090EBF6,
	0x0090EBF7, 0x0090EBF8, 0x0090EBF9, 0x0090EBFA, 0x0090EBFB, 0x0090EBFC, 0x0090EBFD, 0x0090EBFE, 0x0090EBFF, 0x0090EC00, 0x0090EC01, 0x0090EC02, 0x0090EC03,
	0x0090EC04, 0x0090EC05, 0x0090EC06, 0x0090EC07, 0x0090EC08, 0x0090EC09, 0x0090EC0A, 0x0090EC0B, 0x0090EC0C, 0x0090EC0D, 0x0090EC0E, 0x0090EC0F
};

__fastcall TFormMain::TFormMain(TComponent* Owner) : TForm(Owner)
{
}

void __fastcall TFormMain::FormCreate(TObject* Sender)
{
	if (!Stew::_CreateMutex(Title + Version))
	{
		Application->Terminate();
	}
	Application->Title = Title + " " + Version;
	Caption = Title + " " + Version;
	lblTitle->Caption = Title + " " + Version;
	lblForumLink->Caption = ForumLink;
	lblUpdates->Caption = "Atualizações em " + ForumLink;

	UnicodeString configs = Stew::_RegReadString(HKEY_LOCAL_MACHINE, RegKey, "Config");
	GBPath = Stew::_RegReadString(HKEY_LOCAL_MACHINE, "SOFTWARE\\SoftNyx\\GunBoundWC\\", "Location");
	try
	{
		chbPowerUser->Checked = StrToBool(configs[1]);
		chbDeathShot->Checked = StrToBool(configs[2]);
		chbGodMode->Checked = StrToBool(configs[3]);
		chbInstantVictory->Checked = StrToBool(configs[4]);
		chbCopyGP->Checked = StrToBool(configs[5]);
	}
	catch(...)
	{
	}

	Stew::_FormPosition(this, __Center, __Center);
}

void __fastcall TFormMain::OpenForum(TObject* Sender)
{
	ShellExecuteW(Handle, L"open", ForumLink.c_str(), NULL, NULL, 1);
}

void __fastcall TFormMain::FormClose(TObject* Sender, TCloseAction& Action)
{
	if (Deploy)
	{
		OpenForum(this);
	}
}

void __fastcall TFormMain::btnRunGBClick(TObject* Sender)
{
	WinExec(UnicodeString(GBPath + "NyxLauncher.exe").t_str(), 1);
}

void TFormMain::SaveRegConfig()
{
	Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "Config", IntToStr((int)chbPowerUser->Checked) + IntToStr((int)chbDeathShot->Checked) + IntToStr
		((int)chbGodMode->Checked) + IntToStr((int)chbInstantVictory->Checked) + IntToStr((int)chbCopyGP->Checked), true, true);
}

void __fastcall TFormMain::chbHackClick(TObject* Sender)
{
	SaveRegConfig();
}

void __fastcall TFormMain::tmrMainTimer(TObject* Sender)
{
	bool LoginOpen = Stew::_GetPID("NyxLauncher.exe") != 0;
	bool GBOpen = Stew::_GetPID("GunBound.gme") != 0;
	HANDLE GBHandle;

	if (!GBOpen)
	{
		if (!LoginOpen)
		{
			if (FileExists(GBPath + "NyxLauncher.exe"))
			{
				btnRunGB->Enabled = true;
			}
			lblStatus->Caption = "Status: Aguardando Gunbound";
		}
		else
		{
			btnRunGB->Enabled = false;
			lblStatus->Caption = "Status: Aguardando Login";
		}
	}
	else
	{
		if (!LoginOpen)
		{
			lblStatus->Caption = "Status: Ativando Hacks";
			chbPowerUser->Enabled = false;
			chbDeathShot->Enabled = false;
			chbGodMode->Enabled = false;
			chbInstantVictory->Enabled = false;
			chbCopyGP->Enabled = false;
			Stew::_MemoryManagement(Stew::_GetPID("GunBound.gme"), GBHandle);

			int aux = 0;

			ReadProcessMemory(GBHandle, (Pointer)DeathShotOpcodes, &aux, 1, 0);

			if (aux != 0)
			{
				int write = 0;
				if (chbPowerUser->Checked)
				{
					for (UINT i = 0; i < sizeof(PowerUserOpcodes) / sizeof(PowerUserOpcodes[0]); i++)
					{
						WriteProcessMemory(GBHandle, (Pointer)PowerUserOpcodes[i], &write, 1, 0);
					}
				}
				if (chbDeathShot->Checked)
				{
					WriteProcessMemory(GBHandle, (Pointer)DeathShotOpcodes, &write, 1, 0);
				}
				if (chbGodMode->Checked)
				{
					WriteProcessMemory(GBHandle, (Pointer)GodModeOpcodes, &write, 1, 0);
				}
				if (chbInstantVictory->Checked)
				{
					for (UINT i = 0; i < sizeof(InstantVictoryOpcodes) / sizeof(InstantVictoryOpcodes[0]); i++)
					{
						WriteProcessMemory(GBHandle, (Pointer)InstantVictoryOpcodes[i], &write, 1, 0);
					}
				}
				if (chbCopyGP->Checked)
				{
					for (UINT i = 0; i < sizeof(CopyGPOpcodes) / sizeof(CopyGPOpcodes[0]); i++)
					{
						WriteProcessMemory(GBHandle, (Pointer)CopyGPOpcodes[i], &write, 1, 0);
					}
				}
				CloseHandle(GBHandle);
				if (Deploy)
				{
					OpenForum(this);
				}
				Application->Terminate();
			}
			CloseHandle(GBHandle);
		}
		else
		{
			chbPowerUser->Enabled = true;
			chbDeathShot->Enabled = true;
			chbGodMode->Enabled = true;
			chbInstantVictory->Enabled = true;
			chbCopyGP->Enabled = true;
		}
	}

	if (!FileExists(GBPath + "NyxLauncher.exe"))
	{
		btnRunGB->Enabled = false;
		btnRunGB->Caption = "NyxLauncher.exe não encontrado";
	}
	else
	{
		btnRunGB->Caption = "Executar Gunbound";
	}
}
