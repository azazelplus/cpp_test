
; RCtrl & 4::  ; 只监听右 Ctrl + Shift + 4
; return

>^+4::  ; 监听Rctrl + Shift + 4
{
    Send("{End}")  ; 按下end键
}

>^0::  ; 监听Rctrl + Shift + 4
{
    Send("{Home}")  ; 按下end键
}

>^0::  ; 监听Rctrl + Shift + 4
{
    Send("{End}")  ; 将光标移动到行尾
}

Numpad0 & Numpad1::
{
    MsgBox "You pressed Numpad1 while holding down Numpad0."
}









