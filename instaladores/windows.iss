; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

[Setup]
; NOTE: The value of AppId uniquely identifies this application.
; Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{63182007-40B2-45E4-ABD9-DB212908C6D6}
AppName=Kata Qowi IS Library
AppVersion=0.6.0
;AppVerName=APUSistems API 0.5
AppPublisher= Jean P. R. Mazuelos Saavedra, LlulluTuqo
DefaultDirName=C:/Qt/KataQowi
DefaultGroupName=Kata Qowi IS Library
OutputDir=.\
OutputBaseFilename=KataQowi_setup_lastest
Compression=lzma
SolidCompression=yes

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"

[Files]
Source: "..\bin\*"; DestDir: "{app}\bin"; Flags: ignoreversion
Source: "..\lib\*"; DestDir: "{app}\lib"; Flags: ignoreversion
Source: "..\include\*"; DestDir: "{app}\include"; Flags: ignoreversion recursesubdirs createallsubdirs
