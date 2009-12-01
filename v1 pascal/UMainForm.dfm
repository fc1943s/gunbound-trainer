object MainForm: TMainForm
  Left = 0
  Top = 0
  BorderStyle = bsDialog
  ClientHeight = 204
  ClientWidth = 232
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clBlack
  Font.Height = -11
  Font.Name = 'Trebuchet MS'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 16
  object lblStatus: TLabel
    Left = 0
    Top = 164
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
  object lblTitle: TLabel
    Left = 0
    Top = 6
    Width = 235
    Height = 18
    Alignment = taCenter
    AutoSize = False
    Caption = 'UnknowN Trainer X.X'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Trebuchet MS'
    Font.Style = []
    ParentFont = False
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
    OnClick = lblUFClick
  end
  object lblUF: TLabel
    Left = 0
    Top = 39
    Width = 235
    Height = 16
    Cursor = crHandPoint
    Alignment = taCenter
    AutoSize = False
    Caption = 'http://u-forum.org/'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -11
    Font.Name = 'Trebuchet MS'
    Font.Style = [fsUnderline]
    ParentFont = False
    OnClick = lblUFClick
  end
  object lblAntiBan: TLabel
    Left = 0
    Top = 183
    Width = 235
    Height = 16
    Alignment = taCenter
    AutoSize = False
    Caption = 'Bonus: Anti-ban (ativado automaticamente)'
  end
  object gbxHacks: TGroupBox
    Left = 23
    Top = 82
    Width = 189
    Height = 80
    Caption = 'Hacks'
    TabOrder = 1
    object chbDamage: TCheckBox
      Left = 12
      Top = 17
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Damage Hack'
      ParentBiDiMode = False
      TabOrder = 0
    end
    object chbDelay: TCheckBox
      Left = 12
      Top = 55
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Delay Perfect Hack'
      ParentBiDiMode = False
      TabOrder = 2
    end
    object chbPU: TCheckBox
      Left = 12
      Top = 36
      Width = 120
      Height = 17
      BiDiMode = bdLeftToRight
      Caption = 'Power User Hack'
      ParentBiDiMode = False
      TabOrder = 1
    end
  end
  object btnRunGb: TButton
    Left = 49
    Top = 61
    Width = 138
    Height = 18
    Caption = 'Executar Gunbound'
    TabOrder = 0
    OnClick = btnRunGbClick
  end
  object tmrMain: TTimer
    Interval = 100
    OnTimer = tmrMainTimer
    Left = 190
    Top = 6
  end
end
