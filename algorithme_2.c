/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:45 by docteurbadl       #+#    #+#             */
/*   Updated: 2025/03/31 15:27:36 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void init()
{
    // init signal ctrl \ (ignore)
    // init signal ctrl d (exit properly)
    // init signal ctrl c (new line)
    // init pwd
    // create display line. 
    // init $? ? 
}

void routine()
{
    //take input 
    //verifying << (should be abble to write several line in this case) TO DO 
    // update history
        // with << the history is update with all the line of the heredoc.
    //verifying " ' and ) TO DO 

    // parsing
        // replace $ by their value DONE
        //verifying " ' () validity DONE 
        // split into token the different part DONE
        // pass through the array to identify Logical operator ( && || ()) DONE
        //pass through the array to identify fd operator ( |  >> > <) DONE
        //create an array of array of str to contain every group number
        //place the element in the tree 

    // Signal modification in the shell(ignore all)
    //execution
        // while (tree) apply fd
        // process_tree(status);
        // fork() -> modification signal (ctrl c = ^C exit, ctrl \ = core dumped (ctrl d already ignored))
        // exec() 
        // wait(&status); -> update $?
    //reinit signals pwd... 
}

void parsing()
{
     // parsing
        // replace $ by their value ( if not existing replace by "")   DONE
            /*
            // cut the string in several part, part before $ (if not existing create "")the $ and following char all the end of the string.
            // getenv($variable) -> result;
            // join first part result and end part.
            // do it again until no $ followed by non space exist
        */
        //verifying " ' and count word  DONE 
        /*
            // we have to count the word to spli the input so we use this moment to verify different things
            // a word is delimited by space, but if a " or a ' is encountered : pass the char until it's another one or it's the null terminator. 
            // if it's the null terminator we know that it is never close. 
        */
        // split into token the different part DONE
        /*
            //'(' become one token ')' a token representing NULL can be usefull sometime. (maybe ?)
                // we have then an array like "(" "ls" "-a" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
        // pass through the array to identify Logical operator ( && || >> > < |)
            // if you can find an operator put his value in logical_operator  < > << >> = 4 | = 3 && = 2 || = 1 ( = -1 ) = -2 other 0.
            */
        
        // attribute group number to each token to create block of command. DONE
        /*                          change > >> << < to -3 
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         -1    1    1  -3       1      0     2       2   -2    0    3       3
            // check logical -> group number DONE 
            // manage redirection  DONE
            // check for ()     DONE
            // group up token   DONE
            /*
                // if number > 0 combine the number over 0 together. ( the ones with the ones ...) then place it.
                */
            // developpe wildcard TODO 
        //place the element in the tree DONE 
        /*
            //to do so we use the Shunting Yard algorithm
                // we have a list of output and a stack for operator (create a list of parsed_command), (create a stack of parsed command)
                // we have to set the priority of each sign compare to each other.(already done) precedence ; // redirection < > << >> = 4 | = 3 && = 2 || = 1
                // we have to to set the associativity of each symbole. (&& || left it mean that the first one is priorities A || B || C -> (A || B) || C
                //< > << >> it right cmd > file1 > file2 -> cmd > (file1 > file2))
                // operands are push into the list of output
                // operators are pushed onto the stack, but before, we should remove the operator which are already there if they have the same or a stronger precedence.
                // à celle du nouvel opérateur ET si l’opérateur est gauche-associatif. if left associativity ;✅ Pop only operators with strictly higher precedence.
                // the parentheses are pushed onto the stack, to the output until a left parenthesis is encountered.
                // THAT CREATE A LIST OF NODE IN REVERSE POLISH
        */
            //How to create the treeDONE 
            /*
                // create a stack : 
                // push operand into the stack 
                //  When encountering an operator:
                // Pop the required number of operands from the stack. (LINK THE TWO last operrand to the new OPPERATOR POP THE TWO OPERRAND AND SEND the new OPERATOR in the stack)
                // continue until the end of the stack.
                */
            // return the tree DONE 
}

/*
1. Basic Functionality
Syntax: command << DELIMITER

Reads input until DELIMITER appears on a new line.

Input is passed as stdin to the command.

2. Expansion Rules
Unquoted delimiter (<< EOF) → Expands variables ($VAR), commands ($(cmd)),
Quoted delimiter (<< 'EOF') → No expansion, input is treated as raw text.
WILDCARD ARE IGNORED COMAND ALSO. it just text and variable

bash <<EOF &
echo "Hello"
sleep 10
echo "Goodbye"
EOF

4. Signal Handling
CTRL+C (SIGINT) → Interrupt heredoc, discard input, return to prompt.

Use a custom signal handler: exit(1);

CTRL+D (EOF) → End input, warn if DELIMITER is missing.

Check getline() return value.

CTRL+\ (SIGQUIT) → Ignore to match Bash behavior.

signal(SIGQUIT, SIG_IGN);

5. Edge Cases
Nested heredocs.

Combining heredocs with redirections (<< EOF > file).

Handling special characters inside heredocs correctly.

*/



// * problem : to solve the problem different solution are possible.
// writing wildcards, in the beginning of the wildcards list, to atribute has_wildcard.
// to search in the first input where are the wildcards to mark them 
// to developp wildcard later, after the group up. Bash does it here 

//during the parsing, i should make fail for a specifica number ? 

// even if a comand fail it perform redirection ? 
// The following shell builtin commands are inherited from the Bourne Shell. These commands are implemented as specified by the POSIX standard.

//: (a colon)
//: [arguments]
//Do nothing beyond expanding arguments and performing redirections. 
//The return status is zero.