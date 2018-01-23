Attribute VB_Name = "HookModule"
'VB �������¼�

'***********************************************************
'**ģ �� ��         ModuleMouseWheel
'**��    ��         �����ֵ��¼����
'**��    ��         ʯ½
'***********************************************************
Option Explicit


Private Declare Function CallWindowProc Lib "User32" Alias "CallWindowProcA" (ByVal lpPrevWndFunc As Long, ByVal hwnd As Long, ByVal Msg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
Private Declare Function SetWindowLong Lib "User32" Alias "SetWindowLongA" (ByVal hwnd As Long, ByVal nIndex As Long, ByVal dwNewLong As Long) As Long


Private Const GWL_WNDPROC = -4
Private Const WM_MOUSEWHEEL = &H20A

Global lpPrevWndProcA As Long


Public bMouseFlag As Boolean                                                    '����¼������־
Public wzDelta, wKeys As Integer
'wzDelta���ݹ��ֹ����Ŀ�������ֵС�����ʾ���������������û����򣩣�
'�������ʾ������ǰ����������ʾ������
'wKeysָ���Ƿ���CTRL=8��SHIFT=4������(��=2����=16����=2������)���£�������

Public Sub HookMouse(ByVal hwnd As Long)
    lpPrevWndProcA = SetWindowLong(hwnd, GWL_WNDPROC, AddressOf WindowProc)
End Sub

Public Sub UnHookMouse(ByVal hwnd As Long)
    SetWindowLong hwnd, GWL_WNDPROC, lpPrevWndProcA
End Sub

Private Function WindowProc(ByVal hw As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long) As Long
    Dim c1 As New MyDraft3D
    
    
    Select Case uMsg
    Case WM_MOUSEWHEEL                                                          '����
        
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
    HIWORD = (LongIn And &HFFFF0000) \ &H10000                                  'ȡ��32λֵ�ĸ�16λ
End Function
Private Function LOWORD(LongIn As Long) As Integer
    LOWORD = LongIn And &HFFFF&                                                 'ȡ��32λֵ�ĵ�16λ
End Function



