// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: Table.hh,v 1.7 2012/06/29 15:54:38 aperloff Exp $

#ifndef TABLE_DEF
#define TABLE_DEF

//My libraries
#include "CUAnalysis/SpecialTools/interface/TableFormat.hh"
#include "CUAnalysis/SpecialTools/interface/TableRow.hh"
#include "CUAnalysis/SpecialTools/interface/TableCell.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellText.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellInt.hh"
#include "CUAnalysis/SpecialTools/interface/TableCellVal.hh"
#include "CUAnalysis/SpecialTools/interface/Value.hh"
#include "CUAnalysis/AuxFunctions/interface/AuxFunctions.hh"

//C++ libraries
#include <string>
#include <vector>
#include <ostream>
#include <fstream>
#include <functional> // std::plus
#include <numeric>    // std::accumulate

//ROOT libraries
#include "TNamed.h"
#include "TCollection.h"
#include "TString.h"

//----------------------------------------------------------------------------
// a Table is just a collection of rows
class  Table : public TNamed {
  
public :
  
  Table(std::string tableName = "default_Table");  
   Table(std::string tableName, std::vector<std::string> rowNames, std::vector<std::string> colNames, std::string cellType);

  ~Table();
  
  // The operators  
  Table operator+(const Table &rhs) const;
  Table & operator+=(const Table &rhs);

  Table operator-(const Table &rhs) const;
  Table & operator-=(const Table &rhs);

  Table operator/(const Table&rhs) const;
  Table & operator/=(const Table &rhs);

  Table operator*(double rhs) const;
  Table & operator*=(double rhs);

  Table operator/(double rhs) const;
  Table & operator/=(double rhs);

  Table operator*(Value rhs) const;
  Table & operator*=(Value rhs);

  Table operator/(Value rhs) const;
  Table & operator/=(Value rhs);

  TableCell* operator()(std::string row, std::string col);

  TableRow operator[](std::string row);

  // Reset the contents of the table. Keep the name and structure. 
  void reset();
  
  //print the table to a file
  void printToFile(std::string filename, std::string style = "Normal");

  // print the Table in different formats
  void printTable(std::ostream &out,std::string style = "Normal");
  
  // add two tables together
  void addTable(Table &, unsigned int omitFirstRows = 0);

  // add a single row
  void addRow(TableRow row) { tableRows.push_back(row);}

  // remove a single row
  int removeRow(int rowIndex);
  int removeRow(std::string rowName);

  // set the vector of rows
  void setRows(std::vector<TableRow> rows) { tableRows = rows;}

  // get number of rows
  int getNumRows() {return tableRows.size();}

  // get the vector of rows
  std::vector<TableRow> getRows() const { return tableRows;} ;

  // get the TableCell object for a given Row and Column
  // cannot add a missing row when given only a row index because the new name is unknown
  //   could pass a new string name as a parameter, but that seems a little unsafe or haphazard
  TableCell* getCellRowColumn(std::string row, std::string col, bool addMissingRow = false);
  TableCell* getCellRowColumn(std::string row, unsigned int colIndex, bool addMissingRow = false);
  TableCell* getCellRowColumn(unsigned int rowIndex, std::string col);
  TableCell* getCellRowColumn(unsigned int rowIndex, unsigned int colIndex);
  //Alias to getCellRowColumn()
  //From https://stackoverflow.com/questions/9864125/c11-how-to-alias-a-function
  template <typename... Args>
  auto at(Args&&... args) -> decltype(getCellRowColumn(std::forward<Args>(args)...)) {
    return getCellRowColumn(std::forward<Args>(args)...);
  }

  // increment a cell based on its class
  // currently only TableCellInt and TableCellVal are supported
  // makes use of getCellRowColumn()
  TableCell* incrementCellRowColumn(TableCell* cell);
  TableCell* incrementCellRowColumn(std::string row, std::string col, bool addMissingRow = false);
  TableCell* incrementCellRowColumn(std::string row, unsigned int colIndex, bool addMissingRow = false);
  TableCell* incrementCellRowColumn(unsigned int rowIndex, std::string col);
  TableCell* incrementCellRowColumn(unsigned int rowIndex, unsigned int colIndex);

  // A test to fill the table
  void fillWithTest();

  // reports true if the file was parsed successfully
  virtual bool parseFromFile(std::string filename, std::string cellClass = "TableCellText", std::string formatStyle = "Normal");

  // reports true if the Line was parsed successfully
  bool parseLine(std::string filename, int lineCounter, 
		 int goodLineCounter, std::string cellClass,
		 TableFormat format);

  // get the origin of the table
  std::string getTableOrigin() {return tableOrigin;}

  // find a row and return a pointer to it
  // if the row is missing return a nullptr
  // optionally add the row if it is missing
  TableRow* findRow(std::string row, bool addMissing = false, bool verbose = false);
  TableRow* findRow(unsigned int rowIndex, bool verbose = false);

  // get the index in the tableRows vector for the row with the given name
  int getRowIndex(std::string rowName, bool verbose = false) const;

  // squash a set of rows together (delete N-1 rows and rename the last one). The rows must be contiguous.
  int squashRows(std::string beginRowName, std::string endRowName, std::string newName = "");
  int squashRows(int firstRowIndex, int lastRowIndex, std::string newName = "");

  // sum the values in a set of rows and return a new row
  TableRow sumRows(std::string beginRowName, std::string endRowName, std::string name = "") const;
  TableRow sumRows(int firstRowIndex, int lastRowIndex, std::string name = "") const;
  //TableRow sumRows(std::vector<std::string> rowNames);
  //TableRow sumRows(std::vector<int> rowIndices);

  // merge tables into a single table if they have the same name, column, and row titles
  int Merge(TCollection *list);

 protected:

  // Create a newCell of type determined by cellClass
  TableCell* createNewCell(std::string cellClass, std::string cellName);
  
  // The table class is just a vector of rows
  std::vector<TableRow> tableRows;

  // The origin of the table:
  // - The file this table was sucessfuly parsed from, if any.
  //   includes tables that were copied and modified.
  // - Automatic otherwise.
  std::string tableOrigin;

  // Provide an iterator for code simplification.
  typedef  std::vector<TableRow>::iterator tableRows_it;

  ClassDef (Table,1)
};

#endif
