/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   L_print_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdeliot <tdeliot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:23:59 by tdeliot           #+#    #+#             */
/*   Updated: 2025/03/27 18:10:26 by tdeliot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
📌 Algorithme pour dessiner un AST de manière équilibrée
Calculer la profondeur de l'arbre

Placer les nœuds en fonction de leur niveau et de leur position relative

Ajouter les liens entre les parents et les enfants

Afficher le buffer contenant l'arbre bien formaté
*/
/*
// i try to print a tree in a certain way, what do you think about my algorithm  the goals is to have this kind of result : 
					||
				||		D
			&&		&&
		A		B C		E

// look the deepness of the tree
//create an array of deepness of tre
	// 2 power(deepness +1) - 1
	//attribute each case to a node of the tree, the first one is the root, then left then right, then left->left then left->right then right->left then right ->right 
	//print 5 tab print 2^0 node \n
	//print 4 tabs  print 2^1 nodes(tab beetween them)\n
	//print 3 tabs	print 2^2 nodes (tab beetween them)\n
	//print 2 tabs	print 2^3 nodes (tab beetween them)\n
	//print 1 tabs	print 2^4 nodes (tab beetween them)\n
	//print 0 tabs	print 2^5 nodes (tab beetween them)\n

	*/

	void print_tree_with_indent(t_ast_node *node, int depth, int indent)
{
    if (node == NULL)
        return;

    // Calculate the number of nodes at this level
    int nodes_at_level = (1 << depth); // 2^depth

    // Print indentation for this level
    for (int i = 0; i < indent; i++) {
        printf("\t");
    }

    // Print the current node
    printf("%s", node->command->command);

    // Print the next node with appropriate spacing (tab between nodes)
    // Handle recursion for the left and right children
    if (node->left || node->right) {
        printf("\t");
    }

    // Recursively print the left and right children
    if (node->left) {
        print_tree_with_indent(node->left, depth - 1, indent - 1);
    }
    if (node->right) {
        print_tree_with_indent(node->right, depth - 1, indent - 1);
    }

    // After printing all children, print a newline for this level
    if (depth == 0) {
        printf("\n");
    }
}