package structures

import (
	"fmt"
	"testing"

	"github.com/gonum/matrix/mat64"
)

func Test01(t *testing.T) {
	//multiply two matrices
	a := zeros(2, 2)
	b := ones(2, 2)
	var c mat64.Dense
	c.Mul(a, b)
	fc := mat64.Formatted(&c, mat64.Prefix("    "), mat64.Squeeze())
	fmt.Printf("Matrix:\na = %v\n\n", fc)

}
func Test02(t *testing.T) {
	//insert elements into matrix
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
	//setup a simple 3d structure
	var s01 Structure
	s01.Initialize()
	s01.M = 3
	s01.N = 4
	s01.Coord.Set(0, 1, -240.0)
	s01.Coord.Set(1, 2, -240.0)
	s01.Coord.Set(2, 3, -240.0)
	s01.Con.SetRow(0, []float64{2, 3, 4})
	s01.Con.SetRow(0, []float64{1, 1, 1})
	s01.Con.SetRow(0, []float64{1, 1, 1})
	s01.Con.SetRow(0, []float64{1, 1, 1})

	s01.Display()
	s01.Solve()

	//send it to the solver

}
