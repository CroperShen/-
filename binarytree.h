//=============================================
//BinaryTree.h
//Create by CroperShen
//last modified in Dec.15.2018
//二叉树的相关练习之作
//这里的二叉树和链表一样，一棵二叉树是一个完整的储存结构，其"子树"除非使用SubTree重新生成，否则并不是一棵储存意义上的树
//==============================================
#pragma once
#define DEBUGMODE true

#include <stack>
#include <queue>
#include "doublepointer.h"
#include "linkedlist.h"

using std::stack;
using std::queue;

enum Childpos{ pos_left = 0,pos_right=1,pos_root=2,pos_def=-1};
enum TreeOrder{order_pre,order_in,order_post,order_level,order_def=order_level};

template <typename> class BinaryTreeNode;
template <typename> class BinaryTree;

template <typename T> class BinaryTreeNode
{
	friend class BinaryTree<T>;
private:
	T Value;
	BinaryTreeNode<T> *Parent;
	BinaryTreeNode<T> *LeftChild;
	BinaryTreeNode<T> *RightChild;
	BinaryTree<T> *Tree;                      //仅根节点有效，指向所在的树

	int Order;
    //====================函数声明======================
	BinaryTreeNode();                         //构造函数
	BinaryTreeNode(const T&);                 //构造函数
	BinaryTreeNode(const BinaryTreeNode<T>&); //拷贝构造函数
	~BinaryTreeNode();                        //析构函数

	const T& value() const;                                //返回值
	const bool isroot() const;                             //是否是根节点
	const bool isleaf() const;                             //是否是叶节点
	const int depth() const;                               //节点的高度
	const Childpos pos() const;                            //返回节点的位置
	BinaryTreeNode<T>* child(Childpos) const;
	BinaryTreeNode<T>* leftchild() const;                  //返回左右子节点 
	BinaryTreeNode<T>* rightchild() const;                 //返回子节点
	BinaryTreeNode<T>* parent() const;                     //返回父节点
	BinaryTreeNode<T>* sibing(Childpos = pos_def) const;   //指向兄弟节点的指针，没有则返回NULL
	BinaryTreeNode<T>* leftsibing() const;                 //返回左兄弟
	BinaryTreeNode<T>* rightSibing() const;                //返回右兄弟
	BinaryTree<T>* tree() const;                           //返回所在的树
	int order() const;                                     //返回在树中的次序


	BinaryTreeNode<T>& operator=(T&);                   //重载赋值符号，直接对Data赋值，等同于setData
	BinaryTreeNode<T>& operator=(BinaryTreeNode<T>&);   


	void SetValue(T&);                                         //设置值 

	void SetLeftChild(BinaryTreeNode<T>*, bool=false);                     //设置左右子节点,可设定是否带上孙子节点
	void SetRightChild(BinaryTreeNode<T>*,bool=false);
	void SetChild(BinaryTreeNode<T>*,const Childpos=pos_def,bool=false);  
	void SetParent(BinaryTreeNode<T>*, const Childpos = pos_def);          //设置父节点
	void Swap(BinaryTreeNode<T>*, bool = false);                           //与特定节点交换,可设定是否与子节点一起交换

	const bool AddLeftChild(const T&);                         //增加给定值的左右子节点，返回是否添加成功
	const bool AddRightChild(const T&);                        
	const bool AddChild(const T&, Childpos = pos_def);         
};

template <typename T> class BinaryTree
{
	friend class BinaryTreeNode<T>;
private:
	BinaryTreeNode<T> *Root;                         //根节点
	TreeOrder Order;                                 //默认周游次序
	linkedlist<BinaryTreeNode<T>*> OrderList;        //储存节点的次序
    int Size;                                        //储存树的大小
	bool WellOrdered;                                 //储存树是否已经排序好
													 //当树经过改动后，WellOrdered设为false，当调用需要排序才能实现的函数时，检查WellOrdered，如果为否，则排序后再进行操作；
public:
	BinaryTree();                                    //构造函数
	BinaryTree(const BinaryTree<T>&);                //复制构造函数
	BinaryTree(const std::initializer_list<T>&);     //根据初始化表构造函数
	BinaryTree(const linkedlist<T>&);                //根据链表构造函数
	BinaryTree(BinaryTreeNode<T>&);                  //根据节点及其子节点创建树
	~BinaryTree();                                   //析构函数
	   
	const int size();
	const bool empty() const;                   //是否为空树
	const bool height();                        //高度
	BinaryTreeNode<T> *root() const;            //指向根节点的指针，没有则返回NULL
    BinaryTreeNode<T> *node(int) ;              //默认周游次序下的指定节点
	const T& value(int);

	void SetRoot(BinaryTreeNode<T>&);          //设置根节点
	void SetValue(int, const T&);                  //
	void Clear();                              //清空树

	//周游二叉树
	TreeOrder treeorder() const;
	void SetTreeOrder(const TreeOrder);
	void ForTree(void(*)(BinaryTreeNode<T>&));    //根据设定次序周游 
	void DoOrder();                               //进行排序
};

//二叉树节点函数的定义

template <typename T> BinaryTreeNode<T>::BinaryTreeNode()  //构造函数
{ 
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}
template <typename T> BinaryTreeNode<T>::BinaryTreeNode(const T& t) //构造函数
{
	Value = t;
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}

template <typename T> BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& t) //拷贝构造函数
{
	Value = t.Value;
	LeftChild = NULL;
	RightChild = NULL;
	Parent = NULL;
	Tree = NULL;
	Order = -1;
}

template <typename T> BinaryTreeNode<T>::~BinaryTreeNode()  //析构函数
{
	if (LeftChild != NULL) LeftChild->Parent = NULL;
	if (RightChild != NULL) RightChild->Parent = NULL;
	if (Parent != NULL)
	{
		if (Parent->LeftChild == this) Parent->LeftChild = NULL;
		if (Parent->RightChild == this) Parent->RightChild = NULL;
	}
}

template <typename T> inline const T& BinaryTreeNode<T>::value() const                                 //返回值
{
	return Value;
}

template <typename T> inline const bool BinaryTreeNode<T>::isroot() const                             //是否是根节点
{
	if (Parent != NULL) return false;
	if (tree()== NULL) return false;
	if (tree()->root != this) return false;
	return true;
}

template <typename T> inline const bool BinaryTreeNode<T>::isleaf() const                             //是否是叶节点
{
	return ((LeftChild == NULL) && (RightChild == NULL));
}

template <typename T> const int BinaryTreeNode<T>::depth() const                                           //节点的深度
{
	int i = 0;
	BinaryTreeNode<T>* p = Parent;
	while (p != NULL)
	{
		i++;
		p = p->Parent;
	}
	return i;
}

template <typename T> const Childpos BinaryTreeNode<T>::pos() const                                  //返回节点的位置
{
	if (Parent == NULL) return pos_root;
	if (Parent->LeftChild == this) return pos_left;
	return pos_right;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::child(Childpos pos) const                  //返回子节点 
{
	switch (pos)
	{
	case pos_left:
		return LeftChild;
	case pos_right:
		return RightChild;
	case pos_def:
		if (LeftChild != NULL) return LeftChild;
		return RightChild;
	}
	return NULL;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftchild() const                  //返回左子节点 
{
	return LeftChild;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightchild() const                 //返回右子节点
{
	return RightChild;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::parent() const                     //返回父节点
{
	return Parent;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::sibing(Childpos pos) const   //返回兄弟节点
{
	if (Parent== NULL) return NULL;
	switch (pos)
	{
	case pos_left:
		if (Parent->RightChild == this) return Parent->LeftChild;
		return NULL;
	case pos_right:
		if (Parent->LeftChild == this) return Parent->RightChild;
		return NULL;
	case pos_def:
		if (Parent->RightChild == this) return Parent->LeftChild;
		if (Parent->LeftChild == this) return Parent->RightChild;
	}
	return NULL;
}

template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::leftsibing() const                 //返回左兄弟
{
	if (Parent == NULL) return NULL;
	if (Parent->RightChild == this) return Parent->LeftChild;
	return NULL;
}
template <typename T> inline BinaryTreeNode<T>* BinaryTreeNode<T>::rightSibing() const                //返回右兄弟
{
	if (Parent == NULL) return NULL;
	if (Parent->LeftChild == this) return Parent->RightChild;
	return NULL;
}

template <typename T> inline BinaryTree<T>* BinaryTreeNode<T>::tree() const                             //返回所在的树
{
	const BinaryTreeNode<T> *p = this;
	while (p->Parent == NULL) p = p->Parent;
	return p->Tree;
}


template <typename T> inline int BinaryTreeNode<T>::order() const                             //确定在树中的次序
{
	if (tree() == NULL) return -1;
	if (tree()->WellOrderd == false) Tree->DoOrder();
	return Order;
}


template <typename T> BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(T& t)                   //重载赋值符号，直接对Data赋值，等同于setData
{
	Value = t;
	return *this;
}

template <typename T> BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(BinaryTreeNode<T>& t)   //重载赋值符号，直接对Data赋值，等同于setData
{
	Value = t.Value;
	return *this;
}

template <typename T> void BinaryTreeNode<T>::SetValue(T& t)                                          //设置值        
{
	Value = t;
}

template <typename T> void BinaryTreeNode<T>::SetLeftChild(BinaryTreeNode<T>* p,bool withchild)                            //设置左子节点
{	
	if (LeftChild == p) return;    //如果相同，不做任何改动
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree()!=p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (LeftChild != NULL) LeftChild->Parent = NULL;
	LeftChild = p;
	if (p!=NULL)
	{
	    p->Parent = this;
		if (withchild==false)
		{ 
	        p->LeftChild = NULL;
	        p->RightChild = NULL;
		}
	}
}

template <typename T> void BinaryTreeNode<T>::SetRightChild(BinaryTreeNode<T>* p,bool withchild)                            //设置右子节点
{
	if (RightChild == p) return;    //如果相同，不做任何改动
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree() != p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (RightChild != NULL) RightChild->Parent = NULL;
	RightChild = p;
	if (p != NULL)
	{
		p->Parent = this;
		if (withchild == false)
		{
			p->LeftChild = NULL;
			p->RightChild = NULL;
		}
	}
}

template <typename T> void BinaryTreeNode<T>::SetChild(BinaryTreeNode<T>* p, const Childpos pos,bool withchild)                            //设置左右子节点
{
	BinaryTreeNode<T> **pChild;
	if ((pos == pos_def) || (pos == pos_left))
	{
		pChild = &LeftChild;
	}
	else if (pos == pos_right)
	{
		pChild = &RightChild;
	}
	else return;

	if (*pChild == p) return;    //如果相同，不做任何改动
	if (p == NULL) if (tree() != NULL) tree()->WellOrdered = false;
	if (tree() != p->tree())
	{
		if (tree() != NULL) tree()->WellOrdered = false;
		if (p->tree() != NULL) p->tree()->WellOrdered = false;
	}
	if (*pChild != NULL) (*pChild)->Parent = NULL;
	*pChild = p;
	if (p != NULL)
	{
		p->Parent = this;
		if (withchild == false)
		{
			p->LeftChild = NULL;
			p->RightChild = NULL;
		}
	}
}


template <typename T> void BinaryTreeNode<T>::SetParent(BinaryTreeNode<T>* p, const Childpos pos1)                            //设置左右子节点
{
	BinaryTreeNode<T> **pChild;
	Childpos pos0 = pos();

	if (p != NULL) if (p->child(pos0) == this) return;    //如果p指向的是自身的父节点且位置正确则不进行代换
	if (isroot()) tree()->Root = NULL;                    //如果是根节点则将对应树的根节点设为NULL （反正也没有东西换过来）
	if (tree() != NULL) tree()->WellOrdered = false;      //如果自身位于一棵树内那么将这棵树的WellOrdered设为false

	if (pos0 == pos_left) Parent->LeftChild = NULL;        //如果自身是子节点，则与父母断绝关系
	if (pos0 == pos_right) Parent->RightChild = NULL;


	Parent = p;
	Tree = NULL;
	if (p != NULL)
	{
		switch (pos1)
		{
		case pos_left:
		     p->LeftChild = this;
		case pos_right:
			 p->RightChild = this;
		case pos_def:
			if ((p->LeftChild != NULL) && (p->RightChild == NULL)) p->RightChild = this;
			p->LeftChild = this;
		}
		if (tree() != NULL) tree()->WellOrdered = false;
	}
}


template <typename T> void BinaryTreeNode<T>::Swap(BinaryTreeNode<T>* p, bool withchild)                            //交换节点
{
	BinaryTreeNode<T> *pTemp;
	BinaryTree<T> *tr1, *tr2;
	Childpos pos1, pos2;

	if (p == this) return;  //如果p指向的是自身则不进行代换
	if (p == NULL)          //如果p为NULL，视为从树中移除本节点
	{
		tr1 = tree();
		pos1 = pos();
		if (tr1 != NULL) tr1->WellOrdered = false;
		if (isroot()) tr1->root = NULL;
		if (pos = pos_left) Parent->LeftChild = NULL;
		if (pos = pos_right) Parent->RightChild = NULL;

		Parent = NULL;
		Tree = NULL;
		if (withchild == false)
		{
			if (LeftChild != NULL) LeftChild->Parent = NULL;
			if (RightChild != NULL) RightChild->Parent = NULL;
			LeftChild = NULL;
			RightChild = NULL;
		}
		return;
	}

	tr1 = tree();
	tr2 = p->tree();
	if (tr1!= tr2)
	{
		if (tr1 != NULL) tr1->WellOrdered = false;
		if (tr2 != NULL) tr2->WellOrdered = false;
	}
	if (isroot())
	{
		tr1->root = p;
		p->Tree = tr1;
	}

	if (p->isroot())
	{
		tr2->root = this;
		Tree = tr2;
	}

	pos1 = pos();
	pos2 = p->pos();

	if (pos1 == pos_left) Parent->LeftChild = p;
	if (pos1 == pos_right)Parent->RightChild = p;
	if (pos2 == pos_left) p->Parent->LeftChild = this;
	if (pos2 == pos_right) p->Parent->RightChild = this;

	pTemp = Parent;
	Parent = p->Parent;
	p->Parent = pTemp;


	if (withchild == false)
	{
		if (LeftChild != NULL) LeftChild->Parent = p;
		if (p->LeftChild != NULL) p->LeftChild->Parent = this;
		if (RightChild != NULL) RightChild->Parent = p;
		if (p->RightChild != NULL) p->RightChild=this;

		pTemp = LeftChild;
		LeftChild = p->LeftChild;
		p->LeftChild = pTemp;
		pTemp = RightChild;
		RightChild = p->RightChild;
		p->RightChild = pTemp;
	}
}

template <typename T> const bool  BinaryTreeNode<T>::AddChild(const T& t, const Childpos pos)                            //增加给定值的左右子节点,返回是否添加成功
{
	BinaryTreeNode<T> *child;

	switch (pos)
	{
		case pos_left:
		    if (LeftChild != NULL) return false;
			child = new BinaryTreeNode<T>(t);
			child->Parent = this;
			LeftChild = child;
			if (tree() != NULL) tree()->WellOrdered == false;
			return true;
		case pos_right:
			if (RightChild != NULL) return false;
			child = new BinaryTreeNode<T>(t);
			child->Parent = this;
			RightChild = child;
			if (tree() != NULL) tree()->WellOrdered == false;
			return true;
		case pos_def:
			if (LeftChild == NULL)
			{
				child = new BinaryTreeNode<T>(t);
				child->Parent = this;
				LeftChild = child;
				if (tree() != NULL) tree()->WellOrdered == false;
				return true;
			}
			else if (RightChild == NULL)
			{
				child = new BinaryTreeNode<T>(t);
				child->Parent = this;
				RightChild = child;
				if (tree() != NULL) tree()->WellOrdered == false;
				return true;
			}
	}
	return false;
}

template <typename T> const bool  BinaryTreeNode<T>::AddLeftChild(const T& t)                            //增加给定值的左子节点,返回是否添加成功
{
	BinaryTreeNode<T> *child;

	if (LeftChild != NULL) return false;
	child = new BinaryTreeNode<T>(t);
	child->Parent = this;
	LeftChild = child;
	return true;

	if (tree() != NULL) tree()->WellOrdered = false;
}

template <typename T> const bool  BinaryTreeNode<T>::AddRightChild(const T& t)                            //增加给定值的右子节点,返回是否添加成功
{
	BinaryTreeNode<T> *child;

	if (RightChild != NULL) return false;
	child = new BinaryTreeNode<T>(t);
	child->Parent = this;
	RightChild = child;
	return true;

	if (tree() != NULL) tree()->WellOrdered = false;
}

//================================================================================
	//定义

template <typename T> BinaryTree<T>::BinaryTree()                                    //构造函数
{
	Root = NULL;
	Order = order_def;
	WellOrdered = true;
	Size = 0;
}

template <typename T> BinaryTree<T>::BinaryTree(const BinaryTree<T>& tree)                //复制构造函数
{                                                                   
	Order = tree.Order;
	Root = NULL;
	if (tree.Root == NULL) return;                                          //如果tree为空树则创建一个空树                          
	BinaryTree<T>(*tree.root());                                            //根据tree的根节点创建子树
}

template <typename T> BinaryTree<T>::BinaryTree(const std::initializer_list<T>& list)     //根据初始化表构造完全二叉树
{
	//创建的为完全二叉树
	BinaryTreeNode<T> *Node;
	Size = list.size();
	Order = order_def;
	Root = NULL;
	if (Size == 0) return;

	Node = new BinaryTreeNode<T>[Size];
	auto p = list.begin();
	for (int i=0; i < Size; i++)
	{
		Node[i].SetValue((T)p[i]);
		if (2 * i + 1 < Size) Node[i].SetLeftChild(Node[2 * i + 1]);
		if (2 * i + 2 < Size) Node[i].SetRightChild(Node[2 * i + 2]);
	}
}

template <typename T> BinaryTree<T>::BinaryTree(const linkedlist<T>& list)                 //根据链表构造完全二叉树
{
	//创建的为完全二叉树
	BinaryTreeNode<T> *Node;
	Size = list.size();
	Order = order_def;
	Root = NULL;
	if (Size == 0) return;

	Node = new BinaryTreeNode<T>[Size];
	for (int i = 0; i < Size; i++)
	{
		Node[i].SetValue(list.value(i));
		if (2 * i + 1 < Size) Node[i].SetLeftChild(Node[2 * i + 1]);
		if (2 * i + 2 < Size) Node[i].SetRightChild(Node[2 * i + 2]);
	}
}

template <typename T> BinaryTree<T>::BinaryTree(BinaryTreeNode<T>& Node)             //根据节点及其子节点创建树
{
	dpointer<BinaryTreeNode<T>>  p, pNext;
	stack<dpointer<BinaryTreeNode<T>>> stk;

	Root = new BinaryTreeNode<T>(Node);                       //首先复制根节点
	p.p1 = &Node;
	p.p2 = Root;
	do
	{
		if (p.p1->RightChild != NULL)
		{
			p.p2->AddRightChild(p.p1->RightChild->value());
			pNext.p1 = p.p1->RightChild;
			pNext.p2 = p.p2->RightChild;
			stk.push(pNext);
		}
		if (p.p1->LeftChild != NULL)
		{
			p.p2->AddLeftChild(p.p1->LeftChild->value());
		}
		p.p1 = p.p1->LeftChild;
		p.p2 = p.p2->LeftChild;

		if (p.p1 == NULL)
		{
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
	} while ((p.p1 != NULL) || (!stk.empty()));
}

template <typename T> BinaryTree<T>::~BinaryTree()                                   //析构函数
{
	for (int i = Size - 1; i >= 0; i--) delete node(i);

}

template <typename T> void BinaryTree<T>::DoOrder()                                   //排序
{
	queue<BinaryTreeNode<T>*> que;
	stack<BinaryTreeNode<T>*> stk;
	BinaryTreeNode<T> *p;
	if (WellOrdered) return;
	Size = 0;
	OrderList.Clear();

	if (Root == NULL) return;

	switch (Order)
	{
	case order_level:                 
		que.push(Root);
		while (!que.empty())
		{
			p = que.front();
			que.pop();
			OrderList.Append(p);
			p->Order = Size;
			Size++;
			if (p->LeftChild != NULL) que.push(p->LeftChild);
			if (p->RightChild != NULL) que.push(p->RightChild);
		}
	case order_pre:
		p = Root;
		while (p!=NULL)
		{
			while (p != NULL)
			{
				OrderList.Append(p);
				p->Order = Size;
				Size++;
				if (p->RightChild != NULL) stk.push(p->RightChild);
				p = p->LeftChild;
			}
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
	case order_in:
		p = Root;
		do
		{
			while (p != NULL)
			{
				stk.push(p);
				p = p->LeftChild;
			}

			p = stk.top();
			stk.pop();

			OrderList.Append(p);
			p->Order = Size;
			Size++;
			p = p->RightChild;
		}while ((p != NULL) || (!stk.empty()));

	case order_post:                 //后序可视为镜像后的前序再进行翻转；正常后序写法太麻烦
		p = Root;
		while (p != NULL)
		{
			while (p != NULL)
			{
				OrderList.Append(p);
				Size++;
				if (p->LeftChild != NULL) stk.push(p->LeftChild);
				p = p->RightChild;
			}
			if (!stk.empty())
			{
				p = stk.top();
				stk.pop();
			}
		}
		OrderList.Turn();
		for (int i = 0; i < Size; i++)
		{
			OrderList.value(i)->Order = i;
		}
	}

	WellOrdered = true;
}


template <typename T> const int BinaryTree<T>::size()
{
	if (WellOrdered == false) DoOrder();
	return Size;
}

template <typename T> const bool BinaryTree<T>::empty() const                   //是否为空树
{
	return (Root == false);
} 
template <typename T> const bool BinaryTree<T>::height()                       //高度
{
	int maxheight = 0;
	int h1;
	if (WellOrdered == false) DoOrder();
	for (int i = 0; i < Size; i++)
	{
		h1 = value(i)->depth();
		if (h1 > maxheight) maxheight = h1;
	}
	return maxheight;
}
template <typename T> BinaryTreeNode<T> *BinaryTree<T>::root() const      //指向根节点的指针，没有则返回NULL
{
	return Root;
}
template <typename T> BinaryTreeNode<T> *BinaryTree<T>::node(int i)       //默认周游次序下的指定节点
{
	if (WellOrdered == false) DoOrder();
	return OrderList.value(i);
}
template <typename T> const T& BinaryTree<T>::value(int i)
{
	if (WellOrdered == false) DoOrder();
	return OrderList->value(i)->Value;
}


template <typename T> void BinaryTree<T>::SetRoot(BinaryTreeNode<T>& t)   //设置根节点
{
	if (Root == &t) return;
	WellOrdered == false;
	Root = &t;
    t.SetParent(NULL);
	t.Tree = this;
}

template <typename T> void BinaryTree<T>::SetValue(int i, const T& t)   //设置根节点
{
	if (WellOrdered == false) DoOrder();
	OrderList.value(i)->Value = t;
}
template <typename T> void BinaryTree<T>::Clear()                   //清空树
{
	if (Root == NULL) return;
	for (int i = 0;i <= Size; i++)
	{
		delete OrderList.value(i);
	}
	WellOrdered = false;
}
template <typename T> inline TreeOrder BinaryTree<T>::treeorder() const
{
	return Order;
}
template <typename T> void BinaryTree<T>::SetTreeOrder(const TreeOrder)
{
	if (Order == TreeOrder) return;
	Order = TreeOrder;
	WellOrdered = false;
}
template <typename T> void BinaryTree<T>::ForTree(void(*func1)(BinaryTreeNode<T>&))    //根据设定次序周游 
{
	BinaryTreeNode<T> *p;
	if (WellOrdered = false) DoOrder();
	for (int i = 0; i < Size; i++)
	{
		p = OrderList.value(i);
		func1(*p);
	}
}