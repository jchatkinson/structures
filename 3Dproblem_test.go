package structures

import "testing"

func Test01(t *testing.T) {
	//setup a simple 3d structure
	var s01 Structure
	s01.Initialize()
	s01.M = 3
	s01.N = 4
	s01.Coord.Set(0, 1, -240.0)
	s01.Coord.Set(1, 2, -240.0)
	s01.Coord.Set(2, 3, -240.0)
	s01.Con.SetRow(0, float64{2, 3, 4})
	s01.Con.SetRow(0, float64{1, 1, 1})
	s01.Con.SetRow(0, float64{1, 1, 1})
	s01.Con.SetRow(0, float64{1, 1, 1})

	s01.Display()
	s01.Solve()

	//send it to the solver

}
