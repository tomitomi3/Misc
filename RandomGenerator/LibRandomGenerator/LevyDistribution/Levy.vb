Namespace LevyDistribution
    ''' <summary>
    ''' Random number generator(Levy distribution)
    ''' </summary>
    ''' <remarks>
    ''' Refference:
    ''' 四辻 哲章, "計算機シミュレーションのための確率分布乱数生成法", プレアデス出版, 2010年第1版第1刷
    ''' </remarks>
    Public Class Levy
        Private m_rand As New HalfNormalDistribution.BoxMuller()

        ''' <summary>
        ''' Default constructor
        ''' </summary>
        ''' <remarks></remarks>
        Public Sub New()
            'nop
        End Sub

        ''' <summary>
        ''' </summary>
        ''' <param name="ai_u"></param>
        ''' <param name="ai_theta"></param>
        ''' <returns></returns>
        ''' <remarks></remarks>
        Public Function Random(Optional ByVal ai_u As Double = 0, Optional ByVal ai_theta As Double = 1) As Double
            Dim z As Double = 0
            Do
                z = Me.m_rand.Random()
            Loop While z < 0

            Return ai_u + ai_theta / (z * z)
        End Function
    End Class
End Namespace
