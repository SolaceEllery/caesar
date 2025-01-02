#include <string>
#include <cstring>
#include <iostream>

#include "GlobalFuncs.hpp"

#include "Common.hpp"
#include "Csar.hpp"

using namespace std;

static void ShowHelpMessage()
{
	GlobalFuncs_ShowMessage("caesar (v0.5.0)");
	GlobalFuncs_ShowMessage("Originally by kr3nshaw, continued by Solace D. Ellery\n");
	GlobalFuncs_ShowMessage("[-- USAGE --]");
	GlobalFuncs_ShowMessage("caesar [options] <inputs>\n");
	GlobalFuncs_ShowMessage("[-- OPTIONS --]\n");
	GlobalFuncs_ShowMessage("-- Rip Settings --\n");
	GlobalFuncs_ShowMessage("-p");
	GlobalFuncs_ShowMessage("    If specified, this will force-retrieve pan values\n    of all stereo samples.\n");
	GlobalFuncs_ShowMessage("-- Debug Settings --\n");
	GlobalFuncs_ShowMessage("-w");
	GlobalFuncs_ShowMessage("    This will show every warning the program finds.\n");
	GlobalFuncs_ShowMessage("-d");
	GlobalFuncs_ShowMessage("    This will show everything that gets processed, even\nwarnings (Which overrides the \"-w\" argument.");
}

int main(int argc, char* argv[])
{
	bool dontIgnorePanValues = false;

	if (argc <= 0 || argv[1] == "" || argv[argc] == "")
	{
		ShowHelpMessage();
		return 1;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-p"))
			{
				dontIgnorePanValues = true;
			}
			else if (!strcmp(argv[i], "-w"))
			{
				Common::ShowWarnings = true;
			}
			else if (!strcmp(argv[i], "-d"))
			{
				Common::ShowWarnings = true;
				Common::ShowAllProcessDetails = true;
			}
		}

		// Go ahead and extract the BCSAR specified as the last argument on the list
		Csar csar(argv[argc], dontIgnorePanValues);

		// If an error occurs, force-quit
		if (!csar.Extract())
		{
			return 1;
		}
	}

	return 0;
}
