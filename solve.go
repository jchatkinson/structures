package structures

import (
	"fmt"
	"reflect"

	"github.com/gonum/matrix/mat64"
)

const (
	solveAccuracy = 1E-6
)

// Structure type contains the necessary parameters for solving a structural problem
type Structure struct {
	M, N                                                int
	Coord, Con, Re, Load, W, E, G, A, Iz, Iy, J, St, Be mat64.Matrix
}

// MSA = Matrix Structural Analysis
type MSA interface {
	Initialize() ([]mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, error)
	Solve() (mat64.Matrix, mat64.Matrix, mat64.Matrix)
	Display()
}

// initialize initializes the matrices for the system to be solved
func initialize(m int, n int) ([]mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, mat64.Matrix, error) {

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
	return Ni, S, Pf, Q, Qfi, Ei, V, R, nil
}

// Solve assembles the system
func (s Structure) Solve() (Q mat64.Matrix, V mat64.Matrix, R mat64.Matrix) {

	/*--Return Results------------------------------------------------------------------*/
	return Q, V, R
}

// Display prints out the structure info to the console
func (s Structure) Display() {
	sr := reflect.ValueOf(s).Elem()
	typeOfT := sr.Type()
	for i := 0; i < sr.NumField(); i++ {
		f := sr.Field(i)
		fmt.Printf("%d: %s %s = %v\n", i, typeOfT.Field(i).Name, f.Type(), f.Interface())
		// fmt.Printf("Arg %v:\nm = %v\n\n", i, mat64.Formatted(f, mat64.Prefix("    "), mat64.Squeeze()))
	}
}
