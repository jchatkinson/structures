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
	Coord, Con, Re, Load, W, E, G, A, Iz, Iy, J, St, Be mat64.Dense
	S, Pf, Q, Qfi, Ei, V, R                             *mat64.Dense
	Ni                                                  []mat64.Dense
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
	s.Ni = make([]mat64.Dense, s.M)
	// for index := 0; index < s.M; index++ {
	// 	s.Ni[index] = mat64.NewDense(12, 12, nil)
	// }
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

// Set will set the structure properties according to the function inputs
func (s Structure) Set(m, n int, coord, con, re, load, w, E, G, A, Iz, Iy, J, St, be [][]float64) {
	s.M = m
	s.N = n
	s.Coord = *mat64.NewDense(flatten(coord))
	s.Con = *mat64.NewDense(flatten(con))
	s.Re = *mat64.NewDense(flatten(re))
	s.Load = *mat64.NewDense(flatten(load))
	s.W = *mat64.NewDense(flatten(w))
	s.E = *mat64.NewDense(flatten(E))
	s.G = *mat64.NewDense(flatten(G))
	s.A = *mat64.NewDense(flatten(A))
	s.Iz = *mat64.NewDense(flatten(Iz))
	s.Iy = *mat64.NewDense(flatten(Iy))
	s.J = *mat64.NewDense(flatten(J))
	s.St = *mat64.NewDense(flatten(St))
	s.Be = *mat64.NewDense(flatten(be))
}

// Solve assembles the system
func (s Structure) Solve() {
	fmt.Printf("Solving the system with %v nodes and %v elements...", s.N, s.M)

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
	return
}

// Display prints out the structure info to the console
func (s Structure) Display() {
	sr := reflect.ValueOf(&s).Elem()
	typeOfsr := sr.Type()
	for i := 0; i < sr.NumField(); i++ {
		fmt.Printf("%d: %s %s = %v\n", i, typeOfsr.Field(i).Name, sr.Field(i).Type(), sr.Field(i).Interface())
	}
}

func flatten(f [][]float64) (r, c int, d []float64) {
	r = len(f)
	if r == 0 {
		panic("flatten: no row")
	}
	c = len(f[0])
	d = make([]float64, 0, r*c)
	for _, row := range f {
		if len(row) != c {
			panic("flatten: ragged input")
		}
		d = append(d, row...)
	}
	return r, c, d
}

func unflatten(r, c int, d []float64) [][]float64 {
	m := make([][]float64, r)
	for i := 0; i < r; i++ {
		m[i] = d[i*c : (i+1)*c]
	}
	return m
}

// zeros returns a new zero matrix of size r x c
func zeros(m, n int) *mat64.Dense {
	d := make([]float64, m*n)
	for i := 0; i < m*n; i++ {
		d[i] = 0
	}
	return mat64.NewDense(m, n, d)
}

// ones initialize a matrix of ones of size m x n
func ones(m, n int) *mat64.Dense {
	mat := mat64.NewDense(m, n, nil)
	row := OnesVec(n)
	for ii := 0; ii < m; ii++ {
		mat.SetRow(ii, *row)
	}
	return mat
}

// OnesVec creates an array of size m filled with ones
func OnesVec(m int) *[]float64 {
	var data []float64
	for ii := 0; ii < m; ii++ {
		data = append(data, 1)
	}
	return &data
}
