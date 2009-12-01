program ut;

uses
  Forms,
  Stew,
  UMainForm in 'UMainForm.pas' { MainForm } ;
{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMainForm, MainForm);
  Application.Run;

end.
