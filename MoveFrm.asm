.386P
Locals
Jumps
;include WP32.inc
.Model Flat, StdCall
.DATA

 tx    dd ?
 ty    dd ?

POINT struc
 x       dd ?
 y       dd ?
POINT ends

 pt      POINT    <NULL,NULL>




.CODE

;la chié pr bouger la fen
main_ldown:
    push   201
    push   [hIce]
    call   LoadCursorA

    push   eax
    call   SetCursor

    push   offset rect
    push   hwnd 
    call   GetWindowRect

    mov    ecx, rect.right
    sub    ecx, rect.left
    mov    tx, ecx
    mov    edx, rect.bottom
    sub    edx, rect.top
    mov    ty, edx

    mov    eax,lparam
    shr    eax,16
    mov    MouseY, eax
    mov    eax, lparam
    and    eax, 0FFFFh
    mov    MouseX, eax
    mov    KeyDown, 1
    push   hwnd 
    call   SetCapture


    mov    eax, 1
    jmp    main_finish

main_lup:
    mov    KeyDown, 0 
    call   ReleaseCapture
    mov    eax, 1
    jmp    main_finish


main_move:
    cmp    KeyDown, 1
    jnz    main_finish

    push   offset pt
    call   GetCursorPos
    inc    pt.x
    inc    pt.y

    mov    eax,rect.left
    sub    pt.x, eax
    mov    eax,rect.top
    sub    pt.y, eax

    mov    eax,pt.x 
    sub    eax, MouseX
    add    rect.left, eax
    mov    ebx,pt.y
    sub    ebx, MouseY
    add    rect.top, ebx

    push   NULL
    push   ty
    push   tx
    push   rect.top
    push   rect.left
    push   NULL
    push   hwnd 
    call   SetWindowPos 
  
    mov    eax, 1
    jmp    main_finish



