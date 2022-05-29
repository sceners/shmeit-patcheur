; WinPatcheur v1.3.6

;=============
; APIs
;=============
Extrn    RegSetValueExA     :PROC
Extrn    RegCreateKeyExA    :PROC
Extrn    RegCloseKey        :PROC
Extrn    FindWindowA        :PROC
Extrn    UpdateWindow       :PROC
Extrn    MoveWindow         :PROC
Extrn    EndPaint           :PROC
Extrn    BeginPaint         :PROC
Extrn    GetCloseFileNameA  :PROC
Extrn    SetFocus           :PROC
Extrn    SendMessageA       :PROC
Extrn    GetDlgItem         :PROC
Extrn    SetWindowTextA     :PROC
Extrn    SendDlgItemTextA   :PROC
Extrn    DestroyWindow      :PROC
Extrn	 MessageBoxA        :PROC
Extrn    DialogBoxParamA    :PROC
Extrn	 SendDlgItemMessageA:PROC
Extrn	 SetDlgItemTextA    :PROC
Extrn    TranslateMessage   :PROC
Extrn    ExitProcess        :PROC
Extrn    GetMessageA        :PROC
Extrn    DispatchMessageA   :PROC
Extrn    GetDlgItemTextA    :PROC
Extrn	 GetModuleHandleA   :PROC
Extrn    DefWindowProcA     :PROC
Extrn    DispatchMessageA   :PROC
Extrn    GetMessageA        :PROC
Extrn    CreateFileA        :PROC
Extrn    DeleteFileA        :PROC
Extrn    GetOpenFileNameA   :PROC
Extrn    GetFileSize        :PROC
Extrn    CopyFileA          :PROC
Extrn    SetFilePointer     :PROC
Extrn    WriteFile          :PROC
Extrn    ReadFile           :PROC
Extrn    CloseHandle        :PROC
Extrn    GetWindowTextA	    :PROC
Extrn    GetWindowText	    :PROC
Extrn    DlgProcedure       :PROC
Extrn    lstrcat            :PROC
Extrn    MessageBeep        :PROC
Extrn    ShowWindow         :PROC
Extrn    CreateDialogParamA :PROC
Extrn    EndDialog          :PROC
Extrn    LoadIconA          :PROC
Extrn    RegisterClassA     :PROC
Extrn    GetWindowRect      :PROC
Extrn    SetCapture         :PROC
Extrn    ReleaseCapture     :PROC
Extrn    SetWindowPos       :PROC
Extrn    EnableWindow       :PROC
Extrn    GetCursorPos       :PROC
Extrn    LoadCursorA        :PROC
Extrn    SetCursor          :PROC
Extrn    CreateRoundRectRgn :PROC
Extrn    CreateRectRgn      :PROC
Extrn    SetWindowRgn       :PROC
Extrn    CombineRgn         :PROC
Extrn    CreatePolygonRgn   :PROC
Extrn    CreateEllipticRgn  :PROC
Extrn    SetTextColor       :PROC
Extrn    SetBkColor         :PROC
Extrn    SetBkMode          :PROC
Extrn    SelectObject       :PROC
Extrn    CreateSolidBrush   :PROC
Extrn    CreateWindowExA    :PROC
Extrn    DeleteObject       :PROC
Extrn    LoadBitmapA        :PROC
Extrn    GetDC              :PROC
Extrn    CreateCompatibleDC :PROC
Extrn    SelectObject       :PROC
Extrn    BitBlt             :PROC
Extrn    DeleteDC           :PROC
Extrn    ReleaseDC          :PROC
Extrn    CreateFontA        :PROC
 
UINT    EQU <dd>  ; 32 bits for WIN32
ULONG   EQU <dd>

;===================================================================
;
;  Window Class structure
;
;===================================================================

;NULL		EQU	0h

HRGN				typedef	DWORD		;region handle

WNDCLASS struc
        clsStyle          UINT     ?
        clsLpfnWndProc    ULONG    ?
        clsCbClsExtra     UINT     ?
        clsCbWndExtra     UINT     ?
        clsHInstance      UINT     ?
        clsHIcon          UINT     ?
        clsHCursor        UINT     ?
        clsHbrBackground  UINT     ?
        clsLpszMenuName   ULONG    ?
        clsLpszClassName  ULONG    ?
        hIconSm           UINT     ?
WNDCLASS ends

MSGSTRUCT struc
	msHWND	          UINT    ?
   	msMESSAGE	  UINT    ?
    	msWPARAM          UINT    ?
    	msLPARAM       	  ULONG   ?
    	msTIME            ULONG   ?
    	msPT              ULONG   2 dup(?)
MSGSTRUCT ends

RECT struc
        left              ULONG    ?
        top               ULONG    ? 
        right             ULONG    ? 
        bottom            ULONG    ? 
RECT ends


TRG struc
  x1       ULONG ?
  y1       ULONG ?
  x2       ULONG ?
  y2       ULONG ?
  x3       ULONG ?
  y3       ULONG ?
  x4       ULONG ?
  y4       ULONG ?
TRG ends

TRG_long struc
  x1       ULONG ?
  y1       ULONG ?
  x2       ULONG ?
  y2       ULONG ?
  x3       ULONG ?
  y3       ULONG ?
  x4       ULONG ?
  y4       ULONG ?
  x5       ULONG ?
  y5       ULONG ?
  x6       ULONG ?
  y6       ULONG ?
TRG_long ends


FILE_ATTRIBUTE_NORMAL   equ    80h

;
;==================
; Liens evenements
;==================
ID_DLG                  equ     5001
IDD_OPEN                equ     1000
IDD_EXIT                equ     1001
IDD_ABT                 equ     1002
IDD_REDUC               equ     1003
IDD_CROSS               equ     1004
IDD_NFO         	equ     1005

ID_NFODLG               equ     5002
IDD_REDUCNFO         	equ     1111
IDD_CLOSENFO         	equ     1112

IDD_BOX1                equ     1101
IDD_BOX2                equ     1102
IDD_BOX3                equ     1103

ID_FILE                 equ     103
ID_BACKUP	        equ	104
ID_NFOICON    	        equ	105

ID_PIC                  equ     65535

; ==================
; MessageBox() flags
; ==================

MB_OK			equ	00000000h
MB_OKCANCEL		equ	00000001h
MB_ABORTRETRYIGNORE	equ	00000002h
MB_YESNOCANCEL		equ	00000003h
MB_YESNO		equ	00000004h
MB_RETRYCANCEL		equ	00000005h
;
; Icones
MB_ICONHAND             equ     10h
MB_ICONQUESTION         equ     20h
MB_ICONEXCLAMATION	equ	30h
MB_ICONASTERISK         equ     40h

;============================
; Retour infos de MessageBox
;============================

IDCANCEL                equ     2
IDNO                    equ     7

;=====================
; Gestion de fichiers
;=====================

FILE_ATTRIBUTE_NORMAL   equ     80h
OPEN_EXISTING           equ     3
FILE_SHARE_READ         equ     1
GENERIC_WRITE           equ     40000000h
INVALID_HANDLE_VALUE    equ     0FFFFFFFFh
TRUE                    equ     1
FILE_BEGIN              equ     0
OFN_HIDEREADONLY        equ     4h
OFN_FILEMUSTEXIST       equ     1000h
OFN_PATHMUSTEXIST       equ     800h
NULL                    equ     0
GENERIC_WRITE		EQU	040000000h


CS_VREDRAW	        equ 	0001h
CS_HREDRAW      	equ 	0002h
CS_GLOBALCLASS     	equ 	4000h    ; Global window class

; handle
HWND			typedef	DWORD

; =============
; window styles
; =============
;
WS_OVERLAPPED			equ	00000000h
WS_TABSTOP			equ	00010000h
WS_GROUP			equ	00020000h
WS_MAXIMIZEBOX			equ	00010000h
WS_MINIMIZEBOX			equ	00020000h
WS_THICKFRAME			equ	00040000h
WS_SYSMENU			equ	00080000h
WS_HSCROLL			equ	00100000h
WS_VSCROLL			equ	00200000h
WS_DLGFRAME			equ	00400000h
WS_BORDER			equ	00800000h
WS_MAXIMIZE			equ	01000000h
WS_CLIPCHILDREN			equ	02000000h
WS_CLIPSIBLINGS			equ	04000000h
WS_DISABLED			equ	08000000h
WS_VISIBLE			equ	10000000h
WS_MINIMIZE			equ	20000000h
WS_CHILD			equ	40000000h
WS_POPUP			equ	80000000h
;
WS_CAPTION			equ	WS_BORDER+WS_DLGFRAME
WS_POPUPWINDOW			equ	WS_POPUP+WS_BORDER+WS_SYSMENU
WS_MODAL			equ	WS_CAPTION+WS_SYSMENU+WS_VISIBLE
WS_MODELESS			equ	WS_CAPTION+WS_SYSMENU+WS_VISIBLE
WS_CONTROL			equ	WS_CHILD+WS_VISIBLE
WS_OVERLAPPEDWINDOW		equ	WS_OVERLAPPED+WS_CAPTION+WS_SYSMENU+\
					WS_THICKFRAME+WS_MINIMIZEBOX+\
					WS_MAXIMIZEBOX
;
WS_TILED			equ	WS_OVERLAPPED
WS_CHILDWINDOW			equ	WS_CHILD
WS_ICONIC			equ	WS_MINIMIZE
WS_SIZEBOX			equ	WS_THICKFRAME
WS_TILEDWINDOW			equ	WS_OVERLAPPEDWINDOW
;
;------------------------------------------------------------------------------
;
; ======================
; extended window styles
; ======================
;
WS_EX_NONE			equ	00000000h
WS_EX_DLGMODALFRAME		equ	00000001h
WS_EX_NOPARENTNOTIFY		equ	00000004h
WS_EX_TOPMOST			equ	00000008h
WS_EX_ACCEPTFILES		equ	00000010h
WS_EX_TRANSPARENT		equ	00000020h
WS_EX_MDICHILD			equ	00000040h
WS_EX_TOOLWINDOW		equ	00000080h
WS_EX_WINDOWEDGE		equ	00000100h
WS_EX_CLIENTEDGE		equ	00000200h
WS_EX_CONTEXTHELP		equ	00000400h
WS_EX_RIGHT			equ	00001000h
WS_EX_LEFT			equ	00000000h
WS_EX_RTLREADING		equ	00002000h
WS_EX_LTRREADING		equ	00000000h
WS_EX_LEFTSCROLLBAR		equ	00004000h
WS_EX_RIGHTSCROLLBAR		equ	00000000h
WS_EX_CONTROLPARENT		equ	00010000h
WS_EX_STATICEDGE		equ	00020000h
WS_EX_APPWINDOW			equ	00040000h
;
WS_EX_OVERLAPPEDWINDOW		equ	00000300h
WS_EX_PALETTEWINDOW		equ	00000188h
;

;===================
; Evenements souris
;===================
GW_HWNDLAST		equ	1
BM_GETCHECK		equ	00F0h
BM_SETCHECK		equ	00F1h
BM_GETSTATE		equ	00F2h
BM_SETSTATE		equ	00F3h
BM_SETSTYLE		equ	00F4h
BM_CLICK		equ	00F5h
BM_GETIMAGE		equ	00F6h
BM_SETIMAGE		equ	00F7h
BST_CHECKED	        equ	01h

;================
;  window mode
;================

SW_SHOWMINIMIZED	equ	 2
SW_RESTORE              equ      3
SW_HIDE			equ	 4
SW_MAXIMIZE		equ	 5
SW_MINIMIZE		equ	 6
SW_SHOW 		equ	 7
SW_SHOWDEFAULT		equ	 8
SW_SHOWMAXIMIZED	equ	 9
SW_SHOWMINNOACTIVE	equ	 10
SW_SHOWNA		equ	 11
SW_SHOWNOACTIVATE	equ	 12
SW_SHOWNORMAL		equ	 13


; ====================
; SetWindowPos() flags
; ====================
SWP_NOSIZE			equ	0001h
SWP_NOMOVE			equ	0002h
SWP_NOZORDER			equ	0004h
SWP_NOREDRAW			equ	0008h
SWP_NOACTIVATE			equ	0010h
SWP_FRAMECHANGED		equ	0020h
SWP_SHOWWINDOW			equ	0040h
SWP_HIDEWINDOW			equ	0080h
SWP_NOCOPYBITS			equ	0100h
SWP_NOOWNERZORDER		equ	0200h
SWP_NOSENDCHANGING		equ	0400h
SWP_DEFERERASE			equ	2000h
SWP_ASYNCWINDOWPOS		equ	4000h

;===============
; Task bar
;===============

;TB_ISBUTTONPRESSED	equ	 2


;->
IDD_BACK		equ     1100

; ===================
; CombineRgn() styles
; ===================
;
RGN_AND				equ	1
RGN_OR				equ	2
RGN_XOR				equ	3
RGN_DIFF			equ	4
RGN_COPY			equ	5
RGN_MIN				equ	RGN_AND
RGN_MAX				equ	RGN_COPY


RGB_BLACK			equ	00000000h
RGB_VDKGRAY32			equ	00202020h
RGB_DKGRAY			equ	00404040h
RGB_SOLIDGRAY			equ	00808080h
RGB_SOLIDLTGRAY			equ	00C0C0C0h
RGB_EBONY			equ	00E0E0E0h
RGB_BLUE			equ	00FF0000h
RGB_GREEN			equ	0000FF00h
RGB_RED				equ	000000FFh

; =======================
; button control messages
; =======================
;
BM_GETCHECK			equ	00F0h
BM_SETCHECK			equ	00F1h
BM_GETSTATE			equ	00F2h
BM_SETSTATE			equ	00F3h
BM_SETSTYLE			equ	00F4h
BM_CLICK			equ	00F5h
BM_GETIMAGE			equ	00F6h
BM_SETIMAGE			equ	00F7h
;
IMAGE_BITMAP		EQU	00000h
IMAGE_ICON		EQU	00001h
IMAGE_CURSOR		EQU	00002h

; =========================
; ternary raster operations
; =========================
;
SRCCOPY				equ	00CC0020h	;dest = src
SRCPAINT			equ	00EE0086h	;dest = src or dest
SRCAND				equ	008800C6h	;dest = src and dest
SRCINVERT			equ	00660046h	;dest = src xor dest
SRCERASE			equ	00440328h	;dest = src and -dest
NOTSRCCOPY			equ	00330008h	;dest = -src
NOTSRCERASE			equ	001100A6h	;dest = -src and -dest
MERGECOPY			equ	00C000CAh	;dest = src and pat
MERGEPAINT			equ	00BB0226h	;dest = -src or dest
PATCOPY				equ	00F00021h	;dest = pat
PATPAINT			equ	00FB0A09h	;dest = DPSnoo
PATINVERT			equ	005A0049h	;dest = pat xor dest
DSTINVERT			equ	00550009h	;dest = -dest
BLACKNESS			equ	00000042h	;dest = black
WHITENESS			equ	00FF0062h	;dest = white


; ===============
; window messages
; ===============
;
WM_NULL				equ	0000h
WM_CREATE			equ	0001h
WM_DESTROY			equ	0002h
WM_MOVE				equ	0003h
WM_SIZE				equ	0005h
WM_ACTIVATE			equ	0006h
WM_SETFOCUS			equ	0007h
WM_KILLFOCUS			equ	0008h
WM_ENABLE			equ	000Ah
WM_SETREDRAW			equ	000Bh
WM_SETTEXT			equ	000Ch
WM_GETTEXT			equ	000Dh
WM_GETTEXTLENGTH		equ	000Eh
WM_PAINT			equ	000Fh
WM_CLOSE			equ	0010h
WM_QUERYENDSESSION		equ	0011h
WM_QUIT				equ	0012h
WM_QUERYOPEN			equ	0013h
WM_ERASEBKGND			equ	0014h
WM_SYSCOLORCHANGE		equ	0015h
WM_ENDSESSION			equ	0016h
WM_SHOWWINDOW			equ	0018h
WM_WININICHANGE			equ	001Ah
WM_SETTINGCHANGE		equ	WM_WININICHANGE
WM_DEVMODECHANGE		equ	001Bh
WM_ACTIVATEAPP			equ	001Ch
WM_FONTCHANGE			equ	001Dh
WM_TIMECHANGE			equ	001Eh
WM_CANCELMODE			equ	001Fh
WM_SETCURSOR			equ	0020h
WM_MOUSEACTIVATE		equ	0021h
WM_CHILDACTIVATE		equ	0022h
WM_QUEUESYNC			equ	0023h
WM_GETMINMAXINFO		equ	0024h
WM_PAINTICON			equ	0026h
WM_ICONERASEBKGND		equ	0027h
WM_NEXTDLGCTL			equ	0028h
WM_SPOOLERSTATUS		equ	002Ah
WM_DRAWITEM			equ	002Bh
WM_MEASUREITEM			equ	002Ch
WM_DELETEITEM			equ	002Dh
WM_VKEYTOITEM			equ	002Eh
WM_CHARTOITEM			equ	002Fh
WM_SETFONT			equ	0030h
WM_GETFONT			equ	0031h
WM_SETHOTKEY			equ	0032h
WM_GETHOTKEY			equ	0033h
WM_QUERYDRAGICON		equ	0037h
WM_COMPAREITEM			equ	0039h
WM_COMPACTING			equ	0041h
WM_COMMNOTIFY			equ	0044h		;no longer suported
WM_WINDOWPOSCHANGING		equ	0046h
WM_WINDOWPOSCHANGED		equ	0047h
WM_POWER			equ	0048h
WM_COPYDATA			equ	004Ah
WM_CANCELJOURNAL		equ	004Bh
WM_NOTIFY			equ	004Eh
WM_INPUTLANGCHANGEREQUEST	equ	0050h
WM_INPUTLANGCHANGE		equ	0051h
WM_TCARD			equ	0052h
WM_HELP				equ	0053h
WM_USERCHANGED			equ	0054h
WM_NOTIFYFORMAT			equ	0055h
WM_CONTEXTMENU			equ	007Bh
WM_STYLECHANGING		equ	007Ch
WM_STYLECHANGED			equ	007Dh
WM_DISPLAYCHANGE		equ	007Eh
WM_GETICON			equ	007Fh
WM_SETICON			equ	0080h
WM_NCCREATE			equ	0081h
WM_NCDESTROY			equ	0082h
WM_NCCALCSIZE			equ	0083h
WM_NCHITTEST			equ	0084h
WM_NCPAINT			equ	0085h
WM_NCACTIVATE			equ	0086h
WM_GETDLGCODE			equ	0087h
;
WM_NCMOUSEMOVE			equ	00A0h
WM_NCLBUTTONDOWN		equ	00A1h
WM_NCLBUTTONUP			equ	00A2h
WM_NCLBUTTONDBLCLK		equ	00A3h
WM_NCRBUTTONDOWN		equ	00A4h
WM_NCRBUTTONUP			equ	00A5h
WM_NCRBUTTONDBLCLK		equ	00A6h
WM_NCMBUTTONDOWN		equ	00A7h
WM_NCMBUTTONUP			equ	00A8h
WM_NCMBUTTONDBLCLK		equ	00A9h
;
WM_KEYFIRST			equ	0100h
WM_KEYDOWN			equ	0100h
WM_KEYUP			equ	0101h
WM_CHAR				equ	0102h
WM_DEADCHAR			equ	0103h
WM_SYSKEYDOWN			equ	0104h
WM_SYSKEYUP			equ	0105h
WM_SYSCHAR			equ	0106h
WM_SYSDEADCHAR			equ	0107h
WM_KEYLAST			equ	0108h
;
WM_IME_STARTCOMPOSITION		equ	010Dh
WM_IME_ENDCOMPOSITION		equ	010Eh
WM_IME_COMPOSITION		equ	010Fh
WM_IME_KEYLAST			equ	010Fh
WM_INITDIALOG			equ	0110h
WM_COMMAND			equ	0111h
WM_SYSCOMMAND			equ	0112h
WM_TIMER			equ	0113h
WM_HSCROLL			equ	0114h
WM_VSCROLL			equ	0115h
WM_INITMENU			equ	0116h
WM_INITMENUPOPUP		equ	0117h
WM_MENUSELECT			equ	011Fh
WM_MENUCHAR			equ	0120h
WM_ENTERIDLE			equ	0121h
WM_CTLCOLORMSGBOX		equ	0132h
WM_CTLCOLOREDIT			equ	0133h
WM_CTLCOLORLISTBOX		equ	0134h
WM_CTLCOLORBTN			equ	0135h
WM_CTLCOLORDLG			equ	0136h
WM_CTLCOLORSCROLLBAR		equ	0137h
WM_CTLCOLORSTATIC		equ	0138h
;
WM_MOUSEFIRST			equ	0200h
WM_MOUSEMOVE			equ	0200h
WM_LBUTTONDOWN			equ	0201h
WM_LBUTTONUP			equ	0202h
WM_LBUTTONDBLCLK		equ	0203h
WM_RBUTTONDOWN			equ	0204h
WM_RBUTTONUP			equ	0205h
WM_RBUTTONDBLCLK		equ	0206h
WM_MBUTTONDOWN			equ	0207h
WM_MBUTTONUP			equ	0208h
WM_MBUTTONDBLCLK		equ	0209h
WM_MOUSELAST			equ	0209h
;
WM_PARENTNOTIFY			equ	0210h
WM_ENTERMENULOOP		equ	0211h
WM_EXITMENULOOP			equ	0212h
WM_NEXTMENU			equ	0213h
WM_SIZING			equ	0214h
WM_CAPTURECHANGED		equ	0215h
WM_MOVING			equ	0216h
WM_POWERBROADCAST		equ	0218h
WM_DEVICECHANGE			equ	0219h
WM_MDICREATE			equ	0220h
WM_MDIDESTROY			equ	0221h
WM_MDIACTIVATE			equ	0222h
WM_MDIRESTORE			equ	0223h
WM_MDINEXT			equ	0224h
WM_MDIMAXIMIZE			equ	0225h
WM_MDITILE			equ	0226h
WM_MDICASCADE			equ	0227h
WM_MDIICONARRANGE		equ	0228h
WM_MDIGETACTIVE			equ	0229h
WM_MDISETMENU			equ	0230h
WM_ENTERSIZEMOVE		equ	0231h
WM_EXITSIZEMOVE			equ	0232h
WM_DROPFILES			equ	0233h
WM_MDIREFRESHMENU		equ	0234h
;
WM_IME_SETCONTEXT		equ	0281h
WM_IME_NOTIFY			equ	0282h
WM_IME_CONTROL			equ	0283h
WM_IME_COMPOSITIONFULL		equ	0284h
WM_IME_SELECT			equ	0285h
WM_IME_CHAR			equ	0286h
WM_IME_KEYDOWN			equ	0290h
WM_IME_KEYUP			equ	0291h
;
WM_CUT				equ	0300h
WM_COPY				equ	0301h
WM_PASTE			equ	0302h
WM_CLEAR			equ	0303h
WM_UNDO				equ	0304h
WM_RENDERFORMAT			equ	0305h
WM_RENDERALLFORMATS		equ	0306h
WM_DESTROYCLIPBOARD		equ	0307h
WM_DRAWCLIPBOARD		equ	0308h
WM_PAINTCLIPBOARD		equ	0309h
WM_VSCROLLCLIPBOARD		equ	030Ah
WM_SIZECLIPBOARD		equ	030Bh
WM_ASKCBFORMATNAME		equ	030Ch
WM_CHANGECBCHAIN		equ	030Dh
WM_HSCROLLCLIPBOARD		equ	030Eh
WM_QUERYNEWPALETTE		equ	030Fh
WM_PALETTEISCHANGING		equ	0310h
WM_PALETTECHANGED		equ	0311h
WM_HOTKEY			equ	0312h
WM_PRINT			equ	0317h
WM_PRINTCLIENT			equ	0318h
;
WM_HANDHELDFIRST		equ	0358h
WM_HANDHELDLAST			equ	035Fh
;
WM_AFXFIRST			equ	0360h
WM_AFXLAST			equ	037Fh
;
WM_PENWINFIRST			equ	0380h
WM_PENWINLAST			equ	038Fh
;
WM_DDE_FIRST			equ	03E0h
WM_DDE_INITIATE			equ	WM_DDE_FIRST
WM_DDE_TERMINATE		equ	WM_DDE_FIRST+1
WM_DDE_ADVISE			equ	WM_DDE_FIRST+2
WM_DDE_UNADVISE			equ	WM_DDE_FIRST+3
WM_DDE_ACK			equ	WM_DDE_FIRST+4
WM_DDE_DATA			equ	WM_DDE_FIRST+5
WM_DDE_REQUEST			equ	WM_DDE_FIRST+6
WM_DDE_POKE			equ	WM_DDE_FIRST+7
WM_DDE_EXECUTE			equ	WM_DDE_FIRST+8
WM_DDE_LAST			equ	03E8h
;
WM_USER				equ	0400h
WM_APP				equ	8000h

; =================
; owner draw states
; =================
;
ODS_SELECTED			equ	0001h
ODS_GRAYED			equ	0002h
ODS_DISABLED			equ	0004h
ODS_CHECKED			equ	0008h
ODS_FOCUS			equ	0010h
ODS_DEFAULT			equ	0020h
ODS_COMBOBOXEDIT		equ	1000h
;
;------------------------------------------------------------------------------
;
; ================
; owner draw types
; ================
;
ODT_MENU			equ	1
ODT_LISTBOX			equ	2
ODT_COMBOBOX			equ	3
ODT_BUTTON			equ	4
ODT_STATIC			equ	5
;
; =====================
; static control styles
; =====================
;
SS_LEFT				equ	0000h
SS_CENTER			equ	0001h
SS_RIGHT			equ	0002h
SS_ICON				equ	0003h
SS_BLACKRECT			equ	0004h
SS_GRAYRECT			equ	0005h
SS_WHITERECT			equ	0006h
SS_BLACKFRAME			equ	0007h
SS_GRAYFRAME			equ	0008h
SS_WHITEFRAME			equ	0009h
SS_USERITEM			equ	000Ah
SS_SIMPLE			equ	000Bh
SS_LEFTNOWORDWRAP		equ	000Ch
SS_BITMAP			equ	000Eh
SS_OWNERDRAW			equ	000Dh
SS_ENHMETAFILE			equ	000Fh
SS_ETCHEDHORZ			equ	0010h
SS_ETCHEDVERT			equ	0011h
SS_ETCHEDFRAME			equ	0012h
SS_TYPEMASK			equ	001Fh
SS_NOPREFIX			equ	0080h
SS_NOTIFY			equ	0100h
SS_CENTERIMAGE			equ	0200h
SS_RIGHTJUST			equ	0400h
SS_REALSIZEIMAGE		equ	0800h
SS_SUNKEN			equ	1000h

OUT_DEFAULT_PRECIS                   equ 0
OUT_STRING_PRECIS                    equ 1
OUT_CHARACTER_PRECIS                 equ 2
OUT_STROKE_PRECIS                    equ 3
OUT_TT_PRECIS                        equ 4
OUT_DEVICE_PRECIS                    equ 5
OUT_RASTER_PRECIS                    equ 6
OUT_TT_ONLY_PRECIS                   equ 7
OUT_OUTLINE_PRECIS                   equ 8
CLIP_DEFAULT_PRECIS                  equ 0
CLIP_CHARACTER_PRECIS                equ 1
CLIP_STROKE_PRECIS                   equ 2
CLIP_MASK                            equ 0Fh
CLIP_LH_ANGLES                       equ 16
CLIP_TT_ALWAYS                       equ 32
CLIP_EMBEDDED                        equ 128
DEFAULT_QUALITY                      equ 0
DRAFT_QUALITY                        equ 1
PROOF_QUALITY                        equ 2
DEFAULT_PITCH                        equ 0
FIXED_PITCH                          equ 1
VARIABLE_PITCH                       equ 2
ANSI_CHARSET                         equ 0
DEFAULT_CHARSET                      equ 1
SYMBOL_CHARSET                       equ 2
SHIFTJIS_CHARSET                     equ 128
HANGEUL_CHARSET                      equ 129
CHINESEBIG5_CHARSET                  equ 136
OEM_CHARSET                          equ 255
FF_DONTCARE                          equ 0
FF_ROMAN                             equ 16
FF_SWISS                             equ 32
FF_MODERN                            equ 48
FF_SCRIPT                            equ 64
FF_DECORATIVE                        equ 80
FW_DONTCARE                          equ 0
FW_THIN                              equ 100
FW_EXTRALIGHT                        equ 200
FW_LIGHT                             equ 300
FW_NORMAL                            equ 400
FW_MEDIUM                            equ 500
FW_SEMIBOLD                          equ 600
FW_BOLD                              equ 700
FW_EXTRABOLD                         equ 800
FW_HEAVY                             equ 900
FW_ULTRALIGHT                        equ FW_EXTRALIGHT
FW_REGULAR                           equ FW_NORMAL
FW_DEMIBOLD                          equ FW_SEMIBOLD
FW_ULTRABOLD                         equ FW_EXTRABOLD
FW_BLACK                             equ FW_HEAVY
