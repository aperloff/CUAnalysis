// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: FileLocationTable.hh,v 1.3 2013/06/19 17:05:19 aperloff Exp $

#ifndef FILELOCATIONTABLE_DEF
#define FILELOCATIONTABLE_DEF

//My libraries
#include "CUAnalysis/SpecialTools/interface/Table.hh"

//C++ libraries
#include <iostream>
#include <string>
#include <vector>

//ROOT libraries
#include "TNamed.h"

//----------------------------------------------------------------------------
// a Table is just a collection of rows
class  FileLocationTable : public Table {
  
public :
  
  FileLocationTable(std::string name = "FileLocationTable");
 
  void addBasePath();

  std::string getBasePath(std::string col);

  virtual bool parseFromFile(std::string filename, std::string cellClass = "TableCellText", std::string formatStyle = "Normal");

private :

  std::vector<std::string> basePath;
  bool basePathAdded;

};

#endif
