set expandtab
set tabstop=2
set softtabstop=0 noexpandtab
set shiftwidth=2
set number
set autoindent
set cursorline



set ruler


call plug#begin()

Plug 'vimwiki/vimwiki'
Plug 'sheerun/vim-polyglot'
Plug 'junegunn/fzf.vim'
Plug 'mhinz/vim-startify'
Plug 'preservim/nerdtree'
Plug 'arcticicestudio/nord-vim'

call plug#end()

colorscheme nord

set nocompatible
filetype plugin on
syntax on


" Set utf8 as standard encoding and en_US as the standard language
set encoding=utf8

"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" => Spell checking
"""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" Pressing ,ss will toggle and untoggle spell checking
map <leader>ss :setlocal spell!<cr>

" Shortcuts using <leader>
map <leader>sn ]s
map <leader>sp [s
map <leader>sa zg
map <leader>s? z=
