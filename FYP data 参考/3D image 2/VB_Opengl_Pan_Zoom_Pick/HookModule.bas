Attribute VB_Name = "HookModule"
'VB 鼠标滚动事件

'***********************************************************
'**模 块 名         ModuleMouseWheel
'**作    用         鼠标滚轮的事件检测
'**作    者         石陆
'***********************************************************
Option Explicit


Private Declare Function CallWindowProc Lib "User32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function SetWindowLong Lib "User32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long


Private Const GWL_WNDPROC = -4
Private Const WM_MOUSEWHEEL = &H20A

Global lpPrevWndProcA As Long


Public bMouseFlag As Boolean                                                    '鼠标事件激活标志
Public wzDelta, wKeys As Integer
'wzDelta传递滚轮滚动的快慢，该值小于零表示滚轮向后滚动（朝用户方向），
'大于零表示滚轮向前滚动（朝显示器方向）
'wKeys指出是否有CTRL=8、SHIFT=4、鼠标键(左=2、中=16、右=2、附加)按下，允许复合

Public Sub HookMouse(ByVal hwnd As Long)
    lpPrevWndProcA = SetWindowLong(hwnd, GWL_WNDPROC, AddressOf WindowProc)
End Sub

Public Sub UnHookMouse(ByVal hwnd As Long)
    SetWindowLong hwnd, GWL_WNDPROC, lpPrevWndProcA
End Sub

Private Function WindowProc(ByVal hw As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
    Dim c1 As New MyDraft3D
    
    
    Select Case uMsg
    Case WM_MOUSEWHEEL                                                          '滚动
        
        wzDelta = HIWORD(wParam)
        
        wKeys = LOWORD(wParam)
        
        bMouseFlag = True
        '--------------------------------------------------
        If wzDelta < 0 Then
            c1.Zoom_Out
        Else
            c1.Zoom_In
        End If
        '--------------------------------------------------
    Case Else
        bMouseFlag = False
        WindowProc = CallWindowProc(lpPrevWndProcA, hw, uMsg, wParam, lParam)
    End Select
    
End Function

Private Function HIWORD(LongIn As Long) As Integer
    HIWORD = (LongIn And &HFFFF0000) \ &H10000                                  '取出32位值的高16位
End Function
Private Function LOWORD(LongIn As Long) As Integer
    LOWORD = LongIn And &HFFFF&                                                 '取出32位值的低16位
End Function



