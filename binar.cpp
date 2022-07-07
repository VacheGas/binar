#include "binar.hpp"

void Binar::add_element_iter(node *add_data)
{
	node *tmp_quick;
	node *tmp_slow;
	int highe = 0;
	
	tmp_slow = m_head;
	if (m_head->data > add_data->data)
	{
		m_head->size_left += 1;
		highe += 1;
		tmp_quick = m_head->left;
	}
	else
	{
		m_head->size_right += 1;
		highe += 1;
		tmp_quick = m_head->right;
	}
	while (tmp_quick != nullptr)
	{
		tmp_slow->size += 1;
		tmp_slow = tmp_quick;
		if (tmp_quick->data > add_data->data)
		{
			tmp_quick->size_left += 1;
			highe += 1;
			tmp_quick = tmp_quick->left;
		}
		else
		{
			tmp_quick->size_right += 1;
			highe += 1;
			tmp_quick = tmp_quick->right;
		}
	}
	if (tmp_slow->data > add_data->data)
	{
        tmp_slow->size += 1;
		tmp_slow->left = add_data;
	}
	else
	{
        tmp_slow->size += 1;
		tmp_slow->right = add_data;
	}
}

Binar::Binar()
{
	m_head = nullptr;
}

int Binar::post_order_iter()
{
	node *tmp;
	node *other;
	tmp = m_head;
	other = nullptr;
	int max = 0;
	int counter = 0;
	std::stack <node *> root_stock;

	while (!root_stock.empty() || tmp != nullptr)
	{
		if (tmp != nullptr)
		{
			root_stock.push(tmp);
			counter++;
			tmp = tmp->left;
		}
		else
		{
			tmp = root_stock.top();
			if (tmp->right == nullptr || other == tmp->right)
			{
				root_stock.pop();
				if (tmp->right == nullptr) {
					if (counter > max)
						max = counter;
				}
				counter--;
				other = tmp;
				tmp = nullptr;
			}
			else
			{
				tmp = tmp->right;
			}
		}
	}
	std::cout<<std::endl;
	return max;
}

int Binar::high_recursiv(node *hegh)
{
	if (hegh == nullptr)
		return  0;
	return std::max(high_recursiv(hegh->left), high_recursiv(hegh->right)) + 1;
	
}

int Binar::max_hegh()
{
	node *tmp = m_head;
	return(high_recursiv(tmp));
}

Binar::~Binar()
{
	node *tmp;
	std::stack <node *> root_stock;
	tmp = nullptr;
	while (!root_stock.empty() || m_head != nullptr)
	{
		if (m_head != nullptr)
		{
			root_stock.push(m_head);
			m_head = m_head->left;
		}
		else
		{
			m_head = root_stock.top();
			if (m_head->right == nullptr || tmp == m_head->right)
			{
				root_stock.pop();
				tmp = m_head;
				delete m_head;
				m_head = nullptr;
			}
			else
			{
				m_head = m_head->right;
			}
		}
	}
}

bool Binar::find_rec(int key, node *head)
{
	if (head == nullptr)
		return false;
	if (head->data == key)
		return true;
	if (head->data > key) {
		return (find_rec(key, head->left));
	}
	else
	{
		return (find_rec(key, head->right));
	}
	return false;
}

bool Binar::find(int key)
{
	node *tmp;

	tmp = m_head;
	return(find_rec(key, tmp));
}

node *Binar::add_element_rec(node *add_element, node *head)
{
    if (head == nullptr)
    {
		return add_element;
    }
	if (head->data > add_element->data)
	{
		head->left = add_element_rec(add_element, head->left);
		head->size_left += 1;
	}
	else
	{
		head->right = add_element_rec(add_element, head->right);
		
		head->size_right += 1;
	}
	head->size += 1;
	return head;
}

void Binar::add_node(int add_data, type_iter mod)
{
	node *new_node;

	new_node = new node;
	new_node->data = add_data;
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->size = 0;
	new_node->size_left = 0;
	new_node->size_right = 0;
	if (m_head == nullptr)
	{
		m_head = new_node;
	}
	else
	{
        if (mod == type_iter::ITER)
        {
            add_element_iter(new_node);
        }
        else
        {
            node *tmp = m_head;
			
            add_element_rec(new_node, tmp);
        }
	}
}

bool Binar::is_search_tree()
{
	node *tmp = m_head;
	std::stack <node *> root_stock;
	while (tmp != nullptr || !root_stock.empty()) {
		if (tmp != nullptr) {
			root_stock.push(tmp);
			tmp = tmp->left;
			if (tmp != nullptr && tmp->data > (root_stock.top()->data)) {
				return  false;
			}
		}
		else
		{
			tmp = root_stock.top();
			tmp = tmp->right;
			if (tmp != nullptr && root_stock.top()->data > tmp->data)
			{
				return false;
			}
			
			root_stock.pop();
		}
	}
	return true;
}

void Binar::print_inorder(node *head)
{
	if (head == nullptr)
		return;
	print_inorder(head->left);
	std::cout << head->data << " ";
	print_inorder(head->right);
}

void Binar::print_inorder()
{
	node *tmp = m_head;
	print_inorder(tmp);
	std::cout << std::endl;
}

void Binar::print_preorder(node *head)
{
	if (head == nullptr)
		return;
	std::cout << head->data << " ";
	print_preorder(head->left);
	print_preorder(head->right);
}

void Binar::print_preorder()
{
	node *tmp = m_head;
	print_preorder(tmp);
	std::cout << std::endl;
}

void Binar::print_postorder(node *head)
{
	if (head == nullptr)
		return;
	print_postorder(head->left);
	print_postorder(head->right);
	std::cout << head->data << " ";
}

void Binar::print_postorder()
{
	node *tmp = m_head;
	print_postorder(tmp);
	std::cout << std::endl;
}
