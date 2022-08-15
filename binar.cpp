#include "binar.hpp"

#include <iostream>
#include <stack>
#include <limits>
#include <vector>
#include <queue>

BST::node::node()
{
	left = nullptr;
	right = nullptr;
	parent = nullptr;
}

BST::node::node(int data)
{
	left = nullptr;
	right = nullptr;
	parent = nullptr;
	m_data = data;
}

BST::BST()
{
	m_root = nullptr;
}

BST::~BST()
{
	node *tmp = nullptr;
	std::stack<node *> root_stock;

	while (!root_stock.empty() || m_root != nullptr)
	{
		if (m_root != nullptr) {
			root_stock.push(m_root);
			m_root = m_root->left;
		} else {
			m_root = root_stock.top();
			if (m_root->right == nullptr || tmp == m_root->right) {
				root_stock.pop();
				tmp = m_root;
				delete m_root;
				m_root = nullptr;
			} else {
				m_root = m_root->right;
			}
		}
	}
}

void BST::insert(int data, type_iter mod)
{
	node *new_node = new node(data);

	if (mod == type_iter::ITER) {
		insert(new_node);
	} else {
		insert(new_node, m_root);
	}
}

typename BST::node *BST::insert(node *item, node *root)
{
	if (root == nullptr) {
		return item;
	}
	if (root->m_data > item->m_data) {
		root->left = insert(item, root->left);
		root->left->parent = root;
	} else {
		root->right = insert(item, root->right);
		root->right->parent = root;
	}
	return root;
}

void BST::insert(node *new_item)
{
	node *current = m_root;
	node *previous = m_root;
	
	if (m_root == nullptr) {
		m_root = new_item;
		return;
	}
	while (current != nullptr) {
		previous = current;
		if (current->m_data > new_item->m_data) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	if (previous->m_data > new_item->m_data) {
		previous->left = new_item;
	}
	else {
		previous->right = new_item;
	}
	new_item->parent = previous;
	previous = new_item->parent;
	while (previous) {
		int left_count = 0;
		int right_count = 0;
		left_count = height(previous->left);
		right_count = height(previous->right);
		if (left_count > right_count && left_count - right_count > 1) {
			if (previous->left->right != nullptr) {
				previous->left = right_rotate(previous->left);
			}
			left_rotate(previous);
		} else if (right_count > left_count && right_count - left_count > 1) {
			if (previous->right->left != nullptr) {
				previous->right = left_rotate(previous->right);
			}
			right_rotate(previous);
		}
		previous = previous->parent;
	}
}

int BST::post_order_iter() const
{
	node *tmp = m_root;
	node *other = nullptr;
	int max = 0;
	int counter = 0;
	std::stack<node *> root_stock;

	while (tmp != nullptr || !root_stock.empty()) {
		if (tmp != nullptr) {
			root_stock.push(tmp);
			counter++;
			tmp = tmp->left;
		} else {
			tmp = root_stock.top();
			if (tmp->right == nullptr || other == tmp->right) {
				root_stock.pop();
				if (tmp->right == nullptr) {
						max = std::max(max, counter);
				}
				counter--;
				other = tmp;
				tmp = nullptr;
			} else {
				tmp = tmp->right;
			}
		}
	}
	std::cout << std::endl;
	return max;
}

int BST::height(node *current) const
{
	if (current == nullptr) { return  0; }
	return std::max(height(current->left), height(current->right)) + 1;
}

int BST::height() const
{
	return height(m_root);
}

bool BST::find(int key, node *current) const
{
	if (current == nullptr) { return false; }
	if (current->m_data == key) { return true; }
	if (current->m_data > key) {
		return (find(key, current->left));
	}
	return (find(key, current->right));
}

bool BST::find(int key) const
{
	return find(key, m_root);
}

bool BST::is_BST() const
{
	node *tmp = m_root;
	std::stack <node *> root_stock;
	int parent = 0;

	while (tmp != nullptr || !root_stock.empty()) {
		if (tmp != nullptr) {
			root_stock.push(tmp);
			tmp = tmp->left;
			if (tmp != nullptr && tmp->m_data > (root_stock.top()->m_data)) {
				return  false;
			}
		} else {
			tmp = root_stock.top();
			tmp = tmp->right;
			if (tmp != nullptr && (root_stock.top()->m_data > tmp->m_data || parent > root_stock.top()->m_data)) {
				return false;
			}
			parent = root_stock.top()->m_data;
			root_stock.pop();
		}
	}
	return true;
}

void BST::inorder(node *root) const
{
	if (root == nullptr) { return; }
	inorder(root->left);
	std::cout << root->m_data << " ";
	inorder(root->right);
}

void BST::inorder() const
{
	inorder(m_root);
	std::cout << std::endl;
}

void BST::preorder(node *root) const
{
	if (root == nullptr) { return; }
	std::cout << root->m_data << " ";
	preorder(root->left);
	preorder(root->right);
}

void BST::preorder() const
{
	preorder(m_root);
	std::cout << std::endl;
}

void BST::postorder(node *root) const
{
	if (root == nullptr) { return; }
	postorder(root->left);
	postorder(root->right);
	std::cout << root->m_data << " ";
}

void BST::postorder() const
{
	postorder(m_root);
	std::cout << std::endl;
}

int BST::width(node *root, int level, std::vector<int> &stock) const
{
	if (root == nullptr) { return 0; }
	stock[level] += 1;
	width(root->left, level + 1, stock);
	width(root->right, level + 1, stock);
	return 0;
}

int BST::width() const
{
	std::vector<int> stock(height());
	width(m_root, 0, stock);
	return  *std::max_element(stock.begin(), stock.end());
}

int	BST::predecessor(int data) const
{
	node *last_right = nullptr;
	node *tmp = m_root;
	
	while (tmp != nullptr) {
		if (tmp->m_data > data) {
			tmp = tmp->left;
		} else if (tmp->m_data < data) {
			last_right = tmp;
			tmp = tmp->right;
		}
		if (tmp != nullptr && tmp->m_data == data)
		{
			if (last_right == nullptr && tmp->left == nullptr) {
				std::cout << "Minimum value \n";
				return -1;
			}
			if (tmp->left != nullptr) {
				return  tmp->left->m_data;
			}
			return last_right->m_data;
		}
	}
	std::cout << "The value not exist \n";
	return  -1;
}

typename BST::node *BST::min(node *root) const
{
	if (root->left == nullptr) { return root; }
	return min(root->left);
}

typename BST::node *BST::left_rotate(node *root) // left_rotate
{
	if (root == nullptr || root->left == nullptr) {
		return nullptr;
	}
	node *tmp = root->left->right;
	root->left->right = root;
	node *par_tmp = root->parent;
	root->parent = root->left;
	root->left->parent = par_tmp;
	root->left = tmp;
	if (par_tmp == nullptr) {
		m_root = root->parent;
	} else if(par_tmp->left == root) {
		par_tmp->left = root->parent;
	}
	else {
		par_tmp->right = root->parent;
	}
	return root->parent;
}

typename BST::node *BST::right_rotate(node *root) // right_rotate
{
	if (root == nullptr || root->right == nullptr) {
		return nullptr;
	}
	node *tmp = root->right->left;
	root->right->left = root;
	node *parent = root->parent;
	root->parent = root->right;
	root->right->parent = parent;
	root->right = tmp;
	if (parent == nullptr) {
		m_root = root->parent;
	} else if(parent->left == root) {
		parent->left = root->parent;
	} else {
		parent->right = root->parent;
	}
	return root->parent;
}

void BST::min_to_root(node *min_node, node *root)
{
	if (min_node->parent->left == min_node) {
		min_node->parent->left = nullptr;
	}
	min_node->parent = root->parent;
	min_node->left = root->left;
	redifne_parent(root, min_node);
	root->left->parent = min_node;
	if (root->right != min_node) {
		while (min_node->right != nullptr) {
			min_node = min_node->right;
		}
		min_node->right = root->right;
		root->right->parent = min_node;
	}
	delete root;
}

void BST::redifne_parent(node *child, node *future_child)
{
	if (child->parent == nullptr && future_child != nullptr) {
		m_root = future_child;
	}
	else if (child->parent->left == child) {
		child->parent->left = future_child;
	} else {
		child->parent->right = future_child;
	}
}

void BST::delete_node(node *root)
{
	node *replace_node;
	if (root == nullptr) { return; }
	if (root->right == nullptr && root->left == nullptr) {
		redifne_parent(root, nullptr);
		delete root;
	}
	else if (root->right == nullptr) {
		redifne_parent(root, root->left);
		root->left->parent = root->parent;
		delete root;
	} else {
		replace_node = min(root->right);
		min_to_root(replace_node, root);
	}
}
