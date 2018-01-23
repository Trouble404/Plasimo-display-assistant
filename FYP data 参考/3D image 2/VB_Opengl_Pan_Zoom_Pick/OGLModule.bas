Attribute VB_Name = "OGLModule"
Option Explicit

Enum ViewDirection
    ViewFront = 1                                                               ' ǰ��ͼ
    ViewBack = 2                                                                ' ����ͼ
    viewLeft = 3                                                                ' ����ͼ
    ViewRight = 4                                                               ' ����ͼ
    ViewTop = 5                                                                 ' ����ͼ
    ViewBottom = 6                                                              ' ����ͼ
End Enum

Public Type ViewDC
    hglRC As Long                                                               '��Ⱦ������(RC)
    hDC As Long                                                                 '�豸������(DC)
End Type
'����������������
Public m_left As Double
Public m_right As Double
Public m_bottom As Double
Public m_top As Double

Public pikname As Integer
'Texture variables...
Global TArray(0 To 7) As Long, TArray2(0 To 7) As Long, Bdata() As Byte
Dim hBitmap As Long, Binfo As BITMAPINFO

'Public Enum Heavens                                                             'Use Enum as way of defining constants
'    Sun = 1
'    Mercury = 2
'    Venus = 3
'    Earth = 4
'    Moon = 5
'End Enum

'��Դ����
Dim Amb_Dif_Light(3) As Single                                                  '= { 0.5!, 0.5!, 0.5!, 1.0! } 'ambient n diffuse light(both r same!)�������⡪��������η�������Ĺ��Ϊ�����⣬
'�޷�ȷ��������ķ��򣬵����ض��Ĺ�Դ�رպ����ǽ���ʧ.
'ȫ�ֻ����⡪�����ǲ��������ض��Ĺ�Դ����Щ�⾭���˶��ɢ�䣬
'�Ѿ��޷�ȷ�����Դλ�ںδ�.

Dim SpecularLight(3) As Single                                                  '= { 1.0!, 1.0!, 1.0!, 1.0! } ' specular light���߹�          'ɢ��⡪������ͬһ�������䵽��������
'���ظ���������ȷ��䣬��ˣ����۴��ĸ�����۲죬��������ȶ���ͬ.
'���淴��⡪�������ض�����Ҳ�����䵽�ض�����.���淴�����֮���.
'���ʷ���⡪������ģ�ⷢ������.��OpenGL����ģ���У�����ķ����������
'��������ȣ������ܹ�Դ��Ӱ�죬���⣬����ⲻ����������������ӹ���.



Dim Light0Pos!(3), Light1Pos!(3), Light2Pos!(3)

Public ViewDCs(1 To 1) As ViewDC
Global QObj As Long                                                             'GLU Quadric Object




Function InitGL(sViewDC As ViewDC) As Boolean
    '���������ڳ�ʼ����ʾ�ؼ�
    Dim Pfd As PIXELFORMATDESCRIPTOR
    Dim Result As Long
    '�������ظ�ʽ�����ظ�ʽ������ɺ󣬵���ChoosePixelFormat��SetPixelFormat������֮���豸���������ƥ�������
    Pfd.nSize = Len(Pfd)
    Pfd.nVersion = 1
    Pfd.dwFlags = PFD_SUPPORT_OPENGL Or PFD_DRAW_TO_WINDOW Or PFD_DOUBLEBUFFER Or PFD_TYPE_RGBA
    Pfd.iPixelType = PFD_TYPE_RGBA
    Pfd.cColorBits = 32
    Pfd.cDepthBits = 16
    
    Result = ChoosePixelFormat(sViewDC.hDC, Pfd)
    If Result = 0 Then
        MsgBox "OpenGL ��ʼ��ʧ��!", vbCritical
        InitGL = False
        Exit Function
    End If
    SetPixelFormat sViewDC.hDC, Result, Pfd
    
    '����һ���µ�OpenGL��Ⱦ����������������������ڻ��Ƶ���hdc���ص��豸�������Ⱦ�������к��豸������(dc)һ�������ظ�ʽ��
    sViewDC.hglRC = wglCreateContext(sViewDC.hDC)                               '����DC����RC
    
    wglMakeCurrent sViewDC.hDC, sViewDC.hglRC                                   '��DC��RC�����
    '    glClearColor 0, 0, 0, 0                                                '���ñ���ɫ��ɫ����͸��
    
    '���ñ���ɫ��ɫ����͸��
    glClearColor 1, 1, 1, 0
    
    '��ɫģʽ��GL_SMOOTH��Ĭ��ֵ��������ͼ��ʱ����ɫ�仯��ƽ�����ɵģ������Ĵ���ͼԪ�и����������ɫ�������߶�ͼԪ���߶��ϸ������ɫ�����������������ɫͨ����ֵ�õ���
    '���ڶ����ͼԪ��������ڲ��������ɫ���������ж������ɫ��ֵ�õ�����GL_FLAT�������ú㶨��ɫ��ʹ��ͼԪ��ĳ���������ɫ����Ⱦ����ͼԪ��
    '    glShadeModel (GL_SMOOTH)
    
    '    OpenGL���ʹ���߿�ģʽ
    glPolygonMode GL_FRONT_AND_BACK, GL_LINE
    
    '���������Ǳ��治��ʾ����
    '    glEnable GL_CULL_FACE
    
    '�ر��������Ǳ��治��ʾ��������һ����֤��һ�㡣
    glDisable (GL_CULL_FACE)
    
    'ָ��ʲô˳��Ϊ���棬��ʱ�뻹��˳ʱ�롣����CCW����Ϊ�����桱��CCW��CounterClockWise����ʱ�룻GL_CW��CW��ClockWise��˳ʱ�롣
    '��������ʶ˳�����ϱ����ò�һ�£���ῴ�����棬�޷���ʾͼ�Ρ�
    glFrontFace GL_CCW
    
    '������ȱȽϣ�Ȼ�������z����С��buffer�� //��ֵ����ǰ��z��С���������۲�㣩������ʾ��ʵ�ʾ���������
    glEnable GL_DEPTH_TEST                                                      '//��Ȳ���
    
    '���õĲ��������¼���GL_BLEND  GL_DEPTH_TEST  GL_FOG  GL_LINE_STIPPLE GL_LIGHTING
    glEnable GL_LIGHTING
    
    '    ��OpenGL��˫�����ʵ�֣���OpenGL��˫�����ʵ��
    glutInitDisplayMode GLUT_DOUBLE
    
    glEnable (GL_POLYGON_OFFSET_FILL)
    
    '    ����ƽ������
    '    glEnable (GL_POINT_SMOOTH)
    '    glEnable (GL_LINE_SMOOTH)
    
    '����Ȼ���ָ��һ����ʼֵ�������е�ÿ�����ص����ֵ��������� ����1�����
    'ʱ���������滭һ�����壬 ���������ÿ�����ص����ֵ��С�ڵ���1�� �����������嶼����ʾ�˳����� �����ʼֵ
    'ָ��Ϊ0�� �����ÿ�����ص����ֵ�����ڵ���0�� �����������嶼���ɼ��� �����ʼֵָ��Ϊ0.5�� ��ô�����ֻ�����С��0.5���ǲ��ֲ��ǿɼ���
    glClearDepth 1
    
    
    '��Ȳ�������
'GL_NEVER:   ��������
    '      GL_LESS�����Ŀ������zֵ<��ǰ����zֵ�������Ŀ������
    '      GL_EQUAL�����Ŀ������zֵ����ǰ����zֵ�������Ŀ������
    '      GL_LEQUAL�����Ŀ������zֵ<����ǰ����zֵ�������Ŀ������
    '      GL_GREATER �����Ŀ������zֵ>��ǰ����zֵ�������Ŀ������
    '      GL_NOTEQUAL�����Ŀ������zֵ<>��ǰ����zֵ�������Ŀ������
    '      GL_GEQUAL�����Ŀ������zֵ>=��ǰ����zֵ�������Ŀ������\
    '      GL_ALWAYS�����ǻ���  glDepthFunc GL_LESS
    '    �ú���ֻ�����á���Ȳ��ԡ�ʱ����Ч
    glDepthFunc GL_LESS
    '    glDepthFunc cfLEqual
    
    '    ������Ӱƽ��
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST
    
    glBlendFunc GL_SRC_ALPHA, GL_DST_ALPHA
    '��һ������ָ��ԴͼԪ��alpha��ȡֵ���㷽�����ڶ�������ָ��Ŀ�괦��alpha�ļ��㷽����
'����������ȡֵ�����������³���֮һ:
    'GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE
    '����GL_ZERO��ʾalphaȡֵΪ0��GL_ONE��ʾ1��GL_DST_COLOR��ʾȡĿ���������ɫֵ��GL_SRC_ALPHA��ʾȡԴ�����alphaֵ�ȵȡ����磺
    'glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    '��ʾ����Ⱦ��ͼ����ӵ�Ŀ������Ҳ����˵Դ��ÿһ�����ص�alpha�������Լ���alpha��Ŀ���ÿһ�����ص�alpha����1���������Ӵ���Խ�࣬���ӵ�ͼԪ��alphaԽ�ߣ��õ��Ľ����Խ������������ں����ڱ�����Ч����
    
    '    glBlendFunc GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
    '    ��ʾ����Ⱦ��ͼ���ںϵ�Ŀ������Ҳ����˵Դ��ÿһ�����ص�alpha�������Լ���alpha��Ŀ���ÿһ�����ص�alpha����1��ȥ��λ��Դ���ص�alpha�� ��˲��۵��Ӷ��ٴΣ������ǲ���ġ�
    
    '��˵ȵ�?�Լ���һ�ԲŻ�����?
    
    '��������������ܶ��ؼ�Ч���ĺ��ģ�������������˵��ֻ��Ƥë��Ҫ���������ͱ��뿴�ٷ��ĵ���MSDN����һ����ȫ����ĵ�����Ӣ�ﲻ��ҲҪӲ������ʵ˭�տ�ʼ����ʱ�򶼻�ͷ�ۣ�������Ӣ����Ȼ����������...
    
    
    'OpenGL ���Դ��ɫ��Ŀ����ɫ����ȡ����������һ��ϵ����Դ��ɫ���Ե�ϵ����Ϊ��Դ���ӡ���Ŀ����ɫ���Ե�ϵ����Ϊ��Ŀ�����ӡ�����Ȼ����ӣ������͵õ����µ��� ɫ��
    '��Ҳ���Բ�����ӣ��°汾��OpenGL�����������㷽ʽ�������ӡ�����ȡ�����нϴ�ġ�ȡ�����н�С�ġ��߼�����ȣ�����������Ϊ�˼���������� ������ˣ�
    '��������ѧ��ʽ�����һ��������㷽ʽ������Դ��ɫ���ĸ�������ָ��ɫ����ɫ����ɫ��alphaֵ����(Rs, Gs, Bs, As)��Ŀ����ɫ���ĸ�������(Rd, Gd, Bd, Ad)��
    '����Դ����Ϊ(Sr, Sg, Sb, Sa)��Ŀ������Ϊ(Dr, Dg, Db, Da)�����ϲ���������ɫ���Ա�ʾΪ�� (Rs*Sr+Rd*Dr, Gs*Sg+Gd*Dg, Bs*Sb+Bd*Db, As*Sa+Ad*Da) ��Ȼ�ˣ�
    '�����ɫ��ĳһ����������1.0�������ᱻ�Զ���ȡΪ1.0������Ҫ����Խ������⡣
    'Դ���Ӻ�Ŀ�������ǿ���ͨ��glBlendFunc�������������õġ�glBlendFunc������������ǰ�߱�ʾԴ���ӣ����߱�ʾĿ�����ӡ����������������Ƕ���ֵ��������ܱȽϳ��õļ��֡�
    
    'GL_ZERO�� ��ʾʹ��0.0��Ϊ���ӣ�ʵ�����൱�ڲ�ʹ��������ɫ���������㡣
    
    'GL_ONE�� ��ʾʹ��1.0��Ϊ���ӣ�ʵ�����൱����ȫ��ʹ����������ɫ���������㡣
    
'GL_SRC_ALPHA: ��ʾʹ��Դ��ɫ��alphaֵ����Ϊ����.
    
'GL_DST_ALPHA: ��ʾʹ��Ŀ����ɫ��alphaֵ����Ϊ����.
    
    'GL_ONE_MINUS_SRC_ALPHA����ʾ��1.0��ȥԴ��ɫ��alphaֵ����Ϊ���ӡ�
    
    'GL_ONE_MINUS_DST_ALPHA����ʾ��1.0��ȥĿ����ɫ��alphaֵ����Ϊ���ӡ� �������⣬����GL_SRC_COLOR����Դ��ɫ���ĸ������ֱ���Ϊ���ӵ��ĸ���������GL_ONE_MINUS_SRC_COLOR�� GL_DST_COLOR��GL_ONE_MINUS_DST_COLOR�ȣ�ǰ������OpenGL�ɰ汾��ֻ����������Ŀ�����ӣ���������OpenGL �ɰ汾��ֻ����������Դ���ӡ��°汾��OpenGL��û��������ƣ�����֧���µ�GL_CONST_COLOR���趨һ�ֳ�����ɫ�������ĸ������ֱ���Ϊ ���ӵ��ĸ���������GL_ONE_MINUS_CONST_COLOR��GL_CONST_ALPHA�� GL_ONE_MINUS_CONST_ALPHA�����⻹��GL_SRC_ALPHA_SATURATE���°汾��OpenGL��������ɫ��alpha ֵ��RGBֵ���ò�ͬ�Ļ�����ӡ�
    
    '������˵�� ���������glBlendFunc(GL_ONE, GL_ZERO);�����ʾ��ȫʹ��Դ��ɫ����ȫ��ʹ��Ŀ����ɫ����˻���Ч���Ͳ�ʹ�û�ϵ�ʱ��һ�£���ȻЧ�ʿ��ܻ��һ��㣩��
    '���û������Դ���Ӻ�Ŀ�����ӣ���Ĭ������������������á� ���������glBlendFunc(GL_ZERO, GL_ONE);�����ʾ��ȫ��ʹ��Դ��ɫ������������뻭ʲô����󶼲��ᱻ����ȥ�ˡ�
    '�����Ⲣ����˵�������þ�û���ã���Щʱ�������������;�� �� ��������glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);�����ʾԴ��ɫ���������alpha ֵ��Ŀ����ɫ����
    '1.0��ȥԴ��ɫ��alphaֵ������һ����Դ��ɫ��alphaֵԽ�������������ɫ��Դ��ɫ��ռ������Խ�󣬶�Ŀ����ɫ��ռ������� С����������£����ǿ��Լ򵥵Ľ�Դ��ɫ��alpha
    'ֵ���Ϊ����͸���ȡ�����Ҳ�ǻ��ʱ��õķ�ʽ�� ���������glBlendFunc(GL_ONE, GL_ONE);�����ʾ��ȫʹ��Դ��ɫ��Ŀ����ɫ�����յ���ɫʵ���Ͼ���������ɫ�ļ���ӡ�
    '�����ɫ(1, 0, 0)����ɫ(0, 1, 0)��ӵõ�(1, 1, 0)�����Ϊ��ɫ��
    
    'ע�⣺ �� νԴ��ɫ��Ŀ����ɫ���Ǹ����Ƶ�˳���йصġ������Ȼ�����һ����ɫ�����壬�������ϻ�����ɫ�����塣����ɫ��Դ��ɫ����ɫ��Ŀ����ɫ�����˳�򷴹�����
    '�� ��ɫ����Դ��ɫ����ɫ����Ŀ����ɫ���ڻ���ʱ��Ӧ��ע��˳��ʹ�û��Ƶ�Դ��ɫ�����õ�Դ���Ӷ�Ӧ��Ŀ����ɫ�����õ�Ŀ�����Ӷ�Ӧ����Ҫ�����ҵ�˳����� ��
    glEnable GL_COLOR_MATERIAL
    InitGL = True
    
    Amb_Dif_Light(0) = 0.5: Amb_Dif_Light(1) = 0.5: Amb_Dif_Light(2) = 0.5: Amb_Dif_Light(3) = 1
    SpecularLight(0) = 1!: SpecularLight(1) = 1!: SpecularLight(2) = 1!: SpecularLight(3) = 1!
    'OpenGL ����Ⱦ��ˮ��:
    '1.��ͼ�任
    '��һ������ȷ��֮��,����������ƶ�ĳ������,����Ҫʵ�ֳ����ڵ�����,�ͱ������ģ����ͼ�ı任��ģ����ͼ�任���Ը�����Ҫ��
    '�ƶ�����תһ���������塣���磬�����������3D�ռ�������Z����ǰ�ߵĻ���ֻ��Ҫ������������-Z�����ƶ�n����λ���ɡ��������Ҫ���󿴣�
    '��Ӧ�ð�������������Y����Ⱦ������תN���Ƕ�?��ͼ��ʾ���������?
    
    '2.��������
    '��һЩ��յ�3D�����У����������ڲ��������ǲ��ɼ��ġ�������Щ��Զ���ɼ���ƽ�棬���ǿ���ʹ�ñ������غ��Զ����Ļ����������Ⱦ�ٶȡ�Ϊ��ʵ�ֱ������أ�
    '�����ڻ��������ε�ʱ�����ע�������ε��Ʒ���һ��ģ�OpenGLĬ��Ϊ��ʱ����Ƶ��������档����ͼ��ʾ���������У�����Ѷ��㰴��V1->V3->V2��˳�򴫸�OpenGL��
    '��ôOpenGL�ͻ���Ϊ��������γ�����Ļ����������?
    '3.����
    ' ����㿪���˹�����Ⱦ������Ϊÿ������ָ�������ķ��ߣ��ڴ˹����У�OpenGL�����ݶ���ķ��ߺ͹�Դ��λ�ü��������¼��㶥�����ɫ��ʹ�ù���Ч�����Դ����߻������ʵ�ԡ�
    '4.����
    '���þ��ǰ���Щ�����Ӽ��ռ䣬����һ���ڿ��ӿռ��е������޳�����ã��Ա�֤���ó�������Ļ�ϵ�ͼ�ξͲ����֡�
    '5.ͶӰ'
    'Ҫ��һ��3D�ռ��е�������ʾ����Ļ�ϣ���Ҫ����ͶӰ��ͶӰ�������ַ�ʽ��ƽ��ͶӰ��͸��ͶӰ����ƽ��ͶӰ�У�
    'Զ��������ͽ�����������һ����ģ�����ͶӰ��Ҫ�����ڼ����������ƣ�CAD���ϣ���������ͶӰû������У�
    '����һ�������ʹ��͸��ͶӰ����͸��ͶӰ�У�Զ����������ý�С�������͸��ͶӰ�У����ӿռ���һ��ƽͷ���壨��̨�壩����ͼ������ͶӰ�任��ԭ��
    '6.��դ��
    ' ��2Dͼ�ε����б任�����֮�󣬾�Ҫ������դ������ʾ����Ļ�ϣ��򱣴�ΪBMPͼƬ��դ����ʵ�ǰѱ任�õ���2Dʸ��ͼת��Ϊλͼ�Ĺ��̡�
    
    'OpenGL����������
    
    '���磬����glVertex���ڴ��붥�����ݣ���glVertex����glVertex2i, glVertex3f, glVertex2f, glVertex2d,glVertex3d�ȱ��֡�
    '�ں���glVertex3i�У�"gl"��ʾ��ǰ��������OpenGL�⡣��Ȼ����ǰ׺�����"glu"�����ʾ��GLU�⣨OpenGL�����⣩��
    
    
    glEnable (GL_NORMALIZE)
    
    SpecularLight(0) = 1!: SpecularLight(1) = 1!: SpecularLight(2) = 1!: SpecularLight(3) = 1!
    
    '������Դ��λ��
    Light0Pos(0) = 0: Light0Pos(1) = 5: Light0Pos(2) = -40: Light0Pos(3) = 1
    Light1Pos(0) = 0!: Light1Pos(1) = 1!: Light1Pos(2) = -19!: Light1Pos(3) = 1!
    Light2Pos(0) = 0!: Light2Pos(1) = 0!: Light2Pos(2) = 40!: Light2Pos(3) = 1!
    
    'Init Quadric Object...
    QObj = gluNewQuadric()
    'gluNewQuadric()�Ǵ�������������󡣴���һ���µĶ������棬�������棬Բ���棬Բ׶�棬Բ������Բ��
    'gluDeleteQuadric ɾ��һ�������������
    'gluQuadricDrawStyle ָ��Ҫ���ƵĶ�����������
    'gluQuadricNormal ���ö�������ķ�ʸ��
    'gluQuadricOrientation ���ö���������������������ת
    'gluQuadricTexture ���ö��������Ƿ�ʹ������
    
'    gluQuadricTexture QObj, GL_TRUE
'    ' ���ö��������Ƿ�ʹ������,GL_TRUEΪ�棬��ʾʹ������
'    gluQuadricNormals QObj, GL_SMOOTH
'    ' ���ö�������ķ�ʸ��
'    glEnable GL_COLOR_MATERIAL
    '//������������ɫ����ģʽ
    
    '������Դ�����й�Դ��Ч�������½�����Դ��Ĭ�Ϲ�Դ
    glEnable GL_LIGHTING                                                        'enable lighting
    glBlendFunc GL_SRC_ALPHA, GL_DST_ALPHA
    
    
'    'setup LIGHT0, Sunlight for Planets...
    glLightfv GL_LIGHT0, GL_AMBIENT, Amb_Dif_Light(0)
'    '������ԴGL_LIGHT0�����û�������ɫ��GL_AMBIENT��ֵΪAmb_Dif_Light(0)
    glLightfv GL_LIGHT0, GL_DIFFUSE, Amb_Dif_Light(0)
    glLightfv GL_LIGHT0, GL_SPECULAR, SpecularLight(0)                          '�������ɫ
'    '���ù�ԴGL_LIGHT0����������ɫ
    glLightfv GL_LIGHT0, GL_POSITION, Light0Pos(0)                              ' place the light were Sun will be,ָ����ԴGL_LIGHT0λ������
'    glLightfv GL_LIGHT1, GL_POSITION, Light1Pos(0)                              ' place the light were Sun will be,ָ����ԴGL_LIGHT0λ������
'    glLightfv GL_LIGHT2, GL_POSITION, Light2Pos(0)                              ' place the light were Sun will be,ָ����ԴGL_LIGHT0λ������
''    '������Դ������ΪGL_LIGHT0�������ù�Դ����
''    glEnable GL_LIGHT0                                                          ' Enable the light
'        glEnable GL_LIGHT1                                                          ' Enable the light
'        glEnable GL_LIGHT2                                                          ' Enable the light
    '����������Դ GL_LIGHT0
    
'OpenGL�򵥹��չ�Դ��Ϊ:
    
    '�����(Emitted Light)����򵥵�һ�ֹ⣬��ֱ�Ӵ����巢�����Ҳ����κι�ԴӰ�졣
    '������(Ambient Light)���ɹ�Դ�������������ɢ����޷�ȷ���䷽��Ĺ⣬���ƺ��������з���
    '�����(Diffuse Light)����һ����������ֱ������ʱ����бʱ��������
    '�����(Specular Light)�����ض���������һ�������ȥ��
    
    
    '������Դ
    '��Դ��������ԣ�����ɫ��λ�á�����ȡ�
'���ù�Դ���Բ����ĺ���:
    
    ' void glLight{if}[v]( GLenum light , GLenum pname , TYPE param )
    ' ����lightָ���������Ĺ�Դ�ţ��� GL_LIGHT0 ��GL_LIGHT1 ��GL_LIGHT2 ... ...
    '����pnameָ����Դ����
    '����param������Ӧ��Դ����ֵ
    
    'pname ������ ȱʡֵ ˵��
    'GL_AMBIENT ( 0.0 , 0.0 , 0.0 , 1.0 ) ���������ɫ
    'GL_DIFFUSE  ( 1.0 , 1.0 , 1.0 , 1.0 )  ����������ɫ
    'GL_SPECULAR ( 1.0 , 1.0 , 1.0 , 1.0 )  ��������ɫ
    'GL_POSITION ( 0.0 , 0.0 , 1.0 , 0.0 )  ��Դλ������
    'GL_SPOT_DIRECTION ( 0.0 , 0.0 , -1.0 ) ���Դ�۹ⷽ��ʸ��
    'GL_SPOT_EXPONENT 0.0  ���Դ�۹�ָ��
    'GL_SPOT_CUTOFF 180.0 ���Դ�۹��ֹ��
    'GL_CONSTANT_ATTENUATION 1.0 ����˥������
    'GL_LINER_ATTENUATION 0.0 ����˥������
    'GL_QUADRATIC_ATTENUATION 0.0 ƽ��˥������
    'Setup Light1, lits Sun itself...
    glLightfv GL_LIGHT1, GL_AMBIENT, Amb_Dif_Light(0)                           '���������ù�ԴGL_LIGHT1��������������ɫ
    glLightfv GL_LIGHT1, GL_DIFFUSE, Amb_Dif_Light(0)                           '�������ɫ
    glLightfv GL_LIGHT1, GL_SPECULAR, SpecularLight(0)                          '�������ɫ
    glLightfv GL_LIGHT1, GL_POSITION, Light1Pos(0)                              'Place Infront of Sun����Դλ��λ��̫��֮ǰ
    glEnable GL_LIGHT1                                                          ' Enable the light

    glLightfv GL_LIGHT2, GL_AMBIENT, Amb_Dif_Light(0)                           '���������ù�ԴGL_LIGHT1��������������ɫ
    glLightfv GL_LIGHT2, GL_DIFFUSE, Amb_Dif_Light(0)                           '�������ɫ
    glLightfv GL_LIGHT2, GL_SPECULAR, SpecularLight(0)                          '�������ɫ
    glLightfv GL_LIGHT2, GL_POSITION, Light2Pos(0)                              'Place Infront of Sun����Դλ��λ��̫��֮ǰ
    glEnable GL_LIGHT2                                                          ' Enable the light

'    SetupLight                                                                  '���ù�Դ��ɫλ������
    
    'Materials r Specular...
    '    glMaterialfv GL_FRONT, GL_SPECULAR, SpecularLight(0)
    '    glMaterialf GL_FRONT, GL_SHININESS, 1!
    '    glEnable GL_TEXTURE_2D
    
    '����ָ������
    'glMaterialfv()
    'void glMaterial{if}(GLenum face, GLenum pname, TYPE param);
    'void glMaterial{if}v(GLenum face, GLenum pname, TYPE *param);
    'ָ�����ڹ��ռ���ĵ�ǰ�������ԡ�����face��ȡֵ������GL_FRONT��GL_BACK��GL_FRONT_AND_BACK��ָ������
    '���Խ�Ӧ������������档pnameָ��Ҫ���õ����ֲ������ԡ�paramΪҪ���õ�����ֵ����һ��ָ�������ָ�루��
    '���汾����һ����ֵ���������汾����ֻҪ����GL_SHININESS�ǣ�����ʹ�÷������汾���±��оٳ��˲���pname��
    '����ȡֵ��GL_AMBIENT_AND_DIFFUSE�����ܹ�ͬʱ���ò��ʵĻ�����ɫ��ɢ����ɫ��������������Ϊ��ͬ�ģңǣ£�ֵ��
    '������pname�Ŀ���ȡֵ����Ӧֵ�����壺
    '
    '����ֵ Ĭ��ֵ ����
'    GL_AMBIENT (0.2,0.2,0.2,1.0) '���ʵĻ�����ɫ
'    GL_DIFFUSE (0.8,0.8,0.8,1.0) '���ʵ�ɢ����ɫ
'    GL_AMBIENT_AND_DIFFUSE '���ʵĻ�����ɫ��ɢ����ɫ
'    GL_SPECULAR (0.0,0.0,0.0,1.0) '���ʵľ��淴����ɫ
'    GL_SHININESS 0#  '���淴��ָ��
'    GL_EMISSION (0.0,0.0,0.1,1.0) '���ʵķ������ɫ
'    GL_COLOR_INDEXES (0, 1, 1) '������ɫ������ɢ����ɫ�����;��淴����ɫ����
    'Textures...
    'wglMakeCurrent hDC1, hglRC1
'    glGenTextures 8, TArray(0)                                                  'Gen Textures for 1st viewport
    
    Binfo.bmiHeader.biSize = Len(Binfo.bmiHeader)                               'tell me my size
    'Sun's Flare...
    '    If (LoadBMP(App.Path & "\data\Flare.bmp", sViewDC)) = False Then InitGL = False: Exit Function
    '    glBindTexture GL_TEXTURE_2D, TArray(0)
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    '    glTexImage2D GL_TEXTURE_2D, 0, 3, Binfo.bmiHeader.biWidth, Binfo.bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, Bdata(0)
    '    DeleteObject hBitmap: Erase Bdata
    '====������ͼ
    'Sun...
    '    LoadBMP App.Path & "\data\Sun.bmp", sViewDC                                 '����λͼ
    '    'wglMakeCurrent hDC1, hglRC1
    '    glBindTexture GL_TEXTURE_2D, TArray(Sun)                                    '��������λͼ�����ݴ���NEAREST����
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    '    glTexImage2D GL_TEXTURE_2D, 0, 3, Binfo.bmiHeader.biWidth, Binfo.bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, Bdata(0)
    'glTexImage2D(GL_TEXTURE_2D, //��������2D����
    '0, //ͼ�����ϸ�̶ȣ�һ��Ϊ0
    '3, //ͼ��ĳɷ֣�ΪRGB
    'TextureImage[0]->sizeX/2, //ͼ���
    'TextureImage[0]->sizeY/2, //ͼ���
    '0, //ͼ��߿�
    'GL_RGB, //ͼ����RGB��ɫ���
    'GL_UNSIGNED_BYTE, //ͼ���������޷����ֽ�����
    'TextureImage[0]->data); //ͼ��������Դ
    
    
'    '    ���û�����
'    Dim Light_Ambient(3) As GLfloat
'    Light_Ambient(0) = 0.7: Light_Ambient(1) = 0.7
'    Light_Ambient(2) = 0.7: Light_Ambient(3) = 1
'    glLightfv GL_LIGHT0, GL_AMBIENT, Light_Ambient(0)
'    '    ���������
'    Dim Light_Diffuse(3) As GLfloat
'    Light_Diffuse(0) = 0.6: Light_Diffuse(1) = 0.6
'    Light_Diffuse(2) = 0.6: Light_Diffuse(3) = 1
'    glLightfv GL_LIGHT0, GL_DIFFUSE, Light_Diffuse(0)
'    '    ���þ����
'    Dim Light_Specular(3) As GLfloat
'    Light_Specular(0) = 1: Light_Specular(1) = 1
'    Light_Specular(2) = 1: Light_Specular(3) = 1
'    glLightfv GL_LIGHT0, GL_SPECULAR, Light_Specular(0)
'    '    ���ò�������
'
'    '    ����ģ�;���ⷴ��������
'    Dim SpecRef(3) As GLfloat
'    SpecRef(0) = 0.1: SpecRef(1) = 0.1
'    SpecRef(2) = 0.1: SpecRef(3) = 1
'    glMaterialfv GL_FRONT_AND_BACK, GL_SPECULAR, SpecRef(0)
'    '    ���ò��ʾ���ָ������ȷ�������ߵĴ�С�;۽��̶ȡ�ȡֵ1-128����ֵԽ�󣬱������Խ����
'    glMateriali GL_FRONT_AND_BACK, GL_SHININESS, 128
'    '    ʹ����ɫ���ٷ�������ģ��ǰ���滷�������ʺ����䷴��������
'    glEnable GL_COLOR_MATERIAL
'    glColorMaterial GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE
    
    
    
End Function
'This Function Loads BMP files. Don't Try to Load pictures whose dimensions r not power
'of 2 e.g: 32,64,1024 etc as there is no testing for it Yet! and ur Program will Crash!
Function LoadBMP(FileName As String, sViewDC As ViewDC) As Boolean
    'load the bitmap into memory...
    hBitmap = LoadImage(0, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE Or LR_CREATEDIBSECTION)
    If hBitmap = 0 Then MsgBox "Loading Texture File: '" & FileName & "' Failed!", vbCritical: LoadBMP = False: Exit Function
    Binfo.bmiHeader.biPlanes = 1
    Binfo.bmiHeader.biBitCount = 0
    Binfo.bmiHeader.biCompression = BI_RGB
    'Load BMP info in Binfo
    GetDIBits sViewDC.hDC, hBitmap, 0, 0, ByVal 0&, ByVal VarPtr(Binfo), DIB_RGB_COLORS
    If Binfo.bmiHeader.biBitCount = 8 Then                                      'If Bmp is GrayScale
        Binfo.bmiHeader.biBitCount = 24                                         'force 24-bit colors, Load Grayscale pic as RGB
        ReDim Bdata(0 To Binfo.bmiHeader.biSizeImage * 3 - 1)                   'Allocate enough space for Bdata
        'Get BMP data in Bdata
        GetDIBits sViewDC.hDC, hBitmap, 0, Binfo.bmiHeader.biHeight, Bdata(0), ByVal VarPtr(Binfo), DIB_RGB_COLORS
    Else
        ReDim Bdata(0 To Binfo.bmiHeader.biHeight * Binfo.bmiHeader.biWidth * 3 - 1)
        GetDIBits sViewDC.hDC, hBitmap, 0, Binfo.bmiHeader.biHeight, Bdata(0), ByVal VarPtr(Binfo), DIB_RGB_COLORS
    End If
    LoadBMP = True
End Function

Private Sub SetupLight()
    Dim LightAmbient(0 To 3) As Single                                          '�����Դ������ɫֵ
    Dim LightDiffuse(0 To 3) As Single                                          '�����Դ��ɢ��ɫֵ
    Dim LightSpecular(0 To 3) As Single                                         '�����Դ�ķ��䡢������ɫֵ
    Dim LightPosition(0 To 3) As Single                                         '�����Դλ��
    Dim X As Integer                                                            'ѭ������
    
    For X = 0 To 3
        LightAmbient(X) = 0.8                                                   '���ù�Դ�Ļ�����ɫΪ��ɫ
        LightDiffuse(X) = 1                                                     '���ù�Դ����ɢ��ɫΪ��ɫ
        LightSpecular(X) = 0.2                                                  '���ù�Դ������ɫΪ��ɫ
    Next
    
    LightPosition(0) = 0                                                        '���ù�Դ��Xλ��
    LightPosition(1) = 0                                                        '���ù�Դ��Yλ��
    LightPosition(2) = -100                                                     '���ù�Դ��Zλ��
    
    glDisable glcLighting                                                       '�ù�Դ��ʱʧЧ
    glLightfv ltLight0, lpmAmbient, LightAmbient(0)                             '���ù�Դ�� ambient ��ɫֵ
    glLightfv ltLight0, lpmDiffuse, LightDiffuse(0)                             '���ù�Դ�� diffuse ��ɫֵ
    glLightfv ltLight0, lpmSpecular, LightSpecular(0)                           '���ù�Դ�� specular ��ɫֵ
    glLightfv ltLight0, lpmPosition, LightPosition(0)                           '���ù�Դ��λ��
    glEnable glcLighting                                                        '���»ָ���Դ
End Sub
