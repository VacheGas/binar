#ifndef BINAR_HPP
#define BINAR_HPP

#include <vector>

enum class type_iter
{
    ITER,
    RECURS
};

class BST
{
struct node;

public:
	BST();
	~BST();

public:
	void	insert(int data, type_iter mod);
	int		post_order_iter() const;
	void	inorder() const;
	void	preorder() const;
	void	postorder() const;
	bool	is_BST() const;
	bool	find(int data) const;
	int		height() const;
	int		width() const;
	int		predecessor(int data) const;

private:
	int		width(node *root, int level, std::vector<int> &stock) const;
	void	insert(node *data);
	node	*insert(node *data, node *root);
	bool	find(int data, node *root) const;
	void	inorder(node *root) const;
	void	preorder(node *root) const;
	void	postorder(node *root) const;
	int		height(node *root) const;
	node	*min(node *root) const;
	node	*right_rotate(node *root);
	node	*left_rotate(node *root);
	void	delete_node(node *root);
	void	min_to_root(node *min_node, node *root);
	void	redifne_parent(node *child, node *future_child);

private:
	struct node
	{
	public:
		int		m_data;
		node*	left;
		node*	right;
		node*	parent;
	public:
		node();
		node(int data);
	};
	
private:
	node *m_root;
};


#endif //BINAR_HPP
