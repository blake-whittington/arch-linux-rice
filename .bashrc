#
# ~/.bashrc
#
export PATH=$HOME/.local/bin:$PATH
export PATH=/opt/dataspell-2022.3.1/bin:$PATH
PATH="$HOME/.local/bin${PATH:+:${PATH}}"
# If not running interactively, don't do anything
[[ $- != *i* ]] && return

colors() {
	local fgc bgc vals seq0

	printf "Color escapes are %s\n" '\e[${value};...;${value}m'
	printf "Values 30..37 are \e[33mforeground colors\e[m\n"
	printf "Values 40..47 are \e[43mbackground colors\e[m\n"
	printf "Value  1 gives a  \e[1mbold-faced look\e[m\n\n"

	# foreground colors
	for fgc in {30..37}; do
		# background colors
		for bgc in {40..47}; do
			fgc=${fgc#37} # white
			bgc=${bgc#40} # black

			vals="${fgc:+$fgc;}${bgc}"
			vals=${vals%%;}

			seq0="${vals:+\e[${vals}m}"
			printf "  %-9s" "${seq0:-(default)}"
			printf " ${seq0}TEXT\e[m"
			printf " \e[${vals:+${vals+$vals;}}1mBOLD\e[m"
		done
		echo; echo
	done
}

use_color=true

alias p="sudo pacman"
alias grep='grep --colour=auto'
alias egrep='egrep --colour=auto'
alias fgrep='fgrep --colour=auto'
alias surf='surf google.com'
alias ncspot='flatpak run io.github.hrkfdn.ncspot'
# Adding color
alias ls='ls -hN --color=auto --group-directories-first'

PS1='\W\[\033[0;37m\]\$\[\033[00m\] '
source ~/.local/share/blesh/ble.sh
