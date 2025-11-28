"" ============================================================================
""                           BASIC VIM CONFIGURATION
"" ============================================================================

" Enable syntax highlighting based on file type
syntax on

" Show absolute line numbers on the left
set number

" Show relative line numbers (helpful for jumping lines, e.g., '10j')
set relativenumber

" Enable mouse support in all modes (Normal, Visual, Insert, Command)
set mouse=a

" --- Tab & Indentation Settings ---

" Set the width of a tab character to 4 spaces
set tabstop=4

" Set the indentation width to 4 spaces (used by << and >> commands)
set shiftwidth=4

" Convert tab keystrokes into spaces (standard for modern coding)
set expandtab

" Copy indentation from the previous line when starting a new line
set autoindent

" Smart auto-indentation specifically for C-like languages (handles brackets {})
set smartindent

" --- Search Settings ---

" Highlight all matches of the search pattern
set hlsearch

" Highlight the search pattern while you are typing it (Incremental Search)
set incsearch

" Disable compatibility with ancient Vi (enables modern Vim features)
set nocompatible

" --- Clipboard ---

" Sync Vim's clipboard with the system clipboard (Ctrl+C/V functionality)
set clipboard=unnamedplus


"" ============================================================================
""                  KEY MAPPINGS (SHORTCUTS) - ARCH/WINDOWS STYLE
"" ============================================================================

" --- 1. UNDO (Ctrl + z) ---

" Normal Mode: Map Ctrl+z to 'u' (standard Vim undo)
nnoremap <C-z> u

" Insert Mode: Temporarily switch to Normal mode (<C-o>), undo (u), stay in Insert
inoremap <C-z> <C-o>u


" --- 2. COPY (Ctrl + c) ---

" Visual Mode: Copy (yank) the selected text to the system clipboard
vnoremap <C-c> y

" Normal Mode: Copy (yank) the entire current line
nnoremap <C-c> yy


" --- 3. PASTE (Ctrl + v) ---

" Normal Mode: Paste text after the cursor position
nnoremap <C-v> p

" Insert Mode: Paste from the system clipboard (+) exactly where typing
inoremap <C-v> <C-r>+

" Command Line: Allow pasting into the search bar or command prompt
cnoremap <C-v> <C-r>+


" --- 4. RESTORING CONFLICTS ---

" Since Ctrl+v is now mapped to Paste, we lose 'Visual Block' mode.
" Map Ctrl+q to trigger Visual Block mode instead.
nnoremap <C-q> <C-v>


"" ============================================================================
""                            AUTOMATION & AUTOSAVE
"" ============================================================================

" Automatically save all buffers when focus is lost or you leave the buffer.
" This ensures inputs are saved before you run code, or when you Alt-Tab away.
autocmd FocusLost,BufLeave * silent! wa


"" ============================================================================
""                     COMPETITIVE PROGRAMMING LAYOUT (CPP)
"" ============================================================================

" Function to set up the CP workspace (Code, Error, Input, Output windows)
function! CPP(file)
    " Open the main C++ file
    execute "edit ".a:file
    
    " Open error.txt in a horizontal split
    split error.txt
    
    " Swap the current window with the next one
    wincmd x
    
    " Increase the height of the current window by 25 lines
    resize +25
    
    " Open output.txt in a vertical split
    vsplit output.txt
    
    " Swap window again
    wincmd x
    
    " Increase width by 35 columns
    vertical resize +35
    
    " Move cursor to the right window
    wincmd l
    
    " Open input.txt in a split
    split input.txt
    
    " Move cursor to the left window
    wincmd h
    
    " Increase height by 8 lines
    resize +8
endfunction

" Create a command ':Cpp filename' to call the function above easily
command! -nargs=1 Cpp call CPP (<f-args>)


"" ============================================================================
""                       COMPILE & RUN CONFIGURATION
"" ============================================================================

" Tell Vim to automatically read files if they are changed on the disk
" (Vital for seeing output.txt update instantly)
set autoread

" Function to Compile and Run code silently without freezing Vim
function! RunCP()
    " 1. Save the file without showing a message
    silent write

    " 2. Construct the shell command string:
    "    g++        : The compiler
    "    -std=c++23 : Use C++23 standard
    "    -DLOCAL    : Define 'LOCAL' macro for debug prints
    "    shellescape: Safely handle filenames with spaces
    "    < input.txt: Feed input file to stdin
    "    > output.txt: Redirect stdout to output file
    "    2> error.txt: Redirect stderr (debugs) to error file
    let cmd = "g++ -std=c++23 -DLOCAL " . shellescape(expand('%')) . " -o " . shellescape(expand('%:r')) . " && ./" . shellescape(expand('%:r')) . " < input.txt > output.txt 2> error.txt"

    " 3. Execute the command in the background using the system shell
    call system(cmd)

    " 4. Force Vim to check for file changes immediately
    checktime
    
    " 5. Redraw the screen to show the new numbers in output.txt instantly
    redraw!
endfunction

" Map Ctrl + b to call the RunCP function
nnoremap <C-b> :call RunCP()<CR>


"" ============================================================================
""                              PLUGINS
"" ============================================================================

" Initialize vim-plug (Plugin Manager)
call plug#begin('~/.vim/plugged')

" Syntax highlighting specifically for C++
Plug 'octol/vim-cpp-enhanced-highlight'

" Auto-completion engine (LSP client)
Plug 'neoclide/coc.nvim', {'branch': 'release'}

" File explorer tree (visible on the side)
Plug 'preservim/nerdtree'

" Fuzzy finder core (needed for fast file searching)
Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }

" Fuzzy finder Vim integration
Plug 'junegunn/fzf.vim'

" Bottom status bar (adds git branch, file type, etc.)
Plug 'vim-airline/vim-airline'

" Git integration (wrapper for git commands)
Plug 'tpope/vim-fugitive'

" Graphical debugger for Vim
Plug 'puremourning/vimspector'

" Snippet engine
Plug 'SirVer/ultisnips'

" Collection of standard snippets
Plug 'honza/vim-snippets'

" End of plugin initialization
call plug#end()


"" ============================================================================
""                          SNIPPET CONFIGURATION
"" ============================================================================

" Key to trigger snippet expansion (Tab)
let g:UltiSnipsExpandTrigger="<tab>"

" Key to jump to the next placeholder in a snippet
let g:UltiSnipsJumpForwardTrigger="<tab>"

" Key to jump to the previous placeholder
let g:UltiSnipsJumpBackwardTrigger="<s-tab>"

" Folder where your custom snippets are stored
let g:UltiSnipsSnippetDirectories=["UltiSnips"]
