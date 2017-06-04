// Package structures aids in solving structural systems using direct stiffness method
package structures

import (
	"fmt"

	"github.com/gonum/matrix/mat64"
)

func main() {
	fmt.Printf("Hello World.\n")
	// initialize a 3 element float64 slice
	dx := make([]float64, 3)
	dx[0] = 2
	dx[1] = 2
	dx[2] = 3
	// pass the slice dx as data to the matrix x
	x := mat64.NewDense(3, 1, dx)

	// alternatively, create the matrix y by inserting the data directly as an argument
	y := mat64.NewDense(3, 1, []float64{1, 4, 5})

	// create an empty matrix for the addition
	z := mat64.NewDense(3, 1, []float64{0, 0, 0})

	// perform the addition
	z.Add(x, y)

	// print the output
	fmt.Printf("%f %f %f\n", z.At(0, 0), z.At(1, 0), z.At(2, 0))
}

// func solve(m int, n int, coord mat64.Matrix, con mat64.Matrix, re mat64.Matrix, load mat64.Matrix, w mat64.Matrix, E []float64, G []float64, A []float64, Iz []float64, Iy []float64, J []float64, St mat64.Matrix, be []float64) (Q mat64.Matrix, V mat64.Matrix, R mat64.Matrix) {
// 	/*--Initialization------------------------------------------------------------------*/

// 	//initialize a 12x12 matrix for each member
// 	var Ni []mat64.Matrix
// 	for index := 0; index < m; index++ {
// 		Ni[index] = mat64.NewDense(12, 12, nil)
// 	}
// 	//initialize a 6n x 6n global stiffness matrix
// 	S := mat64.NewDense(6*n, 6*n, nil)
// 	//initialize a 6n x 1 matrix of fixed end forces in global coordinates
// 	Pf := mat64.NewDense(6*n, 1, nil)
// 	//initialize a 12m x 1 matrix of internal forces in local coordinates
// 	Q = mat64.NewDense(12*m, 1, nil)
// 	//initialize a 12m x 1 matrix of fixed end forces in local coordinates
// 	Qfi := mat64.NewDense(12*m, 1, nil)
// 	//initialize a 12 x m matrix of element code numbers (locations) in the global stiffness matrix
// 	Ei := mat64.NewDense(12, m, nil)
// 	//initialize the deflections in global coordinates
// 	V = mat64.NewDense(12*m, 1, nil)
// 	//initialize the support reactions in global coordinates
// 	R = mat64.NewDense(12*m, 1, nil)

// 	/*--Coordinate Transformation------------------------------------------------------------------*/
// 	// var Hv mat64.Vector
// 	// for i := 0; i < m; i++ {
// 	// 	H := mat64.Col(nil, i, con)
// 	// 	// Hv = mat64.NewVector()
// 	// }

// 	/*--Return Results------------------------------------------------------------------*/
// 	return Q, V, R
// }
