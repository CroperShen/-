//=============================================
//BinaryTree.h
//Create by CroperShen
//last modified in Dec.11.2018
//二叉树的相关练习之作
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
	BinaryTreeNode &Leftchild();      //返回左右子节点及父节点
	BinaryTreeNode &Rightchild();
	BinaryTreeNode &Parent();
public:
    //====================函数声明=======================
	BinaryTreeNode(T&);          //构造函数
	BinaryTreeNode(BinaryTreeNode<T>&) //拷贝构造函数
	~BinaryTreeNode();            //析构函数

	T&Data();                       //返回值

	void setData(T&);                //设置值                 
	void setChild(BinaryTreeNode<T>&,Childpos=pos_def);   //设置左右子节点及父节点
	void setParent(BinaryTreeNode<T>&);

	BinaryTreeNode *pSibing(Childpos = pos_def);   //指向兄弟节点的指针，没有则返回NULL
	BinaryTreeNode *pLeftSibing();
	BinaryTreeNode *ptRightSibing();

	int Depth();                             //节点的深度
	void operator=(T);                       //重载赋值符号，直接对Data赋值，等同于setData
};

template <typename T> class BinaryTree
{
private:
	BinaryTreeNode<T> *root;            //根节点
public:
	BinaryTree();
	~BinaryTree();               //解构函数，不会删除树中的节点。
	   
	bool isEmpty();              //是否为空树
	bool isLeaf();               //是否为叶，空树会返回否
	BinaryTreeNode<T> *pRoot();  //指向根节点的根节点，没有则返回NULL
	Childpos GetPos();           //获取在父节点中的位置，没有父节点返回pos_root

	void setRoot(BinaryTreeNode<T>&);        //设置根节点

	void Remove();  //移除树，将其从父树中移除，不会删除树
	void Delete();  //删除树，删除树中的所有节点，同时将其从父树中移除
	void Clear();   //清空树，仅仅将根节点的指针指向NULL

	BinaryTreeNode<T> &Create(T&);                  //创建一个指定根节点值的树， ！会创建节点;
	BinaryTreeNode<T> &Create(BinaryTreeNode<T>&);  //创建一个根节点指向Node的树，不会创建节点，等同于setRoot;
	BinaryTreeNode<T> *Create(linkedlist<T>&);      //根据链表创建一个完全二叉树！ 会创建节点

	BinaryTree<T> *SubTree(Childpos = pos_def);     //返回子树，默认情况返回一个不为空的子树，优先左子树  ！会创建树

	int NodeNum();    //树中含有的节点数
	int Depth();      //树的高度

	linkedlist<T> PreOrder();         //周游二叉树 给出链表形式结果  ！会创建链表
	linkedlist<T> PostOrder();
	linkedlist<T> InOrder();
	linkedlist<T> LevelOrder();

	linkedlist<BinaryTreeNode<T>> PreOrderInNode();         //周游二叉树 给出指向node指针的链表形式结果  ！会创建链表
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

int Depth()                             //节点的深度
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
	//定义
BinaryTree() {}
~BinaryTree() {}

bool isEmpty()              //是否为空树
{
	return (root == NULL);
}
bool isLeaf()               //是否为叶，空树会返回否
{
	if (root == NULL) return false;
	if ((root->leftchild == NULL) && (root->rightchild == NULL)) return true;
	reutn false;
}
BinaryTreeNode<T> *Root()     //根节点，没有则返回NULL
{
	return root;
}

void setRoot(BinaryTreeNode<T> &Node)        //设置根节点
{
	root = &BinaryTreeNode;
}

Childpos GetPos() //获取在父节点中的位置，没有父节点返回pos_root
{
	if (root->parnet == NULL) return pos_root;
	if (root->parent->leftchild == root) return pos_left;
	return pos_right;
}

void Remove()  //移除树，将其从父树中移除，不会删除树
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

void Delete()   //删除树，删除树中的所有节点，同时将其从父树中移除
{
	linkedlist<BinaryTreeNode<T>> list = PostOrderInNode();

	Remove();
	for (i = 0; i < list.length(); i++)
	{
		delete list.Value(i);
	}

	root = NULL;

}
void Clear()   //清空树，仅仅将根节点的指针指向NULL
{
	root = NULL;
}

BinaryTreeNode<T> *Create()    //创建树,会创建一个仅有根节点的树, ！会创建节点;
{
	root = new BinaryTreeNode<T>;
	return root;
}

BinaryTreeNode<T> *Create(T &data)  //创建一个根节点指向Data的树， ！会创建节点;
{
	root = new BinaryTreeNode<T>(data);
	return root;
}
BinaryTreeNode<T> *Create(BinaryTreeNode* p)  //创建一个根节点指向Node的树，不会创建节点，等同于setRoot;
{
	root = p;
	return root;
}

BinaryTreeNode<T> *Create(linkedlist<T>& list) //根据链表创建一个完全二叉树  ！会创建节点
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

BinaryTree<T> *SubTree(Childpos pos)  //返回子树，默认情况返回一个不为空的子树，优先左子树  ！会创建树
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

int NodeNum()    //树中含有的节点数
{
	int l;
	linkedlist<T> list = PreOrder();
	return list.length;
}
int Depth()      //树的深度,空树的深度为-1；
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

//周游二叉树 给出链表形式结果  


linkedlist<T> PreOrder()  //前序周游
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