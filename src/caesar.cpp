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
	GlobalFuncs_ShowMessage("[[[-- USAGE --]]]\n");
	GlobalFuncs_ShowMessage("caesar [options] <inputs>\n");
	GlobalFuncs_ShowMessage("[[[-- OPTIONS --]]]\n");
	GlobalFuncs_ShowMessage("[-- Rip Settings --]\n");
	GlobalFuncs_ShowMessage("-i");
	GlobalFuncs_ShowMessage("    Input file, can be used instead of putting the file at the\n    end of the argument list.\n");
	GlobalFuncs_ShowMessage("-o");
	GlobalFuncs_ShowMessage("    Output folder, which can be used instead of extracting the BCSAR\n    in its root folder.\n");
	GlobalFuncs_ShowMessage("-p");
	GlobalFuncs_ShowMessage("    If specified, this will force-retrieve pan values\n    of all stereo samples.\n");
	GlobalFuncs_ShowMessage("[-- Debug Settings --]\n");
	GlobalFuncs_ShowMessage("-w");
	GlobalFuncs_ShowMessage("    This will show every warning the program finds.\n");
	GlobalFuncs_ShowMessage("-d");
	GlobalFuncs_ShowMessage("    This will show everything that gets processed, even\n    warnings (Which overrides the \"-w\" argument.");
}

int main(int argc, char* argv[])
{
	bool dontIgnorePanValues = false;

	bool inPathSpecified = false;
	bool outFolderSpecified = false;

	std::string inPath = "";
	std::string outFolder = "";

	if ((argc <= 1) || (argv[argc] == ""))
	{
		ShowHelpMessage();
		return 1;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			// Don't ignore pan values
			if (argv[i] == "-p")
			{
				dontIgnorePanValues = true;
			}

            // Show warnings
			if (argv[i] == "-w")
			{
				Common::ShowWarnings = true;
			}

			// Show all messages
			if (argv[i] == "-d")
			{
				Common::ShowWarnings = true;
				Common::ShowAllProcessDetails = true;
			}

			// In file (Easier terminal-like file options)
			if (argv[i] == "-i")
			{
				inPath = argv[i + 1];
				inPathSpecified = true;
			}

			// Out folder (Easier terminal-like folder options)
			if (argv[i] == "-o")
			{
				outFolder = argv[i + 1];
				outFolderSpecified = true;
			}
		}

		// Go ahead and extract the BCSAR specified as the last argument on the list
		if (inPathSpecified)
		{
			Csar csar(inPath.c_str(), dontIgnorePanValues, outFolderSpecified, outFolder);

			// If an error occurs, force-quit
			if (!csar.Extract())
			{
				return 1;
			}
		}
		else
		{
			Csar csar(argv[argc], dontIgnorePanValues, outFolderSpecified, outFolder);

			// If an error occurs, force-quit
			if (!csar.Extract())
			{
				return 1;
			}
		}
	}

	return 0;
}
