// MassStream.h
// Class that defines material flows for the Fuel Cycle.  Input into most FCComp objects.
// Effectively an normalized isotopic linked list with associated mass.
// Contains other functions for mixing mass streams and setting up sub streams.

#if !defined(_Bright_MassStream_)
#define _Bright_MassStream_

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <stdio.h>
#include <stdlib.h>

#include "H5Cpp.h"

#include "bright.h"
#include "isoname.h"

// Set Type Definitions
typedef int Iso;
typedef double Weight;
typedef std::map<Iso, Weight> CompDict;
typedef CompDict::iterator CompIter;

class MassStream
{
// Parent Class for Handling Mass Streams"
private:
    double getArrayNthEntry(H5::DataSet *, int );

protected:
    //MassStream function definitions
    double get_comp_sum ();

public:
    void norm_comp_dict ();

    void load_from_hdf5 (std::string, std::string, int = -1);
    void load_from_text (char *);

    //Fundemental mass stream data
    CompDict comp;
    double mass;
    std::string name;

    //MassStream Constructors
    MassStream ();
    MassStream (CompDict, double = -1.0, std::string = "");
    MassStream (char *, double = -1.0, std::string = "");
    MassStream (std::string, double = -1.0, std::string = "");
    ~MassStream ();

    //MassStream function definitions
    void print_ms (); 
    void normalize ();
    CompDict mult_by_mass();
    double atomic_weight();

    //Sub-Stream Computation
    MassStream get_sub_stream (std::set<int>,  std::string n = "");
    MassStream get_sub_stream (std::set<std::string>,  std::string n = "");
    MassStream get_u   (std::string = "");
    MassStream get_pu  (std::string = "");
    MassStream get_lan (std::string = "");
    MassStream get_act (std::string = "");
    MassStream get_tru (std::string = "");
    MassStream get_ma  (std::string = "");
    MassStream get_fp  (std::string = "");

    //Overloaded Operators
    MassStream operator+ (double);
    MassStream operator+ (MassStream);
    MassStream operator* (double);
    MassStream operator/ (double);

};

//std::ostream& operator<< (std::ostream& os, MassStream& ms);
std::ostream& operator<< (std::ostream& os, MassStream ms);

//Exceptions
class HDF5BoundsError: public std::exception
{
  virtual const char* what() const throw()
  {
    return "Index of point is out of bounds.  Cannot read in from HDF5 File.";
  }
};

#endif
