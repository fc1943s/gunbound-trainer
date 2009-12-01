#ifndef UFormMainH
#define UFormMainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Buttons.hpp>
#include <Graphics.hpp>

struct HackStructure
{
	TCheckBox* chbHack;
	UnicodeString chbCaption;
	UnicodeString HackName;
	int* Pointers;
};

class TFormMain : public TForm
{
__published:
	TLabel* lblTitle;
	TLabel* lblForumLink;
	TLabel* lblStew;
	TLabel* lblUpdates;
	TLabel* lblStatus;
	TGroupBox* gbxHacks;
	TTimer* tmrMain;
	TBitBtn* btbRunGB;
	TBitBtn* btbHelp;
	TImage* imgX;
	TImage* imgGB;

	void __fastcall FormCreate(TObject* Sender);
	void __fastcall OpenForum(TObject* Sender);
	void __fastcall chbHackClick(TObject* Sender);
	void __fastcall tmrMainTimer(TObject* Sender);
	void __fastcall btbRunGBClick(TObject* Sender);

private:
public:
	void SaveRegConfig();
	void AddHack(UnicodeString HackName, UnicodeString chbCaption, int* Pointers);
	void ChangeGBButton(int State);
	int GetHackCount();
	void CreateHacks();
	__fastcall TFormMain(TComponent* Owner);
};

extern PACKAGE TFormMain* FormMain;
#endif
