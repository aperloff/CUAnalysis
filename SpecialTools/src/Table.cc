// Ricardo Eusebi
// FNAL eusebi@fnal.gov
// created: Monday February 05, 2007
// $Id: Table.cc,v 1.9 2012/06/29 15:54:38 aperloff Exp $

//My libraries
#include "CUAnalysis/SpecialTools/interface/Table.hh"

//C++ libraries
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip> //setw and other manipulators

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::ostringstream;

using namespace std;

//----------------------------------------------------------------------------
Table::Table(string tableName) {

  SetName(tableName.c_str());
  tableOrigin = "Created by Hand.";

}//Default C'tor

//----------------------------------------------------------------------------
Table::Table(std::string tableName, std::vector<std::string> rowNames, std::vector<std::string> colNames, std::string cellType) {

  SetName(tableName.c_str());
  tableOrigin = "Created by Hand.";

  TableRow* tableRow;
  TableCell* cell;

  for (unsigned int r = 0; r<rowNames.size(); r++) {
     tableRow = new TableRow(rowNames[r]);
     for (unsigned int c = 0; c<colNames.size(); c++) {
        if (cellType.compare("TableCellInt")==0) {
           cell = new TableCellInt(colNames[c]);
        }
        else if (cellType.compare("TableCellVal") == 0) {
           cell = new TableCellVal(colNames[c]);
        }
        else if (cellType.compare("TableCellText") == 0)
           cell = new TableCellText(colNames[c]);
        else {
           cout << "ERROR  Table::Could not determine the cell type" << endl
                << "\tReturning without initializing the entire table" << endl;
           reset();
           return;
        }

        tableRow->addCellEntries(cell);
     }//for columns
     addRow(*tableRow);
     delete tableRow;
  }//for rows

}//C'tor
 
//----------------------------------------------------------------------------
Table::~Table() {} //D'tor
 
//----------------------------------------------------------------------------
void Table::reset(){

  for (unsigned int it=0;it<tableRows.size();it++) {
    
    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
    
    // Loop over all the cells adding the information of the other table
    for (unsigned int icell=0;icell<tableRowCells.size(); icell++)
      tableRowCells[icell]->reset();

  }// for rows

}//reset

//----------------------------------------------------------------------------
//print the table to a file
void Table::printToFile(string filename, string style)
{     
  ofstream fout(filename.c_str(),std::ios_base::out);
  printTable(fout,style);
  fout.close();
}//printToFile

//----------------------------------------------------------------------------
//The provided string determines the characters used to print the table. 
// style is case sensitive, and it must be any of the followings
// style = "Normal" Default
// style = "Latex" 
// style = "Tiki"   
// style = "Twiki" equivalent to Tiki
void Table::printTable(ostream &out, string style){

  // For neatness find first the max width needed in each column 
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // Check is the table is not empty
  if (tableRows.size()==0)
     return;

  // get the format delimiters (add one to columns for row names)
  TableFormat format  = TableFormat::getFormat(style,tableRows[0].getCellEntries().size()+1);

  // Create and find the max size of each column
  // 
  vector<size_t> colWidth;

  // start by including the table name in the first column
  colWidth.push_back(string(GetName()).length());

  // loop over rows. colWidth[0] must exist and represents the legnth of the table name
  for (tableRows_it it=tableRows.begin();it!=tableRows.end(); it++){

    size_t lenR = string(it->GetName()).length();
    if (lenR > colWidth[0] )
      colWidth[0] =  lenR;
    
    // get the cells and loop over them
    vector<TableCell*> cells = it->getCellEntries();
    for (unsigned int col = 0 ;col < cells.size();col++){

      // find len as the max of the cell name and it's content
      size_t len1 = string(cells[col]->GetName()).size();
      size_t len2 = cells[col]->print(format).length();
      size_t len = len1 > len2 ? len1: len2;

      if ((col+1) < colWidth.size()){
        if (len > colWidth[col+1] )
         colWidth[col+1] =  len;
      }else
        colWidth.push_back(len);
    }//for cells in column
  }//for rows

  // Now that we know the actual width of each column just print the table
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

  // This is the number of spaces between the information in each column
  // and the separator character before it. The right pad is always one " ".
  const size_t lpad = 1; 

  // The string to where we print
  ostringstream oss;
  oss << std::setprecision (4);

  //Print the table prefix, if any
  oss<<format.begin_table;

  //Print the table name followed by the column names of the first row. In between lines.
  oss << format.line;
  oss<< std::setw(colWidth[0]+lpad)<<format.Row1HeaderPre+GetName()<<" "<<format.separator;
  
  if (tableRows.size()>0){
 
   vector<TableCell*> cells = tableRows[0].getCellEntries();
  
    // Print the cell's names  
    for (unsigned int col = 0; col < cells.size(); col++){
      if (col < cells.size()-1 )
       oss << std::setw(colWidth[col+1]+lpad) << cells[col]->GetName() << " " <<format.separator.c_str() ;
      else
       oss << std::setw(colWidth[col+1]+lpad)<< cells[col]->GetName();
    }// for cells
    oss<<format.end_row+format.Row1HeaderPos<<endl;   
    oss << format.line;

    //Loop over all rows printing their info
    for (tableRows_it it=tableRows.begin();it!=tableRows.end(); it++) {
      vector<TableCell*> cells = it->getCellEntries();
      
      // Print the Cut name and separator
      oss << std::setw(colWidth[0]+lpad)<<it->GetName() << " " << format.separator;
      
      // Print the info in each cell followed by the separator when needed
      for (unsigned int col = 0; col < cells.size(); col++ ){
       if (col < cells.size()-1 )
         oss << std::setw(colWidth[col+1]+lpad) << cells[col]->print(format) << " " << format.separator;
       else
         oss << std::setw(colWidth[col+1]+lpad) << cells[col]->print(format);
      }
      oss<<format.end_row<<endl;
    }// for rows
  } 

  oss << format.line;
  oss<<format.end_table<<endl;

  //Start from a fresh line
  out<<endl;

  // Print the string stream to the default output
  out<<oss.str()<<endl;
  
}//printTable

//----------------------------------------------------------------------------
Table & Table::operator+=(const Table & rhs){

  vector<TableRow> table2Rows = rhs.getRows();

  //Check
  if (table2Rows.size() != tableRows.size()){
    cout<<"ERROR  Table::AddTable Tables have two different number of rows,"<<endl
	<<" Returning without adding."<<endl;
    return *this;
  }

  //Loop over all the rows adding the information of the other table
  for (unsigned int it = 0 ; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
    vector<TableCell*> table2RowCells = table2Rows[it].getCellEntries();
    
    // Check
    if (tableRowCells.size() != table2RowCells.size()){
      cout<<"ERROR  Table::operator+= TableRow "<<it<<" have two different number of cells"<<endl
	  <<" Returning without adding."<<endl;
      return *this;
    }
    
    // Loop over all the cells adding the information of the other table
    for (unsigned int it = 0 ; it < tableRowCells.size(); it++)
      tableRowCells[it]->operator+=(*table2RowCells[it]);

  }
  return *this;

}//operator+=

//----------------------------------------------------------------------------
Table Table::operator+(const Table &rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res += rhs;
  return res;

}//operator+


//----------------------------------------------------------------------------
Table & Table::operator-=(const Table & rhs){

  vector<TableRow> table2Rows = rhs.getRows();

  //Check
  if (table2Rows.size() != tableRows.size()){
    cout<<"ERROR  Table::AddTable Tables have two different number of rows,"<<endl
	<<" Returning without subtracting."<<endl;
    return *this;
  }

  //Loop over all the rows adding the information of the other table
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
    vector<TableCell*> table2RowCells = table2Rows[it].getCellEntries();
    
    // Check
    if (tableRowCells.size() != table2RowCells.size()){
      cout<<"ERROR  Table::operator-= TableRow "<<it<<" have two different number of cells"<<endl
	  <<" Returning without subtracting."<<endl;
      return *this;
    }
    
    // Loop over all the cells adding the information of the other table
    for (unsigned int it = 0; it < tableRowCells.size(); it++)
      tableRowCells[it]->operator-=(*table2RowCells[it]);

  }
  return *this;

}//operator-=

//----------------------------------------------------------------------------
Table Table::operator-(const Table &rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res -= rhs;
  return res;

}//operator-

//----------------------------------------------------------------------------
Table & Table::operator/=(const Table & rhs){

  vector<TableRow> table2Rows = rhs.getRows();

  //Check
  if (table2Rows.size() != tableRows.size()){
    cout<<"ERROR  Table::DivideTable Tables have two different number of rows,"<<endl
	<<" Returning without dividing."<<endl;
    return *this;
  }

  //Loop over all the rows dividing the information of the other table
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
    vector<TableCell*> table2RowCells = table2Rows[it].getCellEntries();
    
    // Check
    if (tableRowCells.size() != table2RowCells.size()){
      cout<<"ERROR  Table::operator/= TableRow "<<it<<" have two different number of cells"<<endl
	  <<" Returning without dividing."<<endl;
      return *this;
    }
    
    // Loop over all the cells adding the information of the other table
    for (unsigned int it = 0; it < tableRowCells.size(); it++)
      tableRowCells[it]->operator/=(*table2RowCells[it]);

  }
  return *this;

}//opertor/=

//----------------------------------------------------------------------------
Table Table::operator/(const Table &rhs) const {

  // Make a copy in which I divide the right hand side
  Table res = *this;
  res /= rhs;
  return res;

}//operator/

//----------------------------------------------------------------------------
Table Table::operator*(double rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res *= rhs;
  return res;

}//operator*

//----------------------------------------------------------------------------
Table & Table::operator*=(double rhs) {


  //Loop over all the rows 
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
      
    // Loop over all the cells adding the information of the other table
    for (unsigned int icell = 0; icell < tableRowCells.size(); icell++)
      tableRowCells[icell]->operator*=(rhs);

  }//for rows

  return *this;

}//operator*=

//----------------------------------------------------------------------------
Table Table::operator/(double rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res /= rhs;
  return res;

}//operator/

//----------------------------------------------------------------------------
Table & Table::operator/=(double rhs) {

  //Loop over all the rows 
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
      
    // Loop over all the cells adding the information of the other table
    for (unsigned int icell = 0; icell < tableRowCells.size(); icell++)
      tableRowCells[icell]->operator/=(rhs);

  }//for rows

  return *this;

}//operator/=


//----------------------------------------------------------------------------
Table Table::operator*(Value rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res *= rhs;
  return res;

}//operator*

//----------------------------------------------------------------------------
Table & Table::operator*=(Value rhs) {

  //Loop over all the rows 
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
      
    // Loop over all the cells adding the information of the other table
    for (unsigned int icell = 0; icell < tableRowCells.size(); icell++)
      tableRowCells[icell]->operator*=(rhs);

  }//for rows

  return *this;

}//operator*=

//----------------------------------------------------------------------------
Table Table::operator/(Value rhs) const {

  // Make a copy in which I add the right hand side
  Table res = *this;
  res /= rhs;
  return res;

}//operator/

//----------------------------------------------------------------------------
Table & Table::operator/=(Value rhs) {
  
  //Loop over all the rows 
  for (unsigned int it = 0; it < tableRows.size(); it++){

    // get the cells for each row
    vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
      
    // Loop over all the cells adding the information of the other table
    for (unsigned int icell=0; icell < tableRowCells.size(); icell++)
      tableRowCells[icell]->operator/=(rhs);

  }//for 

  return *this;

}//operator/=

//----------------------------------------------------------------------------
TableCell* Table::operator()(std::string row, std::string col) {

   return getCellRowColumn(row,col);

}//operator()

//----------------------------------------------------------------------------
TableRow Table::operator[](std::string row) {

   for (unsigned int r=0; r<tableRows.size(); r++) {
      if (string(tableRows[r].GetName()).compare(row)==0)
         return tableRows[r];
   }

   cout << "ERROR  Table::Specified row (" << row << ") not found" << endl
        << "\tReturning empty table row" << endl;
   TableRow e;
   return e;

}//operator[]

//----------------------------------------------------------------------------
void Table::addTable(Table & table2, unsigned int omitFirstCuts){

  vector<TableRow> table2Rows = table2.getRows();

  //Check
  if (table2Rows.size()!=tableRows.size()){
    cout<<"ERROR  Table::AddTable Tables have two different number of rows,"<<endl
	<<" Returning without adding."<<endl;
    return ;
  }

  //Loop over all the cuts adding the information of the other table
  for (unsigned int it = 0; it < tableRows.size(); it++){
    if (it>=omitFirstCuts){
      
      // get the cells for each row
      vector<TableCell*> tableRowCells = tableRows[it].getCellEntries();
      vector<TableCell*> table2RowCells = table2Rows[it].getCellEntries();
      
      // Check
      if (tableRowCells.size() != table2RowCells.size()){
	cout<<"ERROR  Table::operator+= TableRow "<<it<<" have two different number of cells"<<endl
	    <<" Returning without adding."<<endl;
      }
      
      // Loop over all the cells adding the information of the other table
      for (unsigned int icell = 0; icell < tableRowCells.size(); icell++)
	tableRowCells[icell]->operator+=(*table2RowCells[icell]);
      
    }// if omit cut

  }//for rows
  
}//addTable

//----------------------------------------------------------------------------
// Return a pointer to the TableCell with row and column names with the given strings.
// Returns a null pointer if it does not find it.
// Can optionally add a new row if the row isn't found
TableCell * Table::getCellRowColumn(string row, string col, bool addMissingRow){ 

  //Find the pointer to the row
  TableRow* rowptr = findRow(row,addMissingRow);
  if(!rowptr) {
     return nullptr;
  }
  else {
     // Get the vector of cells
     vector<TableCell*> cells = rowptr->getCellEntries();

     // Now find the cell with the name col
     for (unsigned int cc = 0; cc < cells.size(); cc++){
         if (col.compare(cells[cc]->GetName()) == 0) {
            return cells[cc];
         }
      }//for cells
  }
  return nullptr;

}//getCellRowColumn

//----------------------------------------------------------------------------
TableCell * Table::getCellRowColumn(std::string row, unsigned int colIndex, bool addMissingRow) {
  //Find the pointer to the row
  TableRow* rowptr = findRow(row,addMissingRow);
  if(!rowptr) {
     return nullptr;
  }
  else {
     return rowptr->findCell(colIndex);
  }
  return nullptr;
}

//----------------------------------------------------------------------------
TableCell * Table::getCellRowColumn(unsigned int rowIndex, string col){ 

  //Find the pointer to the row
  TableRow* rowptr = findRow(rowIndex,false);
  if(!rowptr) {
     return nullptr;
  }
  else {
     return rowptr->findCell(col);
  }
  return nullptr;

}//getCellRowColumn

//----------------------------------------------------------------------------
TableCell * Table::getCellRowColumn(unsigned int rowIndex, unsigned int colIndex){ 

  //Find the pointer to the row
  TableRow* rowptr = findRow(rowIndex,false);
  if(!rowptr) {
     return nullptr;
  }
  else {
      return rowptr->findCell(colIndex);
  }
  return nullptr;

}//getCellRowColumn

//----------------------------------------------------------------------------
TableCell* Table::incrementCellRowColumn(TableCell* cell) {
    if(cell==nullptr) {
      std::cout << "ERROR Table::incrementCellRowColumn Cell not found" << std::endl;
      return nullptr;
    }
    else if(std::string(cell->ClassName()).compare("TableCellInt")==0)
      dynamic_cast<TableCellInt&>(*cell)++;
    else if(std::string(cell->ClassName()).compare("TableCellVal")==0)
      dynamic_cast<TableCellVal&>(*cell)++;
    return cell;
}

//----------------------------------------------------------------------------
TableCell* Table::incrementCellRowColumn(std::string row, std::string col, bool addMissingRow) {
    return incrementCellRowColumn(getCellRowColumn(row,col,addMissingRow));
}

//----------------------------------------------------------------------------
TableCell* Table::incrementCellRowColumn(std::string row, unsigned int colIndex, bool addMissingRow) {
    return incrementCellRowColumn(getCellRowColumn(row,colIndex,addMissingRow));
}

//----------------------------------------------------------------------------
TableCell* Table::incrementCellRowColumn(unsigned int rowIndex, std::string col) {
    return incrementCellRowColumn(getCellRowColumn(rowIndex,col));
}

//----------------------------------------------------------------------------
TableCell* Table::incrementCellRowColumn(unsigned int rowIndex, unsigned int colIndex) {
    return incrementCellRowColumn(getCellRowColumn(rowIndex,colIndex));
}

//----------------------------------------------------------------------------
// A test table.
void Table::fillWithTest(){

  vector<TableRow> rows;
  for (int r=0;r<15;r++){
    
    vector<TableCell*> cells ;
    // Create 
    for (int c=0;c<5;c++){
      ostringstream oss;
      oss<< c<<"jets";
      TableCellVal * cell = new TableCellVal(oss.str());
      cell->val.value = c;
      cell->val.value = c*0.5;
      
      cells.push_back(cell);
    }//for cells
    
    ostringstream oss;
    oss <<"cut "<<r;
    TableRow row(oss.str());
    row.setCellEntries(cells);
    rows.push_back(row);
  }//for rows

  tableRows = rows;

  cout << "Value at (*this)(\"cut 1\",\"1jets\")=" << ((TableCellVal*)(*this)("cut 1","1jets"))->val.value << endl;
  cout << "Value at (*this)[\"cut 1\"][\"1jets\"]=" << ((TableCellVal*)(*this)["cut 1"]["1jets"])->val.value << endl;
}

//----------------------------------------------------------------------------
// reports true if the file was parsed successfully. This method
// just loops over lines and pass them to parseLine
bool Table::parseFromFile(string filename, string cellClass, string style){

  ifstream inputFile (filename.c_str());
  
  // check that the file is open
  if (inputFile.is_open()){
    
    //NEEDS TO BE FIXED!!! WON'T WORK WITH LATEX FILES!!!
    TableFormat format  = TableFormat::getFormat(style,0);

    // clear the current table
    tableRows.clear();

    // Read lines until the eof is reached
    int lineCounter = 0;
    int goodLineCounter = 0;
    string currentLine;
  
    while (inputFile.good()){

      // get the next line from the file
      getline(inputFile, currentLine);
      
      // remove leading and trailing spaces on the line
      AuxFunctions::trimSpaces(currentLine);

      lineCounter++;

      // if this is an empty line or a comment (which starts with a "#" char) 
      // continue with the while loop
      if (currentLine.length() == 0 || currentLine.find_first_of('#') == 0)
        continue;

      // if the line specifies the cell class to be used, then use it
      if (currentLine.find("CellClass=") == 0){
        cellClass = currentLine.substr(10,(currentLine.length()-10));
        continue;
      }

      // For debugging report the cell class type to be used
      //if (goodLineCounter ==0) cout<<"Using CellClass="<<cellClass<<endl;

      goodLineCounter ++;

      if (!parseLine(currentLine, lineCounter, goodLineCounter, cellClass, format)){
	cout<<"ERROR  Table::ParseFromFile() file "<<filename
	    <<" could not be parsed at line "<<lineCounter<<endl;
	return false;
      }
      
    }// while

    // Close the file
    inputFile.close();

    // For reference store the file from which this table was parsed.
    tableOrigin = "Parsed from "+filename+".";

  }else{
    cout<<"ERROR  Table::ParseFromFile() could not open file="<<filename<<endl;
  }
  return true;

}//ParseFromFile

//----------------------------------------------------------------------------
// reports true if the file was parsed successfully
bool Table::parseLine(string currentLine, int lineCounter, 
		      int goodLineCounter, string cellClass, 
		      TableFormat format){
  
  static vector<string> colNames; 
 
  // split the line into fields separated by "|"
  vector<string> fields = AuxFunctions::splitLineIntoWords(currentLine,format.separator);
  
  // remove leading and trailing spaces on all fields
  for (unsigned int ff=0;ff < fields.size(); ff++)
    AuxFunctions::trimSpaces(fields[ff]);
  

  // If it is the first good line 
  if (goodLineCounter == 1 && fields.size() > 0) {

    // set the name of the table 
    SetName(fields[0].c_str());
 
    // save the names of the columns for later use.
    colNames = fields; // field 0th is the table name and shouldn't be used.
    
  }else{ 
    // These are the different rows. 
    
    // Check that field size must be smaller than the number of columns
    if (fields.size() > colNames.size()) {
      cout<<"ERROR Table::parseFromFile. Line number "<< (lineCounter+1)
	  <<"  has "<< fields.size() <<" which is more than the "
	  << colNames.size()<< " column names"<<endl;
      return false;
    }
    
    // make sure there is at least two fields (rowname and one entry)
    if (fields.size() > 0 && fields[0].size() > 0 ){
      
      // Create the cells in this row
      vector <TableCell*> cells;
      for (unsigned int cc = 1; cc < fields.size() ; cc++){
	
	// for each field create a cell with name colNames[cc]
	//TableCell * cell = createNewCell(cellClass, colNames[cc]);
    TableCell * cell;
    if(cellClass.compare("TableCellMixed")!=0) {
       cell = createNewCell(cellClass, colNames[cc]);
    }
    else {
       if(TString(fields[cc]).Contains("+/-")) {
          cell = createNewCell("TableCellVal", colNames[cc]);
       }
       else if(TString(fields[cc]).IsDigit()) {
          cell = createNewCell("TableCellInt", colNames[cc]);
       }
       else {
          cell = createNewCell("TableCellText", colNames[cc]);
       }
    }



	// set the information from the file
	if (!cell->parseFromFile(fields[cc],format)){
	  cout<<" ERROR in Table::parseFromFile, method TableCell::parseFromFile(string str) could not parse string="<<fields[cc]<<"="<<endl;
	  cout<<" Table::parseFromFile() failed!"<<endl;
	  return false;
	}
	cells.push_back(cell);
	
      }	
      
      // Create the row and put the cells in
      TableRow row(fields[0]);
      row.setCellEntries(cells);
      tableRows.push_back(row);
      
    }// fields.size >0
  }// else
  
  return true;
  
}//ParseLine

//----------------------------------------------------------------------------
TableCell* Table::createNewCell(string cellClass, string cellName){

  //if (cellClass.compare("TableCellVal")==0)
  //return new TableCellVal(cellName);
  //else 
  if (cellClass.compare("TableCellText")==0)
    return new TableCellText(cellName);
  else if (cellClass.compare("TableCellVal")==0)
    return new TableCellVal(cellName);
  else if (cellClass.compare("TableCellInt")==0)
    return new TableCellInt(cellName);
  
  cout<<"ERROR Table::createNewCell does not know about cellClass="<<cellClass<<endl;
  return 0;

}//createNewCell

//----------------------------------------------------------------------------
int Table::removeRow(std::string rowName) {
  // first find the row index that corresponds to this row name
  int index = -1;
  for(unsigned int irow=0; irow<tableRows.size(); irow++) {
    if (rowName.compare(tableRows[irow].GetName()) == 0){
      index = irow;
      break;
    }
  }
  if(index==-1) {
    cout << "ERROR Table::removeRow could not find the index for the row \"" << rowName << "\"" << endl;
  }
  return removeRow(index);
}

int Table::removeRow(int rowIndex) {
  // erase the rowIndexth element
  tableRows.erase(tableRows.begin()+rowIndex);
  return tableRows.size();
}

//----------------------------------------------------------------------------
TableRow * Table::findRow(std::string row, bool addMissing, bool verbose) {

   for (unsigned int r=0; r<tableRows.size(); r++) {
      if(row.compare(tableRows[r].GetName()) == 0)
         return &tableRows[r];
   }
   if(addMissing) {
      if(tableRows.size()>0) {
         this->addRow(tableRows[0].clone(row.c_str(),true));
         return &tableRows.back();
      }
      else {
         TableRow e(row);
         this->addRow(e);
         return &tableRows.back();
      }
   }
   else {
      if(verbose) cout << "ERROR  Table::Specified row (" << row << ") not found" << endl;
      return nullptr;
   }

}//findRow()

//----------------------------------------------------------------------------
TableRow * Table::findRow(unsigned int rowIndex, bool verbose) {

   if(tableRows.size()==0) {
      if(verbose) cout << "ERROR Table::There are no rows in this table" << endl;
      return nullptr;
   }
   else if(rowIndex >= tableRows.size()) {
      if(verbose) cout << "ERROR Table::Cannot find row (" << rowIndex << ")" << endl
                       << " Please choose a value between 0 and " << tableRows.size()-1 << endl;
      return nullptr;
   }
   else {
      return &tableRows.at(rowIndex);
   }

}//findRow()

//----------------------------------------------------------------------------
// get the index in the tableRows vector for the row with the given name
int Table::getRowIndex(std::string rowName, bool verbose) const {
  int index = -1;

  // find the row index that corresponds to the first and last row names
  for(unsigned int irow=0; irow<tableRows.size(); irow++) {
    if (rowName.compare(tableRows[irow].GetName()) == 0){
      index = irow;
      break;
    }
  }
  if(index == -1 && verbose) {
    cout << "ERROR Table::getRowIndex could not find the index for the row named, \"" << rowName << "\"" << endl;
  }
  return index;
}

//----------------------------------------------------------------------------
// squash a set of rows together (delete N-1 rows and rename the last one). The rows must be contiguous.
int Table::squashRows(std::string beginRowName, std::string endRowName, std::string newName){
  int indexStart = getRowIndex(beginRowName);
  int indexEnd = getRowIndex(endRowName);
  if(indexStart==-1 || indexEnd==-1) {
    cout << "ERROR Table::squashRows could not find the index for either the beginRowName, \"" << beginRowName << "\", or endRowName, \"" << endRowName << "\"" << endl;
  }
  return squashRows(indexStart,indexEnd,newName);
}

int Table::squashRows(int firstRowIndex, int lastRowIndex, std::string newName){
  // change the name of the row being squashed into
  if(!newName.empty()) {
    tableRows[lastRowIndex].SetName(newName.c_str());
  }

  // erase all but the lastRowIndex
  tableRows.erase(tableRows.begin()+firstRowIndex,tableRows.begin()+lastRowIndex);

  return tableRows.size();
}

//----------------------------------------------------------------------------
// sum the values in a set of rows and return a new row
TableRow Table::sumRows(std::string beginRowName, std::string endRowName, std::string name) const {
  int indexStart = getRowIndex(beginRowName);
  int indexEnd = getRowIndex(endRowName);
  if(indexStart==-1 || indexEnd==-1) {
    cout << "ERROR Table::sumRows could not find the index for either the beginRowName, \"" << beginRowName << "\", or endRowName, \"" << endRowName << "\"" << endl;
  }
  return sumRows(indexStart,indexEnd,name);
}

TableRow Table::sumRows(int firstRowIndex, int lastRowIndex, std::string name) const {
  // initialize the return value with the value of the first row to sum
  // this is needed so that the init row has the same number of entries as the other rows
  TableRow ret = tableRows[firstRowIndex];
  if(!name.empty()) ret.SetName(name.c_str());

  // sum the rows from the first+1 index (first is already set on initialization) to the last index
  // need to use lastRowIndex+1 so that we actually include the last index because acummulate works as [first,last)
  return std::accumulate (tableRows.begin()+firstRowIndex+1, tableRows.begin()+lastRowIndex+1, ret, std::plus<TableRow>());
}

//----------------------------------------------------------------------------
// merge tables into a single table if they have the same name, column, and row titles
// returns the total number of tables that were merged
int Table::Merge(TCollection *list){
   if (!list) return 0;
   TIter next(list);
   Table *table;
   while ((table = (Table*)next())){
      if (table==this) continue;
      if (!table->InheritsFrom(TNamed::Class())){
         Error("Add","Attempt to add object of class: %s to a %s", table->ClassName(), ClassName());
         return -1;
      }
      
      unsigned int nrows = table->getRows().size();
      if (nrows == 0) continue;
      
      this->addTable(*table);
   }
   return tableRows.size();
}//Merge

ClassImp(Table)
