// name - the name of the item that is searched for
// tree - a reference to the tree control
// hRoot - the handle to the item where the search begins
HTREEITEM FindItem(const CString& name, CTreeCtrl& tree, HTREEITEM hRoot)
{
	// check whether the current item is the searched one
	CString text = tree.GetItemText(hRoot);
	if (text.Compare(name) == 0)
		return hRoot;

	// get a handle to the first child item
	HTREEITEM hSub = tree.GetChildItem(hRoot);
	// iterate as long a new item is found
	while (hSub)
	{
		// check the children of the current item
		HTREEITEM hFound = FindItem(name, tree, hSub);
		if (hFound)
			return hFound;

		// get the next sibling of the current item
		hSub = tree.GetNextSiblingItem(hSub);
	}

	// return NULL if nothing was found
	return NULL;
}
[Update]
To search the entire tree you can use this helper function, which will work regardless how many roots the tree has.

HTREEITEM CTreeDemoDlg::FindItem(const CString& name, CTreeCtrl& tree)
{
	HTREEITEM root = m_tree.GetRootItem();
	while (root != NULL)
	{
		HTREEITEM hFound = FindItem(name, tree, root);
		if (hFound)
			return hFound;

		root = tree.GetNextSiblingItem(root);
	}

	return NULL;
}


// algorithm to build accounts tree
// 1. Put in the root and save its handle hroot
// 2. Init atl1.....atl6 account names as null and handles hatl1.....hatl6 as null
//    Init catl1..........catl6 current account names as null
// 3. Read atl1........atl6.
// call buildtree(
// level1	If atl1 is null      all levels done, return
//			If atl1 != catl, new level1, so insert in hroot and save hatl1 and catl1
//			goto level2
//
// level2   If atl2 is null      all level 2 done, so reset catl2 to null
//			If atl2 != cat2, new level2, so insert in hatl1 and save hatl2 and catl2
//			goto level3
//
// level3   If atl3 is null      all level 3 done, so reset catl3 to null
//			If atl3 != cat3, new level3, so insert in hatl2 and save hatl3 and catl3
//			goto level4
//
// level4   If atl4 is null      all level 4 done, so reset catl4 to null
//			If atl4 != cat4, new level4, so insert in hatl3 and save hatl4 and catl4
//			goto level5
//
// level5   If atl5 is null      all level 5 done, so reset catl5 to null
//			If atl5 != cat5, new level5, so insert in hatl4 and save hatl5 and catl5
//			goto level6
//
// level6   If atl6 is null      all level 6 done, so reset catl6 to null
//			If atl6 != cat6, new level6, so insert in hatl5 and save hatl6 and catl6
//			put out error message "too many levels" and return
