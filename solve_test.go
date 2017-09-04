package structures

import (
	"fmt"
	"testing"

	"github.com/gonum/matrix/mat64"
)

func Test01(t *testing.T) {
	// Test01 shows how to multiply two matrices
	a := zeros(2, 2)
	b := ones(2, 2)
	var c mat64.Dense
	c.Mul(a, b)
	fc := mat64.Formatted(&c, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix:\na = %v\n\n", fc)
}
func Test02(t *testing.T) {
	//Test02 shows how to insert elements into matrix
	a := zeros(2, 2)
	data := [][]float64{{1, 1}, {2, 2}}
	rows, cols, _ := flatten(data)
	for r := 0; r < rows; r++ {
		for c := 0; c < cols; c++ {
			a.Set(r, c, data[r][c])
		}
	}
	fc := mat64.Formatted(a, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix:\na = %v\n\n", fc)
}
func Test03(t *testing.T) {
	// Test03 shows how to scale a matrix
	a := ones(2, 2)
	a.Scale(5, a)
	fc := mat64.Formatted(a, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix:\na = %v\n\n", fc)
}
func TestMakeRange(t *testing.T) {
	min := 0
	max := 5
	a := makeRange(min, max)
	L := len(a)
	if L != 6 {
		t.Errorf("length incorrect")
	}
	for i := min; i < max; i++ {
		if a[i] != i {
			t.Errorf("a[i]!=i")
		}
	}
}

func TestSlice(t *testing.T) {
	A := ones(3, 3)
	B := A.Slice(0, 2, 0, 2).(*mat64.Dense)
	//changes to the B matrix should be reflected in the A matrix
	B.Set(0, 0, 100)
	B.Set(1, 1, 100)
	fc := mat64.Formatted(A, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix A:\na = %v\n\n", fc)

	fc = mat64.Formatted(B, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix B:\na = %v\n\n", fc)

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
	c = c.Grow(0, 6).(*mat64.Dense)
	c.Augment(c, a)
	printmat(a, b, c)
}
