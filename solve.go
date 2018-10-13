package structures

import (
	"fmt"
	"math"
	"reflect"

	"gonum.org/v1/gonum/mat"
)

const (
	solveAccuracy = 1E-6
)

// Structure type contains the necessary parameters for solving a structural problem
type Structure struct {
	M, N                                                int
	Coord, Con, Re, Load, W, E, G, A, Iz, Iy, J, St, Be *mat.Dense
	S, Pf, Q, Qfi, Ei, V, R                             *mat.Dense
	Ni                                                  []*mat.Dense
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
	for index := 0; index < s.M; index++ {
		s.Ni[index] = zeros(12, 12)
	}
	//initialize a 6n x 6n global stiffness matrix
	s.S = zeros(6*s.N, 6*s.N)
	//initialize a 6n x 1 matrix of fixed end forces in global coordinates
	s.Pf = mat.NewDense(6*s.N, 1, nil)
	//initialize a 12m x 1 matrix of internal forces in local coordinates
	s.Q = mat.NewDense(12, s.M, nil)
	//initialize a 12m x 1 matrix of fixed end forces in local coordinates
	s.Qfi = mat.NewDense(12, s.M, nil)
	//initialize a 12 x m matrix of element code numbers (locations) in the global stiffness matrix
	s.Ei = mat.NewDense(12, s.M, nil)
	//initialize the deflections in global coordinates
	s.V = mat.NewDense(12*s.M, 1, nil)
	//initialize the support reactions in global coordinates
	s.R = mat.NewDense(12*s.M, 1, nil)
}

// Set will set the structure properties according to the function inputs
func (s Structure) Set(m, n int, coord, con, re, load, w, E, G, A, Iz, Iy, J, St, be [][]float64) {
	s.M = m
	s.N = n
	s.Coord = mat.NewDense(flatten(coord))
	s.Con = mat.NewDense(flatten(con))
	s.Re = mat.NewDense(flatten(re))
	s.Load = mat.NewDense(flatten(load))
	s.W = mat.NewDense(flatten(w))
	s.E = mat.NewDense(flatten(E))
	s.G = mat.NewDense(flatten(G))
	s.A = mat.NewDense(flatten(A))
	s.Iz = mat.NewDense(flatten(Iz))
	s.Iy = mat.NewDense(flatten(Iy))
	s.J = mat.NewDense(flatten(J))
	s.St = mat.NewDense(flatten(St))
	s.Be = mat.NewDense(flatten(be))
}

// Solve assembles the system
func (s Structure) Solve() {
	fmt.Printf("Solving the system with %v nodes and %v elements...", s.N, s.M)

	for i := 0; i < s.M; i++ {
		//coordinate transformation
		H := mat.Col(nil, i, s.Con)
		ni := int(H[0]) //node i
		nj := int(H[1])
		bi := int(H[2]) //boundary condition i
		bj := int(H[3])
		C1 := mat.VecDenseCopyOf(s.Coord.ColView(nj))
		C2 := mat.VecDenseCopyOf(s.Coord.ColView(ni))
		C1.SubVec(C1, C2)

		e := makeRange(6*nj-5, 6*nj)
		e = append(e, makeRange(6*bi-5, 6*bi)...)
		c := s.Be.At(i, 0)
		a, b, L := cart2sph(C1.At(0, 0), C1.At(1, 0), C1.At(2, 0))
		ca := math.Cos(a)
		sa := math.Sin(a)
		cb := math.Cos(b)
		sb := math.Sin(b)
		cc := math.Cos(c)
		sc := math.Sin(c)

		r1 := mat.NewDense(flatten([][]float64{{1, 0, 0}, {0, cc, sc}, {0, -sc, cc}}))
		r2 := mat.NewDense(flatten([][]float64{{cb, sb, 0}, {-sb, cb, 0}, {0, 0, 1}}))
		r3 := mat.NewDense(flatten([][]float64{{ca, 0, sa}, {0, 1, 0}, {-sa, 0, ca}}))
		var r *mat.Dense
		r.Mul(r1, r2)
		r.Mul(r, r3) //r should be 3x3
		T := Kronecker(eye(4), r)
		//generate local stiffness matrix

		co := mat.NewDense(flatten([][]float64{{6 / L * 2 * L, 3 * 2 * L, 2 * L * 2 * L, L * 2 * L}}))
		var y, z, K, K1n *mat.Dense
		x := s.A.At(i, 0) * L * L
		y.Scale(s.Iy.At(i, 0), co)
		z.Scale(s.Iz.At(i, 0), co)
		g := s.G.At(i, 0) * s.J.At(i, 0) * L * L / s.E.At(i, 0)
		K1 := Diag([]float64{x, z.At(0, 0), y.At(0, 0)})
		K2 := mat.NewDense(flatten([][]float64{{0, 0, 0}, {0, 0, z.At(1, 0)}, {0 - 1*y.At(1, 0), 0}}))
		K3 := Diag([]float64{g, y.At(3, 0), z.At(3, 0)})
		K4 := Diag([]float64{-g, y.At(3, 0), z.At(4, 0)})
		K = zeros(12, 12)
		K1n = zeros(3, 3)
		Ka := K.Slice(0, 3, 0, 3).(*mat.Dense)
		K1n.Scale(-1.0, K1)
		K.Augment(K, K1n)
		K.Augment(K, K2)

		K.Scale(s.E.At(i, 0)/L/L/L, K)
		//generate local fixed-end forces

		//generate member releases

		//assemble local into global matrix
		printmat(T, K3, K4, Ka)
		printvars(float64(bj))
	}
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
func zeros(m, n int) *mat.Dense {
	d := make([]float64, m*n)
	for i := 0; i < m*n; i++ {
		d[i] = 0
	}
	return mat.NewDense(m, n, d)
}

// ones initialize a matrix of ones of size m x n
func ones(m, n int) *mat.Dense {
	mat := mat.NewDense(m, n, nil)
	row := OnesVec(n)
	for ii := 0; ii < m; ii++ {
		mat.SetRow(ii, *row)
	}
	return mat
}

// eye initializes an identity matrix of size m x m
func eye(n int) *mat.Dense {
	d := make([]float64, n*n)
	for i := 0; i < n*n; i += n + 1 {
		d[i] = 1
	}
	return mat.NewDense(n, n, d)
}

// OnesVec creates an array of size m filled with ones
func OnesVec(m int) *[]float64 {
	var data []float64
	for ii := 0; ii < m; ii++ {
		data = append(data, 1)
	}
	return &data
}

// makeRange returns an incrementing array from min to max, of size max-min+1
func makeRange(min, max int) []int {
	a := make([]int, max-min+1)
	for i := range a {
		a[i] = min + i
	}
	return a
}

// cart2sph transforms cartesian coordinates to spherical coordinates
func cart2sph(x, y, z float64) (azimuth, elev, radius float64) {
	hxy := Hypotenuse(x, y)
	radius = Hypotenuse(hxy, z)
	elev = math.Atan2(z, hxy)
	azimuth = math.Atan2(y, x)
	return
}

// Hypotenuse returns the SRSS of the vector elements
func Hypotenuse(x, y float64, z ...float64) float64 {
	h := x*x + y*y
	for zz := 0; zz < len(z); zz++ {
		h = h + z[zz]*z[zz]
	}
	return math.Sqrt(h)
}

//SetMatrix Copies B into A, with B's 0, 0 aligning with A's i, j
func SetMatrix(i, j int, A, B *mat.Dense) *mat.Dense {
	br, bc := B.Dims()
	for r := 0; r < br; r++ {
		for c := 0; c < bc; c++ {
			A.Set(i+r, j+c, B.At(r, c))
		}
	}
	return A
}

// Kronecker product
func Kronecker(a, b *mat.Dense) (k *mat.Dense) {
	ar, ac := a.Dims()
	br, bc := b.Dims()
	k = mat.NewDense(ar*br, ac*bc, nil)
	for i := 0; i < ar; i++ {
		for j := 0; j < ac; j++ {
			s := k.Slice(i*br, (i+1)*br, j*bc, (j+1)*bc).(*mat.Dense)
			s.Scale(a.At(i, j), b)
		}
	}
	return
}

// Diag creates a matrix with the inputs put along the diagonal and zeros elsewhere
func Diag(a []float64) *mat.Dense {
	l := len(a)
	m := zeros(l, l)
	for ii := 0; ii < l; ii++ {
		m.Set(ii, ii, a[ii])
	}
	return m
}

func printmat(m ...*mat.Dense) {
	for ii := 0; ii < len(m); ii++ {
		f1 := mat.Formatted(m[ii], mat.Squeeze())
		fmt.Printf("Matrix %v:\n%v\n", ii, f1)
	}
}
func printvars(v ...float64) {
	for ii := 0; ii < len(v); ii++ {
		fmt.Printf("v[%v] = %v\n", ii, v[ii])
	}
}

//InsertMatrix will insert the elements of b into a, starting at point (i,j). If b does not fully align with a, InertMatrix will panic.
// func InsertMatrix(a, b *mat.Dense, i, j int) *mat.Dense {
// 	ar, ac := a.Dims()
// 	br, bc := b.Dims()
// 	if i+br > ar || j+bc > ac {
// 		panic(fmt.Errorf("InsertMatrix: Inserting b into a at [%v,%v] will put b beyond the range of a", i, j))
// 	}
// }
