// Kelby Hubbard
// Chaluunbat Purev
// CS202 Group Project
// The Alaskan Phonebook

#include "fltk.hpp"
#include "phonebook.hpp"

// DOESNT REDRAW/REFRESH  YET
void redraw(Fl_Widget* w, void* data)
{
	MyTable &table = *(MyTable*)data;
	table.draw();
}


//Save function for menu dropdown bar
void save(Fl_Widget* w, void* data)
{
	cout << "Save" << endl;
}

//Open function for menu dropdown bar
void open(Fl_Widget* w, void* data)
{
	cout << "Open" << endl;
}

//Help function for menu dropdown bar
void help(Fl_Widget* w, void* data)
{
	cout << "Help" << endl;
}

//Exits program
void quitProgram(Fl_Widget* w, void* data)
{
	exit(0);
}

//Search Record Button Callback
void searchCallback(Fl_Widget* w, void* data)
{
	cout << "Search Record\n";
}

//Modify Record Button Callback
void modifyCallback(Fl_Widget* w, void* data)
{
	cout << "Modify Record\n";
}

//Add Record Button Callback
void addCallback(Fl_Widget* w, void* data)
{
	cout << "Add Record\n";
	vector<tuple<string, string, double>>& vec
		=	*(vector<tuple<string, string, double>>*) data;
	vec.push_back(make_tuple
		("addRecordFirst", "addRecordLast", 123456789));

		for (auto p : vec)
		{
			cout << get<1>(p) << ", " << get<0>(p) << setw(40)
					 << fixed << std::setprecision(0) << get<2>(p) << endl;
		}
}

//Delete Record Button Callback
void deleteCallback(Fl_Widget* w, void* data)
{
	//Get the table
	auto t = (MyTable*)data;

	//Delete a record/row
	t->deletePb(t->callback_row());

	//Decrease the tables row by one
	t->rows((t->rows() - 1));

	//Testing prints to console
	t->printAll();
	cout << "Delete Record\n";
}

//Quit function for menu dropdown bar
void quit(Fl_Widget* w, void* data)
{
	Fl_Window* window = new Fl_Window(340, 150, "Quit");
	Fl_Box* box = new Fl_Box(20, 40, 300, 35, "Are you sure you want to quit?");
	Fl_Button* yesButton = new Fl_Button(120, 100, 100, 25, "Yes I\'m sure.");
	yesButton->callback(quitProgram);

	box->show();
	window->show();
	// exit(0);
}

void MyTable::DrawHeader(const char* s, int X, int Y, int W, int H) {
	fl_push_clip(X, Y, W, H);
	fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, row_header_color());
	fl_color(FL_BLACK);
	fl_draw(s, X, Y, W, H, FL_ALIGN_CENTER);
	fl_pop_clip();
}

void MyTable::draw_cell(TableContext context, int ROW, int COL, int X , int Y , int W , int H) {
	string str;
	switch (context) {
	case CONTEXT_STARTPAGE:                   // before page is drawn..
		fl_font(FL_HELVETICA, 16);              // set the font for our drawing operations
		return;
	case CONTEXT_COL_HEADER:                  // Draw column headers
		switch (COL) {
		case 0: str = "First name"; break;
		case 1: str = "Last name"; break;
		case 2: str = "Phone Number"; break;
		default: str = "Unknown column";
		}
		DrawHeader(str.c_str(), X, Y, W, H);
		return;
	case CONTEXT_ROW_HEADER:                  // Draw row headers
		str = std::to_string(ROW + 1);
		DrawHeader(str.c_str(), X, Y, W, H);
		return;
	case CONTEXT_CELL: {                      // Draw data in cells

		auto tp = _pb.getTuple(ROW);
		switch (COL) {
		case 0: str = get<0>(tp); break;
		case 1: str = get<1>(tp); break;
		case 2: str = std::to_string(get<2>(tp)); str.resize(10); break;
		default: str = "Unknown cell";
		}
		if (row_selected(ROW)) {
			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, FL_BLUE);
			fl_color(FL_WHITE);
			fl_draw(str.c_str(), X, Y, W, H, FL_ALIGN_CENTER);

		}
		else {
			// Handle coloring of cells
			fl_draw_box(FL_THIN_UP_BOX, X, Y, W, H, FL_WHITE);
			fl_color(FL_BLACK);
			fl_draw(str.c_str(), X, Y, W, H, FL_ALIGN_CENTER);
		}
		return;
	}
	default:
		return;
	}
}
