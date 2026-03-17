void inserir_v(int item, Node** tree){
	if(*tree == NULL)
		*tree = criar(item);
	else if(item < (*tree)->item)
		inserir_v(item, &(*tree)->left);
	else if (item > (*tree)->item)
		inserir_v(item, &(*tree)->right);
}