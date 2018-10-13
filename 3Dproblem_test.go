package structures

import (
	"testing"
)

func TestA(t *testing.T) {
	//TestA sets up a simple 3d structure and solves
	var s01 Structure
	s01.Initialize()
	m := 3
	n := 4
	coord := [][]float64{{0, -240, 0, 0}, {0, 0, -240, 0}, {0, 0, 0, -240}}
	con := [][]float64{{2, 3, 4}, {1, 1, 1}, {1, 1, 1}, {1, 1, 1}}
	re := [][]float64{{0, 0, 0, 0, 0, 0}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}, {1, 1, 1, 1, 1, 1}}
	load := [][]float64{{0, 0, 0, -1800, 0, 1800}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0}}
	w := [][]float64{{0, -0.25, 0}, {0, 0, 0}, {0, 0, 0}}
	E := [][]float64{{29000}, {29000}, {29000}}
	G := [][]float64{{11500}, {11500}, {11500}}
	A := [][]float64{{32.9}, {32.9}, {32.9}}
	Iz := [][]float64{{716}, {716}, {716}}
	Iy := [][]float64{{236}, {236}, {236}}
	J := [][]float64{{15.1}, {15.1}, {15.1}}
	St := [][]float64{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}
	be := [][]float64{{0}, {90 * 3.14159 / 180}, {30 * 3.14159 / 180}}

	s01.Set(m, n, coord, con, re, load, w, E, G, A, Iz, Iy, J, St, be)
	s01.Display()
	//send it to the solver
	s01.Solve()

}
