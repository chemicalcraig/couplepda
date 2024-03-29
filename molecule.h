#ifndef MOLECULE_H
#define MOLECULE_H

#include "atom.h"
#include "grid.h"
#include "gsl/gsl_blas.h"
#include <iostream>
#include <cstdio>
#include <math.h>
#include <fstream>

using namespace std;

class Molecule {
  public:
  int spinstate; //spin state, 0=singlet, 1=triplet
  int interaction; //type of interaction (Forster/3-body)
  double groundenergy; //ground state energy in a.u.
  double mass; //molecular mass
  int nstates; //number of excited states to consider
  int nao,nbasis; //number of AO's and eigenvectors
  int nmo; //Number of orthonormal MO's
  int nroots; //Number of TDDFT roots
  int nocc,nuocc; //Number of occupied and unoccupied MO's
  double dipx,dipy,dipz,*idip,*dip,dipmag; //transition dipole moment vector
  int nlindep; //number of linearly dependent eigenvectors
  string excMethod; //excitation method {CIS/RPA}
  double *activeCharges; //transition charges (?)
  double rot[9], rotmatcom[9]; //rotation matrices;
  void rotateTheta(double theta, int axis); //subroutine to rotate molecule
  void rotateCom(double theta, double *cm); //rotate molecule about intermolecular COM vector
  void translate(const int which, double howmuch);//translate molecule
  void resetExcept(int keep);
  void setPostoInit();
  void resetall();
  void arrangeMol();
  int griddim; 

  double *ci; //ci coefficients
  int* nbasisatom; //number of basis functions on an atom
  string *nbasisatomorbitals;
  string *nbasisatomelements; //which element basis function belongs to
  double *overlapm;
  double *excenergy;
  double *transmoment;
  double *oscstrength;
  int * occupation;
  double *moeigenv;
  double *mos;

  double *posx,*posy,*posz;
  Atom *atoms;
  int natoms;
  int nmol;
  int nx,ny,nz;
  double dx1,dx2,dx3,dy1,dy2,dy3,dz1,dz2,dz3;
  double ox,oy,oz;
  double com[3],icom[3];
  double ***dens, ***densrad;

  void setnatoms(int n) {natoms = n;};
  void setxyz(int x, int y, int z) {nx=x;ny=y;nz=z;};
  void setCom();
  string outputfilename;
  
  /* Grid data for translation/rotation **/
  Grid *grid;

  /** Constructor and Destructor **/
  Molecule();
  ~Molecule() {};

  /* Memory allocation routines */
  void allocateMem(const int nb); 
  void allocateMemLindep(const int nb, const int nlindep);
  void allocateMemAtoms(const int na);
  void allocateMemTddft();
  void setnroots(const int n) {this->nroots=n;};

  /** Set masses **/
  void setAtomicMasses(string t, string m);
  void setMass(double m);

  /*********************************************
   * Operators
   */
  Molecule operator= (const Molecule& m);

};

#endif // MOLECULE_H
