Namespace HalfNormalDistribution
    ''' <summary>
    ''' Random number generator using Box-Muller method.(Half Normal Distribution)
    ''' </summary>
    ''' <remarks>
    ''' Refference:
    ''' 四辻 哲章, "計算機シミュレーションのための確率分布乱数生成法", プレアデス出版, 2010年第1版第1刷
    ''' </remarks>
    Public Class BoxMuller
        Private m_rand As New UniformDistribution.Xorshift()
        Private y1 As Double = 0
        Private y2 As Double = 0
        Private flg As Boolean = True

        ''' <summary>
        ''' Default constructor
        ''' </summary>
        ''' <remarks></remarks>
        Public Sub New()
            'nop
        End Sub

        ''' <summary>
        ''' Normal Distribution
        ''' </summary>
        ''' <param name="ai_sigma2">Varianse s^2</param>
        ''' <returns></returns>
        ''' <remarks>
        ''' </remarks>
        Public Function Random(Optional ByVal ai_sigma2 As Double = 1) As Double
            Dim u1 As Double = Me.m_rand.NextDouble()
            Dim u2 As Double = Me.m_rand.NextDouble()

            Dim r As Double = Math.Sqrt(-2.0 * Math.Log(u1))
            Dim theta = Math.PI * u2 * 0.5

            Me.y1 = r * Math.Cos(theta)
            Me.y2 = r * Math.Sin(theta)

            If Me.flg = True Then
                Me.flg = False
                Return y1 * ai_sigma2
            Else
                Me.flg = True
                Return y2 * ai_sigma2
            End If
        End Function

    End Class
End Namespace
