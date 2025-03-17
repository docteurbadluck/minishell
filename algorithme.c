/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: docteurbadluck <docteurbadluck@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:16:45 by docteurbadl       #+#    #+#             */
/*   Updated: 2025/03/17 21:26:28 by docteurbadl      ###   ########.fr       */
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
       
        //verifying <<
       
        //verifying " ' () validity

        // split into token the different part
            //("" become one token '' become one token '(' become one token ')' also)
                // we have then an array like "(" "ls" "-a" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
        // pass through the array to identify Logical operator ( && || ())
            // attribute group number to each token to create block of command. 
                // exemle "(" "ls" "-a" ">" "test.txt" "&&" "cat" "'\pwd'" ")" "||" "echo" "failed"
                //         0    1    1   1       1      0    2       2     0    0    3       3
        //pass through the array to identify fd operator ( |  >> > <)
            // identify file name
        //create an array of array of str to contain every group number
        //place the element in the tree 
            //(the tree can't have only two branches as we thought because (ls && ls && ls) is not forbiden
            // in this case it will not be problematic i guess but it could be later .
            // difficult to say i have to think about it.
}