package structures

import (
	"testing"

	"gonum.org/v1/gonum/mat"
)

// TestKronecker tests the Kronecker product function
func TestKronecker(t *testing.T) {
	A := eye(4)
	B := mat.NewDense(flatten([][]float64{{1, -1}, {-1, 1}}))
	K := Kronecker(A, B)
	// expected result is 8x8
	expected := mat.NewDense(flatten([][]float64{
		{1, -1, 0, 0, 0, 0, 0, 0},
		{-1, 1, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, -1, 0, 0, 0, 0},
		{0, 0, -1, 1, 0, 0, 0, 0},
		{0, 0, 0, 0, 1, -1, 0, 0},
		{0, 0, 0, 0, -1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 1, -1},
		{0, 0, 0, 0, 0, 0, -1, 1}}))

	if K != expected {
		printmat(K, expected)
		t.Fail()
	}

}
