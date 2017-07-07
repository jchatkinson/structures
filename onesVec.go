package structures

// OnesVec creates an array of size m filled with ones
func OnesVec(m int) []float64 {
	var data []float64
	for ii := 0; ii < m; ii++ {
		data = append(data, 1)
	}
	return data
}
