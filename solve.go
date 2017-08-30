package structures

//
//#include <MSA.h>
import "C"
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
	S, Pf, Q, Qfi, Ei, V, R                             mat64.Matrix
	Ni                                                  []mat64.Matrix
}

// MSA (Matrix Structural Analysis) interface with methods for solving strutural problems
type MSA interface {
	Initialize()
	Solve()
	Display()
}

// Initialize sets up the structure s
func (s Structure) Initialize() {

	//initialize a 12x12 matrix for each member
	s.Ni = make([]mat64.Matrix, s.M)
	for index := 0; index < s.M; index++ {
		s.Ni[index] = mat64.NewDense(12, 12, nil)
	}
	//initialize a 6n x 6n global stiffness matrix
	s.S = mat64.NewDense(6*s.N, 6*s.N, nil)
	//initialize a 6n x 1 matrix of fixed end forces in global coordinates
	s.Pf = mat64.NewDense(6*s.N, 1, nil)
	//initialize a 12m x 1 matrix of internal forces in local coordinates
	s.Q = mat64.NewDense(12, s.M, nil)
	//initialize a 12m x 1 matrix of fixed end forces in local coordinates
	s.Qfi = mat64.NewDense(12, s.M, nil)
	//initialize a 12 x m matrix of element code numbers (locations) in the global stiffness matrix
	s.Ei = mat64.NewDense(12, s.M, nil)
	//initialize the deflections in global coordinates
	s.V = mat64.NewDense(12*s.M, 1, nil)
	//initialize the support reactions in global coordinates
	s.R = mat64.NewDense(12*s.M, 1, nil)
}

// Solve assembles the system
func (s Structure) Solve() (mat64.Matrix, mat64.Matrix, mat64.Matrix) {
	fmt.Printf("Solving the system with %v nodes and %v elements...", s.N, s.M)
	//Call the C library "MSA" and utilize the compiled matlab function msa()
	//MSA has the form:
	Q, V, R := C.MSA(s.M, s.N, s.Con, s.Coord, s.be, s.A, s.Iy, s.Iz, s.G, s.J, s.E, s.w, s.St, s.Re, s.Load)
	s.Q = mat64.Matrix(Q)
	s.V = mat64.Matrix(V)
	s.R = mat64.Matrix(R)

	// for i := 0; i < s.M; i++ {
	// 	//coordinate transformation
	// 	H := mat64.Col(nil, i, s.Con)
	// 	ni := H[0]
	// 	nj := H[1]
	// 	e := makeRange(int(6*H[1]-5), int(6*H[1]))
	// 	e = append(e, makeRange(int(6*H[2]-5), int(6*H[2])))
	// 	C.Clone(s.Coord)
	// 	c1.Clone()
	// 	c2 := mat64.Col(nil, int(H[2]), s.Coord)
	// 	C.Sub(c1, c2)

	// 	//generate local stiffness matrix

	// 	//generate local fixed-end forces

	// 	//generate member releases

	// 	//assemble local into global matrix
	// }
}

// Display prints out the structure info to the console
func (s Structure) Display() {
	sr := reflect.ValueOf(&s).Elem()
	typeOfsr := sr.Type()
	for i := 0; i < sr.NumField(); i++ {
		fmt.Printf("%d: %s %s = %v\n", i, typeOfsr.Field(i).Name, sr.Field(i).Type(), sr.Field(i).Interface())
	}
}
