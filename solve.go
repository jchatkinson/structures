package structures

import "github.com/gonum/matrix/mat64"

const (
	solveAccuracy = 1E-6
)

// initialize initializes the matrices for the system to be solved
func initialize(m int, n int) ([]mat64.Matrix, error) {

	if m == 0 {
		panic("cannot solve system with zero members")
	}
	if n < 2 {
		panic("the system must have atleast two nodes defined")
	}

	//initialize a 12x12 matrix for each member
	var Ni []mat64.Matrix
	for index := 0; index < m; index++ {
		Ni[index] = mat64.NewDense(12, 12, nil)
	}
	//initialize a 6n x 6n global stiffness matrix
	S := mat64.NewDense(6*n, 6*n, nil)
	//initialize a 6n x 1 matrix of fixed end forces in global coordinates
	Pf := mat64.NewDense(6*n, 1, nil)
	//initialize a 12m x 1 matrix of internal forces in local coordinates
	Q := mat64.NewDense(12*m, 1, nil)
	//initialize a 12m x 1 matrix of fixed end forces in local coordinates
	Qfi := mat64.NewDense(12*m, 1, nil)
	//initialize a 12 x m matrix of element code numbers (locations) in the global stiffness matrix
	Ei := mat64.NewDense(12, m, nil)
	//initialize the deflections in global coordinates
	V := mat64.NewDense(12*m, 1, nil)
	//initialize the support reactions in global coordinates
	R := mat64.NewDense(12*m, 1, nil)
}

// solve assembles the system
func solve(m int, n int, coord mat64.Matrix, con mat64.Matrix, re mat64.Matrix, load mat64.Matrix, w mat64.Matrix, E []float64, G []float64, A []float64, Iz []float64, Iy []float64, J []float64, St mat64.Matrix, be []float64) (Q mat64.Matrix, V mat64.Matrix, R mat64.Matrix) {
	initialize(m, n)

	/*--Coordinate Transformation------------------------------------------------------------------*/
	// var Hv mat64.Vector
	// for i := 0; i < m; i++ {
	// 	H := mat64.Col(nil, i, con)
	// 	// Hv = mat64.NewVector()
	// }

	/*--Return Results------------------------------------------------------------------*/
	return Q, V, R
}
