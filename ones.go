package structures

import (
	"github.com/gonum/matrix/mat64"
)

//initialize a matrix of ones
func onesMat(m int, n int) *mat64.Dense {
	mat := mat64.NewDense(m, n, nil)
	row := onesVec(n)
	for ii := 0; ii < m; ii++ {
		mat.SetRow(ii, row)
	}
	return mat
}

func onesVec(m int) []float64 {
	var data []float64
	for ii := 0; ii < m; ii++ {
		data = append(data, 1)
	}
	return data
}
