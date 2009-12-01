{$WARN SYMBOL_PLATFORM OFF}
unit UMainForm;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms, Dialogs, xpman,
  StdCtrls, Stew, Menus, Buttons, ExtCtrls, shellapi;

type
  TMainForm = class(TForm)
    lblStatus: TLabel;
    lblTitle: TLabel;
    lblStew: TLabel;
    lblUF: TLabel;
    gbxHacks: TGroupBox;
    chbDamage: TCheckBox;
    chbDelay: TCheckBox;
    chbPU: TCheckBox;
    btnRunGb: TButton;
    lblAntiBan: TLabel;
    tmrMain: TTimer;
    procedure FormCreate(Sender: TObject);
    procedure tmrMainTimer(Sender: TObject);
    procedure btnRunGbClick(Sender: TObject);
    procedure lblUFClick(Sender: TObject);
  end;

var
  MainForm: TMainForm;
  gbpath: UnicodeString;
  gbpid, gbhandle, read, write1: Integer;
  write2: array [1 .. 16] of byte;
  nbw: cardinal;
  GBOpen, LoginOpen: bool;

const
  title = 'UnknowN Trainer';
  version = '1.0';

  PTRdamage: array [1 .. 2] of Integer = ($008F9F29, $008F9F39);
  PTRpu: array [1 .. 2] of Integer = ($008F9218, $008F91A8);
  PTRdelay: array [1 .. 6] of Integer = ($008FC20C, $008FC21C, $008FC22C, $008FC23C, $008FC24C, $008FC25C);

implementation

{$R *.dfm}

procedure TMainForm.btnRunGbClick(Sender: TObject);
begin
  winexec(PAnsiChar(AnsiString(gbpath + 'GWCL.exe')), 1);
end;

procedure TMainForm.FormCreate(Sender: TObject);
var
  i: Integer;
begin
  if not Stewcreatemutex(title + version) then
    halt;
  application.title := title + ' ' + version;
  caption := title + ' ' + version;
  lblTitle.caption := title + ' ' + version;
  gbpath := StewRegReadString(HKEY_LOCAL_MACHINE, 'software\softnyx\gunboundwc\', 'location');
  write1 := 0;
  for i := 1 to 16 do
    write2[i] := 00;
  try
    FileSetAttr(gbpath + 'GunBound.log', 0);
    StewWriteTxt(gbpath + 'GunBound.log', '', false, true);
    FileSetAttr(gbpath + 'GunBound.log', 1);
  except
  end;
  StewFormPos(self, cccenter, cccenter);
end;

procedure TMainForm.lblUFClick(Sender: TObject);
begin
  ShellExecute(Handle, 'open', 'http://u-forum.org/', nil, nil, 1);
end;

procedure TMainForm.tmrMainTimer(Sender: TObject);
var
  i: Integer;
begin
  LoginOpen := StewPID('gwcl.exe') <> 0;
  GBOpen := StewPID('gunbound.gme') <> 0;

  if not GBOpen then
  begin
    if not LoginOpen then
    begin
      if fileexists(gbpath + 'GWCL.exe') then
        btnRunGb.Enabled := true;
      lblStatus.caption := 'Status: Aguardando Gunbound';
    end
    else
    begin
      btnRunGb.Enabled := false;
      lblStatus.caption := 'Status: Aguardando Login';
    end;
  end
  else if not LoginOpen then
  begin
    lblStatus.caption := 'Status: Ativando hacks';
    chbDamage.Enabled := false;
    chbDelay.Enabled := false;
    chbPU.Enabled := false;
    gbpid := StewPID('gunbound.gme');
    gbhandle := OpenProcess(2035711, false, gbpid);
    read := 0;

    ReadProcessMemory(gbhandle, ptr(PTRpu[1]), @read, 8, nbw);
    if read <> 0 then
    begin
      if chbDamage.checked then
        for i := 1 to 2 do
          WriteProcessMemory(gbhandle, ptr(PTRdamage[i]), @write2, 16, nbw);

      if chbDelay.checked then
        for i := 1 to 6 do
          WriteProcessMemory(gbhandle, ptr(PTRdelay[i]), @write2, 16, nbw);

      if chbPU.checked then
        for i := 1 to 2 do
          WriteProcessMemory(gbhandle, ptr(PTRpu[i]), @write1, 8, nbw);

      closehandle(gbhandle);
      halt;
    end;
    closehandle(gbhandle);
  end
  else
  begin
    chbDamage.Enabled := true;
    chbDelay.Enabled := true;
    chbPU.Enabled := true;
  end;

  if not fileexists(gbpath + 'GWCL.exe') then
  begin
    btnRunGb.Enabled := false;
    btnRunGb.caption := 'GWCL.exe não encontrado';
  end
  else
    btnRunGb.caption := 'Executar Gunbound';
end;

end.
