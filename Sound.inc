;================
;  SOUND DEFINES
;================

extrn mciSendCommandA		:PROC
extrn mciGetDeviceID		:PROC
extrn mciGetErrorStringA	:PROC

IDL_MIDI	EQU	993
IDPLAY		EQU	997


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;
;         MMSYSTEM.INC - Multimedia assembly language structures & constants
;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
;       C/C++ Run Time Library - Version 7.0
; 
;       Copyright (c) 1991, 1996 by Borland International
;       All Rights Reserved.
; 
; parameter block for MCI_OPEN command message

MCI_OPEN_PARMS struc
    mciopen_dwCallback        dd    ?
    mciopen_wDeviceID         dw    ?
    mciopen_wReserved0        dw    ?
    mciopen_lpstrDeviceType   dd    ?
    mciopen_lpstrElementName  dd    ?
    mciopen_lpstrAlias        dd    ?
MCI_OPEN_PARMS ends

; parameter block for MCI_PLAY command message
MCI_PLAY_PARMS struc
    mciplay_dwCallback        dd    ?
    mciplay_dwFrom            dd    ?
    mciplay_dwTo              dd    ?
MCI_PLAY_PARMS ends

; MCI command message identifiers
MCI_OPEN                        equ    0803h
MCI_CLOSE                       equ    0804h
MCI_PLAY                        equ    0806h
MCI_STOP                        equ    0808h
MCI_PAUSE                       equ    0809h
MCI_RESUME                      equ    0855h

; common flags for dwFlags parameter of MCI command messages
MCI_NOTIFY                      equ    00000001h

; flags for dwFlags parameter of MCI_OPEN command message
MCI_OPEN_ELEMENT                equ    00000200h
MCI_OPEN_TYPE                   equ    00002000h

;====================
; taken from W32.inc
;====================

LONGINT				typedef	DWORD		;long integer
BOOL				typedef DWORD		;boolean variable
HDC				typedef DWORD		;boolean variable

CANCEL			EQU	0000h
TRUE			EQU	0001h
FALSE			EQU	0000h
NULL			EQU	0000h

BM_SETIMAGE		EQU	00F7h

BS_BITMAP		equ	0080h

DS_3DLOOK		EQU	0004h
DS_CENTER		equ	0800h

IDCLOSE			equ	0008h
IDHELP			equ	0009h
IDOK			equ	0001h

SS_BITMAP		equ	000Eh
SS_CENTER		equ	0001h

;SW_HIDE			EQU	0000h

WM_CLOSE                EQU     0010h
WM_COMMAND              EQU     0111h
WM_CREATE               EQU     0001h
WM_DESTROY              EQU     0002h
WM_INITDIALOG           EQU     0110h
WM_PAINT                EQU     000Fh
WM_SETICON		equ	0080h

WS_CHILD		equ	40000000h
WS_DLGFRAME		equ	00400000h
WS_BORDER		equ	00800000h
WS_VISIBLE		equ	10000000h
WS_EX_DLGMODALFRAME	equ	00000001h
WS_POPUP		equ	80000000h
WS_SYSMENU		equ	00080000h
WS_EX_CLIENTEDGE	equ	00000200h

WS_CAPTION		equ	WS_BORDER+WS_DLGFRAME

PAINTSTRUCT		struct
ps_hdc			HDC	  0		;device context handle
ps_fErase		BOOL	  FALSE		;background erase flag
ps_leftPaint		LONGINT	  0		;left margin of clipping rect
ps_topPaint		LONGINT	  0		;top margin of clipping rect
ps_rightPaint		LONGINT	  0		;right margin of clipping rect
ps_bottomPaint		LONGINT	  0		;bottom margin of clipping rect
ps_fRestore		BOOL	  FALSE		;(reserved)
ps_fIncUpdate		BOOL	  FALSE		;(reserved)
ps_rgbReserved		BYTE	  32 dup (0)	;(reserved)
PAINTSTRUCT		ends

RECT			struct
rc_left			LONGINT	  0		;left margin
rc_top			LONGINT	  0		;top margin
rc_right		LONGINT	  0		;right margin
rc_bottom		LONGINT	  0		;bottom margin
RECT			ends