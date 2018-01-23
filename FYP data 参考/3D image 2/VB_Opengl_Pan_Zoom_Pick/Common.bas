Attribute VB_Name = "Common"
Option Explicit

    
Public imax() As Integer
Public jmax() As Integer
Public kmax() As Integer
    
Public zone As Integer
    
Public X() As Double
Public y() As Double
Public z() As Double

Public xmax As Double
Public ymax As Double
Public zmax As Double

Public pmax As Double

Public is_show_grid As Integer

Public is_show_contour As Integer

Public is_show_boundary As Integer

Public is_show_light As Integer

Public is_show_shade As Integer

Public is_show_axies As Integer

'    API
Public Declare Function GdiTransparentBlt Lib "gdi32" (ByVal hdc1 As Long, ByVal x1 As Long, ByVal y1 As Long, ByVal W1 As Long, ByVal H1 As Long, ByVal Hdc2 As Long, ByVal X2 As Long, ByVal Y2 As Long, ByVal W2 As Long, ByVal H2 As Long, ByVal Color As Long) As Long 'hdc1
