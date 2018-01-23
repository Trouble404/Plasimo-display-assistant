VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "MyDraft3D"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'为了使被显示的三维物体数字化，要在被显示的物体所在的空间中定义一个坐标系。这个坐标系的长度单位和坐标轴的方向要适合对被显示物体的描述，这个坐标系称为世界坐标系。
'世界坐标系是始终固定不变的。
'OpenGL还定义了局部坐标系的概念，所谓局部坐标系，也就是坐标系以物体的中心为坐标原点，物体的旋转或平移等操作都是围绕局部坐标系进行的，
'这 时，当物体模型进行旋转或平移等操作时，局部坐标系也执行相应的旋转或平移操作。需要注意的是，如果对物体模型进行缩放操作，则局部坐标系也要进行相应的 缩放，
'如果缩放比例在案各坐标轴上不同，那么再经过旋转操作后，局部坐标轴之间可能不再相互垂直。无论是在世界坐标系中进行转换还是在局部坐标系中进行转 换，程序代码是相同的，
'只是不同的坐标系考虑的转换方式不同罢了?

'计算机对数字化的显示物体作了加工处理后，要在图形显示器上显示，这就要在图形显示器屏幕上定义一个二维直角坐标系，这个坐标系称为屏幕坐标系。
'这个坐标系坐标轴的方向通常取成平行于屏幕的边缘，坐标原点取在左下角，长度单位常取成一个象素。


Option Explicit

'Const GWL_WNDPROC = -4
'Const WM_MOUSEWHEEL = &H20A
'Public PrevWndProc     As Long




Private WithEvents View1 As PictureBox
Attribute View1.VB_VarHelpID = -1

'以下用于坐标缩放
'Private m_left As Double
'Private m_right As Double
'Private m_bottom As Double
'Private m_top As Double
Private m_zNear As Double
Private m_zFar As Double
'
Private m_mouseX As Integer
Private m_mouseY As Integer
Private m_mouseLeft As Boolean
Private m_mouseMiddle As Boolean
Private m_mouseRight As Boolean
'
Private m_dragPosX As Double
Private m_dragPosY As Double
Private m_dragPosZ As Double
'
Private m_matrix(16) As GLdouble
Private m_matrixInverse(16) As GLdouble
Private zprReferencePoint(4) As GLfloat

Public rQuadX As GLfloat

Dim angle1 As Double
Dim bx1 As Double
Dim by1 As Double
Dim bz1 As Double
Dim y1 As GLdouble

'Public pikname As Integer
'
'以下用于picking

Public Sub BindView(sView As PictureBox, n As Byte)
    '创建引用
    Select Case n
    Case 1
        Set View1 = sView
    End Select
    ViewDCs(n).hDC = sView.hDC
    If InitGL(ViewDCs(n)) = False Then Exit Sub
    ResizeView 1
End Sub

Private Sub Class_Initialize()
    m_zNear = -10
    m_zFar = 10
End Sub

Private Sub pos(px As Double, py As Double, pz As Double, X As Integer, y As Integer, viewport() As GLint)
    
    px = (X - viewport(0)) / viewport(2)
    py = (y - viewport(1)) / viewport(3)
    px = m_left + px * (m_right - m_left)
    py = m_top + py * (m_bottom - m_top)
    pz = m_zNear
    
End Sub

Private Sub View1_MouseDown(Button As Integer, Shift As Integer, X As Single, y As Single)
    Dim viewport(4) As GLint
    m_mouseX = X
    m_mouseY = y
    
    Dim x1 As GLdouble
    x1 = X
    Dim y1 As GLdouble
    y1 = View1.ScaleHeight
    zprPick x1, y1 - 1 - y, 3, 3
    
    glGetIntegerv glgViewport, viewport(0)
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X), CInt(y), viewport
    Form1.Text2.Text = "111"
    
End Sub
Private Sub View1_MouseMove(Button As Integer, Shift As Integer, X As Single, y As Single)
    Dim changed As Boolean
    changed = False
    
    Dim dx As Integer
    Dim dy As Integer
    
    dx = X - m_mouseX
    dy = y - m_mouseY
    
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    
    If dx = 0 And dy = 0 Then Exit Sub
    Dim px As Double
    Dim py As Double
    Dim pz As Double
    
    pos px, py, pz, CInt(X), CInt(y), viewport
    Form1.Text2.Text = "X:" & Format(px, "00.##") & ",Y:" & Format(py, "00.##")
    Form1.Text2.Text = X & "," & y
    changed = True
    
    If Button = 4 Then                                                          '中键，缩放
        Dim s As Double
        s = Exp(dy * 0.01)
        glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
        glScalef s, s, s
        'glScalef函数必须用在 glBegin 与 glEnd. 之间调用,否则产生此错误.
        '如果因子大于1.0并作用于模型观察矩阵并且光照已经允许,那么要求法线的自动法线功能需要开启(在glEnable 与 glDisable 之间要开启 GL_NORMALIZE)
        glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
        changed = True
    ElseIf Button = 1 Then                                                      '左键，旋转
        Dim ax As Double
        Dim ay As Double
        Dim az As Double
        '旋转不会改变形状，改变形状的只能是比例缩放因子
        Dim bx As Double
        Dim by As Double
        Dim bz As Double
        
        Dim angle As Double
        
        ax = dy
        ay = dx
        az = 0
        
        
        angle = Vlen(ax, ay, az) / (viewport(2) + 1) * 180
        '确定局部旋转轴
        bx = m_matrixInverse(0) * ax + m_matrixInverse(4) * ay + m_matrixInverse(8) * az
        by = m_matrixInverse(1) * ax + m_matrixInverse(5) * ay + m_matrixInverse(9) * az
        bz = m_matrixInverse(2) * ax + m_matrixInverse(6) * ay + m_matrixInverse(10) * az
        
        Dim m(16) As GLdouble
        'glMatrixMode mmModelView
        'glLoadIdentity
        glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
        glRotatef angle, bx, by, bz
        '与glTranslatef(x, y, z)类似，glRotatef(angle, x, y, z)也是对坐标系进行操作。
        '旋转轴经过原点，方向为(x,y,z),旋转角度为angle，方向满足右手定则。
        
        glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
        
        changed = True
    ElseIf Button = 2 Then                                                      '右键，平移
        
        pos px, py, pz, CInt(X), CInt(y), viewport
        Form1.Text2.Text = "X:" & Format(px, "00.##") & ",Y:" & Format(py, "00.##")
        glLoadIdentity
        ' Reset The View,重置当前指定的矩阵为单位矩阵,相当于又回到最初的坐标系,一般的做法是glLoadIdentity()在最前面用，保存状态是用glPushMatrix()和glPopMatrix()来操作了.
        'glLoadIdentity()后窗口的中点是坐标系的原点。吧1改为0.1，后面的坐标要小于1，才可见.
        '将当前的用户坐标系的原点移到了屏幕中心：类似于一个复位操作
        '1.X坐标轴从左至右，Y坐标轴从下至上，Z坐标轴从里至外。
        '2.OpenGL屏幕中心的坐标值是X和Y轴上的0.0f点。
        '3.中心左面的坐标值是负值，右面是正值。
        '移向屏幕顶端是正值，移向屏幕底端是负值。
        ' 移入屏幕深处是负值，移出屏幕则是正值。
        
        glTranslatef px - m_dragPosX, py - m_dragPosY, pz - m_dragPosZ
        '沿着 X, Y 和 Z 轴移动。
        
        '注意在glTranslatef(x, y, z)中,当您移动的时候，您并不是相对屏幕中心移动，而是相对与当前所在的屏幕位置。其作用就是将你绘点坐标的原点在当前原点的基础上平移一个(x,y,z)向量。
        
        
        
        glMultMatrixd m_matrix(0)
        '乘上某矩阵？
        
        m_dragPosX = px
        m_dragPosY = py
        m_dragPosZ = pz
        
        changed = True
    End If
    
    m_mouseX = X
    m_mouseY = y
    
    If changed = True Then
        getMatrix
        RenderView 1
    End If
    
    Dim x1 As GLdouble
    x1 = X
    Dim y1 As GLdouble
    y1 = View1.ScaleHeight
    zprPick x1, y1 - 1 - y, 3, 3
    
    glGetIntegerv glgViewport, viewport(0)
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X), CInt(y), viewport
    Form1.Text2.Text = "111"
    
End Sub
Public Sub View1_Paint()
    RenderView 1
End Sub
Private Sub View1_Resize()
    ResizeView 1
End Sub

Public Sub View1_light_set()
    
    If is_show_light = 1 Then glEnable GL_LIGHTING                              'enable lighting
    
    If is_show_light = 0 Then glDisable GL_LIGHTING                             'disable lighting
    
    RenderView 1
    
End Sub

Private Sub ResizeView(sN As Integer)
    Dim TPic As PictureBox
    Select Case sN
    Case 1
        Set TPic = View1
    End Select
    wglMakeCurrent ViewDCs(sN).hDC, ViewDCs(sN).hglRC
    
    '    调用glViewPort函数来决定视见区域，告诉OpenGL应把渲染之后的图形绘制在窗体的哪个部位。当视见区域是整个窗体时，OpenGL将把渲染结果绘制到整个窗口。
    '    参数X，Y指定了视见区域的左下角在窗口中的位置，一般情况下为（0，0），Width和Height指定了视见区域的宽度和高度。
    glViewport 0, 0, TPic.Width, TPic.Height
    
    m_top = 1
    m_bottom = -1
    m_left = -TPic.Width / TPic.Height
    m_right = -m_left
    
    glMatrixMode GL_PROJECTION
    glLoadIdentity
    glOrtho m_left, m_right, m_bottom, m_top, m_zNear, m_zFar
    glMatrixMode GL_MODELVIEW
    getMatrix
    'zprReferencePoint(0) = 1
    'zprReferencePoint(1) = 1
    'zprReferencePoint(2) = 1
    
End Sub

Private Sub RenderView(sN As Integer)
    glClear clrDepthBufferBit Or clrColorBufferBit                              '清除当前的缓冲区，
    Draw
    SwapBuffers ViewDCs(sN).hDC                                                 '由于多个视图用同一RC，所以不用释放RC，显示绘制图形，交换前后缓冲
End Sub

Private Sub getMatrix()
    glGetDoublev GL_MODELVIEW_MATRIX, m_matrix(0)
    invertMatrix m_matrix, m_matrixInverse
End Sub

Private Function Vlen(X As Double, y As Double, z As Double) As Double
    
    'Vlen = Sqr((x - zprReferencePoint(0)) ^ 2 + (y - zprReferencePoint(1)) ^ 2 + (z - zprReferencePoint(2)) ^ 2)
    Vlen = Sqr(X * X + y * y + z * z)
    
End Function

Private Sub invertMatrix(m() As GLdouble, out() As GLdouble)
    
    '计算逆阵
    Dim i As Integer
    
    Dim det As GLdouble
    Dim d12 As GLdouble, d13 As GLdouble
    Dim d23 As GLdouble, d24 As GLdouble
    Dim d34 As GLdouble, d41 As GLdouble
    
    Dim tmp(16) As GLdouble
    
    d12 = (m(2) * m(7) - m(3) * m(6))
    d13 = (m(2) * m(11) - m(3) * m(10))
    d23 = (m(6) * m(11) - m(7) * m(10))
    d24 = (m(6) * m(15) - m(7) * m(14))
    d34 = (m(10) * m(15) - m(11) * m(14))
    d41 = (m(14) * m(3) - m(15) * m(2))
    
    tmp(0) = (m(5) * d34 - m(9) * d24 + m(13) * d23)
    tmp(1) = -(m(1) * d34 + m(9) * d41 + m(13) * d13)
    tmp(2) = (m(1) * d24 + m(5) * d41 + m(13) * d12)
    tmp(3) = -(m(1) * d23 - m(5) * d13 + m(9) * d12)
    
    det = m(0) * tmp(0) + m(4) * tmp(1) + m(8) * tmp(2) + m(12) * tmp(3)
    
    If det = 0 Then
        ' MsgBox ("singular matrix: 退化矩阵, 降秩矩阵")
    Else
        Dim invDet As GLdouble
        invDet = 1 / det
        '计算逆阵？
        tmp(0) = tmp(0) * invDet
        tmp(1) = tmp(1) * invDet
        tmp(2) = tmp(2) * invDet
        tmp(3) = tmp(3) * invDet
        
        tmp(4) = -(m(4) * d34 - m(8) * d24 + m(12) * d23) * invDet
        tmp(5) = (m(0) * d34 + m(8) * d41 + m(12) * d13) * invDet
        tmp(6) = -(m(0) * d24 + m(4) * d41 + m(12) * d12) * invDet
        tmp(7) = (m(0) * d23 - m(4) * d13 + m(8) * d12) * invDet
        
        d12 = m(0) * m(5) - m(1) * m(4)
        d13 = m(0) * m(9) - m(1) * m(8)
        d23 = m(4) * m(9) - m(5) * m(8)
        d24 = m(4) * m(13) - m(5) * m(12)
        d34 = m(8) * m(13) - m(9) * m(12)
        d41 = m(12) * m(1) - m(13) * m(0)
        
        tmp(8) = (m(7) * d34 - m(11) * d24 + m(15) * d23) * invDet
        tmp(9) = -(m(3) * d34 + m(11) * d41 + m(15) * d13) * invDet
        tmp(10) = (m(3) * d24 + m(7) * d41 + m(15) * d12) * invDet
        tmp(11) = -(m(3) * d23 - m(7) * d13 + m(11) * d12) * invDet
        tmp(12) = -(m(6) * d34 - m(10) * d24 + m(14) * d23) * invDet
        tmp(13) = (m(2) * d34 + m(10) * d41 + m(14) * d13) * invDet
        tmp(14) = -(m(2) * d24 + m(6) * d41 + m(14) * d12) * invDet
        tmp(15) = (m(2) * d23 - m(6) * d13 + m(10) * d12) * invDet
        
        For i = 0 To 16
            out(i) = tmp(i)
        Next i
        
    End If
End Sub


'************************** Picking ***********************************

Private Sub zprPick(X As GLdouble, y As GLdouble, delX As GLdouble, delY As GLdouble)
    Dim buffer(1024) As GLuint
    Dim bufferSize As Integer
    Dim viewport(4) As GLint
    Dim projection(16) As GLdouble
    Dim hits As GLint
    Dim j As GLint
    Dim k As GLint
    Dim min As GLint
    Dim minZ As Single
    Dim i As Integer
    Dim helpvar As GLuint
    
    bufferSize = 512
    min = -1
    minZ = -1
    
    glSelectBuffer bufferSize, buffer(0)
    glRenderMode rmSelect
    glInitNames
    
    glMatrixMode mmProjection
    glPushMatrix
    glGetIntegerv glgViewport, viewport(0)
    glGetDoublev glgProjectionMatrix, projection(0)
    glLoadIdentity
    gluPickMatrix X, y, delX, delY, viewport(0)
    glMultMatrixd projection(0)
    
    glMatrixMode mmModelView
    
    Draw                                                                        '需要重新画一下
    
    hits = glRenderMode(rmRender)
    
    If hits <= 0 Then GoTo errhandle
    
    minZ = 1E+30                                                                ' very big number :)
    For i = 1 To hits
        helpvar = buffer((i - 1) * 4 + 1)
        If (GLuint_to_Single(helpvar) < minZ) Then                              'The distance to picked objekt
            minZ = GLuint_to_Single(helpvar)
            min = buffer((i - 1) * 4 + 3)                                       ' near = number of picked objekt
        End If
    Next i
    'Debug.Print min
    
errhandle:
    glMatrixMode mmProjection
    glPopMatrix
    glMatrixMode mmModelView
    
    'Debug.Print min
    Form1.Text1.Text = min
    pikname = min
    glPushName min
    glBegin GL_LINES
    glColor3f 1, 0, 0
    '   glVertex3f 2, 2, 2
    '   glVertex3f 3, 3, 3
    glEnd
    glPopName
    
End Sub


Private Function GLuint_to_Single(GLuint As GLuint) As Single
    ' Transformation of GLuint varibale (UnsignedLongInteger in C , no equivalent in VB) to Single
    Dim Result As Single
    
    Result = GLuint
    If Result < 0 Then Result = 2147483648# + (2147483648# + Result)
    GLuint_to_Single = Result
    
End Function

'视图变换要在模型变换之前进行。通过移动照相机（使用视图变换）来观察这个立方体，
Public Sub ChangeViewDirection(VDire As ViewDirection)
    
    '    一个非常简单的恢复初始坐标系的手段，无论以前进行了多少次矩阵变换，在该命令执行后，当前矩阵均恢复成一个单位矩阵，即相当于没有进行任何矩阵变换状态。
    glMatrixMode GL_MODELVIEW
    glLoadIdentity
    If VDire = ViewFront Then
        '        gluLookAt 0, 0, 5, 0, 0, 0, 0, 1, 0
        gluLookAt 5, 0, 5, 5, 0, 0, 0, 1, 0
        '该函数定义了视点矩阵，并用该矩阵乘以当前矩阵。eyex,eyey,eyez定义了视点的位置；centerx、centery和centerz变量指定了参考点的位置，
        '该点通常为相机所瞄准的场景中心轴线上的点；upx、upy、upz变量指定了向上向量的方向。
        '通常，视点转换操作在模型转换操作之后发出，以便模型转换先对物体发生作用。场景中物体的顶点经过模型转换之后移动到所希望的位置，
        '然后再对场景进行视点定位等操作。模型转换和视点转换共同构成模型视景矩阵。
        '        eyex, eyey,eyez 相机在世界坐标的位置
        '        centerx,centery,centerz 相机镜头对准的物体在世界坐标的位置
        '        upx,upy,upz 相机向上的方向在世界坐标中的方向
'你把相机想象成为你自己的脑袋:
        '第一组数据就是脑袋的位置
        '第二组数据就是眼睛看的物体的位置
        '第三组就是头顶朝向的方向（因为你可以歪着头看同一个物体）。
        '        glFrustum -10, 10, -10, 10, 10, 30
        'glTranslatef 0, 0, -5
    ElseIf VDire = ViewBack Then
        gluLookAt 0, 0, -5, 0, 0, 0, 0, 1, 0
    ElseIf VDire = viewLeft Then
        gluLookAt 5, 0, 0, 0, 0, 0, 0, 1, 0
    ElseIf VDire = ViewRight Then
        gluLookAt -5, 0, 0, 0, 0, 0, 0, 1, 0
    ElseIf VDire = ViewTop Then
        gluLookAt 1, 5, 0.2, 1, 0, 0.2, 0, 0, 1
        'glTranslatef 0, 0, -2
    ElseIf VDire = ViewBottom Then
        gluLookAt 0, -5, 0, 0, 0, 0, 0, 0, 1
    End If
    
    glScalef 2 / 200#, 2 / 200#, 2 / 200#
    '    getMatrix
    RenderView 1
    
End Sub



'-------------------------------------绘图
Private Sub Draw()
    glPushMatrix
    DrawObjs                                                                    '绘制物体
    glPopMatrix
    If is_show_axies = 1 Then DrawAxis                                          '绘制坐标轴
End Sub

'绘制坐标轴
Private Sub DrawAxis()
    
    glShadeModel (GL_FLAT)
    
    ' 设置正面为填充模式
    glPolygonMode GL_FRONT_AND_BACK, GL_FILL
    
    glBegin (GL_LINES)
    ' 绘制x轴
    glColor3f 1, 0, 0
    glVertex3f -0.5 * ymax, 0#, 0#
    glVertex3f 0.5 * ymax, 0#, 0#
    
    ' 绘制y轴
    glColor3f 0, 1, 0
    glVertex3f 0#, -0.5 * ymax, 0#
    glVertex3f 0#, 0.5 * ymax, 0#
    
    ' 绘制z轴
    glColor3f 0, 0, 1
    glVertex3f 0#, 0#, -0.5 * ymax
    glVertex3f 0#, 0#, 0.5 * ymax
    glEnd
    
    
    
    '    需要执行的缩放、平移等操作放在glPushMatrix和glPopMatrix之间。
    '    绘制x轴箭头
    glPushMatrix
    glColor3f 1, 0, 0
    glTranslatef 0.5 * ymax, 0#, 0#
    glRotatef 90#, 0#, 1#, 0#
    glutSolidCone 0.02 * ymax, 0.1 * ymax, 10, 1
    glPopMatrix
    
    '    绘制y轴箭头
    glPushMatrix
    glColor3f 0, 1, 0
    glTranslatef 0#, 0.5 * ymax, 0#
    glRotatef -90#, 1#, 0#, 0#
    glutSolidCone 0.02 * ymax, 0.1 * ymax, 10, 1
    glPopMatrix
    
    '    绘制z轴箭头
    glPushMatrix
    glColor3f 0, 0, 1
    glTranslatef 0#, 0#, 0.5 * ymax
    glRotatef 90#, 0#, 0#, 1#
    glutSolidCone 0.02 * ymax, 0.1 * ymax, 10, 1                                '实心圆锥：底圆半径，高，底圆周向分段数，高度方向段数
    '    glutWireCone 0.1, 0.2, 10, 10                                               '空心圆锥：底圆半径，高，底圆周向分段数，高度方向段数
    
    
    '绘制文字
    '    glColor3f 1, 0, 0
    '    glTranslatef -4, -3, 0
    '    glRotatef -90, 0, 1, 0
    '    glTranslatef -2, 0, -1
    '    Call glDrawString("X")
    '    glColor3f 0, 1, 0
    '    glTranslatef -1.8, 1, 0
    '    Call glDrawString("Y")
    '    glColor3f 0, 0, 1
    '    glTranslatef 0, -1, 1
    '    Call glDrawString("Z")
    
    '消除上一次的变换对本次变换的影响。使本次变换是以世界坐标系的原点为参考点进行。glPushMatrix()和glPopMatrix()的配对使用可以消除上一次的变换对本次变换的影响。
    glPopMatrix
    
    
End Sub

'绘制物体
Private Sub DrawObjs()
    
    Dim i As Integer
    Dim j As Integer
    Dim k As Integer
    Dim n As Integer
    
    '    glPushMatrix
    '
    '    glPushName 1
    '    '绘制实心圆锥
    '    If pikname = 1 Then
    '        glColor3f 1, 0, 0
    '    Else
    '        glColor3f 0, 0, 1
    '    End If
    '    glRotatef 90, 0, 1, 0
    '    'glutWireCone 0.3, 2, 25, 25         '空心圆锥：底圆半径，高，底圆周向分段数，高度方向段数
    '    glPopName
    '
    '    '绘制直线段
    '    glPushName 2
    '    glBegin GL_LINES
    '    glLineWidth 5                                                               '设置粗细，在 0~10.0 ，大于 10 以上按 10 来处理。
    '    If pikname = 2 Then
    '        glColor3f 1, 0, 0
    '    Else
    '        glColor3f 0, 0, 1
    '    End If
    '    glVertex3f 2, 2, 2
    '    glVertex3f 3, 3, 3
    '    glEnd
    '    glPopName
    '
    '    '绘制实心立方体
    '    glPushName 3
    '    glTranslatef 2, 2, 2
    '    If pikname = 3 Then
    '        glColor3f 1, 0, 0
    '    Else
    '        glColor3f 1, 0, 1
    '    End If
    '    glNormal3f 5#, 10#, 3#
    '    glutSolidCube 1
    '    glPopName
    '
    '    '绘制实体球
    '    glPushName 4
    '    'glLoadIdentity            '
    '    glTranslatef 1, 1, 1                                                        'm_dragPosX, m_dragPosY, m_dragPosZ
    '    If pikname = 4 Then
    '        glColor3f 1, 0, 0
    '    Else
    '        glColor3f 0, 1, 1
    '    End If
    '    glutSolidSphere 0.2, 20, 20                                                 '实体球
    '    glPopName
    '
    '    glEnd
    
    
    '    glEnable GL_LIGHTING                                                        'enable lighting
    
    '    设置着色模式，GL_FLAT 采用恒定着色，使用图元中某个顶点的颜色来渲染整个图元。
    '    glShadeModel (GL_FLAT)
    'Public is_show_grid As Integer
    '
    'Public is_show_contour As Integer
    '
    'Public is_show_boundary As Integer
    '
    'Public is_show_light As Integer
    '
    'Public is_show_shade As Integer
    '
    'Public is_show_axies As Integer
    
    
    If is_show_shade = 1 And is_show_contour = 0 Then
        
        glShadeModel (GL_FLAT)
        
        
        glEnable (GL_POLYGON_OFFSET_FILL)
        glPolygonOffset 1#, 1#
        
        ' 设置正面为填充模式
        glPolygonMode GL_FRONT_AND_BACK, GL_FILL
        
        glPopMatrix
        
        glBegin (GL_QUADS)
        
        
        For n = 1 To zone
            
            glPushName n
            glColor3f 1#, 1#, 1#
            For k = 1 To kmax(n)
                For j = 1 To jmax(n) - 1
                    For i = 1 To imax(n) - 1
                        '                        glColor3f z(i, j + 1, k, n) / zmax, 0.5, 1 - z(i, j + 1, k, n) / zmax
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        '    glColor3f 0#, 1#, 0#
                        glVertex3f X(i + 1, j, k, n), y(i + 1, j, k, n), z(i + 1, j, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i + 1, j + 1, k, n), y(i + 1, j + 1, k, n), z(i + 1, j + 1, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i, j + 1, k, n), y(i, j + 1, k, n), z(i, j + 1, k, n)
                    Next i
                Next j
            Next k
            glPopName
        Next n
        
        
        glEnd
        
        '    关闭Polygon Offset
        glDisable (GL_POLYGON_OFFSET_FILL)
        
    End If
    
    If is_show_contour = 1 Then
        
        glShadeModel (GL_SMOOTH)
        
        
        glEnable (GL_POLYGON_OFFSET_FILL)
        glPolygonOffset 1#, 1#
        
        ' 设置正面为填充模式
        glPolygonMode GL_FRONT_AND_BACK, GL_FILL
        ' 设置正面为线形模式
        '    glPolygonMode GL_FRONT_AND_BACK, GL_LINE
        '    ' 设置反面为线形模式
        '    glPolygonMode GL_BACK, GL_LINE
        
        glPopMatrix
        '    glTranslatef 0#, 0#, 0#
        ' 设置逆时针绘制一个正方形
        '    glBegin (GL_QUADS)
        '
        '    glColor3f 1#, 0#, 0#
        '    glVertex3f -0.5, -0.5, 0
        '    glColor3f 0#, 1#, 0#
        '    glVertex3f 0#, -0.5, 0
        '    glColor3f 0#, 0#, 1#
        '    glVertex3f 0#, 0#, 0
        '    glColor3f 1#, 1#, 0#
        '    glVertex3f -0.5, 0#, 0
        '
        '    glEnd
        
        
        glBegin (GL_QUADS)
        
        '    glPushMatrix
        '    glLineWidth (7#)
        For n = 1 To zone
            
            glPushName n
            '        glColor3f 1#, 1#, 1#
            For k = 1 To kmax(n)
                For j = 1 To jmax(n) - 1
                    For i = 1 To imax(n) - 1
                        glColor3f z(i, j + 1, k, n) / zmax, 0.5, 1 - z(i, j + 1, k, n) / zmax
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        '    glColor3f 0#, 1#, 0#
                        glVertex3f X(i + 1, j, k, n), y(i + 1, j, k, n), z(i + 1, j, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i + 1, j + 1, k, n), y(i + 1, j + 1, k, n), z(i + 1, j + 1, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i, j + 1, k, n), y(i, j + 1, k, n), z(i, j + 1, k, n)
                    Next i
                Next j
            Next k
            glPopName
        Next n
        
        
        glEnd
        
        
        '    在OpenGL中，如果想绘制一个多边形同时绘制其边界，可是先使用多边形模式GL_FILL绘制物体，然后使用多边形模式GL_LINE和不同的颜色再次绘制这个多边形。但是由于直线和多边形的光栅化方式不同，导致位于同一位置的多边形和直线的深度值并不相同，进而导致直线有时在多边形的里面，有时在多边形的外面，这种现象就是"Stiching"。
        '    而Z-fighting主要是指当两个面共面时，二者的深度值一样，深度缓冲就不能清楚的将它们两者分离开来，位于后面的图元上的一些像素就会被渲染到前面的图元上，最终导致图象在帧与帧之间产生微弱的闪光。
        '    解决这两个问题的方法就是使用Polygon Offset，当然你也可以使用模板测试，但Polygon Offset的速度会比模板缓存快。
        '    Polygon Offset有多种使用方式。其中之一就是把物体推远一点点，这样，线框和正方形就与物体有了间隔，就不会产生干涉。
        '    启用Polygon Offset有三个可选参数（GL_POLYGON_OFFSET_POINT, GL_POLYGON_OFFSET_LINE 和GL_POLYGON_OFFSET_FILL），分别对应3种光栅化模式（GL_POINT, GL_LINE 和GL_FILL）。
        '    如果想要非常好地使用Polygon Offset，你需要做一些数学上的研究。不过一般而言，只需把1.0和0.0这样简单的值赋给glPolygonOffset即可满足需要。
        '    我们要把物体推远一点，
        
        
        '    关闭Polygon Offset
        glDisable (GL_POLYGON_OFFSET_FILL)
        
    End If
    
    If is_show_grid = 1 Then
        
        glPolygonMode GL_FRONT_AND_BACK, GL_LINE
        
        glBegin (GL_QUADS)
        
        For n = 1 To zone
            
            glPushName n
            glColor3f (2 - n), 0#, (n - 1)
            For k = 1 To kmax(n)
                For j = 1 To jmax(n) - 1
                    For i = 1 To imax(n) - 1
                        '                    glColor3f 1#, 0#, 0#
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        '    glColor3f 0#, 1#, 0#
                        glVertex3f X(i + 1, j, k, n), y(i + 1, j, k, n), z(i + 1, j, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i + 1, j + 1, k, n), y(i + 1, j + 1, k, n), z(i + 1, j + 1, k, n)
                        '    glColor3f 0#, 0#, 1#
                        glVertex3f X(i, j + 1, k, n), y(i, j + 1, k, n), z(i, j + 1, k, n)
                    Next i
                Next j
            Next k
            glPopName
        Next n
        
        glEnd
        
    End If
    
    
    If is_show_boundary = 1 Then
        
                glPolygonMode GL_FRONT_AND_BACK, GL_LINE
        
        glBegin (GL_LINES)
        
        For n = 1 To zone
            
            glColor3f 0#, 0#, 0#
            For k = 1 To kmax(n)
                For j = 1 To 1
                    For i = 1 To imax(n) - 1
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        glVertex3f X(i + 1, j, k, n), y(i + 1, j, k, n), z(i + 1, j, k, n)
                        
                    Next i
                Next j
            Next k
            For k = 1 To kmax(n)
                For j = jmax(n) To jmax(n)
                    For i = 1 To imax(n) - 1
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        glVertex3f X(i + 1, j, k, n), y(i + 1, j, k, n), z(i + 1, j, k, n)
                    Next i
                Next j
            Next k
            For k = 1 To kmax(n)
                For j = 1 To jmax(n) - 1
                    For i = 1 To 1
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        glVertex3f X(i, j + 1, k, n), y(i, j + 1, k, n), z(i, j + 1, k, n)
                    Next i
                Next j
            Next k
            For k = 1 To kmax(n)
                For j = 1 To jmax(n) - 1
                    For i = imax(n) To imax(n)
                        glVertex3f X(i, j, k, n), y(i, j, k, n), z(i, j, k, n)
                        glVertex3f X(i, j + 1, k, n), y(i, j + 1, k, n), z(i, j + 1, k, n)
                    Next i
                Next j
            Next k
        Next n
        
        glEnd
        
    End If
    
    
    ' 设置顺时针绘制一个正方形
    '    glBegin GL_POLYGON
    '    glColor3f 1#, 0#, 0#
    '    glVertex2f 0#, 0#
    '    glColor3f 0#, 1#, 0#
    '    glVertex2f 0#, 0.5
    '    glColor3f 0#, 0#, 1#
    '    glVertex2f 0.5, 0.5
    '    glColor3f 1#, 1#, 0#
    '    glVertex2f 0.5, 0#
    '    glEnd
    
    
    
End Sub

'绘制字符串
Public Sub glDrawString(sStr As String)
    Dim i, listNum As Integer
    Dim pgmf(1) As GLYPHMETRICSFLOAT
    'sStr = "ceui"
    For i = 1 To Len(sStr)
        listNum = glGenLists(1)
        wglUseFontOutlines ViewDCs(1).hDC, Asc(Mid(sStr, i, 1)), 1, listNum, 0, 0.05, WGL_FONT_POLYGONS, pgmf(0)
        glCallList (listNum)
        glDeleteLists listNum, 1
    Next i
End Sub

'放大
Public Sub Zoom_Out()
    
    glScalef 1.1, 1.1, 1.1
    getMatrix
    RenderView 1
    
End Sub

'缩小
Public Sub Zoom_In()
    
    glScalef 0.9, 0.9, 0.9
    getMatrix
    RenderView 1
    
End Sub

'绕x轴正向旋转
Public Sub Rotate_X()
    
    glRotatef 2, 1, 0, 0
    getMatrix
    RenderView 1
    
End Sub

'绕x轴负向旋转
Public Sub Rotate_Xf()
    
    glRotatef -2, 1, 0, 0
    getMatrix
    RenderView 1
    
End Sub

'绕y轴正向旋转
Public Sub Rotate_Y()
    
    glRotatef 2, 0, 1, 0
    getMatrix
    RenderView 1
    
End Sub

'绕y轴负向旋转
Public Sub Rotate_Yf()
    
    glRotatef -2, 0, 1, 0
    getMatrix
    RenderView 1
    
End Sub

'绕z轴正向旋转
Public Sub Rotate_Z()
    
    glRotatef 2, 0, 0, 1
    getMatrix
    RenderView 1
    
End Sub

'绕z轴负向旋转
Public Sub Rotate_Zf()
    
    glRotatef -2, 0, 0, 1
    getMatrix
    RenderView 1
    
End Sub

'向左平移
Public Sub Trans_Left()
    getMatrix
    RenderView 1
    Dim X, y As Single
    X = 1
    y = 1
    
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    Dim px As Double
    Dim py As Double
    Dim pz As Double
    
    pos px, py, pz, CInt(X), CInt(y), viewport
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X + 3), CInt(y), viewport
    glLoadIdentity
    glTranslatef px - m_dragPosX, py - m_dragPosY, pz - m_dragPosZ
    
    glMultMatrixd m_matrix(0)
    
    getMatrix
    RenderView 1
End Sub

'向右平移
Public Sub Trans_Right()
    getMatrix
    RenderView 1
    Dim X, y As Single
    X = 4
    y = 1
    
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    Dim px As Double
    Dim py As Double
    Dim pz As Double
    
    pos px, py, pz, CInt(X), CInt(y), viewport
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X - 3), CInt(y), viewport
    glLoadIdentity
    glTranslatef px - m_dragPosX, py - m_dragPosY, pz - m_dragPosZ
    
    glMultMatrixd m_matrix(0)
    
    getMatrix
    RenderView 1
End Sub

'向上平移
Public Sub Trans_Up()
    getMatrix
    RenderView 1
    Dim X, y As Single
    X = 1
    y = 1
    
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    Dim px As Double
    Dim py As Double
    Dim pz As Double
    
    pos px, py, pz, CInt(X), CInt(y), viewport
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X), CInt(y + 3), viewport
    glLoadIdentity
    glTranslatef px - m_dragPosX, py - m_dragPosY, pz - m_dragPosZ
    
    glMultMatrixd m_matrix(0)
    
    getMatrix
    RenderView 1
End Sub

'向下平移
Public Sub Trans_Down()
    getMatrix
    RenderView 1
    Dim X, y As Single
    X = 1
    y = 4
    
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    Dim px As Double
    Dim py As Double
    Dim pz As Double
    
    pos px, py, pz, CInt(X), CInt(y), viewport
    pos m_dragPosX, m_dragPosY, m_dragPosZ, CInt(X), CInt(y - 3), viewport
    glLoadIdentity
    glTranslatef px - m_dragPosX, py - m_dragPosY, pz - m_dragPosZ
    
    glMultMatrixd m_matrix(0)
    
    getMatrix
    RenderView 1
End Sub

'绕水平轴正向旋转
Public Sub Rotate_Level()
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    getMatrix
    
    Dim ax As Double
    Dim ay As Double
    Dim az As Double
    
    Dim bx As Double
    Dim by As Double
    Dim bz As Double
    
    Dim angle As Double
    
    ax = 0
    ay = 1
    az = 0
    
    angle = 1
    '确定局部旋转轴
    bx = m_matrixInverse(0) * ax + m_matrixInverse(4) * ay + m_matrixInverse(8) * az
    by = m_matrixInverse(1) * ax + m_matrixInverse(5) * ay + m_matrixInverse(9) * az
    bz = m_matrixInverse(2) * ax + m_matrixInverse(6) * ay + m_matrixInverse(10) * az
    
    Dim m(16) As GLdouble
    'glMatrixMode mmModelView
    'glLoadIdentity
    glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
    glRotatef angle, bx, by, bz
    glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
    
    getMatrix
    RenderView 1
    
End Sub

'绕水平轴负向旋转
Public Sub Rotate_Levelf()
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    getMatrix
    
    Dim ax As Double
    Dim ay As Double
    Dim az As Double
    
    Dim bx As Double
    Dim by As Double
    Dim bz As Double
    
    Dim angle As Double
    
    ax = 0
    ay = 1
    az = 0
    
    angle = 1
    '确定局部旋转轴
    bx = m_matrixInverse(0) * ax + m_matrixInverse(4) * ay + m_matrixInverse(8) * az
    by = m_matrixInverse(1) * ax + m_matrixInverse(5) * ay + m_matrixInverse(9) * az
    bz = m_matrixInverse(2) * ax + m_matrixInverse(6) * ay + m_matrixInverse(10) * az
    
    Dim m(16) As GLdouble
    'glMatrixMode mmModelView
    'glLoadIdentity
    glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
    glRotatef -angle, bx, by, bz
    glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
    
    getMatrix
    RenderView 1
    
End Sub

'绕竖直轴正向旋转
Public Sub Rotate_Vertical()
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    getMatrix
    
    Dim ax As Double
    Dim ay As Double
    Dim az As Double
    
    Dim bx As Double
    Dim by As Double
    Dim bz As Double
    
    Dim angle As Double
    
    ax = 1
    ay = 0
    az = 0
    
    angle = 1
    '确定局部旋转轴
    bx = m_matrixInverse(0) * ax + m_matrixInverse(4) * ay + m_matrixInverse(8) * az
    by = m_matrixInverse(1) * ax + m_matrixInverse(5) * ay + m_matrixInverse(9) * az
    bz = m_matrixInverse(2) * ax + m_matrixInverse(6) * ay + m_matrixInverse(10) * az
    
    Dim m(16) As GLdouble
    'glMatrixMode mmModelView
    'glLoadIdentity
    glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
    glRotatef angle, bx, by, bz
    glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
    
    getMatrix
    RenderView 1
    
End Sub

'绕竖直轴负向旋转
Public Sub Rotate_Verticalf()
    Dim viewport(4) As GLint
    glGetIntegerv glgViewport, viewport(0)
    getMatrix
    
    Dim ax As Double
    Dim ay As Double
    Dim az As Double
    
    Dim bx As Double
    Dim by As Double
    Dim bz As Double
    
    Dim angle As Double
    
    ax = 1
    ay = 0
    az = 0
    
    angle = 1
    '确定局部旋转轴
    bx = m_matrixInverse(0) * ax + m_matrixInverse(4) * ay + m_matrixInverse(8) * az
    by = m_matrixInverse(1) * ax + m_matrixInverse(5) * ay + m_matrixInverse(9) * az
    bz = m_matrixInverse(2) * ax + m_matrixInverse(6) * ay + m_matrixInverse(10) * az
    
    Dim m(16) As GLdouble
    'glMatrixMode mmModelView
    'glLoadIdentity
    glTranslatef zprReferencePoint(0), zprReferencePoint(1), zprReferencePoint(2)
    glRotatef -angle, bx, by, bz
    glTranslatef -zprReferencePoint(0), -zprReferencePoint(1), -zprReferencePoint(2)
    
    getMatrix
    RenderView 1
    
End Sub

