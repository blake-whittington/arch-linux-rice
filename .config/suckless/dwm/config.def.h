/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 0;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const unsigned int gappih    = 5;       /* horiz inner gap between windows */
static const unsigned int gappiv    = 5;       /* vert inner gap between windows */
static const unsigned int gappoh    = 5;       /* horiz outer gap between windows and screen edge */
static const unsigned int gappov    = 5;       /* vert outer gap between windows and screen edge */
static       int smartgaps          = 1;        /* 1 means no outer gap when there is only one window */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
// static const char *fonts[]          = { "Hack Nerd Font:size=9" };
static const char *fonts[]     = {
                                  "Fira Code Medium:size=8:antialias=true:autohint=true",
                                //   "Hack:size=8:antialias=true:autohint=true",
                                //   "JoyPixels:size=10:antialias=true:autohint=true"
								"Symbols Nerd Font:size=12:antialias=true:autohint=true"
};


static const char dmenufont[]       = "Fira Code Medium:size=10:antialias=true:autohint=true";
static const char col_gray1[]       = "#2E3440";
static const char col_gray2[]       = "#E5E9F0";
static const char col_gray3[]       = "#E5E9F0";
static const char col_gray4[]       = "#E5E9F0";
static const char col_cyan[]        = "#81A1C1";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray1, col_gray2 },
	[SchemeSel]  = { col_gray4, col_cyan,  col_cyan  },
};

typedef struct {
	const char *name;
	const void *cmd;
} Sp;
const char *spcmd1[] = {"st", "-n", "spterm", "-g", "120x34", NULL };
const char *spcmd2[] = {"st", "-n", "spfm", "-g", "144x41", "-e", "ranger", NULL };
const char *spcmd3[] = {"st", "-n", "sp2", "-g", "120x34", NULL };
const char *spcmd4[] = {"bitwarden", NULL };
const char *spcmd5[] = {"st", "-n", "vol", "-g", "144x41", "-e", "pulsemixer", NULL };
const char *spcmd6[] = {"st", "-n", "mus", "-g", "144x41", "-e", "ncmpcpp", NULL };
const char *spcmd7[] = {"st", "-n", "mail", "-g", "144x41", "-e", "neomutt", NULL };
static Sp scratchpads[] = {
	/* name          cmd  */
	{"spterm",      spcmd1},
	{"spranger",    spcmd2},
	{"sp2",         spcmd3},
	{"bitwarden",   spcmd4},
	{"vol",         spcmd5},
	{"mus",         spcmd6},
	{"mail",        spcmd7},
};

/* tagging */
// static const char *tags[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9" };
static const char *tags[] = { "", "", "", "", "", "", "", "", "" };
static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance    title       tags mask     isfloating   monitor */
	{ "Gimp",	  NULL,			NULL,		0,			1,			 -1 },
	{ "Firefox",      NULL,			NULL,		1 << 8,			0,			 -1 },
	{ "Audacity",	  NULL,			NULL,		0,			1,			 -1 },
	{ "cs",	          NULL,			NULL,		0,			1,			 -1 },
	{ NULL,		  "spterm",		NULL,		SPTAG(0),		1,			 -1 },
	{ NULL,		  "spfm",		NULL,		SPTAG(1),		1,			 -1 },
	{ NULL,		  "sp2",        	NULL,		SPTAG(2),		1,			 -1 },
	{ NULL,		  "bitwarden",        	NULL,		SPTAG(3),		1,			 -1 },
	{ NULL,		  "vol",        	NULL,		SPTAG(4),		1,			 -1 },
	{ NULL,		  "mus",        	NULL,		SPTAG(5),		1,			 -1 },
	{ NULL,		  "mail",        	NULL,		SPTAG(6),		1,			 -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

#define FORCE_VSPLIT 1  /* nrowgrid layout: force two clients to always split vertically */
#include "vanitygaps.c"

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[@]",      spiral },
	{ "[\\]",     dwindle },
	{ "H[]",      deck },
	{ "TTT",      bstack },
	{ "===",      bstackhoriz },
	{ "HHH",      grid },
	{ "###",      nrowgrid },
	{ "---",      horizgrid },
	{ ":::",      gaplessgrid },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	// { "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray3, "-sb", col_cyan, "-sf", col_gray4, NULL };
static const char *termcmd[]  = { "alacritty", NULL };

#include "movestack.c"

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY|ShiftMask, 			XK_b,      spawn,          SHCMD("firefox")},
	{ MODKEY|ShiftMask, 			XK_f,      spawn,          SHCMD("thunar")},
	{ MODKEY|ShiftMask, 			XK_a,      spawn,          SHCMD("alacritty")},
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_v,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
	// { MODKEY|Mod4Mask,              XK_u,      incrgaps,       {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_u,      incrgaps,       {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_i,      incrigaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_i,      incrigaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_o,      incrogaps,      {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_o,      incrogaps,      {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_6,      incrihgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_6,      incrihgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_7,      incrivgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_7,      incrivgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_8,      incrohgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_8,      incrohgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_9,      incrovgaps,     {.i = +1 } },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_9,      incrovgaps,     {.i = -1 } },
	// { MODKEY|Mod4Mask,              XK_0,      togglegaps,     {0} },
	// { MODKEY|Mod4Mask|ShiftMask,    XK_0,      defaultgaps,    {0} },


	/*layout bindings */

	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_F1,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_F2,      setlayout,      {.v = &layouts[3]} },
	{ MODKEY,                       XK_F3,      setlayout,      {.v = &layouts[4]} },
	{ MODKEY,                       XK_F4,      setlayout,      {.v = &layouts[5]} },
	{ MODKEY,                       XK_F5,      setlayout,      {.v = &layouts[6]} },
	{ MODKEY,                       XK_F6,      setlayout,      {.v = &layouts[7]} },
	{ MODKEY,                       XK_F7,      setlayout,      {.v = &layouts[8]} },
	{ MODKEY,                       XK_F8,      setlayout,      {.v = &layouts[9]} },
	{ MODKEY,                       XK_F9,      setlayout,      {.v = &layouts[10]} },
	{ MODKEY,                       XK_F10,     setlayout,      {.v = &layouts[11]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[12]} },
	{ MODKEY|ControlMask,		XK_comma,  cyclelayout,    {.i = -1 } },
	{ MODKEY|ControlMask,           XK_period, cyclelayout,    {.i = +1 } },
	{ MODKEY,                       XK_space,  setlayout,      {0} },

	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,		XK_j,      movestack,      {.i = +1} },
	{ MODKEY|ShiftMask,		XK_k,      movestack,      {.i = -1} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_Left,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_Right, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_Left,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_Right, tagmon,         {.i = +1 } },
	
	{ MODKEY|ShiftMask,             XK_h, tagmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_h, focusmon,         {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_l, tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_l,  focusmon,         {.i = -1 } },
	{ MODKEY,              XK_o,          focusmon,         {.i = -1 } },
	
	/*Scratchpads*/
	{ MODKEY,            			XK_y,  	   togglescratch,  {.ui = 0 } },
	{ MODKEY,            			XK_u,	   togglescratch,  {.ui = 1 } },
	{ MODKEY,            			XK_n,	   togglescratch,  {.ui = 2 } },
	{ MODKEY|ShiftMask,      		XK_n,	   togglescratch,  {.ui = 3 } },
	// { MODKEY,            			XK_o,	   togglescratch,  {.ui = 4 } },
	{ MODKEY,            			XK_i,	   togglescratch,  {.ui = 5 } },
	{ MODKEY,            			XK_m,	   togglescratch,  {.ui = 6 } },

	/*tagkeys*/
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)

	{ MODKEY|ShiftMask,             XK_x,      quit,           {0} },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button1,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
};

