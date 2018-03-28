//this file is part of notepad++
//Copyright (C)2003 Don HO <donho@altern.org>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "definedConstants.h"


//Forward declaration of some defined functions
char* setup(HWND&, int&);
void generalSurround(HWND, const char* startCond, int, const char* endCond, int, char* c, int);
void addText(HWND, int, const char*);



//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );

	ShortcutKey* surrIfKey = new ShortcutKey;
	surrIfKey->_isCtrl = false;
	surrIfKey->_isAlt = true;
	surrIfKey->_isShift = false;
	surrIfKey->_key = 0x49;

	ShortcutKey* surrElseIfKey = new ShortcutKey;
	surrElseIfKey->_isCtrl = false;
	surrElseIfKey->_isAlt = true;
	surrElseIfKey->_isShift = false;
	surrElseIfKey->_key = 0x4C;

	ShortcutKey* surrElseKey = new ShortcutKey;
	surrElseKey->_isCtrl = false;
	surrElseKey->_isAlt = true;
	surrElseKey->_isShift = false;
	surrElseKey->_key = 0x45;

	ShortcutKey* surrWhileKey = new ShortcutKey;
	surrWhileKey->_isCtrl = false;
	surrWhileKey->_isAlt = true;
	surrWhileKey->_isShift = false;
	surrWhileKey->_key = 0x57;

	ShortcutKey* surrForKey = new ShortcutKey;
	surrForKey->_isCtrl = false;
	surrForKey->_isAlt = true;
	surrForKey->_isShift = false;
	surrForKey->_key = 0x46;

	ShortcutKey* surrDoWhileKey = new ShortcutKey;
	surrDoWhileKey->_isCtrl = false;
	surrDoWhileKey->_isAlt = true;
	surrDoWhileKey->_isShift = false;
	surrDoWhileKey->_key = 0x4F;

	ShortcutKey* surrSwitchKey = new ShortcutKey;
	surrSwitchKey->_isCtrl = false;
	surrSwitchKey->_isAlt = true;
	surrSwitchKey->_isShift = false;
	surrSwitchKey->_key = 0x53;

    setCommand(0, TEXT("If"), surroundIf, surrIfKey, false);
	setCommand(1, TEXT("Else if"), surroundElseIf, surrElseIfKey, false);
	setCommand(2, TEXT("Else"), surroundElse, surrElseKey, false);
	setCommand(3, TEXT("While"), surroundWhile , surrWhileKey, false);
	setCommand(4, TEXT("For"), surroundFor, surrForKey, false);
	setCommand(5, TEXT("Do While"), surroundDoWhile, surrDoWhileKey, false);
	setCommand(6, TEXT("Switch"), surroundSwitch, surrSwitchKey, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
	delete funcItem[0]._pShKey;
	delete funcItem[1]._pShKey;
	delete funcItem[2]._pShKey;
	delete funcItem[3]._pShKey;
	delete funcItem[4]._pShKey;
	delete funcItem[5]._pShKey;
	delete funcItem[6]._pShKey;

}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//

//Following functions all defined by Anthony Clemente
//Program is still being worked on as of 3/28/18
//Likely refactoring and improvement can still occur
void surroundIf() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, IF_STATEMENT, IF_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete [] selectedText;
}


void surroundElseIf() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, ELSE_IF_STATEMENT, ELSE_IF_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete[] selectedText;
}


void surroundElse() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, ELSE_STATEMENT, ELSE_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete[] selectedText;
}


void surroundWhile() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, WHILE_STATEMENT, WHILE_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete[] selectedText;
}


void surroundFor() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, FOR_STATEMENT, FOR_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete[] selectedText;
}


void surroundDoWhile() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, DO_WHILE_STATEMENT, DO_WHILE_STATEMENT_LEN, DO_WHILE_END, DO_WHILE_END_LEN, selectedText, startPos);
	delete[] selectedText;
}


void surroundSwitch() {

	HWND curScintilla;
	int startPos;
	char* selectedText = 0;

	selectedText = setup(curScintilla, startPos);

	generalSurround(curScintilla, SWITCH_STATEMENT, SWITCH_STATEMENT_LEN, CLOSE_BRACE_CHAR, 1, selectedText, startPos);
	delete[] selectedText;
}


char* setup(HWND& scintilla, int& startPos) {
	// Get the current scintilla
	int which = -1;
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
	if (which == -1)
		return 0;
	scintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

	//Get length of selected text
	//Warning is generated about these ints not being LRESULT
	int selectedTextLength = 0;
	selectedTextLength = ::SendMessage(scintilla, SCI_GETSELTEXT, 0, 0); //Includes null terminator already in length calc

																			// Get text
	char* selectedText = new char[selectedTextLength]; // = new char[textLength + 1];
	::SendMessage(scintilla, SCI_GETSELTEXT, 0, (LPARAM)selectedText);


	//get proper starting position
	startPos = ::SendMessage(scintilla, SCI_GETSELECTIONSTART, 0, 0);

	//delete text
	//TODO: Check if no text is selected and if so dont delete.
	::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_EDIT_DELETE);

	return selectedText;
}

void generalSurround(HWND curScintilla, const char* startCond, int startCondLen, const char* endCond, int endCondLen, char* c, int startPos) {

	int currentLine = 0;
	currentLine = ::SendMessage(curScintilla, SCI_LINEFROMPOSITION, startPos, 0);

	//returns 4 for each "tab"
	int lineIndent = 0;
	lineIndent = ::SendMessage(curScintilla, SCI_GETLINEINDENTATION, currentLine, 0);

	::SendMessage(curScintilla, SCI_GOTOPOS, startPos, 0);

	//If the lineIndent is 0 it could mean the user simply copied
	//all the way to the left of the window. In this case it must still be checked
	//whether or not there is any indentation and if so determine the level.

	//Once determined, add the tabs needed before continuing
	if (lineIndent == 0) {
		while (*c == '\t') {
			c++;
			lineIndent += 4;
		}
		for (int i = 0; i < lineIndent / 4; i++) {
			addText(curScintilla, 1, TAB_CHAR);
		}
	}

	addText(curScintilla, startCondLen, startCond);

	for (int i = 0; i < lineIndent / 4; i++) {
		addText(curScintilla, 1, TAB_CHAR);
	}


	//Print the selected text out line by line adding tabs needed after each line
	int pos = 0;
	while (c[pos] != '\0') {
		pos++;
		if (c[pos] == '\n') {
			addText(curScintilla, pos + 1, c);
			addText(curScintilla, 1, TAB_CHAR);
			c += (pos + 1);
			pos = 0;
		}
		else if (c[pos] == '\0') {
			addText(curScintilla, pos, c);
		}
	}

	addText(curScintilla, 1, NEW_LINE_CHAR);

	for (int i = 0; i < lineIndent / 4; i++) {
		addText(curScintilla, 1, TAB_CHAR);
	}

	addText(curScintilla, endCondLen, endCond);
}

//Helper function to avoid using SendMessage directly each time.
void addText(HWND curScintilla, int length, const char* text) {

	::SendMessage(curScintilla, SCI_ADDTEXT, length, (LPARAM)text);

}