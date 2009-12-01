#ifndef UFormMainH
#define UFormMainH

#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

class TFormMain : public TForm
{

__published:
	TLabel* lblTitle;
	TLabel* lblForumLink;
	TLabel* lblStew;
	TLabel* lblUpdates;
	TLabel* lblStatus;
	TButton* btnRunGB;
	TGroupBox* gbxHacks;
	TCheckBox* chbPowerUser;
	TCheckBox* chbGodMode;
	TCheckBox* chbDeathShot;
	TCheckBox* chbInstantVictory;
	TCheckBox* chbCopyGP;
	TTimer* tmrMain;

	void __fastcall FormCreate(TObject* Sender);
	void __fastcall OpenForum(TObject* Sender);
	void __fastcall FormClose(TObject* Sender, TCloseAction& Action);
	void __fastcall btnRunGBClick(TObject* Sender);
	void __fastcall chbHackClick(TObject* Sender);
	void __fastcall tmrMainTimer(TObject* Sender);
private:
public:
	void SaveRegConfig();
	__fastcall TFormMain(TComponent* Owner);
};
extern PACKAGE TFormMain* FormMain;
#endif
