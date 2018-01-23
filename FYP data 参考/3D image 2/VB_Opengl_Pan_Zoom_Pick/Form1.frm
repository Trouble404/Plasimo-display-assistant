VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "VB_Opengl_Pan_Zoom_Pick By LLL"
   ClientHeight    =   9285
   ClientLeft      =   60
   ClientTop       =   435
   ClientWidth     =   13185
   LinkTopic       =   "Form1"
   ScaleHeight     =   619
   ScaleMode       =   3  'Pixel
   ScaleWidth      =   879
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command20 
      Caption         =   "保存"
      Height          =   615
      Left            =   7440
      TabIndex        =   35
      Top             =   960
      Width           =   1455
   End
   Begin VB.CheckBox Check6 
      Caption         =   "shade"
      Height          =   375
      Left            =   1440
      TabIndex        =   34
      Top             =   1440
      Width           =   975
   End
   Begin VB.CheckBox Check5 
      Caption         =   "坐标系"
      Height          =   375
      Left            =   480
      TabIndex        =   33
      Top             =   2160
      Width           =   975
   End
   Begin VB.PictureBox Picture1 
      Appearance      =   0  'Flat
      BackColor       =   &H80000005&
      ForeColor       =   &H80000008&
      Height          =   6015
      Left            =   120
      ScaleHeight     =   399
      ScaleMode       =   3  'Pixel
      ScaleWidth      =   857
      TabIndex        =   32
      Top             =   2640
      Width           =   12885
   End
   Begin VB.CheckBox Check4 
      Caption         =   "光照"
      Height          =   375
      Left            =   480
      TabIndex        =   31
      Top             =   1800
      Width           =   855
   End
   Begin VB.CheckBox Check3 
      Caption         =   "边界"
      Height          =   375
      Left            =   480
      TabIndex        =   30
      Top             =   1440
      Width           =   855
   End
   Begin VB.CheckBox Check2 
      Caption         =   "云图"
      Height          =   375
      Left            =   480
      TabIndex        =   29
      Top             =   1080
      Width           =   855
   End
   Begin VB.CheckBox Check1 
      Caption         =   "网格"
      Height          =   375
      Left            =   480
      TabIndex        =   28
      Top             =   720
      Width           =   855
   End
   Begin VB.CommandButton Command19 
      Caption         =   "打开"
      Height          =   615
      Left            =   5280
      TabIndex        =   27
      Top             =   1080
      Width           =   1335
   End
   Begin VB.CommandButton Command18 
      Caption         =   "水平-"
      Height          =   435
      Left            =   -960
      TabIndex        =   26
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command17 
      Caption         =   "垂直-"
      Height          =   435
      Left            =   -960
      TabIndex        =   25
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command16 
      Caption         =   "X轴-"
      Height          =   435
      Left            =   -960
      TabIndex        =   24
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command15 
      Caption         =   "Y轴-"
      Height          =   435
      Left            =   -960
      TabIndex        =   23
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command14 
      Caption         =   "Z轴-"
      Height          =   435
      Left            =   -960
      TabIndex        =   22
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command13 
      Caption         =   "垂直+"
      Height          =   435
      Left            =   -960
      TabIndex        =   21
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command12 
      Caption         =   "水平+"
      Height          =   435
      Left            =   -960
      TabIndex        =   20
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command11 
      Caption         =   "适合"
      Height          =   435
      Left            =   -960
      TabIndex        =   19
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command10 
      Caption         =   "Z轴+"
      Height          =   435
      Left            =   -960
      TabIndex        =   18
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command9 
      Caption         =   "Y轴+"
      Height          =   435
      Left            =   -960
      TabIndex        =   17
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command8 
      Caption         =   "X轴+"
      Height          =   435
      Left            =   -960
      TabIndex        =   16
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command7 
      Caption         =   "下移"
      Height          =   435
      Left            =   -960
      TabIndex        =   15
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command6 
      Caption         =   "上移"
      Height          =   435
      Left            =   -960
      TabIndex        =   14
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command5 
      Caption         =   "右移"
      Height          =   435
      Left            =   -960
      TabIndex        =   13
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command4 
      Caption         =   "左移"
      Height          =   435
      Left            =   -960
      TabIndex        =   12
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command2 
      Caption         =   "放大"
      Height          =   435
      Left            =   -960
      TabIndex        =   11
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.CommandButton Command3 
      Caption         =   "缩小"
      Height          =   435
      Left            =   -960
      TabIndex        =   10
      Top             =   960
      Visible         =   0   'False
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   345
      Left            =   9960
      TabIndex        =   9
      Top             =   2040
      Width           =   1635
   End
   Begin VB.TextBox Text2 
      Height          =   345
      Left            =   7800
      TabIndex        =   8
      Top             =   2040
      Width           =   1845
   End
   Begin VB.TextBox Text1 
      Height          =   315
      Left            =   11160
      TabIndex        =   7
      Top             =   300
      Width           =   1125
   End
   Begin VB.CommandButton Command1 
      Caption         =   "下视图"
      Height          =   435
      Index           =   5
      Left            =   6120
      TabIndex        =   5
      Top             =   150
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "上视图"
      Height          =   435
      Index           =   4
      Left            =   4920
      TabIndex        =   4
      Top             =   150
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "右视图"
      Height          =   435
      Index           =   3
      Left            =   3720
      TabIndex        =   3
      Top             =   150
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "左视图"
      Height          =   435
      Index           =   2
      Left            =   2520
      TabIndex        =   2
      Top             =   150
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "后视图"
      Height          =   435
      Index           =   1
      Left            =   1320
      TabIndex        =   1
      Top             =   150
      Width           =   1215
   End
   Begin VB.CommandButton Command1 
      Caption         =   "前视图"
      Height          =   435
      Index           =   0
      Left            =   120
      TabIndex        =   0
      Top             =   150
      Width           =   1215
   End
   Begin VB.Label Label1 
      AutoSize        =   -1  'True
      Caption         =   "选中物体："
      Height          =   180
      Left            =   10200
      TabIndex        =   6
      Top             =   360
      Width           =   900
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim Draft3D As New MyDraft3D
Dim Draft3D_axes As New MyDraft3D
    
Dim imaxn As Integer, jmaxn As Integer, kmaxn As Integer


Private Sub Check1_Click()
    is_show_grid = Check1.Value: Draft3D.View1_Paint
End Sub

Private Sub Check2_Click()
    is_show_contour = Check2.Value: Draft3D.View1_Paint
    
End Sub

Private Sub Check3_Click()
    is_show_boundary = Check3.Value: Draft3D.View1_Paint
    
End Sub

Private Sub Check4_Click()
    is_show_light = Check4.Value: Draft3D.View1_Paint
    
End Sub

Private Sub Check5_Click()
    is_show_axies = Check5.Value: Draft3D.View1_Paint
    
End Sub

Private Sub Check6_Click()
    is_show_shade = Check6.Value: Draft3D.View1_Paint
    
End Sub

Private Sub Command1_Click(Index As Integer)
    Select Case Index
    Case 0
        Draft3D.ChangeViewDirection ViewFront                                   '前视图
    Case 1
        Draft3D.ChangeViewDirection ViewBack                                    '后视图
    Case 2
        Draft3D.ChangeViewDirection viewLeft                                    '左视图
    Case 3
        Draft3D.ChangeViewDirection ViewRight                                   '右视图
    Case 4
        Draft3D.ChangeViewDirection ViewTop                                     '上视图
    Case 5
        Draft3D.ChangeViewDirection ViewBottom                                  '下视图
    End Select
End Sub

Private Sub Command10_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Z
End Sub

Private Sub Command11_Click()
    glHint htPerspectiveCorrectionHint, hmNicest                                ' Really Nice Perspective Calculations，计算实际最佳投影
    
End Sub

Private Sub Command12_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Level
End Sub

Private Sub Command13_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Verticalf
    
End Sub

Private Sub Command14_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Zf
    
End Sub

Private Sub Command15_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Yf
    
End Sub

Private Sub Command16_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Xf
    
End Sub

Private Sub Command17_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Vertical
End Sub

Private Sub Command18_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Levelf
    
End Sub

Private Sub Command19_Click()
    
    
    Open "wall.x" For Input As #1
    
    
    Dim i As Integer
    Dim j As Integer
    Dim k As Integer
    Dim n As Integer
    
    Input #1, zone
    '    Debug.Print zone
    
    ReDim imax(zone)
    ReDim jmax(zone)
    ReDim kmax(zone)
    
    For n = 1 To zone
        Input #1, imax(n), jmax(n), kmax(n)
        If imaxn < imax(n) Then imaxn = imax(n)
        If jmaxn < jmax(n) Then jmaxn = jmax(n)
        If kmaxn < kmax(n) Then kmaxn = kmax(n)
        '        Debug.Print imax(n), jmax(n), kmax(n)
    Next n
    '    Debug.Print imaxn, jmaxn, kmaxn
    ReDim X(imaxn, jmaxn, kmaxn, zone)
    ReDim y(imaxn, jmaxn, kmaxn, zone)
    ReDim z(imaxn, jmaxn, kmaxn, zone)
    
    xmax = 0: ymax = 0: zmax = 0
    
    For n = 1 To zone
        
        For k = 1 To kmax(n)
            For j = 1 To jmax(n)
                For i = 1 To imax(n)
                    Input #1, X(i, j, k, n)
                    If xmax < X(i, j, k, n) Then xmax = X(i, j, k, n)
                Next i
            Next j
        Next k
        
        For k = 1 To kmax(n)
            For j = 1 To jmax(n)
                For i = 1 To imax(n)
                    Input #1, y(i, j, k, n)
                    If ymax < y(i, j, k, n) Then ymax = y(i, j, k, n)
                Next i
            Next j
        Next k
        
        For k = 1 To kmax(n)
            For j = 1 To jmax(n)
                For i = 1 To imax(n)
                    Input #1, z(i, j, k, n)
                    If zmax < z(i, j, k, n) Then zmax = z(i, j, k, n)
                Next i
            Next j
        Next k
        
    Next n
    
    Close #1
    
End Sub

Private Sub Command2_Click()
    Dim c1 As New MyDraft3D
    c1.Zoom_Out
End Sub

Private Sub Command20_Click()
    On Error Resume Next
    SavePicture Picture1.Picture, App.Path + "\1.jpg"
End Sub

Private Sub Command3_Click()
    Dim c1 As New MyDraft3D
    c1.Zoom_In
    
End Sub

Private Sub Command4_Click()
    Dim c1 As New MyDraft3D
    c1.Trans_Left
End Sub

Private Sub Command5_Click()
    Dim c1 As New MyDraft3D
    c1.Trans_Right
    
End Sub

Private Sub Command6_Click()
    Dim c1 As New MyDraft3D
    c1.Trans_Up
    
End Sub

Private Sub Command7_Click()
    Dim c1 As New MyDraft3D
    c1.Trans_Down
    
End Sub

Private Sub Command8_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_X
End Sub

Private Sub Command9_Click()
    Dim c1 As New MyDraft3D
    c1.Rotate_Y
End Sub

Private Sub Form_Load()
    '
    '    Open "wall.x" For Input As #1
    '
    '
    '    Dim i As Integer
    '    Dim j As Integer
    '    Dim k As Integer
    '    Dim n As Integer
    '
    '    Input #1, zone
    '    '    Debug.Print zone
    '
    '    ReDim imax(zone)
    '    ReDim jmax(zone)
    '    ReDim kmax(zone)
    '
    '    For n = 1 To zone
    '        Input #1, imax(n), jmax(n), kmax(n)
    '        If imaxn < imax(n) Then imaxn = imax(n)
    '        If jmaxn < jmax(n) Then jmaxn = jmax(n)
    '        If kmaxn < kmax(n) Then kmaxn = kmax(n)
    '        '        Debug.Print imax(n), jmax(n), kmax(n)
    '    Next n
    '    '    Debug.Print imaxn, jmaxn, kmaxn
    '    ReDim X(imaxn, jmaxn, kmaxn, zone)
    '    ReDim y(imaxn, jmaxn, kmaxn, zone)
    '    ReDim z(imaxn, jmaxn, kmaxn, zone)
    '
    '    For n = 1 To zone
    '        For k = 1 To kmax(n)
    '            For j = 1 To jmax(n)
    '                For i = 1 To imax(n)
    '                    Input #1, X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
    '                Next i
    '            Next j
    '        Next k
    '    Next n
    '
    '    Close #1
    
    Draft3D.BindView Picture1, 1
    HookMouse Me.hwnd
    
End Sub

Private Sub Form_Resize()
    Picture1.Width = Me.ScaleWidth
    Picture1.Height = Me.ScaleHeight
End Sub

Private Sub Form_Unload(Cancel As Integer)
    UnHookMouse Me.hwnd
    
End Sub

Private Sub Picture1_KeyDown(KeyCode As Integer, Shift As Integer)
    Dim c1 As New MyDraft3D
    
    Select Case KeyCode
    Case vbKeyUp
        c1.Rotate_Verticalf
        
    Case vbKeyDown
        c1.Rotate_Vertical
        
    Case vbKeyLeft
        c1.Rotate_Levelf
        
    Case vbKeyRight
        c1.Rotate_Level
        
    Case vbKeyA
        c1.Trans_Left
        
    Case vbKeyD
        c1.Trans_Right
        
    Case vbKeyS
        c1.Trans_Down
        
    Case vbKeyW
        c1.Trans_Up
        
    Case vbKeyPageUp
        c1.Zoom_Out
        
    Case vbKeyPageDown
        c1.Zoom_In
        
        
        
    End Select
End Sub
