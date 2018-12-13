//=============================================
//BinaryTree.h
//Create by CroperShen
//last modified in Dec.11.2018
//�������������ϰ֮��
//==============================================
#ifdef BINARYTREE_H
#define BINARYTREE_H

#include <stack>
#include <queue>
using std::stack;
using std::queue;

enum Childpos{ pos_left = -1,pos_right=1,pos_root=0,pos_def=2};

template <typename> class BinaryTreeNode;
template <typename> class BinaryTree;

template <typename T> class BinaryTreeNode
{
	friend class BinaryTree<T>;
private:
	T value;
	BinaryTreeNode *leftchild;
	BinaryTreeNode *rightchild;
	BinaryTreeNode *parent;
protected:
	BinaryTreeNode &Leftchild();      //���������ӽڵ㼰���ڵ�
	BinaryTreeNode &Rightchild();
	BinaryTreeNode &Parent();
public:
    //====================��������=======================
	BinaryTreeNode(T&);          //���캯��
	BinaryTreeNode(BinaryTreeNode<T>&) //�������캯��
	~BinaryTreeNode();            //��������

	T&Data();                       //����ֵ

	void setData(T&);                //����ֵ                 
	void setChild(BinaryTreeNode<T>&,Childpos=pos_def);   //���������ӽڵ㼰���ڵ�
	void setParent(BinaryTreeNode<T>&);

	BinaryTreeNode *pSibing(Childpos = pos_def);   //ָ���ֵܽڵ��ָ�룬û���򷵻�NULL
	BinaryTreeNode *pLeftSibing();
	BinaryTreeNode *ptRightSibing();

	int Depth();                             //�ڵ�����
	void operator=(T);                       //���ظ�ֵ���ţ�ֱ�Ӷ�Data��ֵ����ͬ��setData
};

template <typename T> class BinaryTree
{
private:
	BinaryTreeNode<T> *root;            //���ڵ�
public:
	BinaryTree();
	~BinaryTree();               //�⹹����������ɾ�����еĽڵ㡣
	   
	bool isEmpty();              //�Ƿ�Ϊ����
	bool isLeaf();               //�Ƿ�ΪҶ�������᷵�ط�
	BinaryTreeNode<T> *pRoot();  //ָ����ڵ�ĸ��ڵ㣬û���򷵻�NULL
	Childpos GetPos();           //��ȡ�ڸ��ڵ��е�λ�ã�û�и��ڵ㷵��pos_root

	void setRoot(BinaryTreeNode<T>&);        //���ø��ڵ�

	void Remove();  //�Ƴ���������Ӹ������Ƴ�������ɾ����
	void Delete();  //ɾ������ɾ�����е����нڵ㣬ͬʱ����Ӹ������Ƴ�
	void Clear();   //����������������ڵ��ָ��ָ��NULL

	BinaryTreeNode<T> &Create(T&);                  //����һ��ָ�����ڵ�ֵ������ ���ᴴ���ڵ�;
	BinaryTreeNode<T> &Create(BinaryTreeNode<T>&);  //����һ�����ڵ�ָ��Node���������ᴴ���ڵ㣬��ͬ��setRoot;
	BinaryTreeNode<T> *Create(linkedlist<T>&);      //����������һ����ȫ�������� �ᴴ���ڵ�

	BinaryTree<T> *SubTree(Childpos = pos_def);     //����������Ĭ���������һ����Ϊ�յ�����������������  ���ᴴ����

	int NodeNum();    //���к��еĽڵ���
	int Depth();      //���ĸ߶�

	linkedlist<T> PreOrder();         //���ζ����� ����������ʽ���  ���ᴴ������
	linkedlist<T> PostOrder();
	linkedlist<T> InOrder();
	linkedlist<T> LevelOrder();

	linkedlist<BinaryTreeNode<T>> PreOrderInNode();         //���ζ����� ����ָ��nodeָ���������ʽ���  ���ᴴ������
	linkedlist<BinaryTreeNode<T>> PostOrderInNode();
	linkedlist<BinaryTreeNode<T>> InOrderInNode();
	linkedlist<BinaryTreeNode<T>> LevelOrderInNode();
};


BinaryTreeNode()
{
	data = NULL;
	leftchild = NULL;
	rightchild = NULL;
	parent = NULL;
}
BinaryTreeNode(T data)
{
	value = &data;
}
~BinaryTreeNode()
{
	data = NULL;
	leftchild = NULL;
	rightchild = NULL;
	parent = NULL;
}

inline T *Data()
{
	return value;
}

BinaryTreeNode *Leftchild()
{
	return leftchild;
}



BinaryTreeNode *Rightchild()
{
	return rightchild;
}
BinaryTreeNode *Parent()
{
	return parent;
}

void setData(T data)
{
	value = &data
}

void setChild(BinaryTreeNode<T>* ChildNode, Childpos pos)
{
	if ((pos == pos_def) || (pos == pos_left))
	{
		leftchild = ChildNode;
	}
	else if (pos == pos_right)
	{
		rightchild = ChildNode;
	}
	else if (pos == pos_root)
	{
		parent = ChildNode;
	}
}

void setParent(BinaryTreeNode<T> *ParentNode)
{
	parent = ParentNode;
}

BinaryTreeNode *GetSibing(Childpos = pos_def)
{
	if (parent == NULL) return NULL;
	switch pos
	{
	case pos_left:
		if (parent->rightchild == this) return parent->leftchild;
		break;
	case pos_right:
		if (parent->leftchild == this) return parent->rightchild;
		break;
	case pos_def;
		if (parent->rightchild == this) return parent->leftchild;
		if (parant->leftchild == this) return parent->rightchild;
	}
	return NULL;
}
BinaryTreeNode *GetLeftSibing()
{
	if (parent->rightchild == this) return parent->leftchild;
	return NULL;
}
BinaryTreeNode *GetRightSibing()
{
	if (parent->leftchild == this) return parent->rightchild;
	return NULL;
}

int Depth()                             //�ڵ�����
{
	int i = 0;
	BinaryTreeNode<T>* p = parent;
	while (p != NULL)
	{
		i++;
		p = p->parent;
	}
	return i;
}


void operator=(T)
{
	value = &T;
}


//================================================================================
	//����
BinaryTree() {}
~BinaryTree() {}

bool isEmpty()              //�Ƿ�Ϊ����
{
	return (root == NULL);
}
bool isLeaf()               //�Ƿ�ΪҶ�������᷵�ط�
{
	if (root == NULL) return false;
	if ((root->leftchild == NULL) && (root->rightchild == NULL)) return true;
	reutn false;
}
BinaryTreeNode<T> *Root()     //���ڵ㣬û���򷵻�NULL
{
	return root;
}

void setRoot(BinaryTreeNode<T> &Node)        //���ø��ڵ�
{
	root = &BinaryTreeNode;
}

Childpos GetPos() //��ȡ�ڸ��ڵ��е�λ�ã�û�и��ڵ㷵��pos_root
{
	if (root->parnet == NULL) return pos_root;
	if (root->parent->leftchild == root) return pos_left;
	return pos_right;
}

void Remove()  //�Ƴ���������Ӹ������Ƴ�������ɾ����
{
	if (GetPos() == pos_left)
	{
		root->parent->leftchild = NULL;
	}
	if (GetPos() == pos_right)
	{
		root->parent->rightchild = NULL;
	}
	root->parent = NULL;
}

void Delete()   //ɾ������ɾ�����е����нڵ㣬ͬʱ����Ӹ������Ƴ�
{
	linkedlist<BinaryTreeNode<T>> list = PostOrderInNode();

	Remove();
	for (i = 0; i < list.length(); i++)
	{
		delete list.Value(i);
	}

	root = NULL;

}
void Clear()   //����������������ڵ��ָ��ָ��NULL
{
	root = NULL;
}

BinaryTreeNode<T> *Create()    //������,�ᴴ��һ�����и��ڵ����, ���ᴴ���ڵ�;
{
	root = new BinaryTreeNode<T>;
	return root;
}

BinaryTreeNode<T> *Create(T &data)  //����һ�����ڵ�ָ��Data������ ���ᴴ���ڵ�;
{
	root = new BinaryTreeNode<T>(data);
	return root;
}
BinaryTreeNode<T> *Create(BinaryTreeNode* p)  //����һ�����ڵ�ָ��Node���������ᴴ���ڵ㣬��ͬ��setRoot;
{
	root = p;
	return root;
}

BinaryTreeNode<T> *Create(linkedlist<T>& list) //����������һ����ȫ������  ���ᴴ���ڵ�
{
	BinaryTreeNode<T> *Node;
	Node = new BinaryTreeNode<T>[list.length()];
	for (int i = 0; i < list.length(); i++)
	{
		Node[i].value = &T;
		if (2 * i + 1 < list.length()) Node[i].leftchild = Node[2 * i + 1];
		if (2 * i + 2 < list.length()) Node[i].leftchild = Node[2 * i + 2];
		if (i != 0) Node[i].parent = Node[(i - 1) / 2];
	}
}

BinaryTree<T> *SubTree(Childpos pos)  //����������Ĭ���������һ����Ϊ�յ�����������������  ���ᴴ����
{
	BinaryTree<T> *Tree;
	if (isEmpty()) return NULL;
	Tree = new BinaryTree<T>;
	switch pos
	{
	case pos_def:
		if (root->leftchild != NULL)
		{
			SubTree->root = root->leftchild;
		}
		else
		{
			SubTree->root = root->rightchild;
		}
		break;
	case pos_left:
		SubTree->root = root->leftchild;
		break;
	case pos_right:
		SubTree->root = root->rightchild;
	}
	return Tree;
}

int NodeNum()    //���к��еĽڵ���
{
	int l;
	linkedlist<T> list = PreOrder();
	return list.length;
}
int Depth()      //�������,���������Ϊ-1��
{
	int MaxDepth = 0;
	if (root == NULL) return -1;
	linkedlist<BinaryTreeNode<T>> list = PostOrderInNode()
		for (int i = 0; i < list.length(); i++)
		{
			if (list.Value(i).Depth() > MaxDepth) MaxDepth = list.Value(i).Depth();
		}
	return MaxDepth;
}

//���ζ����� ����������ʽ���  


linkedlist<T> PreOrder()  //ǰ������
{
	linkedlist<T> list;
	stack<BinaryTreeNode<T>*> stk;
	BinaryTreeNode<T>* p;

	if (root == NULL) return NULL;
	p = root;
	stk.push(p);
	while (stk.empty() == false)
	{
		p = stk.top;
		stk.pop();
		list.Append(*(p->Value));
		if (p->rightchild != NULL) stk.push(p->rightchild);
		if (p->leftchild != NULL) stk.push(p->leftchild);
	}

	return list;
}

linkedlist<T> PostOrder()
{
	enum iffinish { finish_yes, finish_no }
	class element
	{
		BinaryTreeNode<T> *pointer;
		iffinish finish;
	};
	linkedlist<T> list;
	stack<element> stk;
	BinaryTreeNode<T>* p;
	element ele;

	if (root == NULL) return NULL;
	ele.pointer = root;
	ele.finish = finish_no;
	stk.push(ele);
	while (stk.empty() == false)
	{
		ele = stk.top;
		p = ele.pointer;
		if (ele.finish == finish_yes)
		{
			list.Append(*(p->Value));
		}
		else
		{
			ele.finish = finish_yes;
			stk.push(ele);
			if (p->rightchild != NULL)
			{
				ele.pointer = p->rightchild;
				ele.finish = finish_no;
				stk_push(ele);
			}
			if (p->leftchild != NULL)
			{
				ele.pointer = p->leftchild;
				ele.finish = finish_no;
				stk_push(ele);
			}
		}
	}
	return list;
}
linkedlist<T> InOrder()
{

	linkedlist<T> list;
	stack<BinaryTreeNode<T>*> stk;
	BinaryTreeNode<T>* p;

	if (root == NULL) return NULL;

	p = root;
	do
	{
		while (p != NULL)
		{
			stk.push(p);
			p = p->leftchild;
		}

		p = stk.top;
		stk.pop();

		list.Append(*(p->value));
		p = p->rightchild;
	} while ((p != NULL) || (stk.empty() == NULL);

	return list;
}
linkedlist<T> LevelOrder()
{
	queue<BinaryTreeNode<T>*> que;
	BinaryTreeNode<T>*p;
	linkedlist<T> list;

	if (root == NULL) return NULL;
	que.push(root);
	while (!que.empty())
	{
		p = que.front();
		list.Append(*(p->value));
		if (p->leftchild != NULL) que.push(p->leftchild);
		if (p->rightchild != NULL) que.push(p->rightchild);
	}
	return list;
}

#endif