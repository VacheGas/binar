#ifndef BINAR_HPP
#define BINAR_HPP
#include <iostream>
#include <stack>
struct node
{
	int data;
	int size;
	int size_right;
	int size_left;
	int heigh;
	struct node* left;
	struct node* right;
};

enum class type_iter
{
    ITER,
    RECURS
};

class Binar
{
	private:
		node *m_head;
		void add_element_iter(node *add_element);
        node *add_element_rec(node *add_element, node *head);
		bool find_rec(int finde_value, node *head);
		void print_inorder(node *head);
		void print_preorder(node *head);
		void print_postorder(node *head);
		int	high_recursiv(node *head);
	public:
		Binar();
		void add_node(int add_element, type_iter mod);
		~Binar();
		int post_order_iter();
		void print_inorder();
		void print_preorder();
		void print_postorder();
		bool is_search_tree();
		bool find(int finde_value);
		int max_hegh();
};
#endif
