// Kelby Hubbard
// Chaluunbat Purev
// CS202 Group Project
// The Alaskan Phonebook

#ifndef FLTK_HPP_
#define FLTK_HPP_
//#define WIN32

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Button.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Box.H>
#include <Fl/Fl_Text_Display.H>
#include <FL/Fl_Table_Row.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_Output.H>

#include <iostream>
using std::cout;
using std::endl;
using std::string;
#include <vector>
using std::vector;
#include <tuple>
using std::tuple;
using std::make_tuple;
using std::get;
#include <string>

#include "phonebook.hpp"

// Derive a class from Fl_Table_Row
class MyTable : public Fl_Table_Row {
protected:
	//// Callback whenever someone clicks on different parts of the table
	void cell_event();

	//Static callback whenver someone clicks on different parts of table
		//For table
	static void event_callback(Fl_Widget*, void* v) { ((MyTable*)v)->cell_event(); }
		//For input widget
	static void input_cb(Fl_Widget*, void* v) { ((MyTable*)v)->set_value_hide(); }
public:
	Fl_Input* input;                                      // single instance of Fl_Int_Input widget
	int row_edit, col_edit;                               // row/col being modified
	TableContext context_edit;                            // context being edited (row head/col head/cell)
	// Draw the row/col headings
	//    Make this a dark thin upbox with the text inside.
	void DrawHeader(const char* s, int X, int Y, int W, int H, const Fl_Color c);

	// Handle drawing table's cells
	//     Fl_Table calls this function to draw each visible cell in the table.
	//     It's up to us to use FLTK's drawing functions to draw the cells the way we want.
	void draw_cell(TableContext context, int ROW = 0, int COL = 0, int X = 0, int Y = 0, int W = 0, int H = 0);

	// Start editing a new cell: move the Fl_Int_Input widget to specified row/column
	//    Preload the widget with the cell's current value,
	//    and make the widget 'appear' at the cell's location.
	//    If R==-1, indicates column C is being edited
	//    If C==-1, indicates row R is being edited
	void start_editing(TableContext context, int R, int C);

	// Tell the input widget it's done editing, and to 'hide'
	void done_editing();

	// Apply value from input widget and hide (basically done editing)
	void set_value_hide();

	// Constructor
	//     Make our data array, and initialize the table options.
	MyTable(int X, int Y, int W, int H, int s, const char* L = 0) : Fl_Table_Row(X, Y, W, H, L) {
		when(FL_WHEN_NOT_CHANGED | when());
		// Create input widget that we'll use whenever user clicks on a cell
		input = new Fl_Input(W / 2, H / 2, 0, 0);
		input->hide();
		input->callback(input_cb, (void*)this);
		input->when(FL_WHEN_ENTER_KEY_ALWAYS);              // callback triggered when user hits Enter
		input->maximum_size(10);
		input->color(FL_GRAY);
		// Rows
		rows(s);             // how many rows
		row_header(1);              // enable row headers (along left)
		row_height_all(20);         // default height of rows
		row_resize(0);              // disable row resizing
		// Cols
		cols(3);             // how many columns
		col_header(1);              // enable column headers (along top)
		col_width_all(169);          // default width of columns
		col_resize(0);              // enable column resizing
		end();                      // end the Fl_Table group
		context_edit = CONTEXT_NONE;
		row_edit = col_edit = 0;

	}
	void openFileFLTK(string fileName);
	void addPb(string& first, string& last, double& phone);
	void saveFile(const string& fileName);
	void setPb(const Phonebook& v_){ _pb = v_; }
	void deletePb(const int& num) { _pb.deleteRecord(num); }
	double getRecord(const int& num) const { return get<2>(_pb.getPhone(num)); }
	void printAll() const { _pb.printRecords(); }
	void modifyState() { modify = (modify) ? false : true; }
	void searchState() { searching = (searching) ? false : true; }
	bool search() const { return searching; }
	void clearSearch() { _pb.clearSearch(); }
	size_t search(std::string str) {  return _pb.setSearch(str, searching); }
	size_t phonebook() const { return _pb.sizeP(); }
	~MyTable() { }
private:
	Phonebook _pb;
	bool modify = false;
	bool searching = false;
};

//Callbacks

//Menu items
void save(Fl_Widget* w, void* data);
void quitProgram(Fl_Widget* w, void* data);
void quit(Fl_Widget* w, void* data);
void open(Fl_Widget* w, void* data);
void help(Fl_Widget* w, void* data);
void submitFile(Fl_Widget* w, void* data);

//Search items
void searchCallback(Fl_Widget* w, void* data);
void clearCallback(Fl_Widget* w, void* data);

//Modify items
void modifyCallback(Fl_Widget* w, void* data);

//Add items
void addCallback(Fl_Widget* w, void* data);
void submitCallback(Fl_Widget* w, void* data);

//Delete items
void deleteCallback(Fl_Widget* w, void* data);


#endif
