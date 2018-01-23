Attribute VB_Name = "OGLModule"
Option Explicit

Enum ViewDirection
    ViewFront = 1                                                               ' 前视图
    ViewBack = 2                                                                ' 后视图
    viewLeft = 3                                                                ' 左视图
    ViewRight = 4                                                               ' 右视图
    ViewTop = 5                                                                 ' 上视图
    ViewBottom = 6                                                              ' 下视图
End Enum

Public Type ViewDC
    hglRC As Long                                                               '渲染上下文(RC)
    hDC As Long                                                                 '设备上下文(DC)
End Type
'以下用于坐标缩放
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

'光源变量
Dim Amb_Dif_Light(3) As Single                                                  '= { 0.5!, 0.5!, 0.5!, 1.0! } 'ambient n diffuse light(both r same!)，环境光——经过多次反射而来的光称为环境光，
'无法确定其最初的方向，但当特定的光源关闭后，它们将消失.
'全局环境光——它们并非来自特定的光源，这些光经过了多次散射，
'已经无法确定其光源位于何处.

Dim SpecularLight(3) As Single                                                  '= { 1.0!, 1.0!, 1.0!, 1.0! } ' specular light，高光          '散射光——来自同一方向，照射到物体表面后，
'将沿各个方向均匀反射，因此，无论从哪个方向观察，表面的亮度都相同.
'镜面反射光——来自特定方向，也被反射到特定方向.镜面反射度与之相关.
'材质发射光——用于模拟发光物体.在OpenGL光照模型中，表面的发射光增加了
'物体的亮度，它不受光源的影响，另外，发射光不会给整个场景中增加光线.



Dim Light0Pos!(3), Light1Pos!(3), Light2Pos!(3)

Public ViewDCs(1 To 1) As ViewDC
Global QObj As Long                                                             'GLU Quadric Object




Function InitGL(sViewDC As ViewDC) As Boolean
    '本过程用于初始化显示控件
    Dim Pfd As PIXELFORMATDESCRIPTOR
    Dim Result As Long
    '设置像素格式，象素格式描述完成后，调用ChoosePixelFormat和SetPixelFormat函数将之与设备描述表进行匹配和设置
    Pfd.nSize = Len(Pfd)
    Pfd.nVersion = 1
    Pfd.dwFlags = PFD_SUPPORT_OPENGL Or PFD_DRAW_TO_WINDOW Or PFD_DOUBLEBUFFER Or PFD_TYPE_RGBA
    Pfd.iPixelType = PFD_TYPE_RGBA
    Pfd.cColorBits = 32
    Pfd.cDepthBits = 16
    
    Result = ChoosePixelFormat(sViewDC.hDC, Pfd)
    If Result = 0 Then
        MsgBox "OpenGL 初始化失败!", vbCritical
        InitGL = False
        Exit Function
    End If
    SetPixelFormat sViewDC.hDC, Result, Pfd
    
    '创建一个新的OpenGL渲染描述表，此描述表必须适用于绘制到由hdc返回的设备。这个渲染描述表将有和设备上下文(dc)一样的像素格式。
    sViewDC.hglRC = wglCreateContext(sViewDC.hDC)                               '根据DC创建RC
    
    wglMakeCurrent sViewDC.hDC, sViewDC.hglRC                                   '将DC与RC相关联
    '    glClearColor 0, 0, 0, 0                                                '设置背景色黑色，不透明
    
    '设置背景色白色，不透明
    glClearColor 1, 1, 1, 0
    
    '着色模式。GL_SMOOTH（默认值）——画图的时候颜色变化是平滑过渡的，独立的处理图元中各个顶点的颜色，对于线段图元，线段上各点的颜色将根据两个顶点的颜色通过插值得到。
    '对于多边形图元，多边形内部区域的颜色将根据所有顶点的颜色插值得到。；GL_FLAT——采用恒定着色，使用图元中某个顶点的颜色来渲染整个图元。
    '    glShadeModel (GL_SMOOTH)
    
    '    OpenGL命令，使用线框模式
    glPolygonMode GL_FRONT_AND_BACK, GL_LINE
    
    '打开在曲面是背面不显示功能
    '    glEnable GL_CULL_FACE
    
    '关闭在曲面是背面不显示功能来进一步验证这一点。
    glDisable (GL_CULL_FACE)
    
    '指定什么顺序为正面，逆时针还是顺时针。设置CCW方向为“正面”，CCW即CounterClockWise，逆时针；GL_CW，CW即ClockWise，顺时针。
    '如果顶点标识顺序与上边设置不一致，则会看到背面，无法显示图形。
    glFrontFace GL_CCW
    
    '激活深度比较，然后定义如果z坐标小于buffer中 //的值（当前点z较小，更靠近观察点），则显示，实际就是消隐。
    glEnable GL_DEPTH_TEST                                                      '//深度测试
    
    '常用的参数有以下几个GL_BLEND  GL_DEPTH_TEST  GL_FOG  GL_LINE_STIPPLE GL_LIGHTING
    glEnable GL_LIGHTING
    
    '    在OpenGL里双缓冲的实现，在OpenGL里双缓冲的实现
    glutInitDisplayMode GLUT_DOUBLE
    
    glEnable (GL_POLYGON_OFFSET_FILL)
    
    '    进行平滑处理
    '    glEnable (GL_POINT_SMOOTH)
    '    glEnable (GL_LINE_SMOOTH)
    
    '给深度缓冲指定一个初始值，缓冲中的每个像素的深度值都是这个， 比如1，这个
    '时候你往里面画一个物体， 由于物体的每个像素的深度值都小于等于1， 所以整个物体都被显示了出来。 如果初始值
    '指定为0， 物体的每个像素的深度值都大于等于0， 所以整个物体都不可见。 如果初始值指定为0.5， 那么物体就只有深度小于0.5的那部分才是可见的
    glClearDepth 1
    
    
    '深度测试类型
'GL_NEVER:   永不绘制
    '      GL_LESS：如果目标像素z值<当前像素z值，则绘制目标像素
    '      GL_EQUAL：如果目标像素z值＝当前像素z值，则绘制目标像素
    '      GL_LEQUAL：如果目标像素z值<＝当前像素z值，则绘制目标像素
    '      GL_GREATER ：如果目标像素z值>当前像素z值，则绘制目标像素
    '      GL_NOTEQUAL：如果目标像素z值<>当前像素z值，则绘制目标像素
    '      GL_GEQUAL：如果目标像素z值>=当前像素z值，则绘制目标像素\
    '      GL_ALWAYS：总是绘制  glDepthFunc GL_LESS
    '    该函数只有启用“深度测试”时才有效
    glDepthFunc GL_LESS
    '    glDepthFunc cfLEqual
    
    '    启用阴影平滑
    glHint GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST
    
    glBlendFunc GL_SRC_ALPHA, GL_DST_ALPHA
    '第一个参数指出源图元的alpha的取值计算方法，第二个参数指出目标处的alpha的计算方法。
'两个参数的取值都可以是如下常量之一:
    'GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_DST_ALPHA, GL_ONE_MINUS_DST_ALPHA, and GL_SRC_ALPHA_SATURATE
    '比如GL_ZERO表示alpha取值为0，GL_ONE表示1，GL_DST_COLOR表示取目标区域的颜色值，GL_SRC_ALPHA表示取源区域的alpha值等等。例如：
    'glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    '表示把渲染的图像叠加到目标区域，也就是说源的每一个像素的alpha都等于自己的alpha，目标的每一个像素的alpha等于1。这样叠加次数越多，叠加的图元的alpha越高，得到的结果就越亮。因此这种融合用于表达光亮效果。
    
    '    glBlendFunc GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
    '    表示把渲染的图像融合到目标区域。也就是说源的每一个像素的alpha都等于自己的alpha，目标的每一个像素的alpha等于1减去该位置源像素的alpha。 因此不论叠加多少次，亮度是不变的。
    
    '如此等等?自己试一试才会明白?
    
    '这个函数是制作很多特技效果的核心，变幻无穷，我这里说的只是皮毛，要完整地理解就必须看官方文档（MSDN就是一个很全面的文档），英语不好也要硬看，其实谁刚开始看的时候都会头疼，看多了英语自然就练出来了...
    
    
    'OpenGL 会把源颜色和目标颜色各自取出，并乘以一个系数（源颜色乘以的系数称为“源因子”，目标颜色乘以的系数称为“目标因子”），然后相加，这样就得到了新的颜 色。
    '（也可以不是相加，新版本的OpenGL可以设置运算方式，包括加、减、取两者中较大的、取两者中较小的、逻辑运算等，但我们这里为了简单起见，不讨 论这个了）
    '下面用数学公式来表达一下这个运算方式。假设源颜色的四个分量（指红色，绿色，蓝色，alpha值）是(Rs, Gs, Bs, As)，目标颜色的四个分量是(Rd, Gd, Bd, Ad)，
    '又设源因子为(Sr, Sg, Sb, Sa)，目标因子为(Dr, Dg, Db, Da)。则混合产生的新颜色可以表示为： (Rs*Sr+Rd*Dr, Gs*Sg+Gd*Dg, Bs*Sb+Bd*Db, As*Sa+Ad*Da) 当然了，
    '如果颜色的某一分量超过了1.0，则它会被自动截取为1.0，不需要考虑越界的问题。
    '源因子和目标因子是可以通过glBlendFunc函数来进行设置的。glBlendFunc有两个参数，前者表示源因子，后者表示目标因子。这两个参数可以是多种值，下面介绍比较常用的几种。
    
    'GL_ZERO： 表示使用0.0作为因子，实际上相当于不使用这种颜色参与混合运算。
    
    'GL_ONE： 表示使用1.0作为因子，实际上相当于完全的使用了这种颜色参与混合运算。
    
'GL_SRC_ALPHA: 表示使用源颜色的alpha值来作为因子.
    
'GL_DST_ALPHA: 表示使用目标颜色的alpha值来作为因子.
    
    'GL_ONE_MINUS_SRC_ALPHA：表示用1.0减去源颜色的alpha值来作为因子。
    
    'GL_ONE_MINUS_DST_ALPHA：表示用1.0减去目标颜色的alpha值来作为因子。 除此以外，还有GL_SRC_COLOR（把源颜色的四个分量分别作为因子的四个分量）、GL_ONE_MINUS_SRC_COLOR、 GL_DST_COLOR、GL_ONE_MINUS_DST_COLOR等，前两个在OpenGL旧版本中只能用于设置目标因子，后两个在OpenGL 旧版本中只能用于设置源因子。新版本的OpenGL则没有这个限制，并且支持新的GL_CONST_COLOR（设定一种常数颜色，将其四个分量分别作为 因子的四个分量）、GL_ONE_MINUS_CONST_COLOR、GL_CONST_ALPHA、 GL_ONE_MINUS_CONST_ALPHA。另外还有GL_SRC_ALPHA_SATURATE。新版本的OpenGL还允许颜色的alpha 值和RGB值采用不同的混合因子。
    
    '举例来说： 如果设置了glBlendFunc(GL_ONE, GL_ZERO);，则表示完全使用源颜色，完全不使用目标颜色，因此画面效果和不使用混合的时候一致（当然效率可能会低一点点）。
    '如果没有设置源因子和目标因子，则默认情况就是这样的设置。 如果设置了glBlendFunc(GL_ZERO, GL_ONE);，则表示完全不使用源颜色，因此无论你想画什么，最后都不会被画上去了。
    '（但这并不是说这样设置就没有用，有些时候可能有特殊用途） 如 果设置了glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);，则表示源颜色乘以自身的alpha 值，目标颜色乘以
    '1.0减去源颜色的alpha值，这样一来，源颜色的alpha值越大，则产生的新颜色中源颜色所占比例就越大，而目标颜色所占比例则减 小。这种情况下，我们可以简单的将源颜色的alpha
    '值理解为“不透明度”。这也是混合时最常用的方式。 如果设置了glBlendFunc(GL_ONE, GL_ONE);，则表示完全使用源颜色和目标颜色，最终的颜色实际上就是两种颜色的简单相加。
    '例如红色(1, 0, 0)和绿色(0, 1, 0)相加得到(1, 1, 0)，结果为黄色。
    
    '注意： 所 谓源颜色和目标颜色，是跟绘制的顺序有关的。假如先绘制了一个红色的物体，再在其上绘制绿色的物体。则绿色是源颜色，红色是目标颜色。如果顺序反过来，
    '则 红色就是源颜色，绿色才是目标颜色。在绘制时，应该注意顺序，使得绘制的源颜色与设置的源因子对应，目标颜色与设置的目标因子对应。不要被混乱的顺序搞晕 。
    glEnable GL_COLOR_MATERIAL
    InitGL = True
    
    Amb_Dif_Light(0) = 0.5: Amb_Dif_Light(1) = 0.5: Amb_Dif_Light(2) = 0.5: Amb_Dif_Light(3) = 1
    SpecularLight(0) = 1!: SpecularLight(1) = 1!: SpecularLight(2) = 1!: SpecularLight(3) = 1!
    'OpenGL 的渲染流水线:
    '1.视图变换
    '当一个场景确定之后,如果我们想移动某个物体,或者要实现场景内的漫游,就必须进行模型视图的变换。模型视图变换可以根据需要，
    '移动或旋转一个或多个物体。例如，如果我们想在3D空间中沿着Z轴向前走的话，只需要把所有物体向-Z方向移动n个单位即可。如果我们要向左看，
    '就应该把所有物体沿着Y轴渲染向右旋转N个角度?下图演示了这个过程?
    
    '2.背面隐藏
    '在一些封闭的3D物体中，朝着物体内部的面总是不可见的。对于这些永远不可见的平面，我们可以使用背面隐藏忽略对它的绘制以提高渲染速度。为了实现背面隐藏，
    '我们在绘制三角形的时候必须注意三角形的绕法。一般的，OpenGL默认为逆时针缠绕的面是正面。如下图所示的三角形中，如果把顶点按照V1->V3->V2的顺序传给OpenGL，
    '那么OpenGL就会认为这个三角形朝着屏幕的面是正面?
    '3.光照
    ' 如果你开启了光照渲染，并且为每个顶点指定了它的法线，在此过程中，OpenGL将根据顶点的法线和光源的位置及性质重新计算顶点的颜色。使用光照效果可以大大提高画面的真实性。
    '4.剪裁
    '剪裁就是把那些不在视见空间，或者一半在可视空间中的物体剔除或剪裁，以保证不该出现在屏幕上的图形就不出现。
    '5.投影'
    '要把一个3D空间中的物体显示在屏幕上，就要进行投影。投影又有两种方式：平行投影和透视投影。在平行投影中，
    '远处的物体和近处的物体是一样大的，这种投影主要运用在计算机辅助设计（CAD）上，由于这种投影没有立体感，
    '所以一般情况下使用透视投影。在透视投影中，远处的物体会变得较小，因此在透视投影中，可视空间是一个平头截体（或台体）。下图表明了投影变换的原理。
    '6.格栅化
    ' 当2D图形的所有变换都完成之后，就要把它们栅格化以显示在屏幕上，或保存为BMP图片。栅格化其实是把变换得到的2D矢量图转化为位图的过程。
    
    'OpenGL的命名规则
    
    '例如，函数glVertex用于传入顶点数据，而glVertex又有glVertex2i, glVertex3f, glVertex2f, glVertex2d,glVertex3d等变种。
    '在函数glVertex3i中，"gl"表示当前函数属于OpenGL库。当然，此前缀如果是"glu"，则表示是GLU库（OpenGL辅助库）。
    
    
    glEnable (GL_NORMALIZE)
    
    SpecularLight(0) = 1!: SpecularLight(1) = 1!: SpecularLight(2) = 1!: SpecularLight(3) = 1!
    
    '三个光源的位置
    Light0Pos(0) = 0: Light0Pos(1) = 5: Light0Pos(2) = -40: Light0Pos(3) = 1
    Light1Pos(0) = 0!: Light1Pos(1) = 1!: Light1Pos(2) = -19!: Light1Pos(3) = 1!
    Light2Pos(0) = 0!: Light2Pos(1) = 0!: Light2Pos(2) = 40!: Light2Pos(3) = 1!
    
    'Init Quadric Object...
    QObj = gluNewQuadric()
    'gluNewQuadric()是创建二次曲面对象。创建一个新的二次曲面，例如球面，圆柱面，圆锥面，圆环，半圆环
    'gluDeleteQuadric 删除一个二次曲面对象
    'gluQuadricDrawStyle 指定要绘制的二次曲面类型
    'gluQuadricNormal 设置二次曲面的法矢量
    'gluQuadricOrientation 设置二次曲面是内旋还是外旋转
    'gluQuadricTexture 设置二次曲面是否使用纹理
    
'    gluQuadricTexture QObj, GL_TRUE
'    ' 设置二次曲面是否使用纹理,GL_TRUE为真，表示使用纹理
'    gluQuadricNormals QObj, GL_SMOOTH
'    ' 设置二次曲面的法矢量
'    glEnable GL_COLOR_MATERIAL
    '//这里启用了颜色材质模式
    
    '启动光源，所有光源有效：包括新建立光源和默认光源
    glEnable GL_LIGHTING                                                        'enable lighting
    glBlendFunc GL_SRC_ALPHA, GL_DST_ALPHA
    
    
'    'setup LIGHT0, Sunlight for Planets...
    glLightfv GL_LIGHT0, GL_AMBIENT, Amb_Dif_Light(0)
'    '创建光源GL_LIGHT0，设置环境光颜色（GL_AMBIENT）值为Amb_Dif_Light(0)
    glLightfv GL_LIGHT0, GL_DIFFUSE, Amb_Dif_Light(0)
    glLightfv GL_LIGHT0, GL_SPECULAR, SpecularLight(0)                          '镜面光颜色
'    '设置光源GL_LIGHT0漫反射光的颜色
    glLightfv GL_LIGHT0, GL_POSITION, Light0Pos(0)                              ' place the light were Sun will be,指定光源GL_LIGHT0位置坐标
'    glLightfv GL_LIGHT1, GL_POSITION, Light1Pos(0)                              ' place the light were Sun will be,指定光源GL_LIGHT0位置坐标
'    glLightfv GL_LIGHT2, GL_POSITION, Light2Pos(0)                              ' place the light were Sun will be,指定光源GL_LIGHT0位置坐标
''    '建立光源，名称为GL_LIGHT0，并设置光源属性
''    glEnable GL_LIGHT0                                                          ' Enable the light
'        glEnable GL_LIGHT1                                                          ' Enable the light
'        glEnable GL_LIGHT2                                                          ' Enable the light
    '启动创建光源 GL_LIGHT0
    
'OpenGL简单光照光源分为:
    
    '辐射光(Emitted Light)是最简单的一种光，它直接从物体发出并且不受任何光源影响。
    '环境光(Ambient Light)是由光源发出经环境多次散射而无法确定其方向的光，即似乎来自所有方向。
    '漫射光(Diffuse Light)来自一个方向，它垂直于物体时比倾斜时更明亮。
    '镜面光(Specular Light)来自特定方向并沿另一方向反射出去。
    
    
    '创建光源
    '光源有许多特性，如颜色、位置、方向等。
'设置光源特性参数的函数:
    
    ' void glLight{if}[v]( GLenum light , GLenum pname , TYPE param )
    ' 参数light指定所创建的光源号，如 GL_LIGHT0 ，GL_LIGHT1 ，GL_LIGHT2 ... ...
    '参数pname指定光源特性
    '参数param设置相应光源特性值
    
    'pname 参数名 缺省值 说明
    'GL_AMBIENT ( 0.0 , 0.0 , 0.0 , 1.0 ) 环境光的颜色
    'GL_DIFFUSE  ( 1.0 , 1.0 , 1.0 , 1.0 )  漫反射光的颜色
    'GL_SPECULAR ( 1.0 , 1.0 , 1.0 , 1.0 )  镜面光的颜色
    'GL_POSITION ( 0.0 , 0.0 , 1.0 , 0.0 )  光源位置坐标
    'GL_SPOT_DIRECTION ( 0.0 , 0.0 , -1.0 ) 点光源聚光方向矢量
    'GL_SPOT_EXPONENT 0.0  点光源聚光指数
    'GL_SPOT_CUTOFF 180.0 点光源聚光截止角
    'GL_CONSTANT_ATTENUATION 1.0 常数衰减因子
    'GL_LINER_ATTENUATION 0.0 线性衰减因子
    'GL_QUADRATIC_ATTENUATION 0.0 平方衰减因子
    'Setup Light1, lits Sun itself...
    glLightfv GL_LIGHT1, GL_AMBIENT, Amb_Dif_Light(0)                           '创建并设置光源GL_LIGHT1参数，环境光颜色
    glLightfv GL_LIGHT1, GL_DIFFUSE, Amb_Dif_Light(0)                           '漫射光颜色
    glLightfv GL_LIGHT1, GL_SPECULAR, SpecularLight(0)                          '镜面光颜色
    glLightfv GL_LIGHT1, GL_POSITION, Light1Pos(0)                              'Place Infront of Sun，光源位置位于太阳之前
    glEnable GL_LIGHT1                                                          ' Enable the light

    glLightfv GL_LIGHT2, GL_AMBIENT, Amb_Dif_Light(0)                           '创建并设置光源GL_LIGHT1参数，环境光颜色
    glLightfv GL_LIGHT2, GL_DIFFUSE, Amb_Dif_Light(0)                           '漫射光颜色
    glLightfv GL_LIGHT2, GL_SPECULAR, SpecularLight(0)                          '镜面光颜色
    glLightfv GL_LIGHT2, GL_POSITION, Light2Pos(0)                              'Place Infront of Sun，光源位置位于太阳之前
    glEnable GL_LIGHT2                                                          ' Enable the light

'    SetupLight                                                                  '设置光源颜色位置属性
    
    'Materials r Specular...
    '    glMaterialfv GL_FRONT, GL_SPECULAR, SpecularLight(0)
    '    glMaterialf GL_FRONT, GL_SHININESS, 1!
    '    glEnable GL_TEXTURE_2D
    
    '启动指定纹理
    'glMaterialfv()
    'void glMaterial{if}(GLenum face, GLenum pname, TYPE param);
    'void glMaterial{if}v(GLenum face, GLenum pname, TYPE *param);
    '指定用于光照计算的当前材质属性。参数face的取值可以是GL_FRONT、GL_BACK或GL_FRONT_AND_BACK，指出材质
    '属性将应用于物体的哪面。pname指出要设置的哪种材质属性。param为要设置的属性值，是一个指向数组的指针（向
    '量版本）或一个数值（非向量版本）。只要设置GL_SHININESS是，才能使用非向量版本。下表列举出了参数pname的
    '可能取值。GL_AMBIENT_AND_DIFFUSE让您能够同时设置材质的环境颜色和散射颜色，并将它们设置为相同的ＲＧＢＡ值。
    '下面是pname的可能取值和相应值的意义：
    '
    '参数值 默认值 意义
'    GL_AMBIENT (0.2,0.2,0.2,1.0) '材质的环境颜色
'    GL_DIFFUSE (0.8,0.8,0.8,1.0) '材质的散射颜色
'    GL_AMBIENT_AND_DIFFUSE '材质的环境颜色和散射颜色
'    GL_SPECULAR (0.0,0.0,0.0,1.0) '材质的镜面反射颜色
'    GL_SHININESS 0#  '镜面反射指数
'    GL_EMISSION (0.0,0.0,0.1,1.0) '材质的发射光颜色
'    GL_COLOR_INDEXES (0, 1, 1) '环境颜色索引、散射颜色索引和镜面反射颜色索引
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
    '====纹理贴图
    'Sun...
    '    LoadBMP App.Path & "\data\Sun.bmp", sViewDC                                 '载入位图
    '    'wglMakeCurrent hDC1, hglRC1
    '    glBindTexture GL_TEXTURE_2D, TArray(Sun)                                    '根据来自位图的数据创建NEAREST纹理
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR
    '    glTexParameteri GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR
    '    glTexImage2D GL_TEXTURE_2D, 0, 3, Binfo.bmiHeader.biWidth, Binfo.bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, Bdata(0)
    'glTexImage2D(GL_TEXTURE_2D, //产生的是2D纹理
    '0, //图像的详细程度，一般为0
    '3, //图像的成分，为RGB
    'TextureImage[0]->sizeX/2, //图像宽
    'TextureImage[0]->sizeY/2, //图像高
    '0, //图像边框
    'GL_RGB, //图像是RGB三色组成
    'GL_UNSIGNED_BYTE, //图像数据是无符号字节类型
    'TextureImage[0]->data); //图像数据来源
    
    
'    '    设置环境光
'    Dim Light_Ambient(3) As GLfloat
'    Light_Ambient(0) = 0.7: Light_Ambient(1) = 0.7
'    Light_Ambient(2) = 0.7: Light_Ambient(3) = 1
'    glLightfv GL_LIGHT0, GL_AMBIENT, Light_Ambient(0)
'    '    设置漫射光
'    Dim Light_Diffuse(3) As GLfloat
'    Light_Diffuse(0) = 0.6: Light_Diffuse(1) = 0.6
'    Light_Diffuse(2) = 0.6: Light_Diffuse(3) = 1
'    glLightfv GL_LIGHT0, GL_DIFFUSE, Light_Diffuse(0)
'    '    设置镜面光
'    Dim Light_Specular(3) As GLfloat
'    Light_Specular(0) = 1: Light_Specular(1) = 1
'    Light_Specular(2) = 1: Light_Specular(3) = 1
'    glLightfv GL_LIGHT0, GL_SPECULAR, Light_Specular(0)
'    '    设置材质属性
'
'    '    设置模型镜面光反射率属性
'    Dim SpecRef(3) As GLfloat
'    SpecRef(0) = 0.1: SpecRef(1) = 0.1
'    SpecRef(2) = 0.1: SpecRef(3) = 1
'    glMaterialfv GL_FRONT_AND_BACK, GL_SPECULAR, SpecRef(0)
'    '    设置材质镜面指数，它确定镜面光斑的大小和聚焦程度。取值1-128，该值越大，表面光泽越明显
'    glMateriali GL_FRONT_AND_BACK, GL_SHININESS, 128
'    '    使用颜色跟踪法，设置模型前后面环境反射率和漫射反射率属性
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
    Dim LightAmbient(0 To 3) As Single                                          '保存光源环境颜色值
    Dim LightDiffuse(0 To 3) As Single                                          '保存光源扩散颜色值
    Dim LightSpecular(0 To 3) As Single                                         '保存光源的反射、光谱颜色值
    Dim LightPosition(0 To 3) As Single                                         '保存光源位置
    Dim X As Integer                                                            '循环变量
    
    For X = 0 To 3
        LightAmbient(X) = 0.8                                                   '设置光源的环境颜色为白色
        LightDiffuse(X) = 1                                                     '设置光源的扩散颜色为白色
        LightSpecular(X) = 0.2                                                  '设置光源的谱颜色为白色
    Next
    
    LightPosition(0) = 0                                                        '设置光源的X位置
    LightPosition(1) = 0                                                        '设置光源的Y位置
    LightPosition(2) = -100                                                     '设置光源的Z位置
    
    glDisable glcLighting                                                       '让光源临时失效
    glLightfv ltLight0, lpmAmbient, LightAmbient(0)                             '设置光源的 ambient 颜色值
    glLightfv ltLight0, lpmDiffuse, LightDiffuse(0)                             '设置光源的 diffuse 颜色值
    glLightfv ltLight0, lpmSpecular, LightSpecular(0)                           '设置光源的 specular 颜色值
    glLightfv ltLight0, lpmPosition, LightPosition(0)                           '设置光源的位置
    glEnable glcLighting                                                        '重新恢复光源
End Sub
