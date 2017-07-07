package structures

import (
	"github.com/gonum/matrix/mat64"
)

//OnesMat initialize a matrix of ones of size m x n
func OnesMat(m int, n int) *mat64.Dense {
	mat := mat64.NewDense(m, n, nil)
	row := OnesVec(n)
	for ii := 0; ii < m; ii++ {
		mat.SetRow(ii, row)
	}
	return mat
}
