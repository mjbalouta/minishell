# Minishell
## Creating a simple shell  
**(Team project with @jmiguelmonteiro)**

This project's purpose is to gain extensive knowledge about processes and file descriptors. 

### How to use:
1) Inside the directory you want: `git clone https://github.com/mjbalouta/minishell.git`

2) Type `make` to compile the project

3) Type `./minishell` and then have fun trying out different commands!

### Main Requirements

1) Implement the following redirections:
- `<` should redirect input.
- `>` should redirect output.
- `<<` should be given a delimiter, then read the input until a line containing the
delimiter is seen. However, it doesn’t have to update the history!
- `>>` should redirect output in append mode.

2) In interactive mode:
- `ctrl-C` displays a new prompt on a new line.
- `ctrl-D` exits the shell.
- `ctrl-\` does nothing.

3) Your shell must implement the following built-in commands:
- `echo` with option -n
- `cd` with only a relative or absolute path
- `pwd` with no options
- `export` with no options
- `unset` with no options
- `env` with no options or arguments
- `exit` with no options

4) Implement pipes (| character). The output of each command in the pipeline is connected to the input of the next command via a pipe.

5) Handle environment variables ($ followed by a sequence of characters) which should expand to their values.
