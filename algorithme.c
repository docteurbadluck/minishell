/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:45 by docteurbadl       #+#    #+#             */
/*   Updated: 2025/03/20 13:30:11 by tdeliot          ###   ########.fr       */
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
        // replace $ by their value ( if not existing replace by "")
            // cut the string in several part, part before $ (if not existing create "")the $ and following char all the end of the string.
            // getenv($variable) -> result;
            // join first part result and end part. 
            // do it again until no $ followed by non space exist

        // replace * by their value (if is in the current repository, otherwise ignore)
            // if (complete path == pwd || relative path has not '/' )
            //create an array of filename with matching the condition. ( *.c, *, *.*, a*o*t)
            //path the char, if it's a star pass if it's different char try to find them in another files.
            // if you can't quit otherwise continue until while star, new text or end of char 
            // in the list of potential word, look if you find the matching part at the begining 0 word comp : 1 (depend of number of open text) end -1 (a.out) a*o*t -> correct,  a*t*o
        //verifying << (parrently a lot of law are different)

        //verifying " '  validity
            // we have to count the word to spli the input so we use this moment to verify different things
            // a word is delimited by space, but if a " or a ' is encountered : pass the char until it's another one or it's the null terminator. 
            // if it's the null terminator we know that it is never close. 
        // split into token the different part
        // you have to create a function split which apply the result in t_parsed_command-> text; Add -> text add -> group Id Add-> associativity 0 = right 1 = left remove- > has_wildcards 
            //'(' become one token ')' a token representing NULL can be usefull sometime. (maybe ?)
                // we have then an array like "(" "ls" "-a" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
        // pass through the array to identify Logical operator ( && || >> > < |)
            // check text 
                // if you can find one of this char ( & | < > ) and it is the same as one of the logical operator above
                // it means that it's a mistake.
            // if you can find an operator put his value in logical_operator  < > << >> = 4 | = 3 && = 2 || = 1 other 0.
            // attribute group number to each token to create block of command.
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         -1    1    1   0       2      0     3       3   -2    0    4       4
            // check logical operation 
                // check if 0 are at the beginning or at the end.
                //check if two 0s are stuck together.
            // check for () 
                // for the parenthesis, a conter start to 0 and should finish on 0. and if it pass to -1 it break and show an error.
                    // each -1 that it pass -> +1 each -2 -> -1; 
                    // if -1 is just before -2 erro 
                // place together the token in a new array.
            // group up token 
                // if number > 0 combine the number over 0 together. ( the ones with the ones ...) then place it.

        //place the element in the tree
            //to do so we use the Shunting Yard algorithm
                // we have a list of output and a stack for operator (create a list of parsed_command), (create a stack of parsed command )
                // we have to set the priority of each sign compare to each other.(already done) precedence ; // redirection < > << >> = 4 | = 3 && = 2 || = 1
                // we have to to set the associativity of each symbole. (&& || left it mean that the first one is priorities A || B || C -> (A || B) || C
                //< > << >> it right cmd > file1 > file2 -> cmd > (file1 > file2))
                // operands are push into the list of output
                // operators are pushed onto the stack, but before, we should remove the operator which are already there if they have the same or a stronger precedence.
                // à celle du nouvel opérateur ET si l’opérateur est gauche-associatif. if left associativity ;✅ Pop only operators with strictly higher precedence.
                // the parentheses are pushed onto the stack, to the output until a left parenthesis is encountered.
                // THAT CREATE A LIST OF NODE IN REVERSE POLISH

            //How to create the tree
                // create a stack : 
                // push operand into the stack 
                //  When encountering an operator:
                // Pop the required number of operands from the stack. (LINK THE TWO last operrand to the new OPPERATOR POP THE TWO OPERRAND AND SEND the new OPERATOR in the stack)
                // continue until the end of the stack.
}