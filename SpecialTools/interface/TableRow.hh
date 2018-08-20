// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: TableRow.hh,v 1.2 2011/02/26 19:10:07 eusebi Exp $

#ifndef TABLEROW_DEF
#define TABLEROW_DEF

//My libraries
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/SpecialTools/interface/TableCell.hh"
#include "CUAnalysis/SpecialTools/interface/TableFormat.hh"

//C++ libraries
#include <iostream>
#include <ostream>
#include <sstream>
#include <iomanip> //setw and other manipulators
#include <string>
#include <vector>

//ROOT libraries
#include "TNamed.h"


//----------------------------------------------------------------------------
// A TableRow is just a row-vector  of cells.
class TableRow  : public TNamed {

 public:

  //TableRow ();
  TableRow (const TableRow &);
  TableRow (std::string rowName ="defaultTableRow");
  ~TableRow();

  // Set and Get the vector of entries
  void addCellEntries(TableCell* ent){ cellEntries.push_back(ent); }
  void setCellEntries(std::vector<TableCell*> ent){ cellEntries = ent; }
  std::vector<TableCell*> getCellEntries() const { return cellEntries; }
  unsigned int getNCellEntries() { return cellEntries.size(); }
  std::vector<size_t> getColumnWidths(TableFormat format, bool includeRowName = true) const;
  void printRow(std::ostream &out,std::string style = "Normal");
  TableCell* findCell(std::string col);
  TableCell* findCell(unsigned int colIndex);
  // Reset the information for this row
  TableRow & reset();
  // Clone the row and optionally reset all of the values in the cells
  TableRow & clone(std::string name = "", bool reset = false);
  TableRow & operator=(const TableRow & rhs);
  TableCell* operator[](std::string col);
  TableRow   operator+(const TableRow & rhs) const;
  TableRow & operator+=(const TableRow & rhs);

 private:

  void deleteAllCells();

  std::vector<TableCell*>  cellEntries; // The entries in each cell of this row 

  ClassDef (TableRow,1)
};// TableRow


#endif
