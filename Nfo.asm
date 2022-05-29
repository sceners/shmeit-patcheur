.386P
Locals
Jumps
include WP32.inc
include nfotext.asm
.Model Flat, StdCall



.Data

Nfo         		equ "Shmeit Corp.nfo",0 

titre_nfo         	db ".NFO Viewer",0
handle_of_edit2 	dd  0

nfo_hbutt1      	dd  0
nfo_hibutt11     	dd  0
nfo_hibutt12     	dd  0

nfo_hbutt2      	dd  0
nfo_hibutt21     	dd  0
nfo_hibutt22     	dd  0


trg2      TRG   	<176,0,190,14,200,14,200,0>
trgnfo_1  TRG_long	<131,1,142,12,585,12,585,8,600,8,600,1>
trgnfo_2  TRG_long	<596,23,596,314,586,312,586,324,600,324,600,23>
trgnfo_3  TRG_long	<1,114,2,114,2,111,3,111,3,109,1,100>
trgnfo_4  TRG_long	<3,109,5,107,11,104,1,100>

.CODE


PUBLIC Nfo_DlgProc
Nfo_DlgProc proc STDCALL, abouthwnd:DWORD, wmsg:DWORD, _wparam:DWORD, _lparam:DWORD
    LOCAL hBrush2    :DWORD
    USES  ebx, edi, esi

    push    ebx
    push    esi
    push    edi

    cmp     [wmsg], WM_COMMAND
    jz      nfo_command
    cmp     [wmsg], WM_INITDIALOG
    jz      nfo_init
    cmp     [wmsg], WM_CLOSE
    jz      nfo_dlgdestroy
;gestion du deplacement de la fenetre avec la souris
    cmp     [wmsg], WM_LBUTTONDOWN
    jz      main_ldown
    cmp     [wmsg], WM_LBUTTONUP
    jz      main_lup
    cmp     [wmsg], WM_MOUSEMOVE
    jz      main_move
    cmp     [wmsg], WM_CTLCOLORSTATIC
    jz      nfo_colorstatic
    cmp     [wmsg], WM_DRAWITEM
    jz      nfo_draw

overcolor2:
    mov     eax, 0
  
nfo_finish:
    pop     edi                          ; recupere les registres
    pop     esi
    pop     ebx
    ret

Nfo_DlgProc    endp

;/////////////////////////////////////////////////////////////////////////////////

nfo_command:
    cmp    [wparam], IDD_CLOSENFO
    jz     nfo_dlgdestroy
    mov    eax, 0
    call   DeleteObject,hBrush2
    jmp    nfo_finish

nfo_colorstatic:
    mov    eax,lparam ;h_edit
    cmp    handle_of_edit2,eax
    jne    overcolor2
    mov    eax,wmsg
    mov    eax,wparam ;hdc
    call   SetBkMode,wparam,2       		; 1 = TRANSPARENT or 2 = OPAQUE
    call   SetTextColor,wparam,txt_color 	; Rouge Jaune
    call   SetBkColor,wparam,  00000000h 	; Black  SetBkMode NOT USED
    call   CreateSolidBrush,   00000000h 	; brush color value
    mov    hBrush2,eax
    jmp    nfo_finish

nfo_draw:
    call    CopyBitMap, nfo_hbutt2, nfo_hibutt21, 12, 12
    jmp     main_finish

nfo_init:

    Push    offset titre_nfo
    push    NULL
    push    WM_SETTEXT
    push    hwnd
    call    SendMessageA
; Exit Button
    call    GetDlgItem , hwnd, 1112
    mov     nfo_hbutt2,eax
    call    LoadBitmapA,hIce,4121 
    mov     nfo_hibutt21, eax
    push    IDD_BOX3             ; get handle Dialog
    push    [abouthwnd]          ; of the edit
    call    GetDlgItem		 ; field
    mov     handle_of_edit2,eax
    call    CreateFontA,11,6,0,0,100,0,0,0,OEM_CHARSET,OUT_DEFAULT_PRECIS,1,1,1,offset FontName2
    call    SendMessageA, handle_of_edit2, WM_SETFONT, eax, 1

; Definit la forme de la fenetre 

    call    CreateRectRgn, 1, 1, 600, 324
    mov     hrgn1, eax
    call    CreatePolygonRgn, offset trgnfo_1, 6, 1
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreatePolygonRgn, offset trgnfo_2, 6, 1
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateEllipticRgn, 570,296,597,325
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_OR
    call    CreateRectRgn, 1,1,13,102
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreatePolygonRgn, offset trgnfo_3, 6, 1
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreatePolygonRgn, offset trgnfo_4, 4, 1
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateRectRgn, 1,102,12,104
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateRectRgn, 16,323,25,324
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateRectRgn, 19,322,22,324
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateRectRgn, 1,322,2,324
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call    CreateRectRgn, 1,323,5,324
    mov     hrgn2, eax
    call    CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF

    call    SetWindowRgn, hwnd, hrgn1, 1

    push    offset nfotxt
    push    0
    push    WM_SETTEXT
    push    IDD_BOX3
    push    hwnd
    call    SendDlgItemMessageA
    mov     eax, 0
    jmp     nfo_finish

nfo_dlgdestroy:
    push    0
    push    hwnd
    call    EndDialog
    mov     [etat],1
    mov     eax, 0
    jmp     nfo_finish






