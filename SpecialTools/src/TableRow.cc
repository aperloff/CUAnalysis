// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: TableRow.cc,v 1.2 2011/02/26 19:10:07 eusebi Exp $

//My libraries
#include "CUAnalysis/SpecialTools/interface/TableRow.hh"

//C++ libraries
#include <string>
#include <iostream>

using std::cout;
using std::endl;
using std::string;
using std::vector;


//----------------------------------------------------------------------------
TableRow::TableRow(string _rowName) {
  SetName(_rowName.c_str());
}//C'tor


//----------------------------------------------------------------------------
// Copy constructor
TableRow::TableRow(const TableRow & rhs) {

  cellEntries.clear();

  // Set the name of this row
  SetName(rhs.GetName());
  
  // Get the vector of the new row
  const vector<TableCell*> rhsCells = rhs.getCellEntries();

  //and clone all the cells
  for (unsigned int it=0;it<rhsCells.size();it++){
    TableCell * newCell = (TableCell *) rhsCells[it]->clone();
    cellEntries.push_back(newCell);
  }   

}//C'tor


//----------------------------------------------------------------------------
TableRow::~TableRow(){
  deleteAllCells();
} //D'tor

//----------------------------------------------------------------------------
void TableRow::deleteAllCells(){

  for (unsigned int it=0;it<cellEntries.size();it++)
    delete cellEntries[it];

}

//----------------------------------------------------------------------------
std::vector<size_t> TableRow::getColumnWidths(TableFormat format, bool includeRowName) const {
  vector<size_t> colWidth;

  if(includeRowName) {
    // include the row name in the first column
    colWidth.push_back(string(GetName()).length());
  }

  // loop over the cells
  for (unsigned int col = 0; col < cellEntries.size(); col++){
    // find len as the max of the cell name and it's content
    size_t len1 = string(cellEntries[col]->GetName()).size();
    size_t len2 = cellEntries[col]->print(format).length();
    size_t len = len1 > len2 ? len1: len2;
    colWidth.push_back(len);
  }

  return colWidth;
}

//----------------------------------------------------------------------------
//The provided string determines the characters used to print the row. 
// style is case sensitive, and it must be any of the followings
// style = "Normal" Default
// style = "Latex" 
// style = "Tiki"   
// style = "Twiki" equivalent to Tiki
void TableRow::printRow(std::ostream &out, std::string style) {
  // For neatness find first the max width needed in each column 
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Check is the row is not empty
  if (cellEntries.size()==0)
     return;

  // get the format delimiters (add one to columns for row names)
  TableFormat format  = TableFormat::getFormat(style,cellEntries.size()+1);

  // Create and find the max size of each column
  // 
  vector<size_t> colWidth = getColumnWidths(format, true);

  // Now that we know the actual width of each column just print the row
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // This is the number of spaces between the information in each column
  // and the separator character before it. The right pad is always one " ".
  const size_t lpad = 1; 

  // The string to where we print
  std::ostringstream oss;
  oss << std::setprecision (4);

  //Print the table prefix, if any
  oss<<format.begin_table;

  //Print a blank space followed by the column names of the first row. In between lines.
  oss << format.line;
  oss<< std::setw(colWidth[0]+lpad)<<format.Row1HeaderPre<<" "<<format.separator;


  // Print the cell's names  
  for (unsigned int col = 0; col < cellEntries.size(); col++){
    if (col < cellEntries.size()-1 )
     oss << std::setw(colWidth[col+1]+lpad) << cellEntries[col]->GetName() << " " <<format.separator.c_str() ;
    else
     oss << std::setw(colWidth[col+1]+lpad)<< cellEntries[col]->GetName();
  }// for cellEntries
  oss<<format.end_row+format.Row1HeaderPos<<endl;
  oss << format.line;

  
  // Print the row name and separator
  oss << std::setw(colWidth[0]+lpad)<<GetName() << " " << format.separator;
  // Print the info in each cell followed by the separator when needed
  for (unsigned int col = 0; col < cellEntries.size(); col++ ){
   if (col < cellEntries.size()-1 )
     oss << std::setw(colWidth[col+1]+lpad) << cellEntries[col]->print(format) << " " << format.separator;
   else
     oss << std::setw(colWidth[col+1]+lpad) << cellEntries[col]->print(format);
  }
  oss<<format.end_row<<endl;

  oss << format.line;
  oss<<format.end_table<<endl;

  //Start from a fresh line
  out<<endl;

  // Print the string stream to the default output
  out<<oss.str()<<endl;
}

//----------------------------------------------------------------------------
TableCell* TableRow::findCell(std::string col) {
   for (unsigned int c=0; c<cellEntries.size(); c++) {
      if (col.compare(cellEntries[c]->GetName()) == 0) {
         return cellEntries[c];
      }
   }
   
   cout << "ERROR  TableRow::find Cell Specified column (" << col << ") not found" << endl
        << "\tReturning nullptr" << endl;
   return nullptr;
}

//----------------------------------------------------------------------------
TableCell* TableRow::findCell(unsigned int colIndex) {
   if(cellEntries.size()==0) {
       cout << "ERROR TableRow::findCell There are no cells in the row " << GetName() << endl;
       return nullptr;
   }
   else if(colIndex >= cellEntries.size()) {
       cout << "ERROR Table::findCell Cannot find column (" << colIndex << ")" << endl
            << " Please choose a value between 0 and " << cellEntries.size()-1 << endl;
       return nullptr;
   }
   return cellEntries[colIndex];
}

//----------------------------------------------------------------------------
TableRow & TableRow::reset() {
   for(auto cell : cellEntries) {
      cell->reset();
   }
   return *this;
}//reset

//----------------------------------------------------------------------------
TableRow & TableRow::clone(std::string name, bool reset) {
   if(name.empty()) name = std::string(GetName())+"_clone";
   TableRow* ret = (TableRow*)this->Clone(name.c_str());
   if(reset) ret->reset();
   return *ret;
}//clone

//----------------------------------------------------------------------------
TableRow & TableRow::operator=(const TableRow & rhs){

  // First delete all entries in this row
  deleteAllCells();

  // Clear the content of the cellEntries
  cellEntries.clear();

  // Set the name of this row
  SetName(rhs.GetName());

  // Get the vector of the new row
  vector<TableCell*> rhsCells = rhs.getCellEntries();

  //and clone all the cells
  for (unsigned int it=0;it<rhsCells.size();it++){
    TableCell * newCell = (TableCell *) rhsCells[it]->clone();
    cellEntries.push_back(newCell);
  }
    
  return *this;

}//operator=

//----------------------------------------------------------------------------
TableCell* TableRow::operator[](std::string col) {

   for (unsigned int c=0; c<cellEntries.size(); c++) {
      if (string(cellEntries[c]->GetName()).compare(col)==0)
         return cellEntries[c];
   }
   
   cout << "ERROR  Table::Sprecified column (" << col << ") not found" << endl
        << "\tReturning NULL pointer" << endl;
   return 0;

}//operator[]

//----------------------------------------------------------------------------
TableRow TableRow::operator+(const TableRow & rhs) const {
  TableRow ret(string(this->GetName()));

  // Get the vector of the new row
  vector<TableCell*> rhsCells = rhs.getCellEntries();

  // check that the number of cells is the same
  if (cellEntries.size() != rhsCells.size()){
    cout << "ERROR  TableRow::operator+ The table rows have two different number of cells (" << cellEntries.size() << "," << rhsCells.size() << ")." << endl
         << " Returning without adding." << endl;
    return *this;
  }

  // check that all of the cell types match
  // inefficient to do this initial loop without summing,
  //  but we don't eant to add anything if any of the types are mismatched
  for (unsigned int it=0;it<cellEntries.size();it++) {
    if(string(cellEntries[it]->ClassName()).compare(rhsCells[it]->ClassName()) != 0) {
      cout << "ERROR  TableRow::operator+ At least one cell from the rhs row has a different cell type than the lhs row." << endl
           << " Returning without adding." << endl;
      return *this;
    }
  }

  // sum the cells
  for (unsigned int it=0;it<cellEntries.size();it++) {
    TableCell * newCell = (TableCell *) cellEntries[it]->clone();
    *newCell += *rhsCells[it];
    ret.addCellEntries(newCell);
  }

  return ret;
}//operator+

//----------------------------------------------------------------------------
TableRow & TableRow::operator+=(const TableRow & rhs) {
  // Get the vector of the new row
  vector<TableCell*> rhsCells = rhs.getCellEntries();

  // check that the number of cells is the same
  if (cellEntries.size() != rhsCells.size()){
    cout << "ERROR  TableRow::operator+= The table rows have two different number of cells (" << cellEntries.size() << "," << rhsCells.size() << ")." << endl
         << " Returning without adding." << endl;
    return *this;
  }

  // check that all of the cell types match
  // inefficient to do this initial loop without summing,
  //  but we don't eant to add anything if any of the types are mismatched
  for (unsigned int it=0;it<cellEntries.size();it++) {
    if(string(cellEntries[it]->ClassName()).compare(rhsCells[it]->ClassName()) != 0) {
      cout << "ERROR  TableRow::operator+= At least one cell from the rhs row has a different cell type than the lhs row." << endl
           << " Returning without adding." << endl;
      return *this;
    }
  }

  // sum the cells
  for (unsigned int it=0;it<cellEntries.size();it++) {
    *cellEntries[it] += *rhsCells[it];
  }

  return *this;
}//operator+=

ClassImp(TableRow)
