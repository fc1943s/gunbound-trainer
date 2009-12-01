#include <vcl.h>
#include <stdio.h>
#pragma hdrstop
#include "UFormMain.h"
#include "Stew.cpp"
#pragma package(smart_init)
#pragma resource "*.dfm"

const int HackCount = 5;

bool Deploy = false, CanRunGB = true;

const UnicodeString Title = "Hot Gunbound Tools", Version = "2.0",

ForumLink = "http://hotcheats.org/", RegKey = "software\\Hot Cheats\\" + Title + "\\" + Version;

TFormMain* FormMain;

UnicodeString GBPath;

Pointer PointerCheck;

HackStructure* HackGroup[HackCount];

int PGodMode[1] =
{
	0x0090E244
}, PDeathShot[1] =
{
	0x0090E23C
}, PPowerUser[60] =
{
	0x00636D30, 0x00636D31, 0x00636D32, 0x00636D33, 0x00636D34, 0x00636D35, 0x00636D36, 0x00636D37, 0x00636D38, 0x00636D39, 0x00636D3A, 0x00636D3B, 0x00636D3C,
	0x00636D3D, 0x00636D3E, 0x00636D3F, 0x0090DFE0, 0x0090DFF0, 0x0090E000, 0x0090E010, 0x0090DFE1, 0x0090DFE2, 0x0090DFE3, 0x0090DFE4, 0x0090DFE5, 0x0090DFE6,
	0x0090DFE7, 0x0090DF70, 0x0090DF80, 0x0090DF90, 0x0090DFA0, 0x0090DF71, 0x0090DF72, 0x0090DF73, 0x0090DF74, 0x0090DF75, 0x0090DF76, 0x0090DF77, 0x0090DFE8,
	0x0090DFF8, 0x0090E008, 0x0090E018, 0x0090DFE9, 0x0090DFEA, 0x0090DFEB, 0x0090DFEC, 0x0090DFED, 0x0090DFEE, 0x0090DFEF, 0x0090DF78, 0x0090DF88, 0x0090DF98,
	0x0090DFA8, 0x0090DF79, 0x0090DF7A, 0x0090DF7B, 0x0090DF7C, 0x0090DF7D, 0x0090DF7E, 0x0090DF7F
}, PInstantVictory[16] =
{
	0x0090ECAC, 0x0090ECBC, 0x0090ECCC, 0x0090ECDC, 0x0090ECB4, 0x0090ECC4, 0x0090ECD4, 0x0090ECE4, 0x0090ED1C, 0x0090ED2C, 0x0090ED3C, 0x0090ED4C, 0x0090ED24,
	0x0090ED34, 0x0090ED44, 0x0090ED54
}, PGold[32] =
{
	0x0090EBA0, 0x0090EBA1, 0x0090EBA2, 0x0090EBA3, 0x0090EBA4, 0x0090EBA5, 0x0090EBA6, 0x0090EBA7, 0x0090EBA8, 0x0090EBA9, 0x0090EBAA, 0x0090EBAB, 0x0090EBAC,
	0x0090EBAD, 0x0090EBAE, 0x0090EBAF, 0x0090EC20, 0x0090EC21, 0x0090EC22, 0x0090EC23, 0x0090EC24, 0x0090EC25, 0x0090EC26, 0x0090EC27, 0x0090EC28, 0x0090EC29,
	0x0090EC2A, 0x0090EC2B, 0x0090EC2C, 0x0090EC2D, 0x0090EC2E, 0x0090EC2F
}, PCopyGP[64] =
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
	CreateHacks();
	try
	{
		for (int i = 0; i <= HackCount - 1; i++)
		{
			HackGroup[i]->chbHack->Checked = StrToBool(configs[i + 1]);
		}
	}
	catch(...)
	{
	}
	if (Deploy)
	{
		OpenForum(this);
	}
	Stew::_FormPosition(this, __Center, __Center);
}

void TFormMain::AddHack(UnicodeString HackName, UnicodeString chbCaption, int* Pointers)
{
	HackGroup[GetHackCount() == 0 ? 0 : GetHackCount()] = new HackStructure;
	HackGroup[GetHackCount() - 1]->HackName = HackName;
	HackGroup[GetHackCount() - 1]->Pointers = Pointers;
	HackGroup[GetHackCount() - 1]->chbHack = new TCheckBox(gbxHacks);

	HackGroup[GetHackCount() - 1]->chbHack->Parent = gbxHacks;
	HackGroup[GetHackCount() - 1]->chbHack->Left = 12;
	HackGroup[GetHackCount() - 1]->chbHack->OnClick = chbHackClick;
	HackGroup[GetHackCount() - 1]->chbHack->Top = 16 + ((GetHackCount() - 1) * 19);
	HackGroup[GetHackCount() - 1]->chbHack->Caption = chbCaption;
	HackGroup[GetHackCount() - 1]->chbHack->Width = 140;
	HackGroup[GetHackCount() - 1]->chbHack->Name = "chb" + HackName;

	gbxHacks->Height = gbxHacks->Height + 19;
	FormMain->Height = FormMain->Height + 19;
	lblStatus->Top = lblStatus->Top + 19;
	lblUpdates->Top = lblUpdates->Top + 19;
}

void TFormMain::CreateHacks()
{
	AddHack("PowerUser", "Power User (Phoenix)", PPowerUser);
	AddHack("DeathShot", "Death Shot", PDeathShot);
	AddHack("GodMode", "God Mode", PGodMode);
	AddHack("InstantVictory", "Instant Victory", PInstantVictory);
	AddHack("CopyGP", "Copy GP", PCopyGP);

	PointerCheck = (Pointer)HackGroup[1]->Pointers[0];
}

int TFormMain::GetHackCount()
{
	int aux = 0, aux2 = 0;
	while (true)
	{
		if (HackGroup[aux2] != NULL && aux2 < HackCount)
		{
			aux++;
		}
		else
		{
			return aux;
		}
		aux2++;
	}
}

void __fastcall TFormMain::OpenForum(TObject* Sender)
{
	ShellExecuteW(Handle, L"open", ForumLink.c_str(), NULL, NULL, 6);
}

void TFormMain::SaveRegConfig()
{
	UnicodeString aux;
	for (int i = 0; i <= HackCount - 1; i++)
	{
		aux = aux + IntToStr((int)HackGroup[i]->chbHack->Checked);
	}
	Stew::_RegWriteString(HKEY_LOCAL_MACHINE, RegKey, "Config", aux, true, true);
}

void __fastcall TFormMain::chbHackClick(TObject* Sender)
{
	SaveRegConfig();
}

void TFormMain::ChangeGBButton(int State)
{
	switch(State)
	{
		case 1:
		{
			btbRunGB->Glyph = imgX->Picture->Bitmap;
			btbRunGB->Hint = "NyxLauncher.exe não encontrado";
			CanRunGB = false;
			break;
		}
		case 2:
		{
			btbRunGB->Glyph = imgX->Picture->Bitmap;
			btbRunGB->Hint = "O Gunbound já está aberto";
			CanRunGB = false;
			break;
		}
		case 3:
		{
			btbRunGB->Glyph = imgGB->Picture->Bitmap;
			btbRunGB->Hint = "Executar Gunbound";
			CanRunGB = true;
			break;
		}
	}
}

void __fastcall TFormMain::tmrMainTimer(TObject* Sender)
{
	bool LoginOpen = Stew::_GetPID("NyxLauncher.exe") != 0;
	bool GBOpen = Stew::_GetPID("GunBound.gme") != 0;
	HANDLE GBHandle;

	ChangeGBButton(!FileExists(GBPath + "NyxLauncher.exe") ? 1 : !GBOpen && !LoginOpen ? 3 : 2);

	if (!GBOpen)
	{
		lblStatus->Caption = "Status: Aguardando " + UnicodeString(!LoginOpen ? "Gunbound" : "Login");
		for (int i = 0; i <= HackCount - 1; i++)
		{
			HackGroup[i]->chbHack->Enabled = true;
		}
	}
	else
	{
		if (!LoginOpen)
		{
			lblStatus->Caption = "Status: Ativando Hacks";
			for (int i = 0; i <= HackCount - 1; i++)
			{
				HackGroup[i]->chbHack->Enabled = false;
			}
			Stew::_MemoryManagement(Stew::_GetPID("GunBound.gme"), GBHandle);

			int aux = 0;

			ReadProcessMemory(GBHandle, PointerCheck, &aux, 1, 0);

			if (aux != 0)
			{
				int write = 0;
				for (int i = 0; i <= HackCount - 1; i++)
				{
					if (HackGroup[i]->chbHack->Checked)
					{
						for (UINT j = 0; j < sizeof((HackGroup[i]->Pointers)) / sizeof(HackGroup[i]->Pointers[0]); j++)
						{
							WriteProcessMemory(GBHandle, (Pointer)HackGroup[i]->Pointers[j], &write, 1, 0);
						}
					}
				}
				CloseHandle(GBHandle);
				Application->Terminate();
			}
			CloseHandle(GBHandle);
		}
	}
}

void __fastcall TFormMain::btbRunGBClick(TObject* Sender)
{
	if (CanRunGB)
	{
		WinExec(UnicodeString(GBPath + "NyxLauncher.exe").t_str(), 1);
	}
}
