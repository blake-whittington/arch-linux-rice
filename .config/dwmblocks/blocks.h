//Modify this file to change what commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/ /*Command*/	 	                            /*Update Interval*/	/*Update Signal*/
    // {" 🐧 ", "~/.local/bin/kernel",	 360,		          2},
	{"", "~/.local/bin/clock",	     60,	              1},

	{" Uptime: ", "~/.local/bin/upt",		 60,		          2},

	{" Pacman: ", "~/.local/bin/pacupdate",  360,		          9},
	
	{" Memory: ", "~/.local/bin/memory",	 6,		              1},

	{"", "~/.local/bin/nettraf",     5,		              10},

	{"", "~/.local/bin/battery",	     5,	              3},
};

//sets delimeter between status commands. NULL character ('\0') means no delimeter.
static char delim = '|';
