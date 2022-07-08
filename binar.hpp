#ifndef BINAR_HPP
#define BINAR_HPP

#include <iostream>
#include <stack>
struct node
{
	int data;
	int size;
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
public:
	Binar();
	~Binar();
public:
	void add_node(int add_element, type_iter mod);
	int post_order_iter() const;
	void inorder() const;
	void preorder() const;
	void postorder() const;
	bool is_search_tree() const;
	bool find(int finde_value) const;
	int heigh() const;
private:
	node *m_head;
private:
	void add_element_iter(node *add_element);
	node *add_element_rec(node *add_element, node *head);
	bool find(int finde_value, node *head) const;
	void inorder(node *head) const;
	void preorder(node *head) const;
	void postorder(node *head) const;
	int	heigh(node *head) const;
};
#endif //bBINAR_HPP
