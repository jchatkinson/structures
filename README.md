# Structures
This is a structural analysis package for the Go Language.

## Issues
If you find any bugs or want to discuss changes to the api, additional features, etc, feel free to file an issue on the github issue tracker. 

## Contributing
Contributions of any sort are welcomed. I am a structural engineer, not a programmer, so there are likely many improvements to be made. 

## License
Code is released under the MIT License. Please see the LICENSE.md file for general license information, contributors, authors, etc.

## Symbology
The code in this package uses the following symbols:

Inputs
* m = int of number of members
* n = int of number of nodes
* coord = matrix of nodal coordinates (each row corresponds to X,Y,Z of node[i]) (float64,float64,float64)
* con = matrix of connectivity and boundary conditions (each row corresponds to a member [node[i], node[j], release[i], realease[j]]) (int, int, bool, bool)
* re = matrix of nodal releases (each row is a series of bool's) (6 bool's for 6 DOF)
* load = matrix of nodal loads (each row is the load in 6dof for the node)
* w = matrix of uniformly distributed loads on members in local coordinates (x,y,z components of w)
* E = array of elastic moduli for each member
* G = array of shear moduli for each member
* A = array of areas ...
* Iz = moment of interia for zz axis
* Iy = ''' yy axis
* J = torsional constant for each member
* St = matrix of support settlement and displacements of nodes (each row is the DOFs for the node)
* be = array of element rotations (CCW is positive, in radians)

Internals
* Ni = stiffness matrix for each member
* S = global stiffness matrix for system
* Pf = fixed end forces for each member (global)
* Qfi = fixed end forces for each member (local)
* Ei = member code numbers

Outputs
* Q = matrix of internal forces in local coordinate system
* V = matrix of deflections in global coordinate system
* R = reactions for supported nodes in global coordinate system
