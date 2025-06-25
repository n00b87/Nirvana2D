Function Read32(stream)
	Dim byte_array[4]
	byte_array[3] = ReadByte(stream)
	byte_array[2] = ReadByte(stream)
	byte_array[1] = ReadByte(stream)
	byte_array[0] = ReadByte(stream)
	Return (byte_array[0] shl 24) + (byte_array[1] shl 16) + (byte_array[2] shl 8) + byte_array[3]
End Function

f = OpenFile("tm0.data", BINARY_INPUT)

Dim buf[70, 60]

For y = 0 To 69
	For x = 0 To 59
		buf[y, x] = Read32(f)
	Next
Next

CloseFile(f)

For y = 0 To 69
	For x = 0 To 59
		n = CInt32(buf[y,x])
		If n >= 0 Then
			Print "Tile at ("; x; ", "; y; ") = "; buf[y, x]
		End If
	Next
Next
