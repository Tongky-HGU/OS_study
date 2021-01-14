//// Btree study
//// 2021
//
//#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <math.h>
//
//
//#define Node_Order			5
//#define Node_Childs			Node_Order
//#define Node_Keys			Node_Childs-1
//#define Num_Minimum_Keys	(int)(ceil(Node_Order/2.0))-1
//
//
//struct BTreeNode {							// ��Ʈ���� ��� ����ü
//	bool leaf;
//	int key[Node_Keys + 1];					// Ű ������
//	int num_key;							// Ű ����
//	struct BTreeNode* child[Node_Childs + 1]; // �ڽ��� �ּҸ� ������ ������
//	int num_child;							// �ڽ� ����
//};
//
//struct BTreeNode* root; // ��Ʈ ������
///*SEARCH******************************************************************************************************/
//int searchNode(struct BTreeNode* node, int val) {			// TO DO:: ����Ž��
//	if (!node) { 											// empty tree!
//		printf("Empty tree!!\n");
//		return 0;
//	}
//	struct BTreeNode* level = node;							// root���� leaf���� Ž��
//	while (1) {
//		int pos;
//		for (pos = 0; pos < level->num_key; pos++) {
//			if (val == level->key[pos]) {					// ã���� ���� 1
//				printf("%d exist!!\n", val);
//				return 1;
//			}
//			else if (val < level->key[pos]) {
//				break;
//			}
//		}
//		if (level->leaf) break;
//		level = level->child[pos];
//	}
//	printf("%d not exist!!\n", val);							// leaf �����ͼ��� ��ã���� ���� 0
//	return 0;
//}
//
///*INSERT******************************************************************************************************/
// //Create Node
//struct BTreeNode* createNode(int val) {
//	struct BTreeNode* newNode;
//	newNode = (struct BTreeNode*)malloc(sizeof(struct BTreeNode)); // BƮ�� ����ü��ŭ �����Ҵ�
//
//	newNode->leaf = false;
//	newNode->key[0] = val;
//	newNode->num_key = 1;
//	newNode->num_child = 0;
//	return newNode;
//}
//
////Split Node
//struct BTreeNode* splitNode(int pos, struct BTreeNode* node, struct BTreeNode* parent) {
//	int median;
//	if (Node_Order % 2 == 0) {								// ¦�� ���
//		median = node->num_key / 2 - 0.5;
//	}
//	else {													// Ȧ�� ���
//		median = node->num_key / 2;
//	}
//	struct BTreeNode* child;
//
//	child = (struct BTreeNode*)malloc(sizeof(struct BTreeNode));
//	child->leaf = node->leaf;
//	child->num_key = 0;
//	child->num_child = 0;
//
//	if (!node->leaf) {										 // leaf�� �ƴ� ���� child�� �Ѱ������
//		int num_iter = node->num_child;
//		for (int i = median + 1; i < num_iter; i++) {
//			child->child[i - median - 1] = node->child[i];
//			child->num_child++;
//			node->num_child--;
//		}
//	}
//	int num_iter = node->num_key;
//	for (int i = median + 1; i < num_iter; i++) {		 // child right�� Ű ����ֱ� ���� ���� child left�� �ȴ�
//		child->key[i - median - 1] = node->key[i];
//		child->num_key++;
//		node->num_key--;
//	}
//
//
//	if (node == root) {										 // ���� ��尡 ��Ʈ���
//		struct BTreeNode* new_parent;						 // ���ο� parent���� median Ű�� �־��ش�.
//		new_parent = createNode(node->key[median]);
//		node->num_key--;									 // median �������Ƿ� -1
//		new_parent->child[0] = node;
//		new_parent->child[1] = child;
//		new_parent->num_child = 2;
//		parent = new_parent;
//		return parent;
//	}
//	else {													 // ���� ��尡 ��Ʈ�� �ƴ϶��
//		for (int i = parent->num_key; i > pos; i--) {
//			parent->key[i] = parent->key[i - 1];
//			parent->child[i + 1] = parent->child[i];		 // TODO:: �ߵ����� Ȯ��
//		}
//		parent->key[pos] = node->key[median];				 // �θ� ��忡 key�� �߰����ش�.
//		parent->num_key++;
//		node->num_key--;									 // median �������Ƿ� -1
//		parent->child[pos + 1] = child;						 // �θ� ��忡 �� child�� �߰����ش�.
//		parent->num_child += 1;
//	}
//	return node;
//}
//
////Insert Node
//struct BTreeNode* insertNode(int parent_pos, int val, struct BTreeNode* node, struct BTreeNode* parent) {
//	int pos;												// pos�� ���� �� ������
//	for (pos = 0; pos < node->num_key; pos++) {
//		if (val == node->key[pos]) {
//			printf("Duplicates are not permitted!!\n");		// �ߺ��� Ű�� ����
//			return node;
//		}
//		else if (val < node->key[pos]) {					// val�� �� ��ġ�� ã�´�.
//			break;
//		}
//	}
//	if (!node->leaf) {										// leaf�� �ƴ� ��쿡�� child�� ��������.
//		node->child[pos] = insertNode(pos, val, node->child[pos], node);
//		if (node->num_key == Node_Keys + 1) {				// �Ʒ� ���Կ� ���� Ű�� á�ٸ�, �� split�� ���ش�
//			node = splitNode(parent_pos, node, parent);
//		}
//	}
//	else {													// leaf���� �����Ѵ�.
//		for (int i = node->num_key; i > pos; i--) {
//			node->key[i] = node->key[i - 1];
//			node->child[i + 1] = node->child[i];			// TODO:: �ߵ����� Ȯ��
//		}
//		node->key[pos] = val;
//		node->num_key++;
//		if (node->num_key == Node_Keys + 1) {				// Ű�� ��á�ٸ�? split�� ���ش�!
//			node = splitNode(parent_pos, node, parent);
//		}
//	}
//
//	return node;											// ��� ��ȯ
//}
//
//void insert(int val) {
//	if (!root) { 											// root �� ���ٸ� root�� �����.
//		root = createNode(val);
//		root->leaf = true;
//		return;
//	}
//
//	root = insertNode(0, val, root, root);					// root �� �ִٸ� ��带 ã�� �����Ѵ�.
//}
///*DELETE*****************************************************************************************************/
//
//int findPredecessor(struct BTreeNode* node) {
//	int predecessor;
//	if (node->leaf) {
//		return node->key[node->num_key - 1];
//	}
//	return findPredecessor(node->child[node->num_child - 1]);
//}
//
//int findSuccessor(struct BTreeNode* node) {
//	int successor;
//	if (node->leaf) {
//		return node->key[0];
//	}
//	return findSuccessor(node->child[0]);
//}
//
//int inorderPredecessor(struct BTreeNode* node, int pos) {
//	int predecessor = findPredecessor(node->child[pos]);
//	node->key[pos] = predecessor;
//	return predecessor;
//}
//
//int inorderSuccessor(struct BTreeNode* node, int pos) {
//	int successor = findSuccessor(node->child[pos + 1]);
//	node->key[pos] = successor;
//	return successor;
//}
//
//int inorderMerge(struct BTreeNode* node, int pos) {
//	int target = node->child[pos]->num_key;					// ��ĥ ��ġ�� ������ idx
//	int send = node->key[pos];
//	node->child[pos]->key[target] = node->key[pos];			// ���� child�� ������ �� �ٿ��ֱ�
//	node->child[pos]->num_key++;
//
//	for (int i = 0; i < node->child[pos + 1]->num_key; i++) {   // ������ child�� Ű ���ʿ� �ٿ��ֱ�
//		node->child[pos]->key[target + 1 + i] = node->child[pos + 1]->key[i];
//		node->child[pos]->num_key++;
//	}
//	for (int i = 0; i < node->child[pos + 1]->num_child; i++) { // ������ child�� child ���ʿ� �ٿ��ֱ�
//		node->child[pos]->child[target + 1 + i] = node->child[pos + 1]->child[i];
//		node->child[pos]->num_child++;
//	}
//
//	for (int i = pos; i < node->num_key; i++) {				// �� ��� Ű�� ����
//		node->key[i] = node->key[i + 1];
//		node->num_key--;
//	}
//	for (int i = pos + 1; i < node->num_child; i++) {			// �� ��� child�� ����
//		node->child[i] = node->child[i + 1];
//		node->num_child--;
//	}
//	return send;
//}
//
//void deleteInnerTree(struct BTreeNode* node, int pos) { // TO DO:: �ڽ��� �������� ��� �Ǵ°��� ? 
//	int result_deletion = 0; // TO DO:: CHECK
//	if (node->child[pos]->num_key >= node->child[pos + 1]->num_key) { // ���� �ڽ��� Ű ������ ũ�ų� ������
//		if (node->child[pos]->num_key > Num_Minimum_Keys) {
//			result_deletion = inorderPredecessor(node, pos);
//			deleteValFromNode(result_deletion, node->child[pos]);
//
//		}
//		else {
//			result_deletion = inorderMerge(node, pos);
//			deleteValFromNode(result_deletion, node->child[pos]);
//		}
//	}
//	else {															  // ������ �ڽ��� Ű ������ Ŭ ��
//		if (node->child[pos + 1]->num_key > Num_Minimum_Keys) {
//			result_deletion = inorderSuccessor(node, pos);
//			deleteValFromNode(result_deletion, node->child[pos + 1]);
//		}
//		else {
//			result_deletion = inorderMerge(node, pos);
//			deleteValFromNode(result_deletion, node->child[pos]);
//		}
//	}
//}
//
//void borrowFromLeft(struct BTreeNode* node, int pos) {
//	int target = 0;													 // ������ ��ġ�� ������ idx
//	for (int i = 0; i < node->child[pos]->num_key; i++) {
//		node->child[pos]->key[i + 1] = node->child[pos]->key[i];
//	}
//	node->child[pos]->key[target] = node->key[pos - 1];				 // �� ���� ���ش�.
//	node->child[pos]->num_key++;
//
//	int borrow = node->child[pos - 1]->num_key - 1;						 // ������ ��ġ�� idx
//	node->key[pos - 1] = node->child[pos - 1]->key[borrow];			 // �� ���� ä���.
//
//	node->child[pos - 1]->num_key--;								 // ������ ���� Ű������ �����.
//
//
//	if (node->child[pos - 1]->num_child > 0) {						 // ������ ���� child�� �ִٸ�
//		borrow = node->child[pos - 1]->num_child - 1;			     // ������ ���� child�� �Ѱ��ش�.
//		for (int i = node->child[pos]->num_child; i > 0; i--) {
//			node->child[pos]->child[i] = node->child[pos]->child[i - 1];
//		}
//		node->child[pos]->child[0] = node->child[pos - 1]->child[borrow];
//		node->child[pos]->num_child++;
//
//		node->child[pos - 1]->num_child--;							 // ������ ���� child ����
//	}
//}
//
//void borrowFromRight(struct BTreeNode* node, int pos) {
//	int target = node->child[pos]->num_key;							 // ������ ��ġ�� ������ idx
//	node->child[pos]->key[target] = node->key[pos];				     // �� ���� ���ش�.
//	node->child[pos]->num_key++;
//
//	int borrow = 0;												     // ������ ��ġ�� idx(�ǿ���)
//	node->key[pos] = node->child[pos + 1]->key[borrow];				 // �� ���� ä���.
//
//	for (int i = 0; i < node->child[pos + 1]->num_key - 1; i++) {	 // ������ ���� Ű ����
//		node->child[pos + 1]->key[i] = node->child[pos + 1]->key[i + 1];
//	}
//	node->child[pos + 1]->num_key--;
//
//	if (node->child[pos + 1]->num_child > 0) {
//		target = node->child[pos]->num_child;							 // ������ ���� child�� �Ѱ��ش�.
//		node->child[pos]->child[target] = node->child[pos + 1]->child[borrow];
//		node->child[pos]->num_child++;
//
//		for (int i = 0; i < node->child[pos + 1]->num_child - 1; i++) {	 // ������ ���� child ����
//			node->child[pos + 1]->child[i] = node->child[pos + 1]->child[i + 1];
//		}
//		node->child[pos + 1]->num_child--;
//	}
//}
//
//void mergeNode(struct BTreeNode* node, int pos, int pos_left) {		// ��� Ű�� poe_left ���� �����ش�. TODO:: �� ������ ���ؿ��� �������� ���ư��°�?
//	int target = node->child[pos_left]->num_key;					// ���� �ڽĿ� �� idx
//
//	node->child[pos_left]->key[target] = node->key[pos_left];		// �� ��尪�� �־��ش�.
//	node->child[pos_left]->num_key++;
//
//	for (int i = 0; i < node->child[pos]->num_key; i++) {			// �������ڽ��� Ű�� ���� �ڽĿ� �־��ش�.
//		node->child[pos_left]->key[target + 1 + i] = node->child[pos]->key[i];
//		node->child[pos_left]->num_key++;
//	}
//
//	target = node->child[pos_left]->num_child;
//	for (int i = 0; i < node->child[pos]->num_child; i++) {			// �������ڽ��� Ű�� ���� �ڽĿ� �־��ش�.
//		node->child[pos_left]->child[target + i] = node->child[pos]->child[i];
//		node->child[pos_left]->num_child++;
//	}
//
//	free(node->child[pos]);											// ������ �ڽ��� free ��Ų��.
//
//	for (int i = pos_left; i < node->num_key - 1; i++) {			// �� ����� key ���� 
//		node->key[i] = node->key[i + 1];
//	}
//	node->num_key--;
//
//	for (int i = pos; i < node->num_child - 1; i++) {				// �� ����� child ���� 
//		node->child[i] = node->child[i + 1];
//	}
//	node->num_child--;
//}
//
//
//void adjustNode(struct BTreeNode* node, int pos) {
//	if (pos == 0) {											// child �� ���� ���϶�, ������ ���������� ������ �� �ִ�.
//		if (node->child[pos + 1]->num_key > Num_Minimum_Keys) {
//			borrowFromRight(node, pos);
//		}
//		else {
//			mergeNode(node, pos + 1, pos);
//		}
//		return;
//	}
//	else {
//		if (pos == node->num_key) {										// child �� ������ ���϶�, ���� ���������� ������ �� �ִ�.
//			if (node->child[pos - 1]->num_key > Num_Minimum_Keys) {
//				borrowFromLeft(node, pos);
//			}
//			else {
//				mergeNode(node, pos, pos - 1);
//			}
//			return;
//		}
//		else {												// �� �� ��Ȳ������, ���ʿ��� ������ �� �ִ�.
//			if (node->child[pos - 1]->num_key > Num_Minimum_Keys) {
//				borrowFromLeft(node, pos);
//			}
//			else if (node->child[pos + 1]->num_key > Num_Minimum_Keys) {
//				borrowFromRight(node, pos);
//			}
//			else {
//				mergeNode(node, pos, pos - 1);
//			}
//			return;
//		}
//
//	}
//}
//
//int deleteValFromNode(int val, struct BTreeNode* node) {
//	int pos;
//	int flag = false;
//	for (pos = 0; pos < node->num_key; pos++) {				// �� ��忡�� val, Ȥ�� �� ��ġ�� ã�´�.
//		if (val == node->key[pos]) {
//			flag = true;
//			break;
//		}
//		else if (val < node->key[pos]) {
//			break;
//		}
//	}
//	if (flag) {
//		if (node->leaf) {									// case#1 leaf���� ������ ��
//			for (int i = pos; i < node->num_key; i++) {
//				node->key[i] = node->key[i + 1];
//			}
//			node->num_key--;
//		}
//		else {
//			deleteInnerTree(node, pos);
//		}
//		return flag;
//	}
//	else {
//		if (node->leaf) {
//			return flag;
//		}
//		else {
//			flag = deleteValFromNode(val, node->child[pos]);
//
//		}
//	}
//	if (node->child[pos]->num_key < Num_Minimum_Keys) {    // ��ͷ� ������ �� �����ߴ� �ڽ��� ������ ���ڸ� �� 
//		adjustNode(node, pos);
//	}
//
//	return flag;
//}
//
//void delete(struct BTreeNode* node, int val) {
//	if (!node) { 											// empty tree!
//		printf("Empty tree!!\n");
//		return;
//	}
//	int flag = deleteValFromNode(val, node);
//	if (!flag) { 											// ���� �� ��尡 ���� ��
//		printf("%d no exist in the tree!!\n", val);
//		return;
//	}
//	if (node->num_key == 0) {								// case#3 ������ ��ȭ�� ������
//		node = node->child[0];
//	}
//	root = node;
//
//}
//
///*PRINT******************************************************************************************************/
//void printTree(struct BTreeNode* node, int level) {			 // BƮ�� �׸���
//	if (!node) { 											 // empty tree!
//		printf("Empty tree!!\n");
//		return;
//	}
//	printf("Level %d :   ", level);
//	for (int i = 0; i < level - 1; i++) {
//		printf("            ");
//	}
//	for (int i = 0; i < node->num_key; i++) {
//		printf("%d ", node->key[i]);
//	}
//	printf("\n");
//	level++;
//	for (int i = 0; i < node->num_child; i++) {
//		printTree(node->child[i], level);
//	}
//}
//
/////*MAIN******************************************************************************************************/
//int main(void) {
//	printf("%d\n", Num_Minimum_Keys);
//	insert(10);
//	insert(20);
//	insert(30);
//	insert(40);
//	insert(50);
//	insert(60);
//	insert(70);
//	insert(80);
//	insert(90);
//	insert(100);
//	insert(110);
//	insert(120);
//	insert(130);
//	insert(140);
//	insert(150);
//	insert(160);
//	insert(170);
//	insert(180);
//	insert(190);
//	insert(200);
//	insert(210);
//	insert(220);
//	insert(230);
//	insert(240);
//	insert(250);
//	insert(260);
//
//	insert(9);
//	insert(39);
//	insert(101);
//	insert(102);
//	insert(103);
//	insert(104);
//	insert(161);
//	insert(191);
//	insert(251);
//
//
//	delete(root, 103);
//	printTree(root, 1);
//	printf("****************************************************\n");
//	delete(root, 70);
//
//	//delete(root, 130);
//	//delete(root, 104);
//	//delete(root, 60);
//	//delete(root, 120);
//	//delete(root, 240);
//	//delete(root, 160);
//
//
//
//
//	printTree(root, 1);
//
//	//searchNode(root,30);
//
//
//	return 0;
//}