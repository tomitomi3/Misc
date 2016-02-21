Module test
    Sub Main()
        Dim hndrand As New LibRandomGenerator.HalfNormalDistribution.BoxMuller()
        Dim ndrand As New LibRandomGenerator.NormalDistribution.BoxMuller()
        Dim levy As New LibRandomGenerator.LevyDistribution.Levy()
        For i As Integer = 0 To 10000 - 1
            Console.WriteLine("{0},{1},{2}", hndrand.Random(), ndrand.Random(), levy.Random())
        Next
    End Sub
End Module
