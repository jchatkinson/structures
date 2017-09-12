/*
gonum_test contains basic test functions which demonstrate the various matrix operations available in gonum
*/
package structures

import (
	"testing"

	"github.com/gonum/matrix/mat64"
)

// Test01 shows how to multiply two matrices and scale a matrix

func Test01(t *testing.T) {
	var a, b, c *mat64.Dense
	a = ones(2, 2)
	b = ones(2, 2)
	c = zeros(2, 2)
	a.Scale(5.0, a)
	printmat(a, b)
	c.Mul(a, b)
	printmat(a, b, c)
	if c.At(0, 0) != 10 {
		t.Error("C(0,0) != 10")
	}
}

//Test02 shows how to insert elements into matrix
func Test02(t *testing.T) {
	a := zeros(2, 2)
	data := [][]float64{{1, 1}, {2, 2}}
	rows, cols, _ := flatten(data)
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			a.Set(r, c, data[r][c])
		}
	}
	printmat(a)
}
func Test03(t *testing.T) {
	// Test03 shows how to scale a matrix
	a := ones(2, 2)
	a.Scale(5, a)
	printmat(a)
}

func TestSlice(t *testing.T) {
	A := ones(3, 3)
	B := A.Slice(0, 2, 0, 2).(*mat64.Dense)
	//changes to the B matrix should be reflected in the A matrix
	B.Set(0, 0, 100)
	B.Set(1, 1, 100)
	printmat(A, B)
	if A.At(0, 0) != 100 {
		t.Errorf("B != A")
	}
}

func TestAugment(t *testing.T) {
	//augment should place the matrices beside each other in a new matrix
	a := ones(3, 3)
	b := zeros(3, 3)
	// var c := zeros(3, 6)
	c := mat64.NewDense(3, 6, nil)
	c.Augment(a, b)
	printmat(a, b, c)
}
