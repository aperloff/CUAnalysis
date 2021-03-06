// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: TableCell.hh,v 1.3 2012/06/29 15:54:38 aperloff Exp $

#ifndef TABLECELL_DEF
#define TABLECELL_DEF

//My libraries
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/SpecialTools/interface/TableFormat.hh"

//C++ libraries
#include <string>

//ROOT libraries
#include "TNamed.h"

//----------------------------------------------------------------------------
// The TableCell is an abstract base class which is the basic unit of a table.
// Derived classes need to implement all pure virtual methods.
class TableCell : public TNamed{

public:
  TableCell();
  TableCell(std::string);

  // reset the information for this cell
  virtual void reset() = 0;

  // return the information to be displayed for this cell
  virtual std::string print(TableFormat style) = 0;

  // parse the information in str into the cell contents.
  virtual bool parseFromFile(std::string str, TableFormat style) = 0;

  // create an assignement operator 
  //virtual TableCell & operator=(const TableCell & rhs) = 0;

  // explain how to do operation of cells 
  virtual TableCell & operator+=(const TableCell &rhs) {return *this;}
  virtual TableCell & operator-=(const TableCell &rhs) {return *this;}
  virtual TableCell & operator/=(const TableCell &rhs) {return *this;}

  virtual TableCell & operator*=(const double & rhs) {return *this;}
  virtual TableCell & operator/=(const double & rhs) {return *this;}

  virtual TableCell & operator*=(const Value & rhs) {return *this;}
  virtual TableCell & operator/=(const Value & rhs) {return *this;}
  virtual TableCell & operator=(Value rhs) {return *this;}

  virtual TableCell & operator*=(const int & rhs) {return *this;}
  virtual TableCell & operator/=(const int & rhs) {return *this;}
  virtual TableCell & operator=(const int & rhs) {return *this;}

  virtual TableCell & operator++(int unused) {return *this;}

  // provide a virtual clone method to all the derived classes.
  virtual TableCell * clone() const = 0;
  
  ClassDef (TableCell,1)
};

#endif
