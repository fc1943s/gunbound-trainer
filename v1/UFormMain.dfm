object FormMain: TFormMain
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  ClientHeight = 250
  ClientWidth = 235
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object lblTitle: TLabel
    Left = 0
    Top = 6
    Width = 235
    Height = 18
    Alignment = taCenter
    AutoSize = False
    Caption = '{Title} {Version}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Trebuchet MS'
    Font.Style = []
    ParentFont = False
  end
  object lblForumLink: TLabel
    Left = 0
    Top = 39
    Width = 235
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = '{ForumLink}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    OnClick = OpenForum
  end
  object lblStew: TLabel
    Left = 0
    Top = 23
    Width = 235
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = 'by Stew UnknowN'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    OnClick = OpenForum
  end
  object lblUpdates: TLabel
    Left = 0
    Top = 229
    Width = 235
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = 'Atualiza'#231#245'es em {ForumLink}'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    ParentShowHint = False
    ShowHint = False
    OnClick = OpenForum
  end
  object lblStatus: TLabel
    Left = 0
    Top = 209
    Width = 235
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'Status: Aguardando Gunbound'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object btnRunGB: TButton
    Left = 23
    Top = 59
    Width = 189
    Height = 20
    Caption = 'Executar Gunbound'
    TabOrder = 0
    OnClick = btnRunGBClick
  end
  object gbxHacks: TGroupBox
    Left = 23
    Top = 85
    Width = 189
    Height = 117
    Caption = 'Hacks'
    TabOrder = 1
    object chbPowerUser: TCheckBox
      Left = 12
      Top = 16
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Power User (Phoenix)'
      ParentBiDiMode = False
      TabOrder = 0
      OnClick = chbHackClick
    end
    object chbGodMode: TCheckBox
      Left = 12
      Top = 54
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'God Mode'
      ParentBiDiMode = False
      TabOrder = 2
      OnClick = chbHackClick
    end
    object chbDeathShot: TCheckBox
      Left = 12
      Top = 35
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Death Shot'
      ParentBiDiMode = False
      TabOrder = 1
      OnClick = chbHackClick
    end
    object chbInstantVictory: TCheckBox
      Left = 12
      Top = 73
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Instant Victory'
      ParentBiDiMode = False
      TabOrder = 3
      OnClick = chbHackClick
    end
    object chbCopyGP: TCheckBox
      Left = 12
      Top = 92
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Copy GP'
      ParentBiDiMode = False
      TabOrder = 4
      OnClick = chbHackClick
    end
  end
  object tmrMain: TTimer
    Interval = 200
    OnTimer = tmrMainTimer
    Left = 195
    Top = 6
  end
end
