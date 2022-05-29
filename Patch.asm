.386P
Locals
Jumps
include WP32.inc
include Sound.inc
include nfo.asm
include movefrm.asm
.Model Flat, StdCall
.Data

;Coders => Forge or Van ?
;Kheo, so not bad coder (ph0ne kb!)
;Stat'!!, only 15k? Damn your optimisation method!! :)

 
;[SC]Patcher v1.3.6 (compatible systemes Win9x/NT)
;/////////////////////////////////// Zone à modifier//////////////////////////////////////////

 Nick		equ     " none "            	; Ton nick (respecte l'espace entre chaque guillement)
 Nom_du_prog	equ     " Notepad 5 build 2195 "; Le nom du prog cracké
 Type_de_patch	equ     " Auto Save "  		; Met ici ce que fait ton patch

 Fichier        equ     "Notepad.exe.exe"			; Cette partie n'est pas utile à comprendre
 taille         equ      1007616			; elle est generée par AZ compiler
 nb_blocs       equ      1				; en ce moment il est encore beta mais je 
 patch_ptr0     equ      0A61A0h			; vais bientot le terminé (thx Smeita pour l'hlp!)
 new_val0       equ      00h				; ps: il generera toute cette partie
 long_bloc0     equ      1				;     donc encore un peu de patience ;)

 e_mail		equ	"s_c@mailandnews.com"
 url		equ	"www.shmeitcorp.com"
 greets		equ	"All members from SC and you!"

 txt_color	equ 	00CC9980h	;couleur du texte en hexa
 music_or_not   dd 	1		;1= zik, 0= pas de zik. Cela peut sembler inutile mais sous NT ça l'est un minimum
 
;/////////////////////////////////////////////////////////////////////////////////////////////















;*--------------------------------------------*
;*------------------=Strings=-----------------*
;*--------------------------------------------*

; Divers
 titre         	db "[SC]Patcher - ",Nom_du_prog,"",0
 open_caption   db "Where is the ",Fichier," file ?",0


;Présentation
 crk_release  	db " /¯¯¯¯¯¯`-=<[  CRACK RELEASE  ]>-´ ",13,10
                db "|                                ",13,10
              	db "| fOR	:  ",Nom_du_prog,"",13,10
                db "|                                ",13,10
              	db "| tYPE	:  ",Type_de_patch,"",13,10
             	db "| bY	:  ", Nick ,"",13,10
                db "|		___          ",13,10
            	db " \______,---<>---´      `---<>---. ",0


;About
 about		db "(¯`·.___..-=> Infos <=-..___.·´¯)",13,10,13,10
              	db " cONTACT : ",e_mail,"",13,10
              	db " wEBsITE : ",url,"",13,10
              	db " GrEeTz : ",greets,"",13,10,13,10,13,10
            	db "<-=[Coded by Static && Kheo ]=->",0


; Message de réussite...
 succes_caption db "Okay Dokey!",0
 textfin        db "(¯`·.___..-=> Progress <=-..___.·´¯)",13,10,13,10
                db " ",Fichier," -> Openning... ",13,10
                db " ",Fichier," -> Checking size... ",13,10
                db " ",Fichier," -> Backup to *.uncrk... ",13,10
                db " ",Fichier," -> Patching... ",13,10
                db " ",Fichier," -> Patched successfully! ",0


; Erreurs...
 err_find_file  db "(¯`·.___..-=> In Progress <=-..___.·´¯)",13,10,13,10
                db " ",Fichier," -> Openning... ",0

 size_err_txt   db "(¯`·.___..-=>    Shit!    <=-..___.·´¯)",13,10,13,10
                db " ",Fichier," -> Openning... ",13,10
                db " ",Fichier," -> Checking size... ",13,10
                db " ERROR -> Bad size.",0

;*--------------------------------------------*
;*----=Structures, variable et constantes=----*
;*--------------------------------------------*

;OpenBox

OPENFILENAME struc
lStructSize       dd ?
hwndOwner         dd ?
hInstance         dd ?
lpstrFilter       dd ?
lpstrCustomFilter dd ?
nMaxCustFilter    dd ?
nFilterIndex      dd ?
lpstrFile         dd ?
nMaxFile          dd ?
lpstrFileTitle    dd ?
nMaxFileTitle     dd ?
lpstrInitialDir   dd ?
lpstrTitle        dd ?
Flags             dd ?
nFileOffset       dw ?
nFileExtension    dw ?
lpstrDefExt       dd ?
lCustData         dd ?
lpfnHook          dd ?
lpTemplateName    dd ?
OPENFILENAME ends

open_struct      OPENFILENAME    <76,NULL,NULL,offset open_fichier,NULL,NULL,1,offset open_name,\
                                 200h,NULL,NULL,NULL,offset open_caption,OFN_FILEMUSTEXIST+OFN_HIDEREADONLY+\
                                 OFN_PATHMUSTEXIST,NULL,NULL,offset open_exe,NULL,NULL,NULL>
      
open_fichier     db " (",Fichier,")",0,Fichier,0,0
open_exe         db "exe",0

;--------------------*

 fhandle      	dd ?
 fichier      	db Fichier,0
 filebak      	db Fichier,".uncrk",0
 flag         	db 0
 open_name    	db 201h dup (0)
 bwrite       	dd ?
 new_val      	db new_val0
 patch_ptr    	dd patch_ptr0
 long_bloc    	dd long_bloc0
 msg          	MSGSTRUCT <?>
 wc           	WNDCLASS  <?>
 save         	db 0
 infos        	db 0
 hIce         	dd 0
 hInst	      	DD 0
 hMain	      	DD 0
 hFILE	      	DD 0

 KeyDown      	DB   0
 MouseX       	DD   ?
 MouseY       	DD   ?
 rect         	RECT	<?> 

 etat         	db 0
 cancel       	db 0

;Handle

 hDC		dd 0
 hMemDC		dd 0
 hIcon        	dd 0
 handle_of_edit dd 0
 hwnd_nfo       dd 0
 hrgn1        	HRGN ? 
 hrgn2        	HRGN ?
 hrgn3        	HRGN ?

 hbutt1      	 dd  0
 hibutt11     	 dd  0
 hibutt12     	 dd  0

 hbutt2      	 dd  0
 hibutt21     	 dd  0
 hibutt22     	 dd  0

 hbutt3      	 dd  0
 hibutt31     	 dd  0
 hibutt32     	 dd  0

 hbutt4      	 dd  0
 hibutt41     	 dd  0
 hibutt42     	 dd  0

;Coordonées forme
trg      TRG		<169,0,183,14,190,14,190,0>
trg_1    TRG		<348,28,353,33,353,28>
trg_2    TRG		<348,198,353,193,353,199>
trg_3    TRG		<61,211,74,198,74,211>
trg_4    TRG_long	<88,34,102,20,105,28,103,26,96,32,94,33>
trg_5    TRG		<92,23,97,18,104,18,97,25>
StaticClassName  	db "STATIC",0

FontName1		db "Courrier New",0
FontName2		db "terminal",0


;---Son---*

 file_name 	db "sound.mus"

 MIDbuff	db 256 dup(0)
 seq		db 'sequencer',0
 wDeviceID	dd 0

.data?

 hPlay		dd ?
 hPause		dd ?
 hStop		dd ?

 mciOpenParms	MCI_OPEN_PARMS <?>
 mciPlayParms	MCI_PLAY_PARMS <?>


;----------------------------------------------------------------------------------------*
;---------------*---------------------------=Code=-------------------------*-------------*
;----------------------------------------------------------------------------------------* 

.Code

open_file:   
    push   0
    push   FILE_ATTRIBUTE_NORMAL	; met l'attribu en standard
    push   OPEN_EXISTING
    push   0
    push   FILE_SHARE_READ

    push   GENERIC_WRITE
    cmp    flag, 01
    jne    premier_passage
    push   offset open_name
    jmp    second_passage

premier_passage:
    push   offset fichier 		; Nom du fichier

second_passage:
    Call   CreateFileA                  ; ouvre le fichier
    mov    fhandle,eax
    cmp    eax, INVALID_HANDLE_VALUE    ; eax=INVALID_HANDLE_VALUE alors erreur
    jne    fichier_present
    cmp    flag, 01
    je     erreur_open_file
    push   offset err_find_file
    push   0
    push   WM_SETTEXT
    push   IDD_BOX1
    call   SendDlgItemMessageA,hwnd
    mov    eax,[hwnd]			;
    mov    [open_struct.hwndOwner],eax	;
    mov    eax,[hInst]			;
    mov    [open_struct.hInstance],eax	; Déclaration propriétaire de l'OpenBox
    push   offset open_struct		; On ouvre l'OpenBox    
    call   GetOpenFileNameA
    test   eax, eax                     ; Si c'est Cancel, on reste
    mov    [infos],0
    je     gestion_cancel
    mov    flag, 01
    jmp    open_file

gestion_cancel:
   mov     [cancel],1
   jmp     main_init_suite2

fichier_present:                	; fichier ouvert sans problème
    push   0
    push   fhandle               	; alors on pousse File_Handle
    Call   GetFileSize           
    cmp    eax, taille           	; on vérifie que le fichier fait la bonne taille
    je     taille_ok
    jmp    mauvaise_taille

taille_ok:
    push   TRUE                  	; fait la copie de sauvegarde
    push   offset filebak       
    push   offset fichier       
    call   CopyFileA             	; copie pour uncrk
    cmp    eax, 0                	; erreur ?
    jne    copy_ok               	; non, alors copy_ok
    jmp    backup_erreur

copy_ok:                        	; Maintenant on peut patcher notre fichier
    xor    ecx, ecx                	; gestion du compteur pour la boucle
    mov    eax, offset patch_ptr   
    mov    edx, offset long_bloc   
    mov    ebx, offset new_val     

boucle:                         	; boucle autant de fois qu'il y a de blocs à patcher
    pusha
    pusha                          	; On sauve les registres 2 fois 
    mov    eax, dword ptr [eax]    	; eax = offset dans le fichier
    
    push   FILE_BEGIN             
    push   0
    push   eax
    push   fhandle
    call   SetFilePointer         	; on déplace le pointeur de fichier
    popa                          	; on récupère les registres

    mov    edx, dword ptr [edx]    	; edx = longueur du bloc à écrire
    push   0
    push   offset bwrite
    push   edx
    push   ebx
    push   fhandle
    call   WriteFile               	; écrit
    popa                           	; récupère les registres

    inc    ecx
    cmp    ecx, nb_blocs             	; tous les octects sont patché?
    je     fin_boucle                	; alors fin_boucle
    add    ebx, dword ptr [edx]
    add    edx, 4
    add    eax, 4
    jmp    boucle                   	; boucle autant de fois su'il y à d'octects à patcher

fin_boucle:               		; patch réussit !!
    push   offset textfin
    push   0
    push   WM_SETTEXT
    push   IDD_BOX1
    call   SendDlgItemMessageA,hwnd
    mov    eax, 1
    jmp    fin_kill_handle

fin_kill_handle:            		; ferme le fichier avant de partir
    push   fhandle
    call   CloseHandle
    jmp    main_finish


;*--------------------------------------------*
;*-------------=Gestion d'erreurs=------------*
;*--------------------------------------------*

erreur_open_file:
    push    offset open_struct
    call    GetOpenFileNameA 
    jmp     main_dlgdestroy

mauvaise_taille:
    push    offset size_err_txt
    push    0
    push    WM_SETTEXT
    push    IDD_BOX1
    call    SendDlgItemMessageA,hwnd
    mov     eax, 1
    jmp     main_finish

backup_erreur:
    push    fhandle
    call    CloseHandle
    push    offset filebak       
    call    DeleteFileA
    jmp     taille_ok

;----------------------------------------------------------------------------------------*
;--------------*-------------=Gestion des ressources graphiques=-----------*-------------*
;----------------------------------------------------------------------------------------* 


Start:

    Call    FindWindowA,0, offset titre	;|
    test    eax,eax			;\ empeche la double ouverture du patch, on sait jamais ;p
    jz      go				;/	
    ret					;|

go:

    Call    GetModuleHandleA,0
    mov     [hIce], eax  

    mov     [etat],1 		; permet d'indiquer que l'on est sur la fenetre principale ! S'il est modifi‚ ne pas oubli‚ de le remettre !
    push    0
    push    offset Main_DlgProc
    push    0
    push    ID_DLG
    push    [hIce]
    call    DialogBoxParamA
    jmp     finish
		
Main_DlgProc proc hwnd:DWORD, wmsg:DWORD, wparam:DWORD, lparam:DWORD
    LOCAL hBrush1    :DWORD

    push    ebx
    push    esi
    push    edi

    cmp     [wmsg], WM_CTLCOLORSTATIC
    jz      main_colorstatic
    cmp     [wmsg], WM_COMMAND
    jz      main_command
    cmp     [wmsg], WM_INITDIALOG
    jz      main_init
    cmp     [wmsg], WM_CLOSE
    jz      main_dlgdestroy
    cmp     [wmsg], WM_LBUTTONDOWN 
    jz      main_ldown
    cmp     [wmsg], WM_LBUTTONUP
    jz      main_lup
    cmp     [wmsg], WM_MOUSEMOVE
    jz      main_move
    cmp     [wmsg], WM_DRAWITEM
    jz      main_draw

overcolor1:
    mov     eax, 0

main_finish:  
    pop     edi          ; recupere les registres
    pop     esi
    pop     ebx 
    ret

Main_DlgProc    endp


finish: 

    call DeleteObject,hBrush1
    pop     ebx		; recupere les registres
    pop     edi
    pop     esi
    ret

main_colorstatic:

    mov     eax,lparam 				;h_edit
    cmp     handle_of_edit,eax
    jne     overcolor1

    mov     eax,wmsg
    mov     eax,wparam 				;hdc

    call    SetBkMode,wparam,2       		; 1 = TRANSPARENT ou 2 = OPAQUE
    call    SetTextColor,wparam,txt_color 	; 
    call    SetBkColor,wparam,  00000000h 	; Noir  SetBkMode NON UTILISE

    call    CreateSolidBrush,   00000000h 	; brush color value
    mov     hBrush1,eax
    jmp     main_finish


main_init:
    Push    102            			; l'Id de l'icone ds le RES
    push    [hIce]
    Call    LoadIconA
    mov     hIcon,eax      			; le handle de l'icone

    Push    hIcon
    push    1
    push    WM_SETICON
    push    hwnd
    call    SendMessageA

    push    IDD_BOX1          			; get handle Dialog
    push    [hwnd]            			; de l'edit
    call    GetDlgItem        			; field
    mov     handle_of_edit,eax

    call CreateFontA,13,5,0,0,100,0,0,0,DEFAULT_CHARSET,OUT_DEFAULT_PRECIS,CLIP_CHARACTER_PRECIS,PROOF_QUALITY,DEFAULT_PITCH or FF_SWISS,offset FontName1
;    call CreateFontA,11,7,0,0,100,0,0,0,DEFAULT_CHARSET ,OUT_DEFAULT_PRECIS,1,1,1,offset FontName1
    call    SendMessageA, handle_of_edit, WM_SETFONT, eax, 1


; Patch
    call    GetDlgItem , hwnd, 1000
    mov     hbutt1,eax
    call    LoadBitmapA,hIce,4011 
    mov     hibutt11, eax
; About
    call    GetDlgItem , hwnd, 1005
    mov     hbutt2,eax
    call    LoadBitmapA,hIce,4021 
    mov     hibutt21, eax
; About
    call    GetDlgItem , hwnd, 1002
    mov     hbutt3,eax
    call    LoadBitmapA,hIce,4031 
    mov     hibutt31, eax
; Exit
    call    GetDlgItem , hwnd, 1001
    mov     hbutt4,eax
    call    LoadBitmapA,hIce,4041 
    mov     hibutt41, eax


;Joue le midi (la chié pour le faire)
    cmp      music_or_not, 0						
    je      no_music
    mov      mciOpenParms.mciopen_lpstrDeviceType, OFFSET seq		; ouvre le sequece
    mov      mciOpenParms.mciopen_lpstrElementName, OFFSET file_name	; on met le nom dans l'element à jouer
    push     OFFSET mciOpenParms					; reglage des parametres
    push     MCI_OPEN_ELEMENT+MCI_OPEN_TYPE				; on pousse le peripherique avec l'element
    push     MCI_OPEN							; on pousse l'element
    push     NULL							; 0
    Call     mciSendCommandA						; on appel mci
    mov      bx, mciOpenParms.mciopen_wDeviceID				; on met les parametres dans bx
    mov      word ptr[wDeviceID], bx					; on met bx dans le peripherique
    push     OFFSET mciPlayParms					; on pousse les parametres
    push     MCI_NOTIFY							; on pousse la notification
    push     MCI_PLAY							; on pousse l'action
    push     wDeviceID							; on pousse le peripherique
    Call     mciSendCommandA						; et on active

no_music:
;Fin de section

;    push     191
;    push     353
;    push     1
;    push     1
;    call     CreateRectRgn
;    mov      hrgn2, eax

    push     1
    push     hrgn2
    push     hwnd
    call     SetWindowRgn
	
    call   CreateRoundRectRgn, 1, 1, 214, 21, 7, 25
    mov    hrgn1, eax
    call   CreateRectRgn, 2, 23, 353, 211
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_OR

    call   CreateRectRgn, 102, 20, 354, 28
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF

    call   CreateRectRgn, 74, 198, 354, 212
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF

    call   CreateRectRgn, 350, 47, 354, 179
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF

    call   CreatePolygonRgn, offset trg_1, 3, 1
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call   CreatePolygonRgn, offset trg_2, 3, 1
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call   CreatePolygonRgn, offset trg_3, 3, 1
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call   CreatePolygonRgn, offset trg_4, 6, 1
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_DIFF
    call   CreatePolygonRgn, offset trg_5, 4, 1
    mov    hrgn2, eax
    call   CombineRgn, hrgn1, hrgn1, hrgn2, RGN_OR
    call   SetWindowRgn, hwnd, hrgn1, 1

main_init_suite2:
; Change le nom de la barre de titre de la fenetre !
; Change the name of the bar of title of the fenetre!

    Push      offset titre
    push      NULL
    push      WM_SETTEXT
    push      hwnd
    call      SendMessageA

    push      offset crk_release
    push      0
    push      WM_SETTEXT
    push      IDD_BOX1
    call      SendDlgItemMessageA,hwnd
    cmp       [cancel],1			; ici [cancel] sert à savoir si on a cliquer sur le Cancel de l'openbox
    je        jump_refresh			; si c'est le cas, on ne rafraichi pas la fenetre sinon => recentrage


jump_refresh:
    mov     eax, 1
    jmp     main_finish


main_draw:
    call    CopyBitMap, hbutt1, hibutt11, 80, 21
    call    CopyBitMap, hbutt2, hibutt21, 80, 20
    call    CopyBitMap, hbutt3, hibutt31, 80, 21
    call    CopyBitMap, hbutt4, hibutt41, 80, 20

    jmp     main_finish

main_abt:					; about
    cmp     [infos],0
    jnz     main_release
    mov     [infos],1
    push    offset about
    jmp     real_about

main_release:
    mov     [infos],0
    push    offset crk_release
    jmp     real_about

real_about:
    push    0
    push    WM_SETTEXT
    push    IDD_BOX1
    call    SendDlgItemMessageA,hwnd
    mov     eax, 1
    jmp     main_finish

main_nfo:
    mov     [etat],2 				; defini la fenetre courante !
    push    0
    push    offset Nfo_DlgProc 
    push    hwnd
    push    ID_NFODLG
    push    [hIce]
    call    CreateDialogParamA
    mov     hwnd_nfo, eax
    jmp     main_finish

main_reduc:
    Call    ShowWindow, hwnd, SW_SHOWMINIMIZED
    mov     eax, 1
    jmp     main_finish

main_command:
    cmp     [wparam], IDD_OPEN			; Patch iD
    jz      open_file
    cmp	    [wparam], IDD_ABT			; About iD
    jz      main_abt

    cmp     [etat],2				; \Permet d'ouvrir qu'uîe fois la fenetre nfo
    jz      next				; /
    cmp     [wparam], IDD_NFO                   ; nfo
    jz      main_nfo

next:
    cmp	    [wparam], IDD_REDUC			; Reduction iD
    jz      main_reduc
    cmp	    [wparam], IDD_CROSS 		; Croix iD
    jz      main_dlgdestroy
    cmp     [wparam], IDD_EXIT			; Quit  iD
    jz      main_dlgdestroy
    mov     eax, 0
    jmp     main_finish
	
main_dlgdestroy:
    Call    ShowWindow, hwnd, SW_SHOWMINIMIZED
    call    ExitProcess				; on quitte...


CopyBitMap  PROC hButt:DWORD, hBmp, bWh, bHt

    call    GetDC, hButt
    mov     hDC, eax
    Call    CreateCompatibleDC, hDC
    mov     hMemDC, eax
    Call    SelectObject, hMemDC, hBmp
    Call    BitBlt, hDC, 0, 0, bWh, bHt, hMemDC, 0, 0, SRCCOPY
    Call    DeleteDC, hMemDC
    Call    ReleaseDC, hButt, hDC

    xor    eax, eax
    ret
CopyBitMap  endp

End Start
                                                                         