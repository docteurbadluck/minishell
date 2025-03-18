/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:45 by docteurbadl       #+#    #+#             */
/*   Updated: 2025/03/18 17:03:49 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


void init()
{
    // init signal ctrl \ (ignore)
    // init signal ctrl d (exit properly)
    // init signal ctrl c (new line)
    // init pwd
    // create display line. 
}

void routine()
{
    //take input 
    //verifying << (should be abble to write several line in this case)
    // update history 

    // parsing

        // replace $ by their value

        // replace * by their value (if is in the current repository, otherwise ignore)

        //verifying <<

        //verifying " ' () validity

        // split into token the different part 
        // pass through the array to identify Logical operator ( && || ())
        //pass through the array to identify fd operator ( |  >> > <)
        //create an array of array of str to contain every group number
        //place the element in the tree 

    // Siganl modification in the shell(ignore all)
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
        // replace $ by their value

        // replace * by their value (if is in the current repository, otherwise ignore)

        //verifying << (parrently a lot of law are different)

        //verifying " ' () validity

        // split into token the different part
            // You can't just split it with space cause cat "test.txt"|wc work perfectly on bash.
            //("" become one token '' become one token '(' become one token ')' also) a token representing NULL can be usefull sometime.
                // we have then an array like "(" "ls" "-a" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
        // pass through the array to identify Logical operator ( && || ())
            // attribute group number to each token to create block of command. 
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         0    1    1   0       2      0     3       3     0    0    4       4
        //pass through the array to identify fd operator ( |  >> > <)
            // identify file name
        //create an array of array of str to contain every group number
        
        //place the element in the tree

            //to do so we use the Shunting Yard algorithm
                // we have a list of output and a stack for operator
                // we have to set the priority of each sign compqre to each other. precedence ; // redirection < > << >> = 4 | = 3 && = 2 || = 1 
                // we have to to set the associativity of each symbole. (&& || left it mean that the first one is priorities A || B || C -> (A || B) || C 
                //< > << >> it right cmd > file1 > file2 -> cmd > (file1 > file2))
                // operands are push into the list of output
                // operators are pushed onto the stack, but before, we should remove the operator which are already there if they have the sameor a stronger precedence.
                // à celle du nouvel opérateur ET si l’opérateur est gauche-associatif. if left associativity ;✅ Pop only operators with strictly higher precedence.
                // the parentheses are pushed onto the stack, to the output until a left parenthesis is encountered.
                // THAT CREATE A LIST OF NODE IN REVERSE POLISH 

            //How to create the tree
                // create a stack : 
                // push operand into the stack 
                //  When encountering an operator:
                // Pop the required number of operands from the stack. (LINK THE TWO last operrand to the new OPPERATOR AND SEND the new OPERATOR in the stack 
                // Create a new tree node with the operator as the root.
                // Set the popped operands as children.
                // push the tree onto the stack again
        
}